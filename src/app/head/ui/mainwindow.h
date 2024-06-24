/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 20.05.2024.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "toolbar.h"
#include "leftwidget.h"
#include "rightwidget.h"
#include "sender.h"
#include "compositestatestack.h"
#include "menu.h"
#include "sheetmenu.h"
#include "reportgenerator.h"

/*!
 * \class
 *
 * \brief The MainWindow class that provides whole main window initialization algorigthms.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Menu* menu; ///< menu at the top of the window.
    QMainWindow* mainWindow; ///< main menu window.
    Toolbar* toolbar; ///< items for window switching.
    QWidget* centralwidget; ///< bottom layer.

    LeftWidget* leftWidget; ///< main left side widgets initializator.
    RightWidget* rightWidget; ///< main right side widgets initializator.
    QGridLayout* scrollLayout; ///< scrolling system.
    QGridLayout* layout; ///< main layout.
    SpecialBuffer buffer; ///< buffer for data transfer.
    CompositeStateStack logStack; ///< stack for PDF reporter logs.
    Sender sender; ///< data sender to right and left widgets.
    ReportGenerator* reportGenerator; ///< creates report in pdf or docx format with user data logs.

    std::vector<double> x; ///< x variables nodes.
    std::vector<double> y; ///< y variables nodes.

    pymodules::Modules widgetState = pymodules::Modules::NIL; ///< determines which window to keep open.
    pymodules::Methods methodOfInterpolation; ///< determines which method of interpolation should be invoked.

    QMap<QAction*, std::function<void()>> menuSlots; ///< collection of slots for switching between widgets.
    QList<QWidget*> widgets; ///< current widgets statement.

    bool isSession{ false }; ///< is session mode is opened.
    bool unpinned{ false }; ///< is graph unpinned from main window.
    bool legendEnabled{ false }; ///< is legend enabled.

public:
    /*!
     * \brief MainWindow: constructor with standard heir argument.
     *
     * \param parent: pointer to the parent object.
     */
    explicit MainWindow( QWidget* parent = nullptr );

private:
    /*!
     * \brief buildSpecificWidget: Determine which widget to build based on the given widget number.
     *
     * \param index: a number of widget to build.
     */
    void buildSpecificWidget( int index );

    /*!
     * \brief printDiffGraph: invokes method from right widget for differentiation plot building.
     */
    void printDiffGraph( void );

    /*!
     * \brief calculateIntegral: invokes method from right widget for area calculation.
     */
    void calculateIntegral( void );

    /*!
     * \brief buildPolynomeGraph: defines the interpolation method and invokes invokePolynomeMethod.
     */
    void buildPolynomeGraph( void );

    /*!
     * \brief invokePolynomeMethod: invokes method from right widget for polynomials plot building with the nodes of interpolation and model-made curve.
     *
     * \param method
     */
    void invokePolynomeMethod( pymodules::Methods method );

public slots:
    /*!
     * \brief openMenu: determines the index of the widget and calls the buildSpecificWidget method to build.
     *
     * \param index: number of toolbar widget.
     * \param module: python module if needed.
     */
    void openMenu( int index, pymodules::Modules module );

    /*!
     * \brief printFunctionGraph: invokes method from right widget for simple graph build.
     */
    void printFunctionGraph( void );

    /*!
     * \brief calculateSys: invokes method from right widget for equations system calculation.
     *
     * \param data: numerous of unknown and free members of equation.
     */
    void calculateSys( QVector<QVector<double>>& data );

    /*!
     * \brief clearGraph: invokes method from right widget for plot cleanup process.
     */
    void clearGraph( void );

    /*!
     * \brief resetZoom: invokes method from right widget and resets zoom on plot.
     */
    void resetZoom( void );

    /*!
     * \brief moveLegend: invokes method from right widget for clockwise legend move.
     */
    void moveLegend( void );

    /*!
     * \brief showLegend: shows legend if it was hidden.
     */
    void showLegend( void );

    /*!
     * \brief stepBack: invokes method from right widget and moves state back.
     */
    void stepBack( void );

    /*!
     * \brief stepForward: invokes method from right widget and moves state forward.
     */
    void stepForward( void );

    /*!
     * \brief zoomIn: increases the plot.
     */
    void zoomIn( void );

    /*!
     * \brief zoomOut: decreases the plot.
     */
    void zoomOut( void );

    /*!
     * \brief savePlotAsImage: calls a method from the right widget to save the graph in image format.
     */
    void savePlotAsImage( void );

    /*!
     * \brief unpinGraph: unpins graph from main window.
     */
    void unpinGraph( void );

    /*!
     * \brief startSession: in development. starts a data logging session for the report.
     */
    void startSession( void );

    /*!
     * \brief endSession: in development. ends a data logging session for the report.
     */
    void endSession( void );

    /*!
     * \brief openAboutMenu: invokes about list menu.
     */
    void openAboutMenu( void );

    /*!
     * \brief openAuthorsMenu: invokes authors list menu.
     */
    void openAuthorsMenu( void );

    /*!
     * \brief openLicenseMenu: invokes text of license menu.
     */
    void openLicenseMenu( void );

    /*!
     * \brief draw: determines which rendering method to call
     */
    void draw( void );

    /*!
     * \brief deleteWidgets: widgets cleanup method.
     */
    void deleteWidgets( void );

    /*!
     * \brief couldSavePlotAsImage: return true if plot is not empty.
     *
     * \param couldSave: save or ignore request.
     */
    void couldSavePlotAsImage( bool couldSave );

signals:
    /*!
     * \brief rebuildWidgets: makes it clear to the left widget that it’s time to change the state.
     *
     * \param buffer: x & y variables.
     * \param module: python module if needed.
     */
    void rebuildWidgets( SpecialBuffer& buffer, pymodules::Modules module );

friend RightWidget;
friend LeftWidget;
};

#endif // MAINWINDOW_H
