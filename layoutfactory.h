#ifndef LAYOUTFACTORY_H
#define LAYOUTFACTORY_H

#include <QGridLayout>
#include <QWidget>

class LayoutFactory
{
public:
    static QGridLayout* createFunctionLayout( QWidget* parent );
    static QGridLayout* createPolynomeLayout( QWidget* parent );
    static QGridLayout* createGraphLayout( QWidget* parent );
};

#endif // LAYOUTFACTORY_H
