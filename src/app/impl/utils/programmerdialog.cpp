#include "programmerdialog.h"
#include <QDebug>

ProgrammerDialog::ProgrammerDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Программатор"));


    minStepSpinBox = new QDoubleSpinBox(this);
    minStepSpinBox->setDecimals(5);
    minStepSpinBox->setRange(0.00001, 10000);
    minStepSpinBox->setValue(0.01);

    maxStepSpinBox = new QDoubleSpinBox(this);
    maxStepSpinBox->setDecimals(4);
    maxStepSpinBox->setRange(0.0001, 10000);
    maxStepSpinBox->setValue(10);

    minSpinBox = new QDoubleSpinBox(this);
    minSpinBox->setRange(-99999.1, 99999.1);
    minSpinBox->setValue(-100);

    maxSpinBox = new QDoubleSpinBox(this);
    maxSpinBox->setRange(-99999.1, 99999.1);
    maxSpinBox->setValue(100);

    yMinSpinBox = new QDoubleSpinBox(this);
    yMinSpinBox->setRange(-99999.1, 99999.1);
    yMinSpinBox->setValue(-100);

    yMaxSpinBox = new QDoubleSpinBox(this);
    yMaxSpinBox->setRange(-99999.1, 99999.1);
    yMaxSpinBox->setValue(100);

    minNodesSpinBox = new QDoubleSpinBox(this);
    minNodesSpinBox->setRange(2, 99999);
    minNodesSpinBox->setValue(2);

    maxNodesSpinBox = new QDoubleSpinBox(this);
    maxNodesSpinBox->setRange(2, 99999);
    maxNodesSpinBox->setValue(100);

    applyButton = new QPushButton(tr("Применить"), this);
    resetButton = new QPushButton(tr("Сброс"), this);


    formLayout = new QFormLayout();

    formLayout->addRow(tr("Минимальный шаг:"), minStepSpinBox);
    formLayout->addRow(tr("Максимальный шаг:"), maxStepSpinBox);

    formLayout->addRow(tr("Нижний предел по X:"), minSpinBox);
    formLayout->addRow(tr("Верхний предел по X:"), maxSpinBox);

    formLayout->addRow(tr("Нижний предел по Y:"), yMinSpinBox);
    formLayout->addRow(tr("Верхний предел по Y:"),yMaxSpinBox);

    formLayout->addRow(tr("Наименьшее кол-во узлов:"), minNodesSpinBox);
    formLayout->addRow(tr("Наибольшее кол-во узлов:"), maxNodesSpinBox);

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(formLayout);
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
