#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include "graphbuilder.h"
#include "buffer.h"
#include "pythonconveyor.h"
#include "sender.h"
#include "settings.h"

class RightWidget : public QWidget
{
    Q_OBJECT

public:
    QGridLayout* rightLayout;

    PythonConveyor* conveyor;
    GraphBuilder* graphBuilder;

    QVector<double> x;
    QVector<double> y;

private:
    std::string resultModel;
    QLineEdit* model;
    QLabel* label;

private:
    void clearLayout( QLayout *layout );

public:
    explicit RightWidget( QWidget *parent = nullptr );
    void printGraph( SpecialBuffer& buffer, Sender& sender );
    void buildPolynome( SpecialBuffer& buffer, Sender& sender );
    void interpolationSolve( const std::vector<double>& x, const std::vector<double>& y, Sender& sender);
    void clearGraph( void );

public slots:
    void drawGraph( const std::vector<double> x, const std::vector<double> y );

signals:
    void errorOccured( const QString& err );
    void readyToSendData( const QString& expr, const double a, const double b );
};

#endif // RIGHTWIDGET_H
