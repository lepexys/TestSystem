#include "DataStorage.h"

QList<pair<QStringList, QStringList>> Loader::Load(const QString &path) {
    QRegExp rx("(\\ +|\\,|\\.|\\:|\\t)");
    QList<pair<QStringList, QStringList>> data;
    QAxObject *excel = new QAxObject("Excel.Application");
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", path);
    excel->dynamicCall("SetVisible(bool)", false);
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 1);
    for (int row = 1; row < 33; row++) {
        QAxObject *cell1 = worksheet->querySubObject("Cells(int,int)", row, 1);
        QVariant value1 = cell1->dynamicCall("Value()");
        QAxObject *cell2 = worksheet->querySubObject("Cells(int,int)", row, 2);
        QVariant value2 = cell2->dynamicCall("Value()");
        QStringList query1 = value1.toString().split(rx);
        QStringList query2 = value2.toString().split(rx);
        if ((query1.length() == 2 || query1.length() == 6) && (query2.length() == 2 || query2.length() == 6)) {
            data.append(pair<QStringList, QStringList>(query1, query2));
        }
    }
    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");
    return data;
}

void Saver::Save(const QString &path, QList<pair<QStringList, QStringList>> *dataPtr) {
    QList<pair<QStringList, QStringList>> data = *dataPtr;
    QAxObject *excel = new QAxObject("Excel.Application");
    QAxObject *workbooks = excel->querySubObject("Workbooks");
    QAxObject *workbook = workbooks->querySubObject("Open(const QString&)", path);
    excel->dynamicCall("SetVisible(bool)", false);
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)", 1);
    QAxObject *usedRange = worksheet->querySubObject("UsedRange");
    int initialRow = 1;//usedRange->property("Count").toInt() - 26; //usedRange выводит на 30 строк больше
    QList<pair<QStringList, QStringList>>::const_iterator it = data.begin();
    for (int j = 0; j < data.size(); j++, it++) {
        pair<QStringList, QStringList> pair = *it;
        QStringList::const_iterator it1 = pair.first.begin();
        QStringList::const_iterator it2 = pair.second.begin();
        for (int i = 0; i < pair.first.size() && i < pair.second.size(); i++, it1++, it2++) {
            QAxObject *cell1 = worksheet->querySubObject("Cells(int,int)", initialRow + i, 4);
            QVariant value1 = cell1->dynamicCall("Value()");
            cell1->setProperty("NumberFormat", "@");
            cell1->setProperty("Value",*it1);
            QAxObject *cell2 = worksheet->querySubObject("Cells(int,int)", initialRow + i, 5);
            cell2->setProperty("NumberFormat", "@");
            cell2->setProperty("Value", QVariant(*it2));
            QVariant value2 = cell2->dynamicCall("Value()");
        }
        initialRow += pair.first.size() + 1;
    }
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");
}



