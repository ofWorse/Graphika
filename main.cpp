//#include "stringparser.h"
//#include "graphbuilder.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    MainWindow window;
    window.show();

    //graph::GraphBuilder builder( "x", 250 );
    //builder.buildGraph( X, Y );

    return a.exec();
}
