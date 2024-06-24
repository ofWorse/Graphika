/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef COMPOSITESTATESTACK_H
#define COMPOSITESTATESTACK_H

#include <QWidget>
#include <QVariant>
#include <QDebug>
#include <qcustomplot/qcustomplot.h>


/*!
 * \class CompositeStateStack.
 *
 * \brief Simple stack for saving actions and logging into a pdf report.
 */
class CompositeStateStack : public QWidget
{
    Q_OBJECT
private:
    QVector<QWidget>* stack; ///< stack for logs.

public:

    /*!
     * \brief CompositeStateStack: constructor with standard heir argument.
     *
     * \param parent: pointer to the parent object.
     */
    explicit CompositeStateStack( QWidget *parent = nullptr );

    /*!
     * \brief getLogStack: a standard getter method.
     *
     * \return a stack of QObject's.
     */
    QVector<QWidget>* getLogStack( void )
    { return stack; }

//    void addItem( const QWidget& item )
//    { stack->append( item ); }

public slots:

    /*!
     * \brief receiveData: a slot that accepts data to be removed or stored on the stack.
     *
     * \param data: a class that heirs QObject.
     * \param toRemove: remove or save data to stack.
     */
    //void receiveData( QWidget& data, bool toRemove );
};


#endif // COMPOSITESTATESTACK_H
