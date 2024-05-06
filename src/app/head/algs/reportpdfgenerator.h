#ifndef REPORTPDFGENERATOR_H
#define REPORTPDFGENERATOR_H

#include <QApplication>
#include <QtWidgets>
#include <QPdfWriter>
#include <QPainter>
#include "compositestatestack.h"

class ReportPDFGenerator : public QWidget
{
    Q_OBJECT
private:
    const QString* file;

public:
    explicit ReportPDFGenerator( const QString file, const QString dir, const QString ext, QWidget* parent = nullptr );
    void createPdfReport( CompositeStateStack& logStack );
};

#endif // REPORTPDFGENERATOR_H
