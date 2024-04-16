#include "menu.h"

Menu::Menu( QWidget *parent )
    : QMainWindow{ parent }
{
    createMenu( parent );
}

void Menu::createMenu( QWidget *parent )
{
    QMenuBar* menu = new QMenuBar;

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
    QAction* startSessionAction = utilsMenu->addAction( tr( "Начать сессию" ) );
    QAction* endSessionAction = utilsMenu->addAction( tr( "Закончить сессию" ) );
    QAction* programmatorAction = utilsMenu->addAction( tr( "Программатор" ) );
    endSessionAction->setDisabled( true );

    setMenuBar( menu );
}
