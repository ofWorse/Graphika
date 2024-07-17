#include "reportgenerator.h"
#include <QLineEdit>
#include <QTableWidget>
#include <qcustomplot/qcustomplot.h>

ReportGenerator::ReportGenerator( QWidget* parent )
    : QWidget( parent )
{

}

ReportGenerator::ReportGenerator( const QString file, const QString dir, const QString ext , QWidget* parent )
    : QWidget( parent )
{
    QString fileName = QFileDialog::getSaveFileName( parent, file, dir, ext );
    this->file = new QString( fileName );
}

void ReportGenerator::startSession( void )
{
    //timer.start();
}

void ReportGenerator::endSession( void )
{
    //int elapsedMs = timer.elapsed();
    //int elapsedSecs = elapsedMs / 1000;
    //int elapsedMins = elapsedSecs / 60;
    //int remainingSecs = elapsedSecs % 60;

    //qDebug() << "Time elapsed: " << elapsedMins << ":" << elapsedSecs << "\n";
}
