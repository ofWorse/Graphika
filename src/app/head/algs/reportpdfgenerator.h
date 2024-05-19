/*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef REPORTPDFGENERATOR_H
#define REPORTPDFGENERATOR_H

#include <QApplication>
#include <QtWidgets>
#include <QPdfWriter>
#include <QPainter>
#include "compositestatestack.h"

/*!
 * \class ReportPDFGenerator.
 *
 * \brief A class whose task is to create and save a PDF report in memory.
 */
class ReportPDFGenerator : public QWidget
{
    Q_OBJECT
private:
    const QString* file; ///< path to file to save.

public:
    /*!
     * \brief ReportPDFGenerator: a constructor that generates a report in PDF format depending on the parameters specified to it.
     *
     * \param file: the file name you want to appear as the report name.
     * \param dir: path to specific directory.
     * \param ext: file extension (may be removed in the future).
     * \param parent: pointer to the parent object.
     */
    explicit ReportPDFGenerator( const QString file, const QString dir, const QString ext, QWidget* parent = nullptr );

    /*!
     * \brief createPdfReport: method that generates a report in order using specified logs from the stack.
     *
     * \param logStack: a stack of data logs.
     */
    void createPdfReport( CompositeStateStack& logStack );
};

#endif // REPORTPDFGENERATOR_H
