/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef LEFTWIDGET_H
#define LEFTWIDGET_H

#include <QWidget>
#include "functionlayout.h"
#include "derivationlayout.h"
#include "integrationlayout.h"
#include "equationslayout.h"
#include "polynomialslayout.h"
#include "rightwidget.h"
#include "validatestring.h"
#include "stringparser.h"
#include "datamodel.h"
#include "buffer.h"
#include "mathutils.h"
#include "settings.h"
#include <QDoubleSpinBox>
#include <QDebug>

/*!
 * \class LeftWidget
 *
 * \brief The LeftWidget class, the main link for managing the state of widgets on the left side of the window.
 */
class LeftWidget : public QWidget
{
    Q_OBJECT
private:
    FunctionLayout* functionLayout; ///< contains all widgets for function module need.
    DerivationLayout* derivationLayout; ///< contains all widgets for derivation module need.
    IntegrationLayout* integrationLayout; ///< contains all widgets for integration module need.
    EquationsLayout* equationsLayout; ///< contains all widgets for equations module need.
    PolynomialsLayout* polynomialsLayout; ///< contains all widgets for polynomials module need.

    DataModel* dataModel; // ???

    Widgets* widgets; ///< a class that stores all widgets for editing members of the LeftWidget class, descendants of LayoutInitializer.
    QGridLayout* layout; ///< main left-widget layout.

public:
    LayoutInitializer* currentLayout; ///< layout that contains up-to-date information about the state of widgets.

private:
    // ???
    void clearLayout( QGridLayout* layout );

    /*!
     * \brief hideAllWidgets: goes through the list of widgets and makes them invisible.
     *
     * \param layout: object with widgets container.
     */
    void hideAllWidgets( QLayout* layout );

    /*!
     * \brief connectLabels: method to connect all slots and signals of members of this class.
     *
     * \param buffer: x & y data buffer to transfer.
     */
    void connectLabels( SpecialBuffer& buffer );

public:
    /*!
     * \brief LeftWidget:base constructor.
     *
     * \param buffer: x & y data buffer to transfer.
     * \param parent: pointer to the parent object.
     */
    explicit LeftWidget( SpecialBuffer& buffer, QWidget* parent = nullptr );

public slots:
    /*!
     * \brief initLayout: method for initializing and saving the state of a layout to a class named layout.
     *
     * \param buffer: x & y data buffer to transfer.
     * \param module: specific module for layout generation.
     */
    void initLayout( SpecialBuffer& buffer, pymodules::Modules module );

    //???
    void saveData( pymodules::Modules module );

    //???
    void restoreData(pymodules::Modules module );



/*
public:
    void showTable( const std::vector<double> x, const std::vector<double> y, const std::vector<double> dY );
    QLineEdit* getExpressionInput() const;
    void setEqResult( const QString& eqResult );

   // std::vector<double> getX( void ) { return X; }
   // std::vector<double> getY( void ) { return Y; }

private:
*/
    //void initLabels( void );
    /*
  void connectLabels( SpecialBuffer& buffer );
    void setRange( void );

    void setupNodes( const double node );

    std::vector<double> fillDataFromTable( int column );
    bool tableIsEmpty( void );

    void initLayout( void );
    void buildWidgetForDerivativeOperations( SpecialBuffer& buffer );
    void buildWidgetForIntegrationOperations( SpecialBuffer& buffer );
    void buildWidgetForEquationOperations( SpecialBuffer& buffer );
    void setWidgetToDefaultStatement( SpecialBuffer& buffer );
    void hideAll( void );
    void deleteAll( void );

public slots:
    void onValidateStringValid( void );
    void onValidateStringInvalid( void );

    void handleParserError( const QString& err );

    void onInputTextChanged( const QString& text );

    void onSolveButtonClicked( SpecialBuffer& buffer );
    void onSolveEquationButtonClicked( void );

    void clearDataTable( void );
    void handleClearGraph( RightWidget& right );

    void hideFirstLayer( bool isDerivativeMenu );
    void hideSecondLayer( bool isDerivativeMenu );

    void buildGraphFromManualFilledTable( void );

    void changeLayer( int index );
    void switchLayers( int index, bool isDerivativeMenu );

    void editTable( void );
    void updateDataFromTable( SpecialBuffer& buffer );

    void acceptData( const QString& expr, const double a, const double b );
    void acceptArea( std::string& area );

    void rebuildWidgets( pymodules::Modules modules, SpecialBuffer& buffer );

signals:
    // TODO: паттерны
    void readyToDraw( const std::vector<double> x, const std::vector<double> y );
    void readyToDrawFunctionGraph( std::vector<double>& x, std::vector<double>& y );
    void readyToDrawApproximatedGraph( const std::vector<double> x, const std::vector<double> y );
    void readyToDrawDerivativeGraph( const std::vector<double> x, const std::vector<double> y );
    void sendData( QObject& data, bool toRemove );
    void readyToSendLinearEquationsData( QVector<QVector<double>>& data );
*/
};

#endif // LEFTWIDGET_H
