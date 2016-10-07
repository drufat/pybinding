// Copyright (C) 2010-2016 Dzhelil S. Rufat. All Rights Reserved.
#include <Python.h>

#include <pybindcpp/ctypes/module.h>

using namespace pybindcpp;

extern "C"
int set_string(char c, int size, char *buffer) {
  for (int i = 0; i < size; i++) {
    buffer[i] = c;
  }
  return 0;
}

auto id(PyObject *o) {
  return o;
}

int add(int x, int y) {
  return x + y;
}

double add_d(double x, double y) {
  return x + y;
}

int minus(int x, int y) {
  return x - y;
};

void
exec(ExtModule &m) {

//  api.error();
//  throw "Error!";
//  if (PyErr_Occurred()) {
//    PyErr_Clear();
//    throw "Error!";
//  }

  py_function<int(int)>(*m.api, "pybindcpp.bind", "id")(3);

  m.var("one", 1);
  m.var("two", 2.0);
  m.var("greet", "Hello, World!");

  m.varargs("func", [](PyObject *data, PyObject *args) -> PyObject * {
    Py_RETURN_NONE;
  });

  m.fun_type("id_type", id);
  m.fun_type("add_type", add);
  m.fun_type("minus_type", minus);
  m.fun_type("set_string_type", set_string);

  m.fun("id", id);
  m.fun("add", add);
  m.fun("minus", minus);
  m.fun("add_d", add_d);
  m.fun("set_string", set_string);
  m.fun("mul", [](int x, int y) { return x * y; });
}

PYMODULE_INIT(bindctypes, exec)