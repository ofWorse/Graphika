#ifndef LAYOUTFACTORY_H
#define LAYOUTFACTORY_H

#include <QGridLayout>
#include <QWidget>

class LayoutFactory
{
public:
    static QGridLayout* createLeftLayout( QWidget* parent );
    static QGridLayout* createRightLayout( QWidget* parent );
};

#endif // LAYOUTFACTORY_H
