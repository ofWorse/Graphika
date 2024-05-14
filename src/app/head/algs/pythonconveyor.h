#ifndef PYTHONCONVEYOR_H
#define PYTHONCONVEYOR_H

#include <Python.h>
#include <QObject>
#include <QString>
#include <vector>

class PythonConveyor : public QObject
{
    Q_OBJECT

public:
    explicit PythonConveyor( QObject* parent = nullptr );
    PythonConveyor( const QString& pythonFilePath, const QString& functionName, QObject* parent = nullptr );

    QStringList convertVectorToStringList( const std::vector< double >& inputVector );
    QString convertVectorToQString( const QVector<double>& vector );
    QVector<double> convertPyObjectToQVector( PyObject* pyList );

    void sendArraysToPythonFunction();

    QString getResourceFilePath( const QString& resourcePath );

    void sendDataToDifferentiation();
    void sendDataToIntegration();
    void sendDataToSolveSys();

    void initPythonInterpreter();

    PyObject* getPythonFunction(const QString& functionName);
    PyObject* callPythonFunction( PyObject* function, PyObject* args );
    PyObject* buildPyListFromQStringList( const QStringList &stringList );
    PyObject* buildPyListFromStdVector( const std::vector< double >& vector );

    template<typename T>
    void setData(T PythonConveyor::* member, const T& value) {
        this->*member = value;
    }

    template<typename T>
    T getData(T PythonConveyor::* member) const {
        return this->*member;
    }

private:
    QString pythonFilePath;
    QString functionName;
    QString resultString;
    QString functionToDiff;
    QString functionToIntegration;

    double startNumToIntegration;
    double endNumToIntegration;
    double startNumToDiff;
    double endNumToDiff;
    double resultValue;

    std::vector< double > xVector;
    std::vector< double > yVector;
    std::vector< double > numVector;

    PyObject* module;
    PyObject* globals;
    PyObject* resultPyObj;

    QVector<double> result_Vector;
    QVector<double> resultDiff_XVector;
    QVector<double> resultDiff_YVector;
    QVector<double> resultSys_Vector;

    QVector<QVector<double>> sys;

    bool isResourcePath( const QString& path );
};

#endif // PYTHONCONVEYOR_H
