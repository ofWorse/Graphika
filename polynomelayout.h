#ifndef POLYNOMELAYOUT_H
#define POLYNOMELAYOUT_H

#include <QGridLayout>
#include <QWidget>

class PolynomeLayout : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* layout;

public:
    explicit PolynomeLayout( QWidget *parent = nullptr );
    QGridLayout* getLayout( void )
    {
        return layout;
    }
};

#endif // POLYNOMELAYOUT_H
