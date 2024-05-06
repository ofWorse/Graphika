#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMouseEvent>
#include "../utils/sender.h"
#include "qapplication.h"

class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    explicit Toolbar( QWidget *parent = nullptr );

    pymodules::Methods getSelectedDiffMethod( void ) const;
    pymodules::Methods getSelectedIntegralMethod( void ) const;
    pymodules::Methods getSelectedSysMethod( void ) const;
    void unsetChecked( void );

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    // derivation
    QAction* diffAction;
    QAction* methodTwoDots;
    QAction* methodThreeDots;
    QAction* methodFiveDots;
    // integration
    QAction* integralAction;
    QAction* linearMethod;
    QAction* trapezoidMethod;
    QAction* parabolicMethod;
    // sys
    QAction* sysAction;
    QAction* gaussMethod;
    QAction* simpleIterMethod;

    QMenu* diffMenu;
    QMenu* integralMenu;
    QMenu* sysMenu;

private:
    void initDiffMenu( void );
    void initIntegralMenu( void );
    void initSysMenu( void );
    void updateDiffCheckState( QAction* checkedAction );
    void updateIntegralCheckState( QAction* checkedAction );
    void updateSysCheckState( QAction* checkedAction );
    void setCheckable( void );
};

#endif // TOOLBAR_H
