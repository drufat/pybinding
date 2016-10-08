#ifndef PYBINDCPP_CPYTHONTYPES_H
#define PYBINDCPP_CPYTHONTYPES_H

#include <Python.h>
#include <map>
#include <typeindex>
#include <string>

namespace pybindcpp {

const std::map<std::type_index, std::string> BuildValueTypes = {

    {typeid(char *), "s"},
    {typeid(const char *), "s"},
    {typeid(char), "b"},
    {typeid(double), "d"},
    {typeid(float), "f"},
    {typeid(int), "i"},
    {typeid(unsigned int), "I"},
    {typeid(long), "l"},
    {typeid(unsigned long), "k"},
    {typeid(PyObject *), "N"},

};

const std::map<std::type_index, std::string> ArgParseTypes = {

    {typeid(const char *), "s"},
    {typeid(unsigned char), "b"},
    {typeid(double), "d"},
    {typeid(float), "f"},
    {typeid(int), "i"},
    {typeid(unsigned int), "I"},
    {typeid(long), "l"},
    {typeid(unsigned long), "k"},
    {typeid(PyObject *), "O"},

};

template<class T>
auto convert(const T &t) {
  return t;
}

template<>
auto convert<bool>(const bool &value) {
  auto o = value ? Py_True : Py_False;
  Py_INCREF(o);
  return o;
}

template<>
auto convert<std::string>(const std::string &value) {
  return PyUnicode_FromString(value.c_str());
}

template<>
auto convert<double>(const double &value) {
  return PyFloat_FromDouble(value);
}

template<class... Args>
auto build_value_imp(Args... args) {
  auto format = stringer(BuildValueTypes.at(typeid(Args))...);
  return Py_BuildValue(format.c_str(), args...);
}

template<class... Args>
auto build_value(Args... args) {
  return build_value_imp(convert(args)...);
}

template<class... Args>
auto arg_parse_tuple(PyObject *obj, Args &... args) {
  auto format = stringer(ArgParseTypes.at(typeid(Args))...);
  return PyArg_ParseTuple(obj, format.c_str(), &args...);
}

using VarArg = std::function<PyObject *(PyObject *, PyObject *)>;

}

#endif //PYBINDCPP_CPYTHONTYPES_H
