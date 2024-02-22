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

    QString input = "sin0";
    parser::StringParser parser( input );

    auto res = eval( parser.parseExpression() );
    std::cout << input.toStdString() << " = " << res << std::endl;
}
