#include "programmerdialog.h"
#include <QDebug>
#include <QGroupBox>

ProgrammerDialog::ProgrammerDialog(QWidget *parent)
    : QDialog(parent)
{
setWindowTitle(tr("Программатор"));

    QGroupBox* stepGroupBox = new QGroupBox(tr("Настройки шага"), this);
    QFormLayout* stepLayout = new QFormLayout();

    minStepSpinBox = new QDoubleSpinBox(this);
    minStepSpinBox->setDecimals(5);
    minStepSpinBox->setRange(0.00001, 10000);
    minStepSpinBox->setValue(0.01);
    stepLayout->addRow(tr("Минимальный шаг:"), minStepSpinBox);

    maxStepSpinBox = new QDoubleSpinBox(this);
    maxStepSpinBox->setDecimals(4);
    maxStepSpinBox->setRange(0.0001, 10000);
    maxStepSpinBox->setValue(10);
    stepLayout->addRow(tr("Максимальный шаг:"), maxStepSpinBox);

    stepGroupBox->setLayout(stepLayout);

    QGroupBox* xRangeGroupBox = new QGroupBox(tr("Настройки пределов по X"), this);
    QFormLayout* xRangeLayout = new QFormLayout();

    minSpinBox = new QDoubleSpinBox(this);
    minSpinBox->setRange(-99999.1, 99999.1);
    minSpinBox->setValue(-100);
    xRangeLayout->addRow(tr("Нижний предел по X:"), minSpinBox);

    maxSpinBox = new QDoubleSpinBox(this);
    maxSpinBox->setRange(-99999.1, 99999.1);
    maxSpinBox->setValue(100);
    xRangeLayout->addRow(tr("Верхний предел по X:"), maxSpinBox);

    xRangeGroupBox->setLayout(xRangeLayout);

    QGroupBox* yRangeGroupBox = new QGroupBox(tr("Настройки пределов по Y"), this);
    QFormLayout* yRangeLayout = new QFormLayout();

    yMinSpinBox = new QDoubleSpinBox(this);
    yMinSpinBox->setRange(-99999.1, 99999.1);
    yMinSpinBox->setValue(-100);
    yRangeLayout->addRow(tr("Нижний предел по Y:"), yMinSpinBox);

    yMaxSpinBox = new QDoubleSpinBox(this);
    yMaxSpinBox->setRange(-99999.1, 99999.1);
    yMaxSpinBox->setValue(100);
    yRangeLayout->addRow(tr("Верхний предел по Y:"), yMaxSpinBox);

    yRangeGroupBox->setLayout(yRangeLayout);

    QGroupBox* nodesGroupBox = new QGroupBox(tr("Настройки узлов"), this);
    QFormLayout* nodesLayout = new QFormLayout();

    minNodesSpinBox = new QDoubleSpinBox(this);
    minNodesSpinBox->setRange(2, 99999);
    minNodesSpinBox->setValue(2);
    nodesLayout->addRow(tr("Наименьшее кол-во узлов:"), minNodesSpinBox);

    maxNodesSpinBox = new QDoubleSpinBox(this);
    maxNodesSpinBox->setRange(2, 99999);
    maxNodesSpinBox->setValue(100);
    nodesLayout->addRow(tr("Наибольшее кол-во узлов:"), maxNodesSpinBox);

    nodesGroupBox->setLayout(nodesLayout);

    applyButton = new QPushButton(tr("Применить"), this);
    resetButton = new QPushButton(tr("Сброс"), this);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(stepGroupBox);
    mainLayout->addWidget(xRangeGroupBox);
    mainLayout->addWidget(yRangeGroupBox);
    mainLayout->addWidget(nodesGroupBox);
    mainLayout->addWidget(applyButton);
    mainLayout->addWidget(resetButton);

    setLayout(mainLayout);

    connect(applyButton, &QPushButton::clicked, this, &ProgrammerDialog::applySettings);
    connect(resetButton, &QPushButton::clicked, this, &ProgrammerDialog::resetSettings);
}

double ProgrammerDialog::getMinRange()
{
    return minSpinBox->value();
}

double ProgrammerDialog::getMaxRange()
{
    return maxSpinBox->value();
}

double ProgrammerDialog::getYMinRange()
{
    return yMinSpinBox->value();
}

double ProgrammerDialog::getYMaxRange()
{
    return yMaxSpinBox->value();
}


double ProgrammerDialog::getMinStepRange()
{
    return minStepSpinBox->value();
}

double ProgrammerDialog::getMaxStepRange()
{
    return maxStepSpinBox->value();
}


double ProgrammerDialog::getMinNodesRange()
{
    return minNodesSpinBox->value();
}

double ProgrammerDialog::getMaxNodesRange()
{
    return maxNodesSpinBox->value();
}

int ProgrammerDialog::getDecimals(double value)
{
    QString str = QString::number(value, 'f', 10).remove(QRegExp("0+$")); // Удалить незначащие нули
    int index = str.indexOf('.');
    if (index == -1) return 0; // Нет десятичной точки
    return str.length() - index - 1;
}

void ProgrammerDialog::applySettings()
{
    int decimals = getDecimals(minStepSpinBox->value());
    qDebug() << "Emitting settingsApplied signal";
    emit settingsApplied(getMinRange(), getYMinRange(), getMaxRange(), getYMaxRange(), getMinStepRange(), getMaxStepRange(), getMinNodesRange(), getMaxNodesRange(), decimals);
    accept();
}

void ProgrammerDialog::resetSettings()
{
    minSpinBox->setValue(-100);
    yMinSpinBox->setValue(-100);
    maxSpinBox->setValue(100);
    yMaxSpinBox->setValue(100);

    minStepSpinBox->setValue(0.01);
    maxStepSpinBox->setValue(1);

    minNodesSpinBox->setValue(2);
    maxNodesSpinBox->setValue(100);
}
