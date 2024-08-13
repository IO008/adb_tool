#include "configrepo.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include <QDebug>

ConfigReopostory::ConfigReopostory()
{
}

ConfigReopostory::~ConfigReopostory()
{
}

void ConfigReopostory::readConfig(const QString &path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file for reading " << path;
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject obj = doc.object();

    QJsonArray accountsArray = obj["accounts"].toArray();
    for (const QJsonValue &value : accountsArray)
    {
        QJsonObject accountObj = value.toObject();
        qDebug() << "accountObj username: " << accountObj["username"].toString() << " password : " << accountObj["password"].toString();
        QSharedPointer<Account> account(new Account(accountObj["username"].toString(), accountObj["password"].toString()));
        accounts.append(account);
    }
}

QStringList *ConfigReopostory::getUserNameList()
{
    userNameList.clear();
    for (const QSharedPointer<Account> &account : accounts)
    {
        userNameList.append(account->email);
    }
    return &userNameList;
}