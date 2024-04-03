#ifndef RIGHTLAYOUT_H
#define RIGHTLAYOUT_H

#include <QWidget>
#include "graphbuilder.h"
#include "buffer.h"
#include "pythonconveyor.h"

class RightLayout : public QWidget
{
    Q_OBJECT

private:
    QGridLayout* rightLayout;

    PythonConveyor* conveyor;
    GraphBuilder* graphBuilder;

    QVector<double> x;
    QVector<double> y;

    std::string resultModel;

public:
    explicit RightLayout( SpecialBuffer& buffer, QWidget *parent = nullptr );
    void interpolationSolve( const std::vector<double>& x, const std::vector<double>& y );

    QGridLayout* getLayout( void )
    {
        return rightLayout;
    }
};

#endif // RIGHTLAYOUT_H
