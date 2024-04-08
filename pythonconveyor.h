#ifndef PYTHONCONVEYOR_H
#define PYTHONCONVEYOR_H


#include <QObject>
#include <QString>
#include <vector>

class PythonConveyor : public QObject
{
    Q_OBJECT

public:
    explicit PythonConveyor( QObject* parent = nullptr );
    PythonConveyor( const QString& pythonFilePath, const QString& functionName, double precision, QObject* parent = nullptr );

    void setPythonFilePath( const QString& pythonFilePath );
    QString getPythonFilePath() const;

    void setFunctionName( const QString& functionName );
    QString getFunctionName() const;

    void setPrecision( double precision );
    double getPrecision() const;

    void setDataX( const std::vector< double >& vector );
    std::vector< double > get_X_Vector() const;

    void setDataY( const std::vector< double >& vector );
    std::vector< double > get_Y_Vector() const;

    void setResult( const QString& result );
    QString getResult() const;

    QStringList convertVectorToStringList( const std::vector< double >& inputVector );

    void sendArraysToPythonFunction();
    QString getResourceFilePath( const QString& resourcePath );

private:
    QString m_pythonFilePath;
    QString m_functionName;
    double m_precision;
    std::vector< double > m_xVector;
    std::vector< double > m_yVector;
    QString m_result;

    bool isResourcePath( const QString& path );
};

#endif // PYTHONCONVEYOR_H
