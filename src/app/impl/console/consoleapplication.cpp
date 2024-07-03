#include "consoleapplication.h"

#include <QCompleter>
#include <QFile>
#include <QTextStream>

int ConsoleApplication::run( void )
{
    std::cout << "Project: Graphika,\n" <<
                "by: \"Dnevnie Mechaniki\".\n" <<
                "written by:\n" <<
                "Malaniya Mark Timurovich,\n" <<
                "Korshunov Ilya Dmitrievich,\n" <<
                "Vilenskiy Kirill Romanovich,\n" <<
                "Konak Vladimir Evgen'evich.\n\n\n";
    std::cout << "Enter command (or type 'exit' to quit).\n";

    ConsoleApplication app;

    while( true )
    {
        std::string input;
        std::cout << "<" << getUserName().toStdString() << "/" << "Graphika" << ">:";
        std::getline( std::cin, input );
        std::string command;
        std::stringstream ss( input );

        if( !( ss >> command ) )
        {
            continue;
        }

        app.handleCommand(QString::fromStdString( input ));
    }
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
        if(args.isEmpty())
        {
            printHelp();
            return;
        }
        else if( args.size() == 1 )
        {
            printCommandHelp(args[0]);
            return;
        }
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
    registerCommand( "license", "Show Graphika application license.\n", [](const QStringList& args)
    {
        if(args.size() > 0)
        {
            std::cerr << "Too many arguments for command 'license'.\nExpected: 0, actually: " << args.size() << std::endl;
            return;
        }
        QFile file(":/references/resources/fdl-1.3.txt");
        if( file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                std::cout << in.readLine().toStdString() << std::endl;
            }
            file.close();
        }
        else
        {
            std::cout << "Error oppening license file!\n";
        }
    });
    registerCommand( "authors", "Info about authors & programm.\n", [](const QStringList& args)
    {
        if(args.size() > 0)
        {
            std::cerr << "Too many arguments for command 'authors'.\nExpected: 0, actually: " << args.size() << std::endl;
            return;
        }

        std::cout << "Project: Graphika\n         --2024--\n" <<
            "by: \"Dnevnie Mechaniki\".\n" <<
            "written by:\n" <<
            "Malaniya Mark Timurovich: Head of development. C++, Qt programmer,\n" <<
            "Korshunov Ilya Dmitrievich: С++, Qt software engineer, software developer using C++ and Qt with Python module integration,\n" <<
            "Vilenskiy Kirill Romanovich: Software engineer of C++, Qt and QCUstomPlot, OpenGL libs,\n" <<
            "Konak Vladimir Evgen'evich: Python software engineer, programmer-developer of mathematical modules and algorithms.\n\n" <<
            "other developers:\n" <<
            "Husenov Said: QA engineer, technical writer,\n" <<
            "Filimonov Alexey: UX/UI designer of the interface and documentation of the software product,\n" <<
            "Skorodumov Nikita: QA engineer,\n" <<
            "Shiyan Yana: QA engineer.\n\n";
        std::cout << "Enter command (or type 'exit' to quit).\n";

    });
    registerCommand( "polynome", "Translates into the polynomial interpolation\n" \
                                     "\t\tmodule, after which the user can set the function\n" \
                                     "\t\tanalytically or discretely to get a string\n" \
                                     "\t\trepresentation of the approximating function.\n\n" \
                                     "\t\tExpecting such arguments as:\n     \n\t\t-L\tLagrange\n\t\t-N\tNewthon\n\t\t-B\tBerruta   \n\n", [this](const QStringList& args)
    {
        if(args.size() != 1)
        {
            std::cerr << "Usage: polynome <method>" << std::endl;
            return;
        }

        QString s = args[0];
        if( s !=  "-L" && s != "-N" && s != "-B" )
        {
            std::cerr << "Invalid input argument!\n\n" <<
                "Expected: \n\t-L\tLagrange\n\t-N\tNewthon\n\t-B\tBerruta   \n\n";
            return;
        }
        if(s == "-L") { methodOfInterpolation = pymodules::Methods::LAGRANGE; }
        else if(s == "-N") { methodOfInterpolation = pymodules::Methods::NEWTON; }
        else { methodOfInterpolation = pymodules::Methods::BEIRUT; }
        std::cout << "You in " << (s == "-L" ? "Lagrange" : ( s == "-N" ? "Newthon" : "Berruta") ) << " interpolation mode.\n";

        solveInterpolation();
    });

//    registerCommand( "add", "add.\n", [](const QStringList& args)
//    {
//        if( args.size() != 2 )
//            {
//            std::cerr << "Usage: add <number1> <number2>" << std::endl;
//            return;
//        }

//        bool ok1, ok2;
//        int a = args[0].toInt(&ok1);
//        int b = args[1].toInt(&ok2);

//        if( !ok1 || !ok2 )
//        {
//            std::cerr << "Invalid arguments!\n";
//            return;
//        }

//        std::cout << "Result: " << ( a + b ) << std::endl;
//    } );
}

//void ConsoleApplication::executeCommand( const QString& command )
//{
//    auto it = commands.find( command );
//    if( it != commands.end() )
//    {
//        it->second;
//    }
//    else
//    {
//        std::cout << "Unknown command: " << command.toStdString() << std::endl;
//    }
//}

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

void ConsoleApplication::solveInterpolation( void )
{
    QString func;
    func = enterFunction();
    QVector<double> ranges = enterRanges( func );
    solve( ranges, func );
}

QString ConsoleApplication::enterFunction( void )
{
    std::cout << "Enter function.\n";
    while( true )
    {
        std::cout << "f(x) = ";
        QString funcText = QTextStream(stdin).readLine();
        // TODO: добавить проверку корректности выражения
        return funcText;
    }
}

QVector<double> ConsoleApplication::enterRanges( const QString& func )
{
    std::cout << "Enter x data ranges.\nEx: -5 5 0.1\n";

    outer:
    while( true )
    {
        std::cout << "[x]range: ";
        QString funcText = QTextStream(stdin).readLine();

        QStringList args = funcText.split(" ");
        if( args.size() != 3 )
        {
            std::cerr << "Expected 3 arguments as <Xmin> <XMax> <Xstep>\nActually " << args.size() << " arguments given.\n";
            continue;
        }
        for( const QString& a : args )
        {
            bool ok;
            double xval = a.toDouble(&ok);
            if(!ok)
            {
                std::cerr << "Double arguments expected!\n";
                goto outer;
            }
        }
        double xmin = args[0].toDouble();
        double xmax = args[1].toDouble();
        double xstep = args[2].toDouble();
        return QVector<double>{ xmin, xmax, xstep };
    }
}

void ConsoleApplication::solve( QVector<double> ranges, const QString& func )
{
    std::vector<double> X;
    for( double i = ranges[0]; i <= ranges[1]; i += ranges[2])
    {
        X.push_back( i );
    }
    parser->setDataX( X );
    std::vector<double> Y = parser->parseExpression( func.toStdString().c_str(), 2 );

    RightWidget rw;
    Sender sender;
    sender.setMacro( methodOfInterpolation, pymodules::Modules::POLYNOMIALS );
    rw.interpolationSolve( X, Y, sender );
    std::cout << "Result model: " << QString::fromUtf8( rw.getResultModel().c_str() ).toStdString() << "\n";
}

