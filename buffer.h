#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QVector>

class SpecialBuffer : public QObject
{
    Q_OBJECT
public:
    SpecialBuffer( void );
    QVector<double> x;
    QVector<double> y;
};

#endif // BUFFER_H
