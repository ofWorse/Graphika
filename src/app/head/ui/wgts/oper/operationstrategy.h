#ifndef OPERATIONSTRATEGY_H
#define OPERATIONSTRATEGY_H

#include <vector>
#include <QString>

class OperationStrategy
{
public:
    virtual ~OperationStrategy() = default;
    virtual void execute( const QString& expression, double a, double b, std::vector<double>& x, std::vector<double>& y ) = 0;
};

class DerivativeStrategy : public OperationStrategy
{
public:
    void execute( const QString& expression, double a, double b, std::vector<double>& x, std::vector<double>& y ) override;
};

class IntegrationStrategy : public OperationStrategy
{
public:
    void execute( const QString& expression, double a, double b, std::vector<double>& x, std::vector<double>& y ) override;
};

class EquationStrategy : public OperationStrategy
{
public:
    void execute( const QString& expression, double a, double b, std::vector<double>& x, std::vector<double>& y ) override;
};

#endif // OPERATIONSTRATEGY_H
