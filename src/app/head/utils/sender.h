/*!
 * \attention In development.
 *
 * \author Korshunov Ilya Dmitrievich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef SENDER_H
#define SENDER_H

#include "pythonconveyor.h"
#include "settings.h"
#include <QString>

/*!
 * \class Sender
 *
 * \brief The Sender class between menu logic and pythomconveyor modules
 */
class Sender
{
public:
    /*!
     * \brief Sender: standard constructor.
     */
    Sender( void );

    /*!
     * \brief setMacro: install the macro and determine the correspondence with the python module.
     *
     * \param method: name of method.
     * \param module: name of module.
     */
    void setMacro( pymodules::Methods method, pymodules::Modules module );

public:
    QString moduleName; ///< name of python module.
    QString functionName; ///< name of python function in module.
};

#endif // SENDER_H
