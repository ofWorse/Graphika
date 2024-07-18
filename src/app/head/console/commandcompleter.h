#ifndef COMMANDCOMPLETER_H
#define COMMANDCOMPLETER_H

#include <QObject>
#include <vector>

class CommandCompleter : public QObject
{
    Q_OBJECT
private:
    std::vector<std::string> commands;

public:
    void addCommand( const std::string& command )
    {
        commands.push_back( command );
    }

    std::vector<std::string> getCompletions( const std::string& prefix )
    {
        std::vector<std::string> completions;
        for ( const auto& command : commands )
        {
            if ( command.find( prefix ) == 0 )
            {
                completions.push_back( command );
            }
        }
        return completions;
    }
};

#endif //COMMANDCOMPLETER_H
