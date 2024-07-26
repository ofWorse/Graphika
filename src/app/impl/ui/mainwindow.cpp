#include "mainwindow.h"
#include "errorhandler.h"

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent )
{
    signal( SIGSEGV, signalHandler );

    resize( 1100, 720 );
    setMinimumSize( 640, 380 );
    setMaximumSize( QWIDGETSIZE_MAX, QWIDGETSIZE_MAX );
    setWindowTitle( "Graphika" );
    setWindowIcon( QIcon( ":/toolbaricons/resources/logo.png" ) );

    menu = new Menu( this );
    setMenuBar( menu->getMenu() );
    connect( menu, &Menu::sessionStarted, this, &MainWindow::startSession );
    connect( menu, &Menu::sessionStopped, this, &MainWindow::endSession );
    connect( menu, &Menu::licenseMenuOppened, this, &MainWindow::openLicenseMenu );
    connect( menu, &Menu::aboutMenuOppened, this, &MainWindow::openAboutMenu );
    connect( menu, &Menu::authorsMenuOppened, this, &MainWindow::openAuthorsMenu );

    connect( qApp, &QApplication::aboutToQuit, this, &MainWindow::deleteWidgets );

    connect( menu, &Menu::programmatorTriggered, this, &MainWindow::openProgrammerDialog );

    toolbar = new Toolbar( this );
    toolbar->setContextMenuPolicy( Qt::ContextMenuPolicy::PreventContextMenu );
    toolbar->setIconSize( *new QSize( 40, 40 ) );
    addToolBar( Qt::TopToolBarArea, toolbar );

    QScrollArea* scrollArea = new QScrollArea( this );
    QWidget* scrollContentWidget = new QWidget;

    centralwidget = new QWidget( this );
    layout = new QGridLayout( centralwidget );

    leftWidget = new LeftWidget( this );
    leftWidget->initLayout( buffer, pymodules::Modules::NIL );
    toolbar->actions().at( 0 )->setChecked( true );
    connect( leftWidget->currentLayout->widgets->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );

    rightWidget = new RightWidget( this );

    connect( leftWidget, &LeftWidget::switchToGraphBuilder, rightWidget->graphBuilder, &GraphBuilder::switchToGraphBuilder );
    connect( leftWidget, &LeftWidget::switchToGL3DGraphBuilder, rightWidget->graphBuilder, &GraphBuilder::switchToGL3DGraphBuilder );

    centralwidget->setLayout( layout );
    setCentralWidget( centralwidget );
    scrollLayout = new QGridLayout( scrollContentWidget );

    scrollLayout->addWidget( leftWidget, 0, 0 );
    scrollLayout->addWidget( rightWidget, 0, 1 );
    scrollContentWidget->setLayout(scrollLayout);

    scrollArea->setWidget( scrollContentWidget );
    scrollArea->setWidgetResizable( true );

    reportGenerator = new ReportGenerator( this );

    //connect( rightWidget, &RightWidget::sendData, &logStack, &CompositeStateStack::receiveData );
    connect( rightWidget, &RightWidget::readyToSendData, leftWidget->currentLayout, &LayoutInitializer::acceptData );
    connect( rightWidget, &RightWidget::readyToSendArea, leftWidget->currentLayout, &LayoutInitializer::acceptArea );
    connect( leftWidget->currentLayout, &LayoutInitializer::readyToDraw, rightWidget, &RightWidget::drawInterpolationGraph );
    scrollLayout->addWidget( leftWidget, 1, 0 );
    scrollLayout->addWidget( rightWidget, 1, 1 );
    connect( rightWidget, &RightWidget::errorOccured, leftWidget->currentLayout, &LayoutInitializer::handleParserError );
    connect( rightWidget, &RightWidget::readyToSendData, leftWidget->currentLayout, &LayoutInitializer::acceptData );
    connect( rightWidget, &RightWidget::readyToSendArea, leftWidget->currentLayout, &LayoutInitializer::acceptArea );
    connect( leftWidget->currentLayout, &LayoutInitializer::readyToDraw, rightWidget, &RightWidget::drawInterpolationGraph );
    connect( this, &MainWindow::rebuildWidgets, leftWidget, &LeftWidget::initLayout );

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    scrollArea->setWidget( scrollContentWidget );
    layout->addWidget( scrollArea, 0, 0 );

    //connect( toolbar, &Toolbar::buildTwoDimensionalWidget, leftWidget, &LeftWidget::buildTwoDimensionalWidget );
   // connect( toolbar, &Toolbar::buildThreeDimensionalWidget, leftWidget, &LeftWidget::buildThreeDimensionalWidget );

    connect( toolbar->actions().at( 9 ),  &QAction::triggered, this, &MainWindow::clearGraph  );
    connect( toolbar->actions().at( 10 ), &QAction::triggered, this, &MainWindow::resetZoom   );
    connect( toolbar->actions().at( 11 ), &QAction::triggered, this, &MainWindow::moveLegend  );
    connect( toolbar->actions().at( 12 ), &QAction::triggered, this, &MainWindow::showLegend  );
    connect( toolbar->actions().at( 13 ), &QAction::triggered, this, &MainWindow::stepBack    );
    connect( toolbar->actions().at( 14 ), &QAction::triggered, this, &MainWindow::stepForward );
    connect( toolbar->actions().at( 15 ), &QAction::triggered, this, &MainWindow::zoomOut     );
    connect( toolbar->actions().at( 16 ), &QAction::triggered, this, &MainWindow::zoomIn      );
    connect( toolbar->actions().at( 17 ), &QAction::triggered, this, &MainWindow::unpinGraph  );
    connect( toolbar->actions().at( 18 ), &QAction::triggered, this, &MainWindow::savePlotAsImage);
    connect( rightWidget->graphBuilder, &GraphBuilder::couldSavePlotAsImage, this, &MainWindow::couldSavePlotAsImage);

    toolbar->actions().at( 18 )->setEnabled( false );

    menuSlots.insert( toolbar->actions().at( 0 ), [ this ]()
                     { openMenu( 0, pymodules::Modules::NIL ); } );
    menuSlots.insert( toolbar->actions().at( 1 ), [ this ]()
                     { openMenu( 1, pymodules::Modules::DIFFERENTIATION ); } );
    menuSlots.insert( toolbar->actions().at( 2 ), [ this ]()
                     { openMenu( 2, pymodules::Modules::INTEGRATION ); } );
    menuSlots.insert( toolbar->actions().at( 3 ), [ this ]()
                     { openMenu( 3, pymodules::Modules::EQUATIONS ); } );
    menuSlots.insert( toolbar->actions().at( 5 ), [ this ]()
                     { openMenu( 5, pymodules::Modules::POLYNOMIALS ); } );
    menuSlots.insert( toolbar->actions().at( 6 ), [ this ]()
                     { openMenu( 6, pymodules::Modules::POLYNOMIALS ); } );
    menuSlots.insert( toolbar->actions().at( 7 ), [ this ]()
                     { openMenu( 7, pymodules::Modules::POLYNOMIALS ); } );
    for( auto act = menuSlots.constBegin(); act != menuSlots.constEnd(); ++act )
    {
        connect( act.key(), &QAction::triggered, this, act.value() );
    }

    programmer = new ProgrammerDialog( this );
    connect( programmer, &ProgrammerDialog::settingsApplied, leftWidget, &LeftWidget::applyProgrammerSettings );
}

