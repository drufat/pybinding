#ifndef PYBINDCPP_API_H
#define PYBINDCPP_API_H

#include <Python.h>

namespace pybindcpp {

static struct API {
  PyObject *(*get_type)(const char *);
  void *(*get_capsule)(const char *, const char *);
  void *(*get_cfunction)(const char *, const char *);
  PyObject *(*get_pyfunction)(const char *, const char *, PyObject *);
  void *(*get_addr)(PyObject *);
  PyObject* (*register_)(void *, PyObject *);
} api;

static void import_pybindcpp() {

  auto mod = PyImport_ImportModule("pybindcpp.api");
  if (!mod) throw;

  auto init_addr = PyObject_GetAttrString(mod, "init_addr");
  if (!init_addr) throw;

  void *ptr = PyLong_AsVoidPtr(init_addr);
  auto init = *static_cast<void (**)(API *)>(ptr);

  init(&api);

  Py_DecRef(init_addr);
  Py_DecRef(mod);

}

}
#endif //PYBINDCPP_API_H