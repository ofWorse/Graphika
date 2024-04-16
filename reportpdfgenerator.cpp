#include "reportpdfgenerator.h"

ReportPDFGenerator::ReportPDFGenerator( const QString file, const QString dir, const QString ext , QWidget *parent )
    : QWidget( parent )
{
    QString fileName = QFileDialog::getSaveFileName( parent, file, dir, ext );
    this->file = new QString( fileName );
}

void ReportPDFGenerator::createPdfReport()
{
    if( file->isEmpty() )
    {
        //emit
        return;
    }

    QPdfWriter writer( *file );
    QPainter painter( &writer );

    // ...

    painter.end();
}
