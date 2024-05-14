#include "pythonconveyor.h"
#include <Python.h>
#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QResource>
#include <QTemporaryFile>
#include <QDir>
#include <QTemporaryDir>
#include <QFileDialog>

PythonConveyor::PythonConveyor( QObject* parent ) : QObject( parent ) {}

PythonConveyor::PythonConveyor( const QString& pythonFilePath, const QString& functionName, QObject* parent )
    : QObject( parent ), pythonFilePath( pythonFilePath ), functionName( functionName ) {}

QStringList PythonConveyor::convertVectorToStringList( const std::vector< double >& inputVector )
{
    QStringList stringList;
    for ( double value : inputVector )
    {
        stringList.append( QString::number( value ) );
    }
    return stringList;
}

bool PythonConveyor::isResourcePath( const QString& path )
{
    return path.startsWith( ":/" );
}

QString PythonConveyor::getResourceFilePath( const QString& resourcePath )
{
    if ( !QFile::exists( resourcePath ) ) {
        qDebug() << "Resource file does not exist: " << resourcePath;
        return QString();
    }

    QString absoluteFilePath = QFileInfo( resourcePath ).absoluteFilePath();

    return absoluteFilePath;
}

PyObject* PythonConveyor::callPythonFunction(PyObject* function, PyObject* args)
{
    PyObject* result = PyObject_CallObject(function, args);
    if (!result) {
        qDebug() << "Failed to call function" << functionName;
        PyErr_Print();
    }
    return result;
}

PyObject* PythonConveyor::buildPyListFromQStringList(const QStringList &stringList)
{
    PyObject* pyList = PyList_New(stringList.size());
    for (int i = 0; i < stringList.size(); ++i) {
        PyList_SetItem(pyList, i, Py_BuildValue("s", stringList[i].toStdString().c_str()));
    }
    return pyList;
}

PyObject* PythonConveyor::buildPyListFromStdVector(const std::vector< double >& vector)
{
    PyObject* pyList = PyList_New(vector.size());
    for (int i = 0; i < vector.size(); ++i) {
        PyList_SetItem(pyList, i, PyFloat_FromDouble(vector[i]));
    }
    return pyList;
}

QVector<double> PythonConveyor::convertPyObjectToQVector(PyObject* pyList)
{
    QVector<double> result;
    int size = PyList_Size(pyList);
    for (int i = 0; i < size; ++i) {
        PyObject* item = PyList_GetItem(pyList, i);
        double value = PyFloat_AsDouble(item);
        result.append(value);
    }
    return result;
}

QString PythonConveyor::convertVectorToQString(const QVector<double>& vector)
{
    QString result;
    for (double value : vector) {
        result += QString::number(value) + " ";
    }
    return result;
}

void PythonConveyor::sendArraysToPythonFunction()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(functionName);
    if (!function)
    {
        return;
    }

    PyObject* args = PyTuple_New(2);

    QStringList xStringList = convertVectorToStringList(xVector);
    QStringList yStringList = convertVectorToStringList(yVector);

    PyObject* xList = buildPyListFromQStringList(xStringList);
    PyObject* yList = buildPyListFromQStringList(yStringList);

    PyTuple_SetItem(args, 0, xList);
    PyTuple_SetItem(args, 1, yList);

    PyObject* pyResult = callPythonFunction(function, args);
    if (pyResult) {
        QString resultString = PyUnicode_AsUTF8(pyResult);
        setData(&PythonConveyor::resultString, resultString);
        Py_DECREF(pyResult);
    }

    Py_DECREF(args);
    Py_DECREF(function);
    Py_DECREF(resultPyObj);

    Py_Finalize();
}

void PythonConveyor::sendDataToIntegration()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(functionName);
    if (!function)
    {
        return;
    }

    PyObject* args = PyTuple_New( 2 );

    PyObject* xList = buildPyListFromStdVector( xVector );
    PyObject* yList = buildPyListFromStdVector( yVector );

    PyTuple_SetItem( args, 0, xList );
    PyTuple_SetItem( args, 1, yList);

    PyObject* pyResult = callPythonFunction( function, args );
    if ( pyResult ) {
        double resultValue = PyFloat_AsDouble(pyResult);
        setData( &PythonConveyor::resultValue, resultValue );

        QString resultString = QString::number(resultValue);
        qDebug() << "Integration result: " << resultString;
        setData( &PythonConveyor::resultString, resultString );

        Py_DECREF( pyResult );
    }

    Py_DECREF( args );
    Py_DECREF( function );
    Py_DECREF( resultPyObj );

    Py_Finalize();
}

