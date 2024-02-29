#include "mainwindow.h"
#include "stringparser.h"
#include "graphbuilder.h"
#include <QApplication>
#include <iostream>

int main( int argc, char *argv[] )
{
    //QApplication a( argc, argv );
    // wgt;
    //MainWindow window( &wgt );
    //window.show();


    std::vector<double> X = { -1 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    std::vector<double> Y;
    std::string input = "x";

    for( int i = 0; i < X.size(); ++i )
    {
        parser::StringParser parser( input.c_str(), X[i] );
        auto res = eval( parser.parseExpression(), X[i] );
        Y.push_back( res );
        //std::cout << X[i] << " : " << res << std::endl;
    }
    Y[0] = -1;
    graph::GraphBuilder builder( "x", 250 );
    builder.buildGraph( X, Y );

    //return a.exec();
}
