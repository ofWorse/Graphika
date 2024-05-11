#include_next "toolbar.h"
#include <QIcon>

Toolbar::Toolbar( QWidget *parent ) : QToolBar(parent)
{
    addAction( QIcon( ":/toolbaricons/resources/function.PNG" ), "Построить график функции f(x)" );
    diffAction = addAction( QIcon( ":/toolbaricons/resources/derivation.PNG" ), "Построить график функции f'(x)" );
    integralAction = addAction( QIcon( ":/toolbaricons/resources/integral.PNG" ), "Найти площадь трапеции" );
    sysAction = addAction( QIcon( ":/toolbaricons/resources/sysfunctions.PNG" ), "sys" );
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/lagrange.PNG" ), "Построить модель полинома Лагранжа" );
    addAction( QIcon( ":/toolbaricons/resources/newthon.PNG" ), "Построить модель полинома Ньютона" );
    addAction( QIcon( ":/toolbaricons/resources/berruta.PNG" ), "Построить модель полинома Берута" );
    addSeparator();
    addAction( QIcon( ":/toolbaricons/resources/clearPlot.PNG" ), "Очистить график" );
    addAction( QIcon( ":/toolbaricons/resources/home.PNG" ), "Вернуть график" );
    addAction( QIcon( ":/toolbaricons/resources/moveLegend.PNG" ), "Переместить легенду" );
    addAction( QIcon( ":/toolbaricons/resources/showLegend.PNG" ), "Показать/скрыть легенду" );
    addAction( QIcon( ":/toolbaricons/resources/back.PNG" ), "Шаг назад" );
    addAction( QIcon( ":/toolbaricons/resources/forward.PNG" ), "Шаг вперед" );
    addAction( QIcon( ":/toolbaricons/resources/decreasePlot.PNG" ), "Увеличить график" );
    addAction( QIcon( ":/toolbaricons/resources/increasePlot.PNG" ), "Уменьшить график" );
    addAction( QIcon( ":/toolbaricons/resources/unpinPlot.PNG" ), "Отделить график от окна" );

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
    QStringList diffItems = { "Дифференцировать по 2 точкам", "Дифференцировать по 3 точкам", "Дифференцировать по 5 точкам" };
    initMenu( diffMenu, diffItems, &Toolbar::updateDiffCheckState );
}

void Toolbar::initIntegralMenu()
{
    QStringList integralItems = { "Линейный метод", "Метод трапеций", "Метод Симпсона (парабол)" };
    initMenu( integralMenu, integralItems, &Toolbar::updateIntegralCheckState );
}

void Toolbar::initSysMenu()
{
    QStringList sysItems = { "Метод Гаусса", "Метод простых итераций" };
    initMenu( sysMenu, sysItems, &Toolbar::updateSysCheckState );
}

void Toolbar::initMenu( QMenu*& menu, const QStringList& items, void ( Toolbar::*updateCheckState )( QAction* ) )
{
    menu = new QMenu( this );

    QList<QAction*> actions;
    for( const QString& item : items )
    {
        QAction* action = menu->addAction( item );
        action->setCheckable( true );
        actions.append( action );
    }

    actions.first()->setChecked( true );

    for( QAction* action : qAsConst( actions ) )
    {
        connect( action, &QAction::triggered, this, [ = ]()
        {
            (this->*updateCheckState)(action);
        });
    }
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
