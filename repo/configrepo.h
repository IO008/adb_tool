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
    QStringListModel userListModel;

public:
    ConfigReopostory();
    ~ConfigReopostory();

    void readConfig(const QString &path);
    QStringListModel* getUserListModel();
};

#endif