void MainWindow::openMenu( int index, pymodules::Modules module )
{
    toolbar->unsetChecked();
    toolbar->actions().at( index )->setChecked( true );
    widgetState = module;
    buildSpecificWidget( index );
}

void MainWindow::buildSpecificWidget( int index )
{
    switch( index )
    {
    case 0:
        [[fallthrough]];
    case 1:
        [[fallthrough]];
    case 2:
        emit rebuildWidgets( buffer, widgetState );
        connect( leftWidget->currentLayout->widgets->buildGraph, &QPushButton::clicked, this, &MainWindow::draw );
        break;
    case 3:
        emit rebuildWidgets( buffer, widgetState );
        connect( leftWidget->currentLayout, &LayoutInitializer::readyToSendEquationsData, this, &MainWindow::calculateSys );
        connect( rightWidget, &RightWidget::readyToSendSysResult, leftWidget->currentLayout, &LayoutInitializer::setEquationsResult );
        break;
    case 5:
        emit rebuildWidgets( buffer, widgetState );
        methodOfInterpolation = pymodules::Methods::LAGRANGE;
        connect( leftWidget->currentLayout->widgets->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
        break;
    case 6:
        emit rebuildWidgets( buffer, widgetState );
        methodOfInterpolation = pymodules::Methods::NEWTON;
        connect( leftWidget->currentLayout->widgets->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
        break;
    case 7:
        emit rebuildWidgets( buffer, widgetState );
        methodOfInterpolation = pymodules::Methods::BEIRUT;
        connect( leftWidget->currentLayout->widgets->buildGraph, &QPushButton::clicked, this, &MainWindow::buildPolynomeGraph );
        break;
    }
}

void MainWindow::draw( void )
{
    switch( widgetState )
    {
    case pymodules::Modules::NIL:
        printFunctionGraph();
        break;
    case pymodules::Modules::DIFFERENTIATION:
        printDiffGraph();
        break;
    case pymodules::Modules::POLYNOMIALS:
        buildPolynomeGraph();
        break;
    case pymodules::Modules::INTEGRATION:
        calculateIntegral();
        break;
    default:
        break;
    }
}

void MainWindow::deleteWidgets( void )
{
    ReferenceMenu::cleanupWidgets( widgets );
    widgets.clear();
}

void MainWindow::couldSavePlotAsImage( bool couldSave )
{
    toolbar->actions().at( 18 )->setEnabled(couldSave);
}

void MainWindow::buildPolynomeGraph( void )
{
    switch( methodOfInterpolation )
    {
    case pymodules::Methods::LAGRANGE:
        invokePolynomeMethod( pymodules::Methods::LAGRANGE );
        break;
    case pymodules::Methods::NEWTON:
        invokePolynomeMethod( pymodules::Methods::NEWTON );
        break;
    case pymodules::Methods::BEIRUT:
        invokePolynomeMethod( pymodules::Methods::BEIRUT );
        break;
    default:
        break;
    }
}

void MainWindow::printFunctionGraph( void )
{
    if( isSession )
    {
        rightWidget->printGraph( buffer, sender, &logStack );
        return;
    }
    rightWidget->printGraph( buffer, sender, nullptr );
}


void MainWindow::printDiffGraph( void )
{
    pymodules::Methods method = toolbar->getSelectedDiffMethod();
    sender.setMacro( method, pymodules::Modules::DIFFERENTIATION );
    if( isSession )
    {
        rightWidget->printDiffGraph( buffer, sender, &logStack );
        return;
    }
    rightWidget->printDiffGraph( buffer, sender, nullptr );
}

void MainWindow::calculateIntegral( void )
{
    pymodules::Methods method = toolbar->getSelectedIntegralMethod();
    sender.setMacro( method, pymodules::Modules::INTEGRATION );
    if( isSession )
    {
        rightWidget->calculateIntegral( buffer, sender, &logStack );
        return;
    }
    rightWidget->calculateIntegral( buffer, sender, nullptr );
}

void MainWindow::calculateSys( QVector<QVector<double>>& data )
{
    pymodules::Methods method = toolbar->getSelectedSysMethod();
    sender.setMacro( method, pymodules::Modules::EQUATIONS );
    rightWidget->sysSolve( data, sender );
}

void MainWindow::invokePolynomeMethod( pymodules::Methods method )
{
    widgetState = pymodules::Modules::POLYNOMIALS;
    sender.setMacro( method, pymodules::Modules::POLYNOMIALS );
    if( isSession )
    {
        rightWidget->buildPolynome( buffer, sender, &logStack );
        return;
    }
    rightWidget->buildPolynome( buffer, sender, nullptr );
}

void MainWindow::clearGraph( void )
{
    toolbar->unsetChecked();
    rightWidget->clearGraph();
}

void MainWindow::resetZoom( void )
{
    toolbar->unsetChecked();
    rightWidget->graphBuilder->resetZoom();
}

void MainWindow::moveLegend( void )
{
    toolbar->unsetChecked();
    rightWidget->moveLegend();
}

void MainWindow::showLegend( void )
{
    toolbar->unsetChecked();
    if( !legendEnabled )
    {
        toolbar->actions().at( 12 )->setIcon( QIcon( ":/toolbaricons/resources/hideLegend.PNG" ) );
        rightWidget->showLegend();
        legendEnabled = true;
        return;
    }
    toolbar->actions().at( 12 )->setIcon( QIcon( ":/toolbaricons/resources/showLegend.PNG" ) );
    rightWidget->hideLegend();
    legendEnabled = false;
}

void MainWindow::stepBack( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 13 )->setChecked( true );
    rightWidget->stepBack();
    toolbar->actions().at( 13 )->setChecked( false );
}

void MainWindow::stepForward( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 14 )->setChecked( true );
    rightWidget->stepForward();
    toolbar->actions().at( 14 )->setChecked( false );
}

