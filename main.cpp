#include "mainwindow.h"
#include "stringparser.h"
#include <QApplication>
#include <iostream>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );
    QWidget wgt;
    MainWindow window( &wgt );
    window.show();


    std::vector<double> X = { -1.0, -0.5, 0.0, 1.0 };
    std::string input = "1/x";

    for( int i = 0; i < X.size(); ++i )
    {
        parser::StringParser parser( input.c_str(), X[i] );
        auto res = eval( parser.parseExpression(), X[i] );
        std::cout << X[i] << " : " << res << std::endl;
    }

    //return a.exec();
}
