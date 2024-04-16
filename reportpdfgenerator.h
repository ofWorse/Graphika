#ifndef REPORTPDFGENERATOR_H
#define REPORTPDFGENERATOR_H

#include <QApplication>
#include <QtWidgets>
#include <QPdfWriter>
#include <QPainter>

class ReportPDFGenerator : public QWidget
{
    Q_OBJECT
private:
    const QString* file;

public:
    explicit ReportPDFGenerator( const QString file, const QString dir, const QString ext, QWidget* parent = nullptr );
    void createPdfReport( void );
};

#endif // REPORTPDFGENERATOR_H
