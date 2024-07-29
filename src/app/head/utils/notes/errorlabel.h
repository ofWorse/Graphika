#ifndef ERRORLABEL_H
#define ERRORLABEL_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

class ErrorLabel : public QWidget
{
    Q_OBJECT
    Q_PROPERTY( float popupOpacity READ getPopupOpacity WRITE setPopupOpacity )

private:
    QLabel label; ///< label with message
    QGridLayout layout;
    QPropertyAnimation animation;
    QTimer *timer;

    float popupOpacity;

private:
    void setPopupOpacity( float opacity );
    float getPopupOpacity( void ) const;

public:
    explicit ErrorLabel( QWidget* parent = 0 );

protected:
    void paintEvent( QPaintEvent* event );

public slots:
    void setPopupText( const QString& text );
    void show( void );

private slots:
    void hideAnimation( void );
    void hide( void );
};

#endif //ERRORLABEL_H
