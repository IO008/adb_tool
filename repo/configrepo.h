#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QList>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QStringList>
#include <QStringListModel>

#include "../data/account.h"

class ConfigReopostory
{
private:
    QList<QSharedPointer<Account>> accounts;
    QStringList userNameList;

public:
    ConfigReopostory();
    ~ConfigReopostory();

    void readConfig(const QString &path);

    QStringList *getUserNameList();
};

#endif