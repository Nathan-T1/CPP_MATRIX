//g++ -c main.cpp
//g++ -shared -o main.dll main.o

#include <iostream>
#include <Python.h>
#include <string.h>


static PyObject* func(PyObject* self)
{
    return Py_BuildValue("s", "Hello from c++");
}

static PyMethodDef module_methods[] = 
{
    {"func", (PyCFunction)func, METH_NOARGS, NULL},
    {NULL}
};


static struct PyModuleDef test_module = 
{
    PyModuleDef_HEAD_INIT,
    "test",                 //Name of python module
    "Docs",                 //Module Docstring
    -1,                     //Memory needed to store program state
    module_methods          //Refereance to method table
};

//Initialization Function
PyMODINIT_FUNC PyInit_test(void)
{
   return PyModule_Create(&test_module);

    //return PyModule_Create(&test_module);
}