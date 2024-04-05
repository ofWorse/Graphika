#include "rightwidget.h"
#include <qstring.h>
#include <filesystem>

void RightWidget::clearLayout(QLayout *layout)
{
    if ( layout == NULL )
    {
        return;
    }
    QLayoutItem *item;
    while( ( item = layout->takeAt( 0 ) ) )
    {
        if ( item->layout() )
        {
            clearLayout( item->layout() );
            delete item->layout();
        }
        if ( item->widget() )
        {
            delete item->widget();
        }
        delete item;
    }
}

RightWidget::RightWidget( QWidget *parent )
    : QWidget{ parent }
{
    graphBuilder = new GraphBuilder( this );
    conveyor = new PythonConveyor( "./", "polynomials", "lagrange_polynomial" );
    rightLayout = new QGridLayout( this );
    label = new QLabel( "Полученная модель: ", this );
    model = new QLineEdit( this );
    rightLayout->addWidget( label );
    rightLayout->addWidget( model );
    rightLayout->addWidget( graphBuilder );
}

void RightWidget::printGraph( SpecialBuffer& buffer )
{
    x = buffer.x;
    y = buffer.y;
    graphBuilder->wGraphic->replot();
    graphBuilder->PaintG( x, y, "Полином Лагранжа" );
    interpolationSolve( x.toStdVector(), y.toStdVector() );

    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );
}

void RightWidget::interpolationSolve( const std::vector<double> &x, const std::vector<double> &y )
{
    conveyor->setDataX( x );
    conveyor->setDataY( y );

    conveyor->initialize();
    conveyor->sendArraysToPythonFunction();
    resultModel = conveyor->getResult();
}

void RightWidget::clearGraph( void )
{
    graphBuilder->on_clearButton_clicked();
}
