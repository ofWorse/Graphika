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
    std::string area;
    QLineEdit* model;
    QLabel* label;

private:
    void clearLayout( QLayout *layout );
    void buildWidgetForDerivativeOperations( void );

public:
    explicit RightWidget( QWidget *parent = nullptr );
    void printGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack );
    void printDiffGraph( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack );

    void calculateIntegral( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack );

    void buildPolynome( SpecialBuffer& buffer, Sender& sender, const CompositeStateStack* stack  );
    void interpolationSolve( const std::vector<double>& x, const std::vector<double>& y, Sender& sender );

    void differentiationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender );
    void integrationSolve( const QVector<double>& x, const QVector<double>& y, Sender& sender );
    void sysSolve( QVector<QVector<double>>& data, Sender& sender );

    void clearGraph( void );
    void moveLegend( void );
    void showLegend( void );
    void hideLegend( void );
    void stepBack( void );
    void stepForward( void );
    void zoomIn();
    void zoomOut();

public slots:
    void drawInterpolationGraph( const std::vector<double> x, const std::vector<double> y );
    void rebuildWidgets( pymodules::Modules modules );
    void solveLinearEquations( QVector<QVector<double>>& data );
    void printDerivationGraph( const QVector<double>& x, const QVector<double>& y, Sender& sender, const CompositeStateStack* stack );
    void printFunctionGraph( std::vector<double>& x, std::vector<double>& y );

signals:
    void errorOccured( const QString& err );
    void readyToSendData( const QString& expr, const double a, const double b );
    void sendData( QObject& data, bool toRemove );
    void readyToSendArea( std::string& area );
    void readyToSendSysResult( const QString &result );
};

#endif // RIGHTWIDGET_H
