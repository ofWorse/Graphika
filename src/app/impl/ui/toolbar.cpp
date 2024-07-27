#include "toolbar.h"
#include <QIcon>

Toolbar::Toolbar( QWidget* parent ) : QToolBar( parent )
{
    QPixmap lagrange( ":/toolbaricons/resources/lagrange.PNG" );
    QPixmap scaledlagrange = lagrange.scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation );
    QPixmap newthon( ":/toolbaricons/resources/newthon.PNG" );
    QPixmap scaledNewthon = newthon.scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation );
    QPixmap beirut( ":/toolbaricons/resources/beirut.PNG" );
    QPixmap scaledBeirut = beirut.scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation );

    QActionGroup* plotGroup = new QActionGroup( this );
    plotFunctionAction = addAction( QIcon( ":/toolbaricons/resources/function.PNG" ), "Построить график функции f(x)" );
    plotFunctionAction->setCheckable( true );
    plotGroup->addAction( plotFunctionAction );

    diffAction = addAction( QIcon( ":/toolbaricons/resources/derivation.PNG" ), "Построить график функции f'(x)" );
    integralAction = addAction( QIcon( ":/toolbaricons/resources/integral.PNG" ), "Найти площадь трапеции" );
    sysAction = addAction( QIcon( ":/toolbaricons/resources/sysfunctions.PNG" ), "Решить систему линейных/нелинейных уравнений" );

    plotGroup->addAction( diffAction );
    plotGroup->addAction( integralAction );
    plotGroup->addAction( sysAction );

    addSeparator();
    lagrangeAction = addAction( QIcon( QPixmap( ":/toolbaricons/resources/lagrange.PNG" )
                        .scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation ) ),
                        "Построить модель полинома Лагранжа" );
    newthonAction = addAction( QIcon( QPixmap( ":/toolbaricons/resources/newthon.PNG" )
                        .scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation ) ),
                        "Построить модель полинома Ньютона" );
    beirutAction = addAction( QIcon( QPixmap( ":/toolbaricons/resources/beirut.PNG" )
                        .scaled( 32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation ) ),
                        "Построить модель полинома Беррута" );
    plotGroup->addAction( lagrangeAction );
    plotGroup->addAction( newthonAction );
    plotGroup->addAction( beirutAction );

    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/clearPlot.PNG" ), "Очистить график" );
    addAction( QIcon( ":/toolbaricons/resources/home.PNG" ), "Вернуть график" );
    addAction( QIcon( ":/toolbaricons/resources/rotateLegend.PNG" ), "Переместить легенду" );
    addAction( QIcon( ":/toolbaricons/resources/showLegend.PNG" ), "Показать/скрыть легенду" );
    addAction( QIcon( ":/toolbaricons/resources/back.PNG" ), "Шаг назад" );
    addAction( QIcon( ":/toolbaricons/resources/forward.PNG" ), "Шаг вперед" );
    addAction( QIcon( ":/toolbaricons/resources/decreasePlot.PNG" ), "Увеличить график" );
    addAction( QIcon( ":/toolbaricons/resources/increasePlot.PNG" ), "Уменьшить график" );
    addAction( QIcon( ":/toolbaricons/resources/unpinPlot.PNG" ), "Отделить график от окна" );
    addAction( QIcon( ":/toolbaricons/resources/savePlotAsImage.png" ), "Сохранить состояние графика" );

    setCheckable();
    initDiffMenu();
    initIntegralMenu();
    initSysMenu();
    initPolynomeMenu();

    connect(diffAction, &QAction::triggered, this, &Toolbar::handleDiffActionTriggered);
    connect(integralAction, &QAction::triggered, this, &Toolbar::handleIntegralActionTriggered);
}

void Toolbar::handleDiffActionTriggered()
{
    if ( methodTwoDots->isChecked() )
    {
        emit currentMethodChanged( "Дифференцирование по 2 точкам" );
    }
    else if ( methodThreeDots->isChecked() )
    {
        emit currentMethodChanged( "Дифференцирование по 3 точкам" );
    }
    else if ( methodFiveDots->isChecked() )
    {
        emit currentMethodChanged( "Дифференцирование по 5 точкам" );
    }
}

