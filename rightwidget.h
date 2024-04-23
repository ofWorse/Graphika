#ifndef RIGHTWIDGET_H
#define RIGHTWIDGET_H

#include <QWidget>
#include <QVector>
#include "graphbuilder.h"
#include "buffer.h"
#include "pythonconveyor.h"
#include "sender.h"
#include "compositestatestack.h"
#include "settings.h"

struct TablePair
{
    double x;
    double y;
};

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
    void buildWidgetForDerivativeOperations( void );

public:
    explicit RightWidget( QWidget *parent = nullptr );
    void printGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack );
    void printGraph( QVector<double>& x, QVector<double>& y, Sender& sender, const CompositeStateStack* stack );
    void printDiffGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack );

    void buildPolynome( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack  );
    void interpolationSolve( const std::vector<double>& x, const std::vector<double>& y, Sender& sender );

    void differentiationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender );
    void integrationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender );

    void clearGraph( void );

public slots:
    void drawGraph( const std::vector<double> x, const std::vector<double> y );
    void rebuildWidgets( pymodules::Modules modules );

signals:
    void errorOccured( const QString& err );
    void readyToSendData( const QString& expr, const double a, const double b );
    void sendData( QObject& data, bool toRemove );
};

#endif // RIGHTWIDGET_H
