#include "reportpdfgenerator.h"

ReportPDFGenerator::ReportPDFGenerator( const QString file, const QString dir, const QString ext , QWidget *parent )
    : QWidget( parent )
{
    QString fileName = QFileDialog::getSaveFileName( parent, file, dir, ext );
    this->file = new QString( fileName );
}

void ReportPDFGenerator::createPdfReport( CompositeStateStack& logStack )
{
    if( file->isEmpty() )
    {
        //emit
        qDebug() << "Нет такого файла или каталога!\n";
        return;
    }

    QPdfWriter writer( *file );
    QPainter painter( &writer );

    // TODO: Подумать над решением
    while( !logStack.getLogStack().empty() )
    {

    }

    painter.end();
}
