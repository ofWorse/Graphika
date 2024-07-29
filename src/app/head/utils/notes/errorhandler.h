/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <iostream>
#include <csignal>
#include <cstring>
#include <QMessageBox>

/*!
 * \brief signalHandler: returns a window with error or warning message.
 *
 * \param signal: type of system response signal.
 */
void signalHandler( int signal )
{
    QMessageBox mb;
    if( signal == SIGSEGV )
    {
        mb.setIcon( QMessageBox::Warning );
        mb.setWindowTitle( "Ошибка" );
        mb.setText( "Ошибка сегментации!" );
        mb.setStandardButtons( QMessageBox::Ok );
        mb.exec();
        exit( signal );
    }
}

#endif // ERRORHANDLER_H
