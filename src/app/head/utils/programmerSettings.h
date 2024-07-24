#ifndef PROGRAMMERSETTINGS_H
#define PROGRAMMERSETTINGS_H
#include <QDebug>

struct ProgrammerSettings {
    double min;
    double yMin;
    double max;
    double yMax;
    double minStep;
    double maxStep;
    double minNodes;
    double maxNodes;
    int decimals;

    ProgrammerSettings()
        : min(-100.0), yMin(-100.0), max(100.0), yMax(100.0),
        minStep(0.01), maxStep(1.0), minNodes(2.0), maxNodes(100.0),
        decimals(2) {}
};

#endif // PROGRAMMERSETTINGS_H
