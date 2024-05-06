#ifndef COMPOSITESTATESTACK_H
#define COMPOSITESTATESTACK_H

#include <QWidget>
#include <QStack>
#include <QDebug>

class CompositeStateStack : public QWidget
{
    Q_OBJECT
private:
    QStack<QObject*> stack;

public:
    explicit CompositeStateStack( QWidget *parent = nullptr );

public: QStack<QObject*> getLogStack( void )
    { return stack; }

private:
    void set( QObject* data );
    void pop( QObject* data );

public slots:
    void receiveData( QObject& data, bool toRemove );
};


#endif // COMPOSITESTATESTACK_H
