    /*!
 * \attention In development.
 *
 * \author Malaniya Mark Timurovich, Dnevnie Mechaniki.
 *
 * \date last update: 18.05.2024.
 */

#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QApplication>
#include <QTime>
#include <QString>
#include <QTableWidget>
#include <QLineEdit>
#include <QPdfWriter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>
#include <QTextTableFormat>
#include <type_traits>
#include "compositestatestack.h"


/*!
 * \class ReportPDFGenerator.
 *
 * \brief A class whose task is to create and save a PDF report in memory.
 */
class ReportGenerator : public QWidget
{
    Q_OBJECT
private:
    const QString* file; ///< path to file to save.
    QTime timer;

public:
    enum class ReportFormat
    {
        PDF,
        DOCX
    };

public:

    /*!
     * \brief ReportGenerator: a standard constructor with parent.
     *
     * \param parent: a parent object.
     */
    explicit ReportGenerator( QWidget* parent = nullptr );

    /*!
     * \brief ReportPDFGenerator: a constructor that generates a report in PDF format depending on the parameters specified to it.
     *
     * \param file: the file name you want to appear as the report name.
     * \param dir: path to specific directory.
     * \param ext: file extension (may be removed in the future).
     * \param parent: pointer to the parent object.
     */
    explicit ReportGenerator( const QString file, const QString dir, const QString ext, QWidget* parent = nullptr );

    void startSession( void );
    void endSession( void );

    QString getFilePath(ReportFormat format) {
        QString fileExtension = (format == ReportFormat::PDF) ? "PDF files (*.pdf)" : "DOCX files (*.docx)";
        return QFileDialog::getSaveFileName(nullptr, "Save Report", QString(), fileExtension);
    }

    void generateReport( CompositeStateStack& stack, ReportFormat format, const QString& filename) {
        if (format == ReportFormat::PDF) {
            generatePdfReport(stack, filename);
        } else if (format == ReportFormat::DOCX) {
            //generateDocxReport(filename);
        }
    }

private:
    void saveAsDocx( CompositeStateStack& stack, const QString& fileName );
    void saveAsPdf( CompositeStateStack& stack, const QString& fileName );
    template <typename T>
    void addObjectToDocument(QTextCursor& cursor, const QWidget& object) {
        // TODO
    }

    void generatePdfReport( CompositeStateStack& stack, const QString& filename) {
        // TODO
    }
    void addTableToDocument(QTextCursor& cursor, QTableWidget* table) {
        QTextTable* textTable = cursor.insertTable(table->rowCount(), table->columnCount());

        for (int row = 0; row < table->rowCount(); ++row) {
            for (int col = 0; col < table->columnCount(); ++col) {
                textTable->cellAt(row, col).firstCursorPosition().insertText(table->item(row, col)->text());
            }
        }

        cursor.insertBlock();
    }

    void addTextToDocument(QTextCursor& cursor, const QString& text) {
        cursor.insertText(text);
        cursor.insertBlock();
    }

    void addPlotToDocument(QTextCursor& cursor, QCustomPlot* plot) {
        // Implement the logic to add the plot to the document
    }

    void addLineEditToDocument(QTextCursor& cursor, QLineEdit* lineEdit) {
        cursor.insertText(lineEdit->text());
        cursor.insertBlock();
    }
};

#endif // REPORTGENERATOR_H
