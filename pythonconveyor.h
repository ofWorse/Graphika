#ifndef PYTHONCONVEYOR_H
#define PYTHONCONVEYOR_H
#include <Python.h>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>

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

    std::vector<double> x;
    std::vector<double> y;

public:
    PythonConveyor( const std::string& folderPath, const std::string& moduleName, const std::string& functionName );
    ~PythonConveyor();

    void setDataX( const std::vector<double>& x )
    {
        this->x = x;
    }

    void setDataY( const std::vector<double>& y )
    {
        this->y = y;
    }

    void setFolderPath( const std::string& folderPath );
    void setModuleName( const std::string& moduleName );
    void setFunctionName( const std::string& functionName );
    std::string getResult( void );

    void initialize( void );

    std::vector<std::string> convertDoubleToString( const std::vector<double>& input )
    {
        std::vector<std::string> output;

        for ( const auto& value : input )
        {
            std::ostringstream stream;
            stream << value;
            output.push_back( stream.str() );
        }

        return output;
    }

    void clear( void );
    void sendArraysToPythonFunction(  );
    void checkArraysSizes( const std::vector< std::string >& array1, const std::vector< std::string >& array2 );
};

#endif // PYTHONCONVEYOR_H
