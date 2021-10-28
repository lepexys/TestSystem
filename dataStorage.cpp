#include "testui.h"

DataStorage::DataStorage():Loader(),Saver()
{
    data = Load();
}

void Saver::Save()
{

}

QList<pair<QStringList,QStringList>> Loader::Load()
{
    QRegExp rx("(\\ +|\\,|\\.|\\:|\\t)");
    QList<pair<QStringList,QStringList>> data;
    QAxObject* excel = new QAxObject("Excel.Application");
    QAxObject* workbooks = excel->querySubObject("Workbooks");
    QAxObject* workbook = workbooks->querySubObject("Open(const QString&)",path);
    excel->dynamicCall("SetVisible(bool)",false);
    QAxObject* worksheet = workbook->querySubObject("WorkSheets(int)",1);
    QAxObject* usedrange = worksheet->querySubObject("UsedRange");
    QAxObject* rows = usedrange->querySubObject("Rows");
    QAxObject* columns = usedrange->querySubObject("Columns");
    int introwStart = usedrange->property("Row").toInt();
    int intcolStart = usedrange->property("Column").toInt();
    int intcols = usedrange->property("Count").toInt();
    int introws = usedrange->property("Count").toInt();
    for(int row = 0,i=0;row<introws;row++)
    {
        QAxObject* cell1 = worksheet->querySubObject("Cells(int,int)",row+1,1);
        QVariant value1 = cell1->dynamicCall("Value()");
        QAxObject* cell2 = worksheet->querySubObject("Cells(int,int)",row+1,2);
        QVariant value2 = cell2->dynamicCall("Value()");
        QStringList query1 = value1.toString().split(rx);
        QStringList query2 = value2.toString().split(rx);
        if((query1.length() == 2 || query1.length() == 6) && (query2.length() == 2 || query2.length() == 6))
        {
            data.insert(i++,pair<QStringList,QStringList>(query1,query2));
        }
    }
    workbook->dynamicCall("Close");
    excel->dynamicCall("Quit()");
    return data;
}
