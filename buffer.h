#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QVector>
#include <iostream>

class SpecialBuffer : public QObject
{
    Q_OBJECT
public:
    SpecialBuffer( void );
    QVector<double> x;
    QVector<double> y;

    void print()
    {
        for( auto& a : x )
        {
            std::cout << a << " ";
        }
        std::cout << std::endl;

        for( auto& a : y )
        {
            std::cout << a << " ";
        }
        std::cout << std::endl;
    }
};

#endif // BUFFER_H
