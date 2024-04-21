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

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QAction *diffAction;
    QAction *methodTwoDots;
    QAction *methodThreeDots;
    QAction *methodFiveDots;

    QMenu *diffMenu;

    void initDiffMenu();
    void updateDiffCheckState(QAction *checkedAction);

};

#endif // TOOLBAR_H