void Toolbar::handleIntegralActionTriggered()
{
    if ( linearMethod->isChecked() )
    {
        emit currentMethodChanged( "Линейный метод" );
    }
    else if ( trapezoidMethod->isChecked() )
    {
        emit currentMethodChanged( "Метод трапеций" );
    }
    else if ( parabolicMethod->isChecked() )
    {
        emit currentMethodChanged( "Метод Симпсона (парабол)" );
    }
}

void Toolbar::mousePressEvent( QMouseEvent* event )
{
    if ( event->button() == Qt::RightButton ) {
        QAction *action = actionAt( event->pos() );
        if ( action == diffAction )
        {
            diffMenu->popup( event->globalPos() );
        }
        if( action == integralAction )
        {
            integralMenu->popup( event->globalPos() );
        }
        if( action == sysAction )
        {
            sysMenu->popup( event->globalPos() );
        }
    }
    else
    {
        QToolBar::mousePressEvent( event );
    }
}

void Toolbar::initDiffMenu( void )
{
    diffMenu = new QMenu( this );

    methodTwoDots = diffMenu->addAction( "Дифференцировать по 2 точкам" );
    methodThreeDots = diffMenu->addAction( "Дифференцировать по 3 точкам" );
    methodFiveDots = diffMenu->addAction( "Дифференцировать по 5 точкам" );

    methodTwoDots->setCheckable( true );
    methodThreeDots->setCheckable( true );
    methodFiveDots->setCheckable( true );

    methodThreeDots->setChecked( true );

    connect( methodTwoDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState( methodTwoDots );
        emit currentMethodChanged( "Дифференцирование по 2 точкам" );
    } );
    connect( methodThreeDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState( methodThreeDots );
        emit currentMethodChanged( "Дифференцирование по 3 точкам" );
    } );
    connect(methodFiveDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState( methodFiveDots );
        emit currentMethodChanged( "Дифференцирование по 5 точкам" );
    } );
}

void Toolbar::initIntegralMenu()
{
    integralMenu = new QMenu( this );

    linearMethod = integralMenu->addAction( "Линейный метод" );
    trapezoidMethod = integralMenu->addAction( "Метод трапеций" );
    parabolicMethod = integralMenu->addAction( "Метод Симпсона (парабол)" );

    linearMethod->setCheckable( true );
    trapezoidMethod->setCheckable( true );
    parabolicMethod->setCheckable( true );

    linearMethod->setChecked( true );

    connect( linearMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState( linearMethod );
        emit currentMethodChanged( "Линейный метод" );
    } );
    connect( trapezoidMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState( trapezoidMethod );
        emit currentMethodChanged( "Метод трапеций" );
    } );
    connect( parabolicMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState( parabolicMethod );
        emit currentMethodChanged( "Метод Симпсона (парабол)" );
    } );
}

void Toolbar::initSysMenu()
{
    sysMenu = new QMenu( this );

    gaussMethod = sysMenu->addAction( "Метод Гаусса" );
    simpleIterMethod = sysMenu->addAction( "Метод простых итераций" );

    gaussMethod->setCheckable( true );
    simpleIterMethod->setCheckable( true );
    simpleIterMethod->setDisabled( true );

    gaussMethod->setChecked( true );

    connect( gaussMethod, &QAction::triggered, this, [=]() {
        updateSysCheckState( gaussMethod );
    });
    connect( simpleIterMethod, &QAction::triggered, this, [=]() {
        updateSysCheckState( simpleIterMethod );
    });
}

void Toolbar::initPolynomeMenu()
{
    connect(lagrangeAction, &QAction::triggered, this, [=]() {
        emit currentMethodChanged("Полином Лагранжа");
    });
    connect(newthonAction, &QAction::triggered, this, [=]() {
        emit currentMethodChanged("Полином Ньютона");
    });
    connect(beirutAction, &QAction::triggered, this, [=]() {
        emit currentMethodChanged("Полином Беррута");
    });
}


void Toolbar::updateDiffCheckState( QAction *checkedAction )
{
    if ( checkedAction->isChecked() )
    {
        if ( checkedAction == methodTwoDots )
        {
            methodThreeDots->setChecked( false );
            methodFiveDots->setChecked( false );
        }
        else if ( checkedAction == methodThreeDots )
        {
            methodTwoDots->setChecked( false );
            methodFiveDots->setChecked( false );
        }
        else if ( checkedAction == methodFiveDots )
        {
            methodTwoDots->setChecked( false );
            methodThreeDots->setChecked( false );
        }
    }
    else
    {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if ( !methodTwoDots->isChecked() && !methodThreeDots->isChecked() && !methodFiveDots->isChecked() )
        {
            methodThreeDots->setChecked( true );
        }
    }
}

