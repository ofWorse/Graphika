#include "errorlabel.h"

ErrorLabel::ErrorLabel( QWidget* parent ) : QWidget( parent )
{
    setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint );
    setAttribute( Qt::WA_TranslucentBackground );
    setAttribute( Qt::WA_ShowWithoutActivating );

    animation.setTargetObject( this );
    animation.setPropertyName( "popupOpacity" );
    connect( &animation, &QAbstractAnimation::finished, this, &ErrorLabel::hide );

    label.setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
    label.setStyleSheet( "QLabel { color : white; "
                         "margin-top: 32;"
                         "margin-bottom: 32;"
                         "margin-left: 64px;"
                         "margin-right: 64px; }" );
    layout.addWidget( &label, 0, 0 );
    setLayout( &layout );

    timer = new QTimer;
    connect( timer, &QTimer::timeout, this, &ErrorLabel::hideAnimation );
}

void ErrorLabel::paintEvent( QPaintEvent* event )
{
    Q_UNUSED( event )
    QPainter painter( this );
    painter.setRenderHint( QPainter::Antialiasing );

    QRect roundedRect;
    roundedRect.setX( rect().x() + 5 );
    roundedRect.setY( rect().y() + 5 );
    roundedRect.setWidth( rect().width() - 10 );
    roundedRect.setHeight( rect().height() - 10 );

    painter.setBrush( QBrush( QColor( 180, 0, 0, 180 ) ) );
    painter.setPen( Qt::NoPen );

    painter.drawRoundedRect( roundedRect, 10, 10 );
}

void ErrorLabel::setPopupText( const QString& text )
{
    label.setText( text );
    adjustSize();
}

void ErrorLabel::show( void )
{
    setWindowOpacity( 0.0 );

    animation.setDuration( 150 );
    animation.setStartValue( 0.0 );
    animation.setEndValue( 1.0 );

    setGeometry( QApplication::desktop()->availableGeometry().width()/2,
                 QApplication::desktop()->availableGeometry().height()/2,
                 width(),
                 height() );

    QWidget::show();

    animation.start();
    timer->start( 3000 );
}

void ErrorLabel::hideAnimation( void )
{
    timer->stop();
    animation.setDuration( 1000 );
    animation.setStartValue( 1.0 );
    animation.setEndValue( 0.0 );
    animation.start();
}

void ErrorLabel::hide( void )
{
    if( getPopupOpacity() == 0.0 )
    {
        QWidget::hide();
    }
}

void ErrorLabel::setPopupOpacity( float opacity )
{
    popupOpacity = opacity;
    setWindowOpacity( opacity );
}

float ErrorLabel::getPopupOpacity( void ) const
{
    return popupOpacity;
}
