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
    : QObject( parent ), m_pythonFilePath( pythonFilePath ), m_functionName( functionName ) {}

void PythonConveyor::setPythonFilePath( const QString& pythonFilePath )
{
    m_pythonFilePath = pythonFilePath;
}

QString PythonConveyor::getPythonFilePath() const
{
    return m_pythonFilePath;
}

void PythonConveyor::setFunctionName( const QString& functionName )
{
    m_functionName = functionName;
}

QString PythonConveyor::getFunctionName() const
{
    return m_functionName;
}

void PythonConveyor::setPrecision( double precision )
{
    m_precision = precision;
}

double PythonConveyor::getPrecision() const
{
    return m_precision;
}

void PythonConveyor::setDataX( const std::vector< double >& vector )
{
    m_xVector = vector;
}

std::vector< double > PythonConveyor::get_X_Vector() const
{
    return m_xVector;
}

void PythonConveyor::setDataY( const std::vector< double >& vector )
{
    m_yVector = vector;
}

std::vector< double > PythonConveyor::get_Y_Vector() const
{
    return m_yVector;
}

void PythonConveyor::setResult( const QString& result )
{
    m_result = result;
}

QString PythonConveyor::getResult() const
{
    return m_result;
}

std::vector< double > PythonConveyor::get_Nums_Vector() const
{
    return m_numVector;
}

void PythonConveyor::setDataNums( const std::vector< double > &vector )
{
    m_numVector = vector;
}

void PythonConveyor::setFunctionToDiff( const QString& expression )
{
    m_functionToDiff = expression;
}

QString PythonConveyor::getFunctionToDiff() const
{
    return m_functionToDiff;
}

void PythonConveyor::setFunctionToIntegration(const QString &expression)
{
    m_functionToIntegration = expression;
}
QString PythonConveyor::getFunctionToIntegration() const
{
    return m_functionToIntegration;
}

void PythonConveyor::setStartNumToIntegration(double startNumToIntegration)
{
    m_startNumToIntegration = startNumToIntegration;
}

double PythonConveyor::getStartNumToIntegration() const
{
    return m_startNumToIntegration;
}

void PythonConveyor::setEndNumToIntegration(double endNumToIntegration)
{
    m_endNumToIntegration = endNumToIntegration;
}

double PythonConveyor::getEndNumToIntegration() const
{
    return m_endNumToIntegration;
}

void PythonConveyor::setStartNumToDiff(double startNumToDiff)
{
    m_startNumToDiff = startNumToDiff;
}

double PythonConveyor::getStartNumToDiff() const
{
    return m_startNumToDiff;
}

void PythonConveyor::setEndNumToDiff(double endNumToDiff)
{
    m_endNumToDiff = endNumToDiff;
}

double PythonConveyor::getEndNumToDiff() const
{
    return m_endNumToDiff;
}

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
    // Проверяем, существует ли ресурсный файл
    if ( !QFile::exists( resourcePath ) ) {
        qDebug() << "Resource file does not exist: " << resourcePath;
        return QString(); // Возвращаем пустую строку в случае ошибки
    }

    // Получаем абсолютный путь к ресурсному файлу
    QString absoluteFilePath = QFileInfo( resourcePath ).absoluteFilePath();

    // Возвращаем абсолютный путь к ресурсному файлу
    return absoluteFilePath;
}

void PythonConveyor::sendArraysToPythonFunction()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(m_functionName);
    if (!function)
    {
        return;
    }

    // Подготовка аргументов для вызова функции Python
    PyObject* args = PyTuple_New( 2 );

    // Преобразование векторов чисел в вектора строк
    QStringList xStringList = convertVectorToStringList(m_xVector);
    QStringList yStringList = convertVectorToStringList(m_yVector);

    // Создание списков Python для значений x и y
    PyObject* xList = PyList_New(xStringList.size());
    PyObject* yList = PyList_New(yStringList.size());

    // Заполнение списков значениями из xStringList и yStringList
    for (int i = 0; i < xStringList.size(); ++i) {
        PyList_SetItem(xList, i, Py_BuildValue("s", xStringList[i].toStdString().c_str()));
    }
    for (int i = 0; i < yStringList.size(); ++i) {
        PyList_SetItem(yList, i, Py_BuildValue("s", yStringList[i].toStdString().c_str()));
    }

    // Установка списков в аргументы кортежа
    PyTuple_SetItem(args, 0, xList);
    PyTuple_SetItem(args, 1, yList);
    //PyTuple_SetItem( args, 2, Py_BuildValue( "f", m_precision ) );

    // Вызов функции Python
    PyObject* pyResult = PyObject_CallObject( function, args );
    if ( !pyResult ) {
        qDebug() << "Failed to call function" << m_functionName;
        PyErr_Print();
    } else {
        // Обработка результата, если это необходимо
        setResult( PyUnicode_AsUTF8( pyResult ) );
        Py_DECREF( pyResult );
    }

    // Освобождение ресурсов
    Py_DECREF( args );
    Py_DECREF( function );
    Py_DECREF( result );

    // Финализация интерпретатора Python
    Py_Finalize();
}

