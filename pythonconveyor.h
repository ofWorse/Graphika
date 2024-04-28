#ifndef PYTHONCONVEYOR_H
#define PYTHONCONVEYOR_H

#include<Python.h>
#include <QObject>
#include <QString>
#include <vector>

class PythonConveyor : public QObject
{
    Q_OBJECT

public:
    explicit PythonConveyor( QObject* parent = nullptr );
    PythonConveyor( const QString& pythonFilePath, const QString& functionName, QObject* parent = nullptr );

    void setPythonFilePath( const QString& pythonFilePath );
    QString getPythonFilePath() const;

    void setFunctionName( const QString& functionName );
    QString getFunctionName() const;

    void setFunctionToDiff( const QString& expression );
    QString getFunctionToDiff() const;

    void setFunctionToIntegration( const QString& expression );
    QString getFunctionToIntegration() const;

    void setPrecision( double precision );
    double getPrecision() const;

    void setResultVector(const QVector<double>& resultVector);
    QVector<double> getResultVector() const;

    void setResultDiff_XVector(const QVector<double>& result_XVector);
    QVector<double> getResultDiff_XVector() const;

    void setResultDiff_YVector(const QVector<double>& result_YVector);
    QVector<double> getResultDiff_YVector() const;

    void setStartNumToIntegration( double startNumToIntegration );
    double getStartNumToIntegration() const;

    void setEndNumToIntegration( double endNumToIntegration );
    double getEndNumToIntegration() const;

    void setStartNumToDiff( double startNumToDiff );
    double getStartNumToDiff() const;

    void setEndNumToDiff( double endNumToDiff );
    double getEndNumToDiff() const;

    void setDataX( const std::vector< double >& vector );
    std::vector< double > get_X_Vector() const;

    void setDataY( const std::vector< double >& vector );
    std::vector< double > get_Y_Vector() const;

    void setDataNums( const std::vector< double >& vector );
    std::vector< double > get_Nums_Vector() const;

    void setResult( const QString& result );
    QString getResult() const;

    void setResultValue(const double resultValue);
    double getResultValue() const;

    QStringList convertVectorToStringList( const std::vector< double >& inputVector );

    void sendArraysToPythonFunction();
    QString getResourceFilePath( const QString& resourcePath );

    void sendDataToDifferentiation();
    void sendDataToIntegration();
    void sendDataToSolveSys();

    void initPythonInterpreter();
    PyObject* getPythonFunction(const QString& functionName);

    void setSys(QVector<QVector<double>> sys);
    QVector<QVector<double>> getSys() const;

    void setResultSysVector(QVector<double> resultSysVector);
    QVector<double> getResultSysVector() const;

private:
    QString m_pythonFilePath;
    QString m_functionName;
    QString m_result;
    QString m_functionToDiff;
    QString m_functionToIntegration;

    double m_precision;
    double m_startNumToIntegration;
    double m_endNumToIntegration;
    double m_startNumToDiff;
    double m_endNumToDiff;
    double m_resultValue;

    std::vector< double > m_xVector;
    std::vector< double > m_yVector;
    std::vector< double > m_numVector;

    PyObject* module;
    PyObject* globals;
    PyObject* result;

    QVector<double> m_result_Vector;
    QVector<double> m_resultDiff_XVector;
    QVector<double> m_resultDiff_YVector;
    QVector<double> m_resultSys_Vector;

    QVector<QVector<double>> m_sys;

    bool isResourcePath( const QString& path );
};

#endif // PYTHONCONVEYOR_H