void MainWindow::zoomIn( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 16 )->setChecked( true );
    rightWidget->zoomIn();
    toolbar->actions().at( 16 )->setChecked( false );
}

void MainWindow::zoomOut( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 15 )->setChecked( true );
    rightWidget->zoomOut();
    toolbar->actions().at( 15 )->setChecked( false );
}

void MainWindow::savePlotAsImage( void )
{
    toolbar->unsetChecked();
    rightWidget->savePlotAsImage();
}

void MainWindow::unpinGraph( void )
{
    toolbar->unsetChecked();
    toolbar->actions().at( 17 )->setChecked( true );

    if( unpinned )
    {
        toolbar->actions().at( 17 )->setChecked( false );
        return;
    }
    toolbar->actions().at( 17 )->setEnabled( false );


    QDialog* dialog = new QDialog( this );
    dialog->setWindowFlags( dialog->windowFlags() & ~Qt::WindowSystemMenuHint );
    dialog->setWindowTitle( "Unpinned plot" );
    QVBoxLayout* layout = new QVBoxLayout( dialog );

    layout->addWidget( this->toolbar );
    layout->addWidget( rightWidget->graphBuilder->graph2d );
    dialog->setLayout( layout );

    connect( dialog, &QDialog::finished, this, [=]( int result )
        {
            Q_UNUSED( result );
            rightWidget->rightLayout->addWidget( rightWidget->graphBuilder->graph2d );
            toolbar->actions().at( 17 )->setEnabled( true );
            this->addToolBar( this->toolbar );
            dialog->deleteLater();
            unpinned = false;
        }
    );

    dialog->show();
    unpinned = true;
    toolbar->actions().at( 17 )->setChecked( false );
}

void MainWindow::openAboutMenu( void )
{
    widgets.append( ReferenceMenu::invokeAboutWidget() );
}

void MainWindow::openAuthorsMenu( void )
{
    widgets.append( ReferenceMenu::invokeAuthorsWidget() );
}

void MainWindow::openLicenseMenu( void )
{
    widgets.append( ReferenceMenu::invokeLicenseWidget() );
}

void MainWindow::startSession( void )
{
    isSession = true;
    menu->getEndSessionAction()->setEnabled( true );
    menu->getStartSessionAction()->setEnabled( false );

    reportGenerator->startSession();
}

void MainWindow::endSession( void )
{
    isSession = false;
    menu->getEndSessionAction()->setEnabled( false );
    menu->getStartSessionAction()->setEnabled( true );

    reportGenerator->endSession();
    reportGenerator->generateReport( logStack, ReportGenerator::ReportFormat::PDF, "report" );
}

void MainWindow::openProgrammerDialog()
{
    programmer->setWindowTitle(tr ( "Программатор" ) );
    programmer->resize( 600, 400 );
    programmer->move( 100, 100 );
    programmer->show();
}
