/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef POLYNOMIALSLAYOUT_H
#define POLYNOMIALSLAYOUT_H


#include "layoutInitializer.h"

/*!
 * \class PolynomialsLayout
 *
 * \brief The PolynomialsLayout class, that heir a super class "LayoutInitializer" which contains widget controls.
 */
class PolynomialsLayout : public LayoutInitializer
{
    Q_OBJECT

private:
    QGridLayout* layout; ///< a grid layout for widgets.

public:
    /*!
     * standard class-destructor.
     */
    ~PolynomialsLayout( void ) { delete layout; }

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
};

#endif
