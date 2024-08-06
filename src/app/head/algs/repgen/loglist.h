/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef LOGLIST_H
#define LOGLIST_H

#include <QVariant>
#include <QDebug>
#include "graphbuilder.h"


/*!
 * \class LogList.
 *
 * \brief Simple stack for saving actions and logging into a pdf report.
 */
class LogList : public QWidget
{
    Q_OBJECT
public:
    enum class ItemType
    {
        QWidget,
        QString,
        QLineEdit,
        QTableWidget,
        QCustomPlot
    };
    struct Item
    {
        ItemType item;
        union
        {
            QWidget* wgt;
            GraphBuilder* gbd;
            QCPGraph* grp;
            QString* str;
            QTableWidget* tbl;
        };
    };

public:
    void addItem( const Item& item );
    QList<Item> getItems( void ) const { return items; };

private:
    ItemType getItemType( const Item& item );

private:
    QList<Item> items;
};


#endif // LOGLIST_H
