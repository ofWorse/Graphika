#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include "qapplication.h"

class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit Toolbar( QWidget *parent = nullptr );

signals:

};

#endif // TOOLBAR_H
