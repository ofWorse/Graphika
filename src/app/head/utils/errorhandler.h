#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <iostream>
#include <csignal>
#include <cstring>
#include <QMessageBox>

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
