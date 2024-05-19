/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef FUNCTIONLAYOUT_H
#define FUNCTIONLAYOUT_H

#include "layoutInitializer.h"

/*!
 * \class FunctionLayout
 *
 * \brief The FunctionLayout class, that heir a super class "LayoutInitializer" which contains widget controls.
 */
class FunctionLayout : public LayoutInitializer
{
    Q_OBJECT
private:
    QGridLayout* layout; ///< a grid layout for widgets.
public:
    /*!
     * standard class-destructor.
     */
    ~FunctionLayout( void ) { delete layout; }

    /*!
     * \brief generateWidgets: method adopting class, additional list of widgets.
     *
     * \param widgets: special class for storing all widgets on the left side of the window control.
     */
    void generateWidgets( Widgets& widgets ) override;

    /*!
     * \brief get: standard layout getter.
     *
     * \return private class member layout.
     */
    QGridLayout* get( void ) override;

    /*!
     * \brief saveData: a method which saves data from widgets to special buffer.
     */
    void saveData( void ) override;

    /*!
     * \brief loadData: a method which load data and setting it up to local widgets class.
     */
    void loadData( void ) override;
};

#endif