void Toolbar::updateIntegralCheckState( QAction *checkedAction )
{
    if ( checkedAction->isChecked() )
    {
        if ( checkedAction == linearMethod )
        {
            trapezoidMethod->setChecked( false );
            parabolicMethod->setChecked( false );
        }
        else if ( checkedAction == trapezoidMethod )
        {
            linearMethod->setChecked( false );
            parabolicMethod->setChecked( false );
        }
        else if ( checkedAction == parabolicMethod )
        {
            linearMethod->setChecked( false );
            trapezoidMethod->setChecked( false );
        }
    }
    else
    {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if ( !linearMethod->isChecked() && !trapezoidMethod->isChecked() && !parabolicMethod->isChecked() )
        {
            linearMethod->setChecked( true );
        }
    }
}

void Toolbar::updateSysCheckState( QAction *checkedAction )
{
    if ( checkedAction->isChecked() )
    {
        if ( checkedAction == gaussMethod )
        {
            simpleIterMethod->setChecked( false );
        }
        else if ( checkedAction == simpleIterMethod )
        {
            gaussMethod->setChecked( false );
        }
    }
    else
    {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if ( !gaussMethod->isChecked() && !simpleIterMethod->isChecked() )
        {
            gaussMethod->setChecked( true );
        }
    }
}

void Toolbar::setCheckable( void )
{
    for( auto i = 0; i < actions().count(); ++i )
    {
        this->actions().at( i )->setCheckable( true );
    }
}

void Toolbar::unsetChecked( void )
{
    for ( auto i = 0; i < actions().count(); ++i )
    {
        if ( actions().at( i )->isChecked() && !isPersistentAction( actions().at( i ) ) )
        {
            actions().at( i )->setChecked( false );
        }
    }
}

bool Toolbar::isPersistentAction( QAction* action ) {
    return action->text() == "Построить график функции f(x)" ||
           action->text() == "Построить график функции f'(x)" ||
           action->text() == "Найти площадь трапеции" ||
           action->text() == "Решить систему линейных/нелинейных уравнений" ||
           action->text() == "Построить модель полинома Лагранжа" ||
           action->text() == "Построить модель полинома Ньютона" ||
           action->text() == "Построить модель полинома Беррута";
}

void Toolbar::connectActions() {
    QList<QAction*> persistentActions;
    for ( auto i = 0; i < actions().count(); ++i )
    {
        QAction* action = actions().at( i );
        if ( isPersistentAction( action ) )
        {
            persistentActions.append( action );
        }
    }

    for ( QAction* action : persistentActions )
    {
        connect( action, &QAction::triggered, this, [ this, action, persistentActions ]() {
            if ( action->isChecked() )
            {
                for ( QAction* otherAction : persistentActions )
                {
                    if ( otherAction != action && otherAction->isChecked() )
                    {
                        otherAction->setChecked( false );
                    }
                }
            }
        });
    }
}

pymodules::Methods Toolbar::getSelectedDiffMethod( void ) const
{
    if ( methodTwoDots->isChecked() )
    {
        return pymodules::Methods::DIFF_2P;
    }
    else if ( methodThreeDots->isChecked() )
    {
        return pymodules::Methods::DIFF_3P;
    }
    else if ( methodFiveDots->isChecked() )
    {
        return pymodules::Methods::DIFF_5P;
    }
    return pymodules::Methods::DIFF_3P;
}

pymodules::Methods Toolbar::getSelectedIntegralMethod( void ) const
{
    if ( linearMethod->isChecked() )
    {
        return pymodules::Methods::INTEG_LINEAR;
    }
    else if ( trapezoidMethod->isChecked() )
    {
        return pymodules::Methods::INTEG_TRAP;
    }
    else if ( parabolicMethod->isChecked() )
    {
        return pymodules::Methods::INTEG_PARAB;
    }
    return pymodules::Methods::INTEG_LINEAR;
}

pymodules::Methods Toolbar::getSelectedSysMethod( void ) const
{
    if ( gaussMethod->isChecked() )
    {
        return pymodules::Methods::GAUSS;
    }
    else if ( simpleIterMethod->isChecked() )
    {
        return pymodules::Methods::SIMPLE_ITER;
    }
    return pymodules::Methods::GAUSS;
}
