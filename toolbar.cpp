#include "toolbar.h"
#include <QIcon>

Toolbar::Toolbar(QWidget *parent) : QToolBar(parent)
{
    addAction(QIcon(":/toolbaricons/resources/function.PNG"), "Построить график функции f(x)");
    diffAction = addAction(QIcon(":/toolbaricons/resources/diff.PNG"), "Построить график функции f'(x)");
    addSeparator();
    addAction(QIcon(":/toolbaricons/resources/lagrange.PNG"), "Построить модель полинома Лагранжа");
    addAction(QIcon(":/toolbaricons/resources/newthon.PNG"), "Построить модель полинома Ньютона");
    addAction(QIcon(":/toolbaricons/resources/berruta.PNG"), "Построить модель полинома Берута");
    addSeparator();
    addAction(QIcon(":/toolbaricons/resources/clean.PNG"), "Очистить график");
    addAction(QIcon(":/toolbaricons/resources/home.PNG"), "Вернуть график");
    addAction("GLeg");
    addAction("SLeg");
    addAction("<-");
    addAction("->");

    initDiffMenu();
}

void Toolbar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        QAction *action = actionAt(event->pos());
        if (action == diffAction)
        {
            diffMenu->popup(event->globalPos());
        }
    } else {
        QToolBar::mousePressEvent(event);
    }
}

void Toolbar::initDiffMenu()
{
    diffMenu = new QMenu(this);

    methodTwoDots = diffMenu->addAction("Дифференцировать по 2 точкам");
    methodThreeDots = diffMenu->addAction("Дифференцировать по 3 точкам");
    methodFiveDots = diffMenu->addAction("Дифференцировать по 5 точкам");

    methodTwoDots->setCheckable(true);
    methodThreeDots->setCheckable(true);
    methodFiveDots->setCheckable(true);

    methodThreeDots->setChecked(true);

    connect(methodTwoDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodTwoDots);
    });
    connect(methodThreeDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodThreeDots);
    });
    connect(methodFiveDots, &QAction::triggered, this, [=]() {
        updateDiffCheckState(methodFiveDots);
    });
}

void Toolbar::updateDiffCheckState(QAction *checkedAction)
{
    if (checkedAction->isChecked()) {
        if (checkedAction == methodTwoDots) {
            methodThreeDots->setChecked(false);
            methodFiveDots->setChecked(false);
        } else if (checkedAction == methodThreeDots) {
            methodTwoDots->setChecked(false);
            methodFiveDots->setChecked(false);
        } else if (checkedAction == methodFiveDots) {
            methodTwoDots->setChecked(false);
            methodThreeDots->setChecked(false);
        }
    } else {
        // Если действие было снято с выбора, оставляем один из вариантов выбранным
        if (!methodTwoDots->isChecked() && !methodThreeDots->isChecked() && !methodFiveDots->isChecked()) {
            methodThreeDots->setChecked(true);
        }
    }
}

pymodules::Methods Toolbar::getSelectedDiffMethod() const
{
    if ( methodTwoDots->isChecked() )
    {
        return pymodules::Methods::DIFF_2P;
    }
    else if ( methodThreeDots->isChecked() )
    {
        return pymodules::Methods::DIFF_3P;
    }
    else if ( methodFiveDots->isChecked() )
    {
        return pymodules::Methods::DIFF_5P;
    }
    else
    {
        // Если ни один вариант не выбран, возвращаем значение по умолчанию
        return pymodules::Methods::DIFF_3P;
    }
}
