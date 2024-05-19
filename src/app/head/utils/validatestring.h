/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef VALIDATESTRING_H
#define VALIDATESTRING_H

#include <QObject>
#include "expressionvalidator.h"
#include "settings.h"

/*!
 * \class ValidateString
 * \brief The ValidateString class, checking valid string.
 */
class ValidateString : public QObject
{
    Q_OBJECT

public:
    /*!
     * \brief ValidateString: constructor with standard heir argument.
     *
     * \param parent: pointer to the parent object.
     */
    explicit ValidateString( QObject *parent = nullptr );

signals:
    /*!
     * \brief validExpression: emit if given expression valid.
     */
    void validExpression( void );

    /*!
     * \brief invalidExpression: emit if given expression is invalid.
     */
    void invalidExpression( void );

public slots:
    /*!
     * \brief validateExpression: validating a given expression.
     *
     * \param expr: a string typed math expression.
     */
    void validateExpression( const QString& expr );

private:
    /*!
     * \brief isValidExpression: checks is the expression is valid.
     *
     * \param expr: given math expression as string.
     * \return boolean operator.
     */
    bool isValidExpression( const QString& expr );
};

#endif // VALIDATESTRING_H
