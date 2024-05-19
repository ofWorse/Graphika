#include "functionlayout.h"

void FunctionLayout::generateWidgets( Widgets& widgets )
{
    layout = new QGridLayout;
    this->widgets = &widgets;
    layout->addWidget( widgets.label, 0, 0 );
    layout->addWidget( widgets.expressionInput, 0, 1, 1, 10 );
    layout->addWidget( widgets.derivativeLabel, layout->rowCount() - layout->rowCount() + 1, 0 );
    layout->addWidget( widgets.derivativeExpressionInput, layout->rowCount() - layout->rowCount() + 1, 1, 1, 10 );
    layout->addWidget( widgets.errLabel, 2, 0 );
    layout->addWidget( widgets.typeOfInput, 3, 0 );
    layout->addWidget( widgets.typeOfVariableInput, 3, 1 );
    layout->addWidget( widgets.minLabel, 4, 0 );
    layout->addWidget( widgets.min, 4, 1 );
    layout->addWidget( widgets.maxLabel, 5, 0 );
    layout->addWidget( widgets.max, 5, 1 );
    layout->addWidget( widgets.stepLabel, 6, 0 );
    layout->addWidget( widgets.step, 6, 1 );
    layout->addWidget( widgets.nodesLabel, 7, 0 );
    layout->addWidget( widgets.nodes, 7, 1 );
    layout->addWidget( widgets.solve, 8, 0 );
    layout->addWidget( widgets.clearTable, 8, 1 );
    layout->addWidget( widgets.buildGraph, 9, 0 );
    layout->addWidget( widgets.manualTableInput, 9, 1 );
    layout->addWidget( widgets.tableWidget, 10, 0, 1, 2 );
    layout->addWidget( widgets.averError, layout->rowCount(), 0 );
    layout->addWidget( widgets.error = new QLineEdit( this ), layout->rowCount() - 1, 1 );
    layout->addWidget( widgets.calculatedArea = new QLabel( "Вычисленная площадь: ", this ),
                      layout->rowCount(), 0 );
    layout->addWidget( widgets.area = new QLineEdit( this ), layout->rowCount() - 1, 1 );

    layout->setColumnStretch( 1, 10 );
    layout->setColumnStretch( 0, 2 );

    this->hideWidgets( widgets.derivativeExpressionInput, widgets.derivativeLabel,
                       widgets.error, widgets.area, widgets.calculatedArea );

    hideFirstLayer();
}

QGridLayout *FunctionLayout::get()
{
    return layout;
}

void FunctionLayout::saveData( void )
{
    // Сохранение текста из QLineEdit
    QSettings settings;
    settings.beginGroup("FunctionLayout");
    settings.setValue("expressionInput", widgets->expressionInput->text());
    settings.setValue("derivativeExpressionInput", widgets->derivativeExpressionInput->text());
    settings.setValue("min", widgets->min->text());
    settings.setValue("max", widgets->max->text());
    settings.setValue("step", widgets->step->text());
    settings.setValue("nodes", widgets->nodes->text());
    settings.setValue("error", widgets->error->text());
    settings.setValue("area", widgets->area->text());
    settings.endGroup();

    // Сохранение данных из таблицы
    settings.beginGroup("TableData");
    settings.beginWriteArray("rows");
    for (int row = 0; row < widgets->tableWidget->rowCount(); ++row) {
        settings.setArrayIndex(row);
        QStringList rowData;
        for (int col = 0; col < widgets->tableWidget->columnCount(); ++col) {
            rowData << widgets->tableWidget->item(row, col)->text();
        }
        settings.setValue("data", rowData);
    }
    settings.endArray();
    settings.endGroup();
}

void FunctionLayout::loadData( void )
{
    QSettings settings;
    settings.beginGroup("FunctionLayout");
    widgets->expressionInput->setText(settings.value("expressionInput").toString());
    widgets->derivativeExpressionInput->setText(settings.value("derivativeExpressionInput").toString());
    widgets->min->setValue(settings.value("min").toDouble());
    widgets->max->setValue(settings.value("max").toDouble());
    widgets->step->setValue(settings.value("step").toDouble());
    widgets->nodes->setValue(settings.value("nodes").toDouble());
    widgets->error->setText(settings.value("error").toString());
    widgets->area->setText(settings.value("area").toString());
    settings.endGroup();

    settings.beginGroup("TableData");
    int rows = settings.beginReadArray("rows");
    widgets->tableWidget->setRowCount(rows);
    for (int row = 0; row < rows; ++row) {
        settings.setArrayIndex(row);
        QStringList rowData = settings.value("data").toStringList();
        for (int col = 0; col < rowData.size(); ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(rowData.at(col));
            widgets->tableWidget->setItem(row, col, item);
        }
    }
    settings.endArray();
    settings.endGroup();
}
