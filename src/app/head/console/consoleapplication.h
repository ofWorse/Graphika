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
#include <vector>


#ifdef Q_OS_WIN
#include <windows.h>
#elif defined( Q_OS_UNIX )
#include <unistd.h>
#include <pwd.h>
#endif


class ConsoleApplication
{
private:
    QApplication* app;
    CommandCompleter* completer;
    Statement statement = Statement::HOME;
    std::string state;
    using CommandFunction = std::function<void(const QStringList&)>;
    QMap<QString, std::pair<QString, CommandFunction>> commands;
    StringParser* parser;

    pymodules::Methods methodOfInterpolation;

public:
    ConsoleApplication( QApplication& app )
    {
        this->app = &app;
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
    void enterFunction( void );
    int manualInput( std::vector<std::vector<double>>& xy );
    void functionInput( void );
    bool parseArguments( const std::string& input, std::vector<double>& x, std::vector<double>& y );
    QVector<double> enterRanges( const QString& func );

    template<typename T>
    void solve( T ranges, const QString& func );
};

#endif