void PythonConveyor::sendDataToIntegration()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(m_functionName);
    if (!function)
    {
        return;
    }

    // Подготовка аргументов для вызова функции Python
    PyObject* args = PyTuple_New( 2 );

    PyObject* xList = PyList_New(m_xVector.size());

    for ( int i = 0; i < m_xVector.size(); ++i )
    {
        PyList_SetItem( xList, i, PyFloat_FromDouble( m_xVector[i] ) );
    }

    PyObject* yList = PyList_New(m_yVector.size());

    for ( int i = 0; i < m_yVector.size(); ++i )
    {
        PyList_SetItem( yList, i, PyFloat_FromDouble( m_yVector[i] ) );
    }

    PyTuple_SetItem( args, 0, xList );

    PyTuple_SetItem( args, 1, yList);

    // Вызов функции Python
    PyObject* pyResult = PyObject_CallObject( function, args );
    if ( !pyResult ) {
        qDebug() << "Failed to call function" << m_functionName;
        PyErr_Print();
    } else {
        // Обработка результата, если это необходимо
        double resultValue = PyFloat_AsDouble(pyResult); // Преобразование результата в число
        setResultValue(resultValue); // Установка результата в поле класса

        // Преобразование результата в строку для вывода в консоль
        QString resultString = QString::number(resultValue);
        qDebug() << "Integration result: " << resultString;
        setResult(resultString);

        Py_DECREF( pyResult );
    }

    // Освобождение ресурсов
    Py_DECREF( args );
    Py_DECREF( function );
    Py_DECREF( result );

    // Финализация интерпретатора Python
    Py_Finalize();
}

void PythonConveyor::sendDataToDifferentiation()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(m_functionName);
    if (!function)
    {
        return;
    }

    // Подготовка аргументов для вызова функции Python
    PyObject* args = PyTuple_New( 2 );

    PyObject* xList = PyList_New(m_xVector.size());

    for ( int i = 0; i < m_xVector.size(); ++i )
    {
        PyList_SetItem( xList, i, PyFloat_FromDouble( m_xVector[i] ) );
    }

    PyObject* yList = PyList_New(m_yVector.size());

    for ( int i = 0; i < m_yVector.size(); ++i )
    {
        PyList_SetItem( yList, i, PyFloat_FromDouble( m_yVector[i] ) );
    }


    PyTuple_SetItem( args, 0, xList );

    PyTuple_SetItem( args, 1, yList);

    // Вызов функции Python
    PyObject* pyResult = PyObject_CallObject( function, args );
    if ( !pyResult ) {
        qDebug() << "Failed to call function" << m_functionName;
        PyErr_Print();
    } else {
        // Преобразование списка в вектор чисел
        if (PyTuple_Check(pyResult) && PyTuple_Size(pyResult) == 2) {
            PyObject* xResult = PyTuple_GetItem(pyResult, 0);
            PyObject* yResult = PyTuple_GetItem(pyResult, 1);

            QVector<double> xResultList;
            QVector<double> yResultList;

            QString xResultString;
            QString yResultString;

            int xSize = PyList_Size(xResult);
            int ySize = PyList_Size(yResult);

            for (int i = 0; i < xSize; ++i) {
                PyObject* xItem = PyList_GetItem(xResult, i);
                double xValue = PyFloat_AsDouble(xItem);
                xResultList.append(xValue);
                xResultString += QString::number(xValue) + " ";
            }

            for (int i = 0; i < ySize; ++i) {
                PyObject* yItem = PyList_GetItem(yResult, i);
                double yValue = PyFloat_AsDouble(yItem);
                yResultList.append(yValue);
                yResultString += QString::number(yValue) + " ";
            }

            qDebug() << "Differentiation result for x: " << xResultString;
            qDebug() << "Differentiation result for y: " << yResultString;

            setResult(xResultString);
            setResultDiff_XVector(xResultList);
            setResultDiff_YVector(yResultList);
            Py_DECREF(xResult);
            Py_DECREF(yResult);

        }
        Py_DECREF(pyResult);
    }

    // Освобождение ресурсов
    Py_DECREF( args );
    Py_DECREF( function );
    Py_DECREF( result );

    // Финализация интерпретатора Python
    Py_Finalize();
}

