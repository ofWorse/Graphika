#include "mainwindow.h"
//#include "ui_mainwindow.h"

QPushButton* MainWindow::createButton(const QString &str)
{
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(40, 40);
    connect(pcmd, SIGNAL(clicked()), SLOT(buttonClicked()));
    return pcmd;
}
