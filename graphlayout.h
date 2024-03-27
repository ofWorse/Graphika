#ifndef GRAPHLAYOUT_H
#define GRAPHLAYOUT_H

#include <QGridLayout>
#include <QWidget>

class GraphLayout : public QWidget
{
    Q_OBJECT
private:
    QGridLayout* layout;

public:
    explicit GraphLayout( QWidget* parent = nullptr );
    QGridLayout* getLayout( void ) const
    {
        return layout;
    }
};

#endif // GRAPHLAYOUT_H
