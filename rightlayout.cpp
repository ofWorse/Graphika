#include "rightlayout.h"
#include <qstring.h>
#include <filesystem>

RightLayout::RightLayout( SpecialBuffer& buffer, QWidget *parent )
    : QWidget{ parent }
{  
    graphBuilder = new GraphBuilder( this );
    conveyor = new PythonConveyor( "./", "polynomials", "lagrange_polynomial" );
    rightLayout = new QGridLayout( this );

    graphBuilder->PaintG( buffer.x, buffer.y, "Полином лагранжа" );
    interpolationSolve( buffer.x.toStdVector(), buffer.y.toStdVector() );

    QLabel* label = new QLabel( "Полученная модель: ", this );
    QString str = QString::fromUtf8( resultModel.c_str() );
    QLineEdit* model = new QLineEdit( this );
    model->insert( str );

    rightLayout->addWidget( graphBuilder );
    rightLayout->addWidget( label );
    rightLayout->addWidget( model );
}

void RightLayout::interpolationSolve( const std::vector<double> &x, const std::vector<double> &y )
{
    conveyor->setDataX( x );
    conveyor->setDataY( y );

    conveyor->initialize();
    conveyor->sendArraysToPythonFunction();
    resultModel = conveyor->getResult();

    std::cout << resultModel << std::endl;
}
