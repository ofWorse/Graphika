#ifndef SHEETMENU_H
#define SHEETMENU_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QShortcut>
#include <QIcon>
#include <QTextEdit>
#include <QFile>
#include <QDebug>


class SheetMenu : public QWidget
{
    Q_OBJECT

public:
    SheetMenu( QWidget* parent = nullptr );
    static QWidget* invokeLicenseWidget( void ) noexcept;
    static QWidget* invokeAuthorsWidget( void ) noexcept;
    static QWidget* invokeAboutWidget( void ) noexcept;

    static void cleanupWidgets( QList<QWidget*>& widgets );
};

#endif
