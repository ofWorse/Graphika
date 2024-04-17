#include "menu.h"

Menu::Menu( QWidget *parent )
    : QMainWindow{ parent }
{
    createMenu( parent );
}

void Menu::createMenu( QWidget *parent )
{
    menu = new QMenuBar( parent );

    QMenu* fileMenu = menu->addMenu( tr( "&Файл" ) );
    QAction* cleanAction = fileMenu->addAction( tr( "Очистить" ) );
    QAction* openAction = fileMenu->addAction( tr( "Открыть" ) );
    fileMenu->addSeparator();
    QAction* saveAction = fileMenu->addAction( tr( "Сохранить PDF" ) );

    QMenu* viewMenu = menu->addMenu( tr( "&Вид" ) );
    QAction* viewAction = viewMenu->addAction( "Внешний вид" );

    QMenu* aboutMenu = menu->addMenu( tr( "&О программе" ) );
    QAction* licenceAction = aboutMenu->addAction( tr( "Лицензия" ) );
    QAction* authorsAction = aboutMenu->addAction( tr( "Об авторах" ) );
    QAction* programmAction = aboutMenu->addAction( tr( "О программе" ) );

    QMenu* utilsMenu = menu->addMenu( tr( "&Утилиты" ) );
    startSessionAction = utilsMenu->addAction( tr( "Начать сессию" ) );
    endSessionAction = utilsMenu->addAction( tr( "Закончить сессию" ) );
    QAction* programmatorAction = utilsMenu->addAction( tr( "Программатор" ) );
    connect( startSessionAction, &QAction::triggered, this, &Menu::sessionStarted );
    connect( endSessionAction, &QAction::triggered, this, &Menu::sessionStopped );
    endSessionAction->setDisabled( true );
}
