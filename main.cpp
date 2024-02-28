#include "mainwindow.h"
#include "stringparser.h"
#include <QApplication>
#include <iostream>

int main( void )
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();

    std::vector<double> X = { -1.0, -0.5, 0.0, 1.0 };
    std::string input = "1/x";



    for( int i = 0; i < X.size(); ++i )
    {
        parser::StringParser parser( input.c_str(), X[i] );
        auto res = eval( parser.parseExpression(), X[i] );
        std::cout << X[i] << " : " << res << std::endl;
    }
}
