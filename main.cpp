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

    std::string input = "1+10*2";
    parser::StringParser parser( input.c_str() );

    auto res = eval( parser.parseExpression() );
    std::cout << input << " = " << res << std::endl;
}
