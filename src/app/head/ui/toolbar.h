/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QMouseEvent>
#include "sender.h"
#include "qapplication.h"

/*!
 * \class Toolbar
 *
 * \brief The Toolbar class that contains every menu module.
 */
class Toolbar : public QToolBar
{
    Q_OBJECT
public:
    /*!
     * \brief Toolbar: constructor with standard heir argument.
     *
     * \param parent: pointer to the parent object.
     */
    explicit Toolbar( QWidget *parent = nullptr );

    /*!
     * \brief getSelectedDiffMethod: standard getter.
     * \return pymodules::Methods
     */
    pymodules::Methods getSelectedDiffMethod( void ) const;

    /*!
     * \brief getSelectedDiffMethod: standard getter.
     * \return pymodules::Methods
     */
    pymodules::Methods getSelectedIntegralMethod( void ) const;

    /*!
     * \brief getSelectedDiffMethod: standard getter.
     * \return pymodules::Methods
     */
    pymodules::Methods getSelectedSysMethod( void ) const;

    /*!
     * \brief unsetChecked: makes every checkable action unchecked.
     */
    void unsetChecked( void );

protected:
    /*!
     * \brief mousePressEvent: calls a method when the right mouse button is clicked.
     * \param event: right button click.
     */
    void mousePressEvent( QMouseEvent *event ) override;

private:
    QAction* diffAction; ///< derivation action menu.
    QAction* methodTwoDots; ///< specific derivation method.
    QAction* methodThreeDots; ///< specific derivation method.
    QAction* methodFiveDots; ///< specific derivation method.

    QAction* integralAction; ///< integration action menu.
    QAction* linearMethod; ///< specific integration method.
    QAction* trapezoidMethod; ///< specific integration method.
    QAction* parabolicMethod; ///< specific integration method.

    QAction* sysAction; ///< equations action menu.
    QAction* gaussMethod; ///< specific equations method.
    QAction* simpleIterMethod; ///< specific equations method.

    QMenu* diffMenu; ///< derivation menu.
    QMenu* integralMenu; ///< integration menu.
    QMenu* sysMenu; ///< equations menu.

private:
    /*!
     * \brief initDiffMenu: setup menu of derivation actions.
     */
    void initDiffMenu( void );

    /*!
     * \brief initIntegralMenu: setup menu of integration actions.
     */
    void initIntegralMenu( void );

    /*!
     * \brief initSysMenu: setup menu of equation actions.
     */
    void initSysMenu( void );

    /*!
     * \brief initMenu: invokes specific menu method.
     *
     * \param menu: type of menu.
     * \param items: list of options.
     */
    void initMenu( QMenu*& menu, const QStringList& items );

    /*!
     * \brief updateDiffCheckState: updates derivation checkbox object.
     *
     * \param checkedAction: specific action.
     */
    void updateDiffCheckState( QAction* checkedAction );

    /*!
     * \brief updateIntegralCheckState: updates integration checkbox object.
     *
     * \param checkedAction: specific action.
     */
    void updateIntegralCheckState( QAction* checkedAction );

    /*!
     * \brief updateSysCheckState: updates equations checkbox object.
     *
     * \param checkedAction: specific action.
     */
    void updateSysCheckState( QAction* checkedAction );

    /*!
     * \brief updateDiffCheckState: updates checkbox object.
     *
     * \param checkedAction: specific action.
     * \param actions: list of actions.
     */
    void updateCheckState( QAction* checkedAction, QList<QAction*> actions );

    /*!
     * \brief setCheckable: set all actions checkable.
     */
    void setCheckable( void );
};

#endif // TOOLBAR_H
