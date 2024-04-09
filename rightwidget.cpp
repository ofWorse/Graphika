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
    conveyor = new PythonConveyor();
    rightLayout = new QGridLayout( this );
    label = new QLabel( "Полученная модель: ", this );
    model = new QLineEdit( this );
    rightLayout->addWidget( label );
    rightLayout->addWidget( model );
    rightLayout->addWidget( graphBuilder );
}

void RightWidget::printGraph( SpecialBuffer& buffer, Sender& sender)
{
    x = buffer.x;
    y = buffer.y;
    graphBuilder->wGraphic->replot();
    graphBuilder->PaintG( x, y, "Полином Лагранжа" );
    interpolationSolve( x.toStdVector(), y.toStdVector(), sender);

    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );
}

void RightWidget::interpolationSolve( const std::vector<double> &x, const std::vector<double> &y, Sender& sender )
{
    conveyor->setFunctionName(sender.functionName);
    conveyor->setPythonFilePath(sender.moduleName);
    conveyor->setDataX( x );
    conveyor->setDataY( y );

    conveyor->sendArraysToPythonFunction();
    resultModel = conveyor->getResult().toStdString();
}

void RightWidget::clearGraph( void )
{
    graphBuilder->on_clearButton_clicked();
}
