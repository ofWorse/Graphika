#ifndef VALIDATESTRING_H
#define VALIDATESTRING_H

#include <QObject>
#include "expressionvalidator.h"

class ValidateString : public QObject
{
    Q_OBJECT

public:
    explicit ValidateString( QObject *parent = nullptr );

signals:
    void validExpression();
    void invalidExpression();

public slots:
    void validateExpression( const QString& expr );

private:
    bool isValidExpression( const QString& expr );

};

#endif // VALIDATESTRING_H
