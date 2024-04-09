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
    // Инициализация интерпретатора Python
    Py_Initialize();

    QString absoluteFilePath = isResourcePath( m_pythonFilePath ) ? getResourceFilePath( m_pythonFilePath ) : m_pythonFilePath;

    // Проверка существования файла Python
    QFile file( absoluteFilePath );
    if ( !file.exists() ) {
        qDebug() << "Python file does not exist: " << absoluteFilePath;
        Py_Finalize();
        return;
    }

    // Открытие файла Python
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text ) ) {
        qDebug() << "Failed to open Python file: " << absoluteFilePath;
        Py_Finalize();
        return;
    }

    // Загрузка кода из файла Python
    QByteArray byteArray = file.readAll();
    PyObject* module = PyImport_AddModule( "__main__" );
    PyObject* globals = PyModule_GetDict( module );
    PyObject* result = PyRun_String( byteArray.constData(), Py_file_input, globals, globals );
    if ( !result ) {
        qDebug() << "Failed to execute Python script: " << absoluteFilePath;
        PyErr_Print();
        file.close();
        Py_Finalize();
        return;
    }

    // Закрытие файла Python
    file.close();

    // Получение объекта функции из модуля Python
    PyObject* function = PyObject_GetAttrString( module, m_functionName.toStdString().c_str() );
    if ( !function || !PyCallable_Check( function ) ) {
        qDebug() << "Function" << m_functionName << "is not callable or does not exist";
        Py_DECREF(result);
        Py_Finalize();
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

