#ifndef CONSOLEAPPLICATION_H
#define CONSOLEAPPLICATION_H

#include <QMap>
#include <QStringList>
#include <functional>
#include <iostream>
#include <sstream>


#ifdef Q_OS_WIN
#include <windows.h>
#elif defined( Q_OS_UNIX )
#include <unistd.h>
#include <pwd.h>
#endif


class ConsoleApplication
{
private:
    using CommandFunction = std::function<void(const QStringList&)>;
    QMap<QString, std::pair<QString, CommandFunction>> commands;

public:
    ConsoleApplication( void )
    {
        initCommandMap();
    }
    int run( void );

    void registerCommand( const QString& name, const QString& description, CommandFunction function );
    void handleCommand( const QString& input );

private:
    void initCommandMap( void );
    void executeCommand( const QString& command );
    void printHelp( void );
    void printCommandHelp( const QString& commandName );
    QString getUserName( void );
};


#endif
