/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef REFERENCEMENU_H
#define REFERENCEMENU_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QShortcut>
#include <QIcon>
#include <QTextEdit>
#include <QFile>
#include <QDebug>

/*!
 * \class Reference
 *
 * \brief The SheetMenu class
 */
class ReferenceMenu : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief ReferenceMenu: constructor with standard heir argument.
     *
     * \param parent: pointer to the parent object.
     */
    ReferenceMenu( QWidget* parent = nullptr ) : QWidget(parent) {}

    /*!
     * \brief invokeLicenseWidget: a method that generates and displays a window with a text license of a software product.
     *
     * \return a widget with license window.
     */
    static QWidget* invokeLicenseWidget( void ) noexcept;

    /*!
     * \brief invokeAuthorsWidget: a method that generates and displays a window with a authors list.
     *
     * \return a widget with license window.
     */
    static QWidget* invokeAuthorsWidget( void ) noexcept;

    /*!
     * \brief invokeAboutWidget: a method that generates and displays a window with a documentation of software usage.
     *
     * \return a widget with license window.
     */
    static QWidget* invokeAboutWidget( void ) noexcept;

    /*!
     * \brief cleanupWidgets: method for clearing widget contents.
     *
     * \param widgets: list of widgets that must to be cleaned.
     */
    static void cleanupWidgets( QList<QWidget*>& widgets );
};

#endif
