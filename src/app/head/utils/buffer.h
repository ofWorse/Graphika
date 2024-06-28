/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef BUFFER_H
#define BUFFER_H

#include <QObject>
#include <QVector>
#include <iostream>

/*!
 * \class SpecialBuffer
 *
 * \brief The SpecialBuffer class that contains shared data to be passed between widgets.
 */
class SpecialBuffer : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief SpecialBuffer: standard constructor.
     */
    SpecialBuffer( void );

    QVector<double> x; ///< x data variables.
    QVector<double> y; ///< y data variables.
    QVector<double> z; ///< z data variables.
    QVector<double> dy; ///< derivated y data variables.
};

#endif // BUFFER_H
