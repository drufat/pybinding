#ifndef PYBINDCPP_CALLABLE_H
#define PYBINDCPP_CALLABLE_H

#include <Python.h>
#include <string>
#include <sstream>

#include "pybindcpp/ctypes/types.h"

namespace pybindcpp {

template<class F>
struct func_trait;

template<class Ret, class... Args>
struct func_trait<Ret(*)(Args...)> {

  static constexpr size_t size = 1 + sizeof...(Args);

  static auto value() {
    const std::array<std::type_index, size> a = {typeid(Ret), typeid(Args)...};
    return a;
  }

  static auto str() {
    auto sign = value();
    std::stringstream ss;
    for (size_t i = 0; i < size; i++) {
      if (i) { ss << ","; }
      ss << ctype_map.at(sign[i]);
    }
    return ss.str();
  }

  static auto pystr() {
    auto s = str();
    return PyBytes_FromString(s.c_str());
  }

  static auto pyctype() {
    auto sign = value();

    auto ctypes = PyImport_ImportModule("ctypes");
    auto attr = [ctypes](const char *name) {
      return PyObject_GetAttrString(ctypes, name);
    };
    auto tup = PyTuple_New(size);
    for (size_t i = 0; i < size; i++) {
      PyTuple_SetItem(tup, i, attr(ctype_map.at(sign[i])));
    }
    auto CFUNCTYPE = attr("CFUNCTYPE");
    auto rslt = PyObject_Call(CFUNCTYPE, tup, nullptr);

    Py_DecRef(CFUNCTYPE);
    Py_DecRef(ctypes);
    Py_DecRef(tup);

    return rslt;
  }
};

template<class F>
struct callable_trait;

template<class F>
struct callable_trait
    : public callable_trait<decltype(&F::operator())> {
};

template<class F, class Ret, class... Args>
struct callable_trait<Ret(F::*)(Args...) const> {
  static
  PyObject *
  get(F f) {
    Py_RETURN_NONE;
  }
};

template<class Ret, class... Args>
struct callable_trait<Ret(*)(Args...)> {
  static
  PyObject *
  get(REGFUNCTYPE reg, Ret(*func)(Args...)) {
    auto sign = func_trait<decltype(func)>::str();

    auto func_type = func_trait<decltype(func)>::pyctype();
    Py_DecRef(func_type);

    auto o = reg((void *) (func), sign.c_str());
    return o;
  }
};

};

#endif //PYBINDCPP_CALLABLE_H
