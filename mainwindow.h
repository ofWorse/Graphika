#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stringparser.h"
#include <QMainWindow>

namespace
{

    using namespace parser;

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    private:
        QString expression;
        StringParser parser;

    public:
        MainWindow( QWidget *parent = 0 );
        QPushButton* createButton( const QString& str );

    public slots:
        //void buttonClicked();
    };

} // anonymous namespace

#endif // MAINWINDOW_H
