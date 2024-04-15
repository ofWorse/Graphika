#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QtWidgets>

class Menu : public QMainWindow
{
    Q_OBJECT
    QWidget* parent;
public:
    explicit Menu( QWidget *parent = nullptr );
    Menu* get( void )
    { return this; }

private:
    void createMenu( void );
};

#endif // MENU_H
