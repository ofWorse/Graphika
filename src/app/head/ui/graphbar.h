#ifndef GRAPHBAR_H
#define GRAPHBAR_H

#include <QToolBar>

class GraphBar : public QToolBar
{
    Q_OBJECT
public:
    bool legendEnabled{ false };

public:
    explicit GraphBar( QWidget* parent = nullptr );
};

#endif //GRAPHBAR_H
