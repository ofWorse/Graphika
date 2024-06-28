/*!
               -=*#%@@@@@%#*=:
            -#@@@@@@@@@@@@@@@@@%
          :%@@@@@@@@@@@@@@@@@@@@
         =@@@@@@@@@@@@@@@@@@@@%:
        :@@@@@@@@@%-.    .:++:
        #@@@@@@@@*    ::::::::::.
        @@@@@@@@@.   =@@@@@@@@@@@
        @@@@@@@@@    =@@@@@@@@@@@
        #@@@@@@@@*   -@@@@@@@@@@@
        :@@@@@@@@@%+=----%@@@@@@@
         :@@@@@@@@@@@@@@@@@@@@@@@
           +@@@@@@@@@@@@@@@@@@@@@
             =#@@@@@@@@@@@@@@@@#-

        Project: Graphika,
        by: "Dnevnie Mechaniki".

        \authors
        Malaniya Mark Timurovich,
        Korshunov Ilya Dmitrievich,
        Vilenskiy Kirill Romanovich,
        Konak Vladimir Evgen'evich.
*/

#include <QApplication>
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include "config.h"
#include "mainwindow.h"
#include "consoleapplication.h"

enum class ApplicationMode
{
    CONSOLE, GUI
};

ApplicationMode getApplicationMode( int argc, char* argv[] )
{
    for( int i = 1; i < argc; ++i )
    {
        if( strcmp( argv[i], "--console" ) == 0 )
        {
            return ApplicationMode::CONSOLE;
        }
        else if( strcmp( argv[i], "--gui" ) == 0 )
        {
            return ApplicationMode::GUI;
        }
    }
    return ApplicationMode::GUI;
}

int main( int argc, char *argv[] )
{
    ApplicationMode mode = getApplicationMode( argc, argv );

#if defined( CONSOLE_MODE )
    if( mode == ApplicationMode::CONSOLE )
    {
        QCoreApplication a( argc, argv );
        ConsoleApplication consoleApp;
        consoleApp.run();

        return 0;
    }
#endif

#if defined( GUI_MODE )
    if( mode == ApplicationMode::GUI )
    {
        QApplication a( argc, argv );
        MainWindow window;
        window.show();

        return a.exec();
    }
#endif
    qCritical() << "Invalid appliation mode.\nExiting.\n";
    return 1;
}
