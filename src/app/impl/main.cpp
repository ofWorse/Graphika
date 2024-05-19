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

#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow window;
    window.show();

    return a.exec();
}
