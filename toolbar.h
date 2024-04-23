#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMouseEvent>
#include "sender.h"
#include "qapplication.h"

class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit Toolbar( QWidget *parent = nullptr );

    pymodules::Methods getSelectedDiffMethod() const;
    void unsetChecked( void );

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QAction *diffAction;
    QAction *methodTwoDots;
    QAction *methodThreeDots;
    QAction *methodFiveDots;

    QMenu *diffMenu;

private:
    void initDiffMenu( void );
    void updateDiffCheckState( QAction* checkedAction );
    void setCheckable( void );
};

#endif // TOOLBAR_H
