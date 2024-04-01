#ifndef PYTHONCONVEYOR_H
#define PYTHONCONVEYOR_H
#include <Python.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

class PythonConveyor
{
private:
    PyObject* pName;
    PyObject* pModule;
    PyObject* pDict;
    PyObject* pObjct;
    PyObject* pVal;
    PyObject* sys;
    PyObject* sys_path;
    PyObject* folder_path;

    std::string m_folderPath;
    std::string m_moduleName;
    std::string m_functionName;
    std::string m_result;

public:
    PythonConveyor( const std::string& folderPath, const std::string& moduleName, const std::string& functionName );
    ~PythonConveyor();

    void setFolderPath( const std::string& folderPath );
    void setModuleName( const std::string& moduleName );
    void setFunctionName( const std::string& functionName );
    std::string getResult();

    void initialize();
    void clear();
    void sendArraysToPythonFunction( const std::vector< std::string >& array1, const std::vector< std::string >& array2 );
    void checkArraysSizes( const std::vector< std::string >& array1, const std::vector< std::string >& array2 );
};

#endif // PYTHONCONVEYOR_H
