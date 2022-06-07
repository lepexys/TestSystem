#ifndef TESTSYSTEM_DATASTORAGE_H
#define TESTSYSTEM_DATASTORAGE_H

#include <QStringList>
#include <QAxObject>
#include <QDir>

using namespace std;

class Loader {
public:
    Loader() = default;

    ~Loader() = default;

    QList<pair<QStringList, QStringList>> Load(const QString &path);
};

class Saver {
public:
    Saver() = default;

    ~Saver() = default;

    void Save(const QString &path, QList<pair<QStringList, QStringList>> *dataPtr);

};

class DataStorage : public Loader, public Saver {
public:
    QList<pair<QStringList, QStringList>> data;

    DataStorage() = default;

    ~DataStorage() = default;

};

#endif //TESTSYSTEM_DATASTORAGE_H
