#include "consoleapplication.h"


int ConsoleApplication::run( void )
{
//    QLineEdit commandInput;
//    QCompleter* completer = new QCompleter( &commandInput );
//    commandInput.setCompleter( completer );
//    completer->setModel( new QStringListModel( aviableCommands ) );

    std::cout << "Project: Graphika,\n" <<
                "by: \"Dnevnie Mechaniki\".\n" <<
                "authors\n" <<
                "Malaniya Mark Timurovich,\n" <<
                "Korshunov Ilya Dmitrievich,\n" <<
                "Vilenskiy Kirill Romanovich,\n" <<
                "Konak Vladimir Evgen'evich.\n\n\n";
    std::cout << "Enter command (or type 'exit' to quit).\n";

    ConsoleApplication app;

    while( true )
    {
        std::string input;
        std::cout << "<" << getUserName().toStdString() << "/" << "home" << ">:";
        std::getline( std::cin, input );
        std::string command;
        std::stringstream ss( input );

        if( !( ss >> command ) )
        {
            continue;
        }

        app.handleCommand(QString::fromStdString( input ));
    }

//    while( !shouldQuit )
//    {
//        std::string input;
//        std::cout << "<" << getUserName().toStdString() << "/" << "home" << ">";
//        std::getline( std::cin, input );

//        std::string command;
//        std::stringstream ss( input );
//        if( !( ss >> command ) )
//        {
//            continue;
//        }

//        auto it = commandMap.find( command );
//        if( it != commandMap.end() )
//        {
//            it->second();
//        }
//        else
//        {
//            std::cout << "Invalid command. Type 'help' for to see aviable commands.\n";
//        }
//    }
}

void ConsoleApplication::registerCommand(const QString &name, const QString &description, CommandFunction function)
{
    commands[name] = { description, function };
}

void ConsoleApplication::handleCommand(const QString &input)
{
    QStringList parts = input.split(" ");
    if(parts.isEmpty())
    {
        return;
    }

    QString commandName = parts[0];
    QStringList arguments = parts.mid(1);

    if(commandName == "help")
    {
        if(arguments.isEmpty())
        {
            printHelp();
        }
        else
        {
            printCommandHelp(arguments[0]);
        }
        return;
    }

    auto it = commands.find(commandName);
    if(it == commands.end())
    {
        std::cerr << "Invalid command: " << commandName.toStdString() << "\n";
        std::cerr << "Type 'help' for to see aviable commands.\n";
        return;
    }

    const auto& [description, function] = it.value();
    function(arguments);
}

void ConsoleApplication::initCommandMap( void )
{
    registerCommand( "help", "Prints info about programm components.\n", [this](const QStringList& args)
    {
        if(args.size() > 1)
        {
            std::cerr << "Too many arguments for commans 'help'.\nExpected: 1, actually: " << args.size() << std::endl;
            return;
        }
        printHelp();
    } );
    registerCommand( "exit", "Exit from Graphika console application.\n", [](const QStringList& args)
    {
        if(args.size() > 0)
        {
            std::cerr << "Too many arguments for commans 'exit'.\nExpected: 0, actually: " << args.size() << std::endl;
            return;
        }
        std::cout << "quit now.\n";
        exit(0);
    } );
    registerCommand( "cls", "Clear console consistance.\n", [](const QStringList& args)
    {
        if(args.size() > 0)
        {
            std::cerr << "Too many arguments for commans 'cls'.\nExpected: 0, actually: " << args.size() << std::endl;
            return;
        }
        std::cout << "\033[2J";
        std::cout << "\033[0;0f";
    });
    registerCommand( "add", "add.\n", [](const QStringList& args)
    {
        if( args.size() != 2 )
            {
            std::cerr << "Usage: add <number1> <number2>" << std::endl;
            return;
        }

        bool ok1, ok2;
        int a = args[0].toInt(&ok1);
        int b = args[1].toInt(&ok2);

        if( !ok1 || !ok2 )
        {
            std::cerr << "Invalid arguments!\n";
            return;
        }

        std::cout << "Result: " << ( a + b ) << std::endl;
    } );
}

void ConsoleApplication::executeCommand( const QString& command )
{
    auto it = commands.find( command );
    if( it != commands.end() )
    {
        it->second;
    }
    else
    {
        std::cout << "Unknown command: " << command.toStdString() << std::endl;
    }
}

void ConsoleApplication::printHelp( void )
{
    std::cout << "Aviable commands:\n\n";
    for( const QString& name : commands.keys())
    {
        const auto& info = commands.value(name);
        std::cout << "\t" << name.toStdString() << ": " << info.first.toStdString() << "\n";
    }
    std::cout << "\n";
}

void ConsoleApplication::printCommandHelp(const QString &commandName)
{
    auto it = commands.find( commandName );
    if( it == commands.end())
    {
        std::cerr << "Unknown command: " << commandName.toStdString() << "\n";
        return;
    }

    const auto& [description, function] = it.value();
    std::cout << "Command: " << commandName.toStdString() << "\n";
    std::cout << "Description: " << description.toStdString() << "\n\n";
}

QString ConsoleApplication::getUserName( void )
{
#ifdef Q_OS_WIN
    TCHAR username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    if( GetUserNameW( username, &username_len ) )
    {
        return QString::fromWCharArray( username );
    }
#elif defined( Q_OS_UNIX )
    struct passwd* pw = getpwuid( getuid() );
    if( pw )
    {
        return QString::fromUtf8( pw->pw_name );
    }
#endif
    return QString( "usr" );
}