void PythonConveyor::sendDataToDifferentiation()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(functionName);
    if (!function)
    {
        return;
    }

    PyObject* args = PyTuple_New( 2 );

    PyObject* xList = buildPyListFromStdVector( xVector );
    PyObject* yList = buildPyListFromStdVector( yVector );

    PyTuple_SetItem( args, 0, xList );
    PyTuple_SetItem( args, 1, yList);

    PyObject* pyResult = callPythonFunction( function, args );
    if ( pyResult ) {
        if (PyTuple_Check(pyResult) && PyTuple_Size(pyResult) == 2) {
            PyObject* xResult = PyTuple_GetItem(pyResult, 0);
            PyObject* yResult = PyTuple_GetItem(pyResult, 1);

            QVector<double> xResultList = convertPyObjectToQVector( xResult );
            QVector<double> yResultList = convertPyObjectToQVector( yResult );

            QString xResultString = convertVectorToQString( xResultList );
            QString yResultString = convertVectorToQString( yResultList );

            qDebug() << "Differentiation result for x: " << xResultString;
            qDebug() << "Differentiation result for y: " << yResultString;

            setData( &PythonConveyor::resultString, xResultString );
            setData( &PythonConveyor::resultDiff_XVector, xResultList );
            setData( &PythonConveyor::resultDiff_YVector, yResultList );

            Py_DECREF(xResult);
            Py_DECREF(yResult);

        }
        Py_DECREF(pyResult);
    }

    Py_DECREF( args );
    Py_DECREF( function );
    Py_DECREF( resultPyObj );

    Py_Finalize();
}

void PythonConveyor::sendDataToSolveSys()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(functionName);
    if (!function)
    {
        return;
    }

    PyObject* args = PyTuple_New( 1 );
    PyObject* dataList = PyList_New( sys.size() );

    for ( int i = 0; i < sys.size(); ++i )
    {
        PyObject* sublist = PyList_New(sys[i].size());
        for ( int j = 0; j < sys[i].size(); ++j)
        {
            PyList_SetItem( sublist, j, PyFloat_FromDouble( sys[i][j] ) );
        }
        PyList_SetItem( dataList, i, sublist );
    }

    PyTuple_SetItem( args, 0, dataList );

    PyObject* pyResult = PyObject_CallObject(function, args);
    if (!pyResult) {
        qDebug() << "Failed to call function" << functionName;
        PyErr_Print();
        resultString = "Решение не найдено";
    }
    else
    {
        if (PyList_Check( pyResult ) )
        {
            QVector<double> resultList;
            QString resultString;

            int size = PyList_Size( pyResult );

            for (int i = 0; i < size; ++i)
            {
                PyObject* item = PyList_GetItem( pyResult, i);
                double value = PyFloat_AsDouble( item );
                resultList.append( value );
                resultString += QString::number( value ) + " ";
            }
            qDebug() << "Result of sys using "<< functionName << " :" << resultString;
            setData( &PythonConveyor::resultSys_Vector, resultList );
            setData( &PythonConveyor::resultString, resultString );
        }
        Py_DECREF(pyResult);
    }

    Py_DECREF(args);
    Py_DECREF(function);

    Py_Finalize();
}

void PythonConveyor::initPythonInterpreter()
{
    Py_Initialize();

    QString absoluteFilePath = isResourcePath( pythonFilePath ) ? getResourceFilePath( pythonFilePath ) : pythonFilePath;

    QFile file( absoluteFilePath );
    if ( !file.exists() ) {
        qDebug() << "Python file does not exist: " << absoluteFilePath;
        Py_Finalize();
        return;
    }

    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        qDebug() << "Failed to open Python file: " << absoluteFilePath;
        Py_Finalize();
        return;
    }

    QByteArray byteArray = file.readAll();
    module = PyImport_AddModule( "__main__" );
    globals = PyModule_GetDict( module );
    resultPyObj = PyRun_String( byteArray.constData(), Py_file_input, globals, globals );
    if ( !resultPyObj ) {
        qDebug() << "Failed to execute Python script: " << absoluteFilePath;
        PyErr_Print();
        file.close();
        Py_Finalize();
        return;
    }

    file.close();
    Py_DECREF(resultPyObj);
}

PyObject* PythonConveyor::getPythonFunction(const QString &functionName)
{
    PyObject* function = PyObject_GetAttrString(module, functionName.toStdString().c_str());
    if (!function || !PyCallable_Check(function)) {
        qDebug() << "Function" << functionName << "is not callable or does not exist";
        Py_DECREF(resultPyObj);
        Py_Finalize();
        return nullptr;
    }
    return function;
}
