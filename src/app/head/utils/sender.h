#ifndef SENDER_H
#define SENDER_H

#include "../algs/pythonconveyor.h"
#include "../settings/settings.h"
#include <QString>

class Sender {
public:
    Sender();
    void setMacro( pymodules::Methods method, pymodules::Modules module );

public:
    QString moduleName;
    QString functionName;

private:

};

#endif // SENDER_H
