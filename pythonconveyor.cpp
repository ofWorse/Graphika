#include "pythonconveyor.h"
#include <Python.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

PythonConveyor::PythonConveyor( const std::string& folderPath, const std::string& moduleName, const std::string& functionName )
    : pName( nullptr ), pModule( nullptr ), pDict( nullptr ), pObjct( nullptr ), pVal( nullptr ), sys( nullptr ), sys_path( nullptr ), folder_path( nullptr ),
    m_folderPath( folderPath ), m_moduleName( moduleName ), m_functionName( functionName ) {}

PythonConveyor::~PythonConveyor()
{
    clear();
}

void PythonConveyor::setFolderPath( const std::string& folderPath )
{
    m_folderPath = folderPath;
}

void PythonConveyor::setModuleName( const std::string& moduleName )
{
    m_moduleName = moduleName;
}

void PythonConveyor::setFunctionName( const std::string& functionName )
{
    m_functionName = functionName;
}

std::string PythonConveyor::getResult()
{
    return m_result;
}

void PythonConveyor::initialize()
{
    Py_Initialize();

    do {
        sys = PyImport_ImportModule( "sys" );
        sys_path = PyObject_GetAttrString( sys, "path" );

        folder_path = PyUnicode_FromString( m_folderPath.c_str() );
        PyList_Append( sys_path, folder_path );

        pName = PyUnicode_FromString( m_moduleName.c_str() );
        if ( !pName )
        {
            break;
        }

        pModule = PyImport_Import( pName );
        if ( !pModule )
        {
            break;
        }

        pDict = PyModule_GetDict( pModule );
        if ( !pDict )
        {
            break;
        }
    } while( 0 );

    if ( PyErr_Occurred() )
    {
        PyErr_Print();
    }
}

void PythonConveyor::clear()
{
    Py_XDECREF( pDict );
    Py_XDECREF( pModule );
    Py_XDECREF( pName );
    Py_XDECREF( folder_path );
    Py_XDECREF( sys_path );
    Py_XDECREF( sys );

    Py_Finalize();
}

void PythonConveyor::checkArraysSizes( const std::vector< std::string >& array1, const std::vector< std::string >& array2 )
{
    if ( array1.size() != array2.size() )
    {
        throw std::invalid_argument( "Arrays sizes must be equal." );
    }
}

void PythonConveyor::sendArraysToPythonFunction( const std::vector< std::string >& array1, const std::vector< std::string >& array2 )
{
    checkArraysSizes( array1, array2 );

    pObjct = PyDict_GetItemString( pDict, m_functionName.c_str() );
    if ( !pObjct )
    {
        std::cerr << "Function " << m_functionName << " not found in Python module" << std::endl;
        return;
    }

    do {
        if ( !PyCallable_Check(pObjct) )
        {
            std::cerr << "Object " << m_functionName << " is not callable" << std::endl;
            break;
        }

        PyObject* pList1 = PyList_New( array1.size() );
        for ( size_t i = 0; i < array1.size(); ++i )
        {
            PyList_SetItem( pList1, i, PyUnicode_FromString( array1[i].c_str() ) );
        }

        PyObject* pList2 = PyList_New( array2.size() );
        for ( size_t i = 0; i < array2.size(); ++i )
        {
            PyList_SetItem( pList2, i, PyUnicode_FromString( array2[i].c_str() ) );
        }

        pVal = PyObject_CallFunction( pObjct, "OO", pList1, pList2 );
        if ( pVal != nullptr )
        {
            PyObject* pResultRepr = PyObject_Repr( pVal );
            m_result = PyBytes_AsString( PyUnicode_AsEncodedString( pResultRepr, "utf-8", "ERROR" ) );
            std::cout << "Function " << m_functionName << " result: " << m_result << std::endl;
            Py_XDECREF( pResultRepr );
            Py_XDECREF( pVal );
        }
        else
        {
            PyErr_Print();
        }

        Py_XDECREF( pList1 );
        Py_XDECREF( pList2 );
    } while( 0 );
}
