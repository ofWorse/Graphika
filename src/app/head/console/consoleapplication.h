#ifndef CONSOLEAPPLICATION_H
#define CONSOLEAPPLICATION_H

#include <QMap>
#include <functional>
#include <iostream>
#include <sstream>
#include <tuple>
#include "commandhandler.h"
#include "commandcompleter.h"
#include "stringparser.h"
#include "rightwidget.h"


#ifdef Q_OS_WIN
#include <windows.h>
#elif defined( Q_OS_UNIX )
#include <unistd.h>
#include <pwd.h>
#endif


class ConsoleApplication
{
private:
    CommandCompleter* completer;
    Statement statement = Statement::HOME;
    std::string state;
    using CommandFunction = std::function<void(const QStringList&)>;
    QMap<QString, std::pair<QString, CommandFunction>> commands;
    StringParser* parser;

    pymodules::Methods methodOfInterpolation;

public:
    ConsoleApplication( void )
    {
        parser = new StringParser();
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

    void solveInterpolation( void );
    QString enterFunction( void );
    QVector<double> enterRanges( const QString& func );
    void solve( QVector<double> ranges, const QString& func );
};

#endif
