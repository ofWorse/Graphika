#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QPainter>

class Drawable
{
public:
    virtual void draw( QPainter* painter ) = 0;
};

#endif // DRAWABLE_H
