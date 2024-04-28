#include "toolbar.h"
#include <QIcon>

Toolbar::Toolbar( QWidget *parent ) : QToolBar(parent)
{
    addAction( QIcon( ":/toolbaricons/resources/function.PNG" ), "Построить график функции f(x)" );
    diffAction = addAction( QIcon(":/toolbaricons/resources/diff.PNG"), "Построить график функции f'(x)" );
    integralAction = addAction( QIcon( ":/toolbaricons/resources/int.PNG" ), "Найти площадь трапеции" );
    sysAction = addAction( "sys" );
    addSeparator();
    addAction( QIcon(":/toolbaricons/resources/lagrange.PNG"), "Построить модель полинома Лагранжа");
    addAction( QIcon(":/toolbaricons/resources/newthon.PNG"), "Построить модель полинома Ньютона");
    addAction( QIcon(":/toolbaricons/resources/berruta.PNG"), "Построить модель полинома Берута");
    addSeparator();
    addAction( QIcon(":/toolbaricons/resources/clearPlot.PNG"), "Очистить график");
    addAction( QIcon(":/toolbaricons/resources/home.PNG"), "Вернуть график");
    addAction( "GLeg" );
    addAction( "SLeg" );
    addAction( QIcon(":/toolbaricons/resources/back.PNG"), "Шаг назад" );
    addAction( QIcon(":/toolbaricons/resources/forward.PNG"), "Шаг вперед" );
    addAction( QIcon(":/toolbaricons/resources/decreasePlot.PNG"), "Увеличить график" );
    addAction( QIcon(":/toolbaricons/resources/increasePlot.PNG"), "Уменьшить график" );
    addAction( QIcon(":/toolbaricons/resources/unpinPlot.PNG"), "Отделить график от окна" );

    setCheckable();
    initDiffMenu();
    initIntegralMenu();
    initSysMenu();
}

void Toolbar::mousePressEvent( QMouseEvent *event )
{
    if (event->button() == Qt::RightButton) {
        QAction *action = actionAt(event->pos());
        if (action == diffAction)
        {
            diffMenu->popup(event->globalPos());
        }
        if( action == integralAction )
        {
            integralMenu->popup( event->globalPos() );
        }
        if( action == sysAction )
        {
            sysMenu->popup( event->globalPos() );
        }
    } else {
        QToolBar::mousePressEvent(event);
    }
}

void Toolbar::initDiffMenu( void )
{
    diffMenu = new QMenu(this);

    methodTwoDots = diffMenu->addAction("Дифференцировать по 2 точкам");
    methodThreeDots = diffMenu->addAction("Дифференцировать по 3 точкам");
    methodFiveDots = diffMenu->addAction("Дифференцировать по 5 точкам");

    methodTwoDots->setCheckable(true);
    methodThreeDots->setCheckable(true);
    methodFiveDots->setCheckable(true);

    methodThreeDots->setChecked(true);

    connect(methodTwoDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodTwoDots);
    });
    connect(methodThreeDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodThreeDots);
    });
    connect(methodFiveDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodFiveDots);
    });
}

void Toolbar::initIntegralMenu()
{
    integralMenu = new QMenu( this );

    linearMethod = integralMenu->addAction("Линейный метод");
    trapezoidMethod = integralMenu->addAction("Метод трапеций");
    parabolicMethod = integralMenu->addAction("Метод Симпсона (парабол)");

    linearMethod->setCheckable(true);
    trapezoidMethod->setCheckable(true);
    parabolicMethod->setCheckable(true);

    linearMethod->setChecked(true);

    connect(linearMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState(linearMethod);
    });
    connect(trapezoidMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState(trapezoidMethod);
    });
    connect(parabolicMethod, &QAction::triggered, this, [=]() {
        updateIntegralCheckState(parabolicMethod);
    });
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
        updateSysCheckState(gaussMethod);
    });
    connect( simpleIterMethod, &QAction::triggered, this, [=]() {
        updateSysCheckState( simpleIterMethod );
    });
}

void Toolbar::updateDiffCheckState(QAction *checkedAction)
{
    if (checkedAction->isChecked()) {
        if (checkedAction == methodTwoDots) {
            methodThreeDots->setChecked(false);
            methodFiveDots->setChecked(false);
        } else if (checkedAction == methodThreeDots) {
            methodTwoDots->setChecked(false);
            methodFiveDots->setChecked(false);
        } else if (checkedAction == methodFiveDots) {
            methodTwoDots->setChecked(false);
            methodThreeDots->setChecked(false);
        }
    } else {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if (!methodTwoDots->isChecked() && !methodThreeDots->isChecked() && !methodFiveDots->isChecked()) {
            methodThreeDots->setChecked(true);
        }
    }
}

void Toolbar::updateIntegralCheckState(QAction *checkedAction)
{
    if (checkedAction->isChecked()) {
        if (checkedAction == linearMethod) {
            trapezoidMethod->setChecked(false);
            parabolicMethod->setChecked(false);
        } else if (checkedAction == trapezoidMethod) {
            linearMethod->setChecked(false);
            parabolicMethod->setChecked(false);
        } else if (checkedAction == parabolicMethod) {
            linearMethod->setChecked(false);
            trapezoidMethod->setChecked(false);
        }
    } else {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if (!linearMethod->isChecked() && !trapezoidMethod->isChecked() && !parabolicMethod->isChecked()) {
            linearMethod->setChecked(true);
        }
    }
}

void Toolbar::updateSysCheckState(QAction *checkedAction)
{
    if (checkedAction->isChecked()) {
        if (checkedAction == gaussMethod) {
            simpleIterMethod->setChecked(false);
        } else if (checkedAction == simpleIterMethod) {
            gaussMethod->setChecked(false);
        }
    } else {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if (!gaussMethod->isChecked() && !simpleIterMethod->isChecked()) {
            gaussMethod->setChecked(true);
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
    for( auto i = 0; i < actions().count(); ++i )
    {
        if( actions().at( i )->isChecked() )
        {
            actions().at( i )->setChecked( false );
        }
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
