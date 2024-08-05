#include "equationslayout.h"

void EquationsLayout::generateWidgets( Widgets& widgets )
{
    layout = new QGridLayout;
    widgets.oddsInputLabel->setText( QString::asprintf( "Введите через пробел коэффициенты \n линейных уравнений и свободный член" ) );
    QStringList labels;
    labels << "C1 C2 ... Cn" << "X0";
    widgets.equationsTableWidget->setColumnCount( 2 );
    widgets.equationsTableWidget->setRowCount( 10 );
    for( int row{}; row < widgets.equationsTableWidget->rowCount(); ++row )
    {
        QRadioButton* button = new QRadioButton;
        widgets.equationsTableWidget->setCellWidget( row, 2, button );
    }
    widgets.equationsTableWidget->setHorizontalHeaderLabels( labels );
    widgets.solveEquations->setText( "Решить" );
    widgets.clearEquationsTable->setText( "Очистить Таблицу" );
    widgets.resultOfEquations->setText( "Результат вычислений: " );
    widgets.resultDescription->setText( "Описание: " );

    layout->addWidget( widgets.oddsInputLabel, 0, 0 );
    layout->addWidget( widgets.equationsTableWidget, 1, 0, 1, 2 );
    layout->addWidget( widgets.solveEquations, 2, 0 );
    layout->addWidget( widgets.clearEquationsTable, 2, 1 );
    layout->addWidget( widgets.resultOfEquations, 3, 0 );
    layout->addWidget( widgets.eqResult, 4, 0 );
    layout->addWidget( widgets.resultDescription, 5, 0 );
    layout->addWidget( widgets.description, 6, 0 );

    // ВРЕМЕННО ЗАКРОЕМ ДОСТУП К ДАННЫМ ПУНКТАМ
    {
        widgets.resultDescription->setDisabled( true );
        widgets.description->setDisabled( true );
    }
    this->widgets = &widgets;
    emit equationsTableEdited();
}

void EquationsLayout::updateEquationsButtonsPosition()
{
    // Проверяем, существует ли уже equationsButtonsWidget
    if (widgets->equationsButtonsWidget != nullptr)
    {
        widgets->equationsButtonsWidget->hide();
        delete widgets->equationsButtonsWidget;
    }

    widgets->equationsButtonsWidget = new QWidget(widgets->equationsTableWidget->parentWidget());
    QVBoxLayout* buttonsLayout = new QVBoxLayout(widgets->equationsButtonsWidget);

    QPushButton* addButton = new QPushButton("+");
    addButton->setFixedSize(30, 30);
    addButton->setStyleSheet("border-radius: 15px; background-color: limegreen; font-weight: bold;");

    QPushButton* removeButton = new QPushButton("-");
    removeButton->setFixedSize(30, 30);
    removeButton->setStyleSheet("border-radius: 15px; background-color: orange; font-weight: bold;");

    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addStretch();

    widgets->equationsButtonsWidget->setLayout(buttonsLayout);

    QRect tableGeometry = widgets->equationsTableWidget->geometry();
    int columnCount = widgets->equationsTableWidget->columnCount();
    int lastColumnWidth = widgets->equationsTableWidget->columnWidth(columnCount - 1);

    // Получаем размер крайнего правого заголовка колонки
    int headerWidth = widgets->equationsTableWidget->horizontalHeader()->sectionSize(columnCount - 1);

    int buttonWidgetX = tableGeometry.left() + widgets->equationsTableWidget->verticalHeader()->width()
                        + widgets->equationsTableWidget->columnViewportPosition(columnCount - 1)
                        + headerWidth + 5; // +5 для небольшого отступа
    int buttonWidgetY = tableGeometry.top() + (tableGeometry.height() / 2) - (widgets->equationsButtonsWidget->height() / 2);

    widgets->equationsButtonsWidget->setGeometry(buttonWidgetX, buttonWidgetY, widgets->equationsButtonsWidget->sizeHint().width(), widgets->equationsButtonsWidget->sizeHint().height());

    connect(addButton, &QPushButton::clicked, this, &EquationsLayout::onAddEquationRowButtonClicked);
    connect(removeButton, &QPushButton::clicked, this, &EquationsLayout::onRemoveEquationRowButtonClicked);

    widgets->equationsButtonsWidget->show();
}

void EquationsLayout::onAddEquationRowButtonClicked()
{
    int rowCount = widgets->equationsTableWidget->rowCount();
    widgets->equationsTableWidget->insertRow(rowCount);
}

void EquationsLayout::onRemoveEquationRowButtonClicked()
{
    int rowCount = widgets->equationsTableWidget->rowCount();
    if (rowCount > 0) // Не удалять последнюю строку
    {
        widgets->equationsTableWidget->removeRow(rowCount - 1);
    }
}

QGridLayout *EquationsLayout::get()
{
    return layout;
}