void PythonConveyor::sendDataToSolveSys()
{
    initPythonInterpreter();

    PyObject* function = getPythonFunction(m_functionName);
    if (!function)
    {
        return;
    }

    PyObject* args = PyTuple_New( 1 );
    PyObject* dataList = PyList_New( m_sys.size() );

    for ( int i = 0; i < m_sys.size(); ++i )
    {
        PyObject* sublist = PyList_New(m_sys[i].size());
        for ( int j = 0; j < m_sys[i].size(); ++j)
        {
            PyList_SetItem( sublist, j, PyFloat_FromDouble( m_sys[i][j] ) );
        }
        PyList_SetItem( dataList, i, sublist );
    }

    PyTuple_SetItem( args, 0, dataList );

    PyObject* pyResult = PyObject_CallObject(function, args);
    if (!pyResult) {
        qDebug() << "Failed to call function" << m_functionName;
        PyErr_Print();
        setResult("Решение не найдено");
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
            qDebug() << "Result of sys using "<< m_functionName << " :" << resultString;
            setResultSysVector(resultList);
            setResult(resultString);
        }
        Py_DECREF(pyResult);
    }

    Py_DECREF(args);
    Py_DECREF(function);

    Py_Finalize();
}

void PythonConveyor::setResultVector(const QVector<double>& resultVector)
{
    m_result_Vector = resultVector;
}

QVector<double> PythonConveyor::getResultVector() const{
    return m_result_Vector;
}

void PythonConveyor::setResultDiff_XVector( const QVector<double>& result_XVector)
{
    m_resultDiff_XVector = result_XVector;
}

QVector<double> PythonConveyor::getResultDiff_XVector() const{
    return m_resultDiff_XVector;
}

void PythonConveyor::setResultDiff_YVector(const QVector<double>& result_YVector)
{
    m_resultDiff_YVector = result_YVector;
}

QVector<double> PythonConveyor::getResultDiff_YVector() const{
    return m_resultDiff_YVector;
}

void PythonConveyor::setResultValue(const double resultValue)
{
    m_resultValue = resultValue;
}

double PythonConveyor::getResultValue() const
{
    return m_resultValue;
}

void PythonConveyor::setSys( QVector<QVector<double> > sys )
{
    m_sys = sys;
}

QVector<QVector<double>> PythonConveyor::getSys() const
{
    return m_sys;
}

void PythonConveyor::setResultSysVector(QVector<double> resultSysVector)
{
    m_resultSys_Vector = resultSysVector;
}

QVector<double> PythonConveyor::getResultSysVector() const
{
    return m_resultSys_Vector;
}

void PythonConveyor::initPythonInterpreter()
{
    Py_Initialize();

    QString absoluteFilePath = isResourcePath( m_pythonFilePath ) ? getResourceFilePath( m_pythonFilePath ) : m_pythonFilePath;

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
    result = PyRun_String( byteArray.constData(), Py_file_input, globals, globals );
    if ( !result ) {
        qDebug() << "Failed to execute Python script: " << absoluteFilePath;
        PyErr_Print();
        file.close();
        Py_Finalize();
        return;
    }

    file.close();
    Py_DECREF(result);
}

PyObject* PythonConveyor::getPythonFunction(const QString &functionName)
{
    PyObject* function = PyObject_GetAttrString(module, functionName.toStdString().c_str());
    if (!function || !PyCallable_Check(function)) {
        qDebug() << "Function" << functionName << "is not callable or does not exist";
        Py_DECREF(result);
        Py_Finalize();
        return nullptr;
    }
    return function;
}
