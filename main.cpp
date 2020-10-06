//git add -A
//git commit -m "Changes"
//git push origin master

//https://gist.github.com/dfm/3247796

#include <iostream>
#include <Python.h>
#include <string.h>
#include <numpy/arrayobject.h>
#include <math.h>

void print_array(float  *array, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cout << array[i * M + j];
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

void mat_mul(float  *ret_array, float  *array_a, int N_a, int M_a, float  *array_b, int N_b, int M_b)
{

    //M_a = N_b

    
}


static PyObject* func(PyObject* self, PyObject* args)
{
    PyObject *array_obj_a, *array_obj_b;

    if (!PyArg_ParseTuple(args, "OO", &array_obj_a, &array_obj_b))
    {
        return NULL;
    }

    PyObject *array_a = PyArray_FROM_OTF(array_obj_a, NPY_FLOAT32 , NPY_IN_ARRAY, NPY_ARRAY_C_CONTIGUOUS);
    PyObject *array_b = PyArray_FROM_OTF(array_obj_b, NPY_FLOAT32 , NPY_IN_ARRAY, NPY_ARRAY_C_CONTIGUOUS);

    if (array_a == NULL || array_b == NULL)
    {
        Py_XDECREF(array_a);
        Py_XDECREF(array_b);

        return NULL;
    }

    //Get number of dimensions
    //int dims_a = (int)PyArray_NDIM(array_a);
    //int dims_b = (int)PyArray_NDIM(array_b);

    
    int N_a = (int)PyArray_DIM(array_a, 0);
    int M_a = (int)PyArray_DIM(array_a, 1); 
    int N_b = (int)PyArray_DIM(array_b, 0);
    int M_b = (int)PyArray_DIM(array_b, 1); 
    
    float  *array_pointer_a = (float *)PyArray_DATA(array_a);
    float  *array_pointer_b = (float *)PyArray_DATA(array_b);
    float  *ret_array{new float [N_a * M_b]};
    
    #pragma omp parallel for 
    for(int i = 0; i < N_a; i++)
    {
        for(int k = 0; k < N_a; k++)
        {
            for(int j = 0; j < M_b; j++)
            {
                const int temp1 = i * M_a;
                const int temp2 = k * M_b;
                const int A_index = temp1 + k;
                const int B_index = temp2 + j;

                ret_array[i*M_b+j] += array_pointer_a[A_index] * array_pointer_b[B_index];
            }

        }
    }

    npy_intp dims[2]{N_a, M_b};
    PyObject *pArray = PyArray_SimpleNewFromData(
        2, dims , NPY_FLOAT32 , reinterpret_cast<void*>(ret_array));

    if (!pArray)
        goto fail_np_array;

    
    Py_DecRef(array_a);
    Py_DecRef(array_b);

    return pArray;

fail_np_array:
    delete[] ret_array, array_pointer_a, array_pointer_b;

}

static PyMethodDef module_methods[] = 
{
    {"func", (PyCFunction)func, METH_VARARGS, NULL},
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

    import_array();
    return PyModule_Create(&test_module);

    //return PyModule_Create(&test_module);
}