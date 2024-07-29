#include "graphbar.h"

GraphBar::GraphBar( QWidget* parent ) : QToolBar( parent )
{
    setIconSize( QSize( 32, 32 ) );
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
}

