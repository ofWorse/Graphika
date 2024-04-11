#include "rightwidget.h"
#include <qstring.h>
#include <filesystem>

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

void RightWidget::printGraph( SpecialBuffer& buffer, Sender& sender )
{
    x = buffer.x;
    y = buffer.y;

    graphBuilder->wGraphic->replot();
    // TODO: исправить заглушку
    graphBuilder->PaintG( x, y, sender.functionName == nullptr ? "График заданной функции" : sender.functionName );

    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );
}

void RightWidget::printGraph( QVector<double>& x, QVector<double>& y, Sender& sender )
{
    graphBuilder->wGraphic->replot();
    // TODO: исправить заглушку
    graphBuilder->PaintG( x, y, "График производной функции" );

}


void RightWidget::printDiffGraph( SpecialBuffer &buffer, Sender &sender, const QString& expression )
{
    //Временный код для тестирования differentiationSolve
    x = buffer.x;

    graphBuilder->wGraphic->replot();

    differentiationSolve( expression, x, sender );
}

void RightWidget::buildPolynome( SpecialBuffer &buffer, Sender &sender )
{
    x = buffer.x;
    y = buffer.y;
    graphBuilder->wGraphic->replot();
    interpolationSolve( x.toStdVector(), y.toStdVector(), sender );
    QString str = QString::fromUtf8( resultModel.c_str() );
    model->setText( str );
    emit readyToSendData( model->text(), x[0], x.back() );
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

void RightWidget::integrationSolve(const QString &expression, const double &a, const double &b, Sender &sender)
{
    conveyor->setFunctionName(sender.functionName);
    conveyor->setPythonFilePath(sender.moduleName);

    conveyor->setFunctionToIntegration(expression);
    conveyor->setStartNumToIntegration(a);
    conveyor->setEndNumToIntegration(b);

    conveyor->sendDataToIntegration();
    resultModel = conveyor->getResult().toStdString();
}

void RightWidget::differentiationSolve(const QString& expression, const QVector<double>& x, Sender& sender)
{
    conveyor->setFunctionName(sender.functionName);
    conveyor->setPythonFilePath(sender.moduleName);

    conveyor->setFunctionToDiff(expression);
    conveyor->setDataNums(x.toStdVector());

    conveyor->sendDataToDifferentiation();
    QVector<double> resultX = QVector<double>::fromStdVector(conveyor->get_Nums_Vector());
    QVector<double> resultY = conveyor->getResultVector();
    printGraph(resultX, resultY, sender);
}

void RightWidget::clearGraph( void )
{
    graphBuilder->on_clearButton_clicked();
}

void RightWidget::drawGraph( const std::vector<double> x, const std::vector<double> y )
{
    QVector<double> X = QVector<double>::fromStdVector( x );
    QVector<double> Y = QVector<double>::fromStdVector( y );
    graphBuilder->PaintG( X, Y, "График интерполяции" );
}
