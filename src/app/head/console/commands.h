#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>
#include <QStringList>

struct Command
{
    QString name;
    int numArguments;
    QString description;
};

static QStringList parseCommandLine( const QString& commandLine )
{
    return commandLine.split( " ", Qt::SkipEmptyParts );
}

static bool validateArguments( const QStringList& tokens, const Command& command )
{
    if( tokens.size() - 1 != command.numArguments )
    {
        return false;
    }

    for( int i = 1; i < tokens.size(); ++i )
    {
        // TODO: create logic analization process here
    }

    return true;
}


#endif // COMMANDS_H
