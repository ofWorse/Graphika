#include "appearance.h"

Appearance::Appearance( QWidget* parent ) : QDialog( parent )
{
    this->parent = parent;
    currentStyle = setWindowStyleSheet( "light" );

    setWindowTitle( "Внешний вид" );

    layout = new QVBoxLayout( this );

    theme = new QComboBox;
    theme->addItems( { "Default", "Light", "Dark" } );
    layout->addWidget( new QLabel( "Тема: " ) );
    layout->addWidget( theme );

    font = new QFontComboBox;
    layout->addWidget( new QLabel( "Шрифт: " ) );
    layout->addWidget( font );

    fontSize = new QSpinBox;
    fontSize->setRange( 8, 18 );
    layout->addWidget( new QLabel( "Размер шрифта: " ) );
    layout->addWidget( fontSize );

    buttonLayout = new QHBoxLayout;
    apply = new QPushButton( "Принять" );
    cancel = new QPushButton( "Отмена" );

    buttonLayout->addWidget( apply );
    buttonLayout->addWidget( cancel );

    layout->addLayout( buttonLayout );

    connect( apply, &QPushButton::clicked, this, &Appearance::applySettings );
    connect( cancel, &QPushButton::clicked, this, &QDialog::reject );

}

void Appearance::applySettings( void )
{
    QString theme = this->theme->currentText().toLower();
    QString font = this->font->currentFont().family();
    int fontSize = this->fontSize->value();

    QApplication::setStyle( theme == "dark" ? "Dark" : "Fusion" );
    QPalette palette = QApplication::palette();

    currentStyle = setWindowStyleSheet( theme );

    palette.setColor( QPalette::Window, setWindowColor( theme ) );
    palette.setColor( QPalette::WindowText, theme.contains( "dark" ) ? Qt::white : Qt::black );

    QApplication::setPalette( palette );
    QFont appFont( font, fontSize );
    QApplication::setFont( appFont );

    parent->setStyleSheet( currentStyle );

    accept();
}

void Appearance::loadSettings( void )
{
    QSettings settings( "Dnevnie Mechaniki", "Graphika" );
    this->theme->setCurrentText( settings.value( "theme", "Light" ).toString() );
    this->font->setCurrentFont( QFont( settings.value( "font", "Arial" ).toString() ) );
    this->fontSize->setValue( settings.value( "fontSize", 12 ).toInt() );
    applySettings();
}

void Appearance::setStyleSheet( void )
{
    parent->setStyleSheet( currentStyle );
}

Qt::GlobalColor Appearance::setWindowColor( const QString& theme )
{
    if( theme == "dark" )
    {
        return Qt::darkGray;
    }
    return Qt::white;
}

QString Appearance::loadStyleSheet( const QString& path )
{
    QFile file( path );
    if ( file.open( QFile::ReadOnly ) )
    {
        QTextStream stream( &file );
        return stream.readAll();
    }
    else
    {
        qWarning() << "Failed to load stylesheet:" << path;
    }
    return QString();
}

QString Appearance::setWindowStyleSheet( const QString& style )
{
    if( style.contains( "dark" ) )
    {
        return loadStyleSheet( ":/themes/resources/themes/dark.qss" );
    }
    else if( style.contains( "light" ) )
    {
        return loadStyleSheet( ":/themes/resources/themes/light.qss" );
    }
    return "";
}


