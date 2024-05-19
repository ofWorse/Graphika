

#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QWidget>
#include <QMap>
#include "settings.h"

class DataModel : public QObject
{
    Q_OBJECT
private:
    struct ModuleData
    {
        QVector<QVector<QString>> tableData;
        QString inputData;
    };

    QMap<pymodules::Modules, ModuleData> data;

public:
    DataModel(QObject* parent = nullptr) : QObject(parent) {}

    void saveData(pymodules::Modules module, const QVector<QVector<QString>>& tableData, const QString& inputData)
    {
        data[module].tableData = tableData;
        data[module].inputData = inputData;
    }

    void restoreData(pymodules::Modules module, QVector<QVector<QString>>& tableData, QString& inputData)
    {
        tableData = data[module].tableData;
        inputData = data[module].inputData;
    }
};
#endif // DATAMODEL_H
