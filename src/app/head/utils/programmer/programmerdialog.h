#ifndef PROGRAMMERDIALOG_H
#define PROGRAMMERDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include "programmerSettings.h"

class ProgrammerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgrammerDialog(QWidget *parent = nullptr);

    double getMinRange();
    double getYMinRange();
    double getMaxRange();
    double getYMaxRange();

    double getMinStepRange();
    double getMaxStepRange();

    double getMinNodesRange();
    double getMaxNodesRange();
    int getDecimals(double value);

signals:
    void settingsApplied(double min, double Ymin, double max, double Ymax, double minStep, double maxStep, double minNodes, double maxNodes, int decimels);

private slots:
    void applySettings();
    void resetSettings();

private:
    QDoubleSpinBox* minSpinBox;
    QDoubleSpinBox* yMinSpinBox;
    QDoubleSpinBox* maxSpinBox;
    QDoubleSpinBox* yMaxSpinBox;
    QDoubleSpinBox* minStepSpinBox;
    QDoubleSpinBox* maxStepSpinBox;
    QDoubleSpinBox* minNodesSpinBox;
    QDoubleSpinBox* maxNodesSpinBox;
    QPushButton *applyButton;
    QPushButton *resetButton;
    QFormLayout *formLayout;
    QVBoxLayout *mainLayout;
};

#endif // PROGRAMMERDIALOG_H
