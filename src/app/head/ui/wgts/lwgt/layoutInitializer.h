#ifndef LAYOUTINITIALIZER_H
#define LAYOUTINITIALIZER_H

#include <QGridLayout>
#include <buffer.h>
#include "widgets.h"
#include "mathutils.h"

class LayoutInitializer : public QWidget
{
    Q_OBJECT
private:
    bool couldBuildTable{ true };
    bool manualInput{ false };
    bool derivativeLabel{ false };
    bool polynomialsLabel{ false };

public:
    Widgets* widgets;

public:
    virtual ~LayoutInitializer( void ) {}
    virtual void generateWidgets( Widgets& widgets ) = 0;
    virtual QGridLayout* get( void ) = 0;
    virtual void saveData( void ) = 0;
    virtual void loadData( void ) = 0;

    template<typename... widgets>
    void hideWidgets( widgets*... w )
    {
        ( ... , ( std::is_base_of_v<QWidget, std::decay_t<Widgets>> ? static_cast<void>( w->hide() ) : void() ) );
    }
    void onInputTextChanged( const QString &text );
    void onValidateDataValid( void );
    void onValidateDataInvalid( void );

    void editTable( void );
    void buildGraphFromManualFilledTable( void );
    void clearDataTable( void );
    void changeLayer( int index );

    void hideFirstLayer();
    void hideSecondLayer();

    void onSolveButtonClicked( SpecialBuffer& buffer );
    void updateDataFromTable( SpecialBuffer& buffer );
    void setupNodes( const double node );
    std::vector<double> fillDataFromTable( int column );
    void showTable( const std::vector<double> x, const std::vector<double> y, const std::vector<double> dY );

public slots:
    void handleParserError( const QString &err );
    void acceptData( const QString& model, const double a, const double b );
    void onSolveEquationsButtonClicked( void );
    void setEquationsResult( const QString &result );
    void acceptArea( const std::string& area );

signals:
    void validExpression( void );
    void invalidExpression( void );
    void readyToDraw( std::vector<double>& x, std::vector<double>& y );
    void readyToSendEquationsData( QVector<QVector<double>>& data );
};

#endif
