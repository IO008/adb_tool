#include "command.h"

#include <QDebug>
Command::Command()
{
}

Command::~Command()
{
}

QList<QString> Command::getDevices()
{
    QList<QString> devices;
    process.start("adb", QStringList() << "devices");
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to execute adb devices command.";
        return devices;
    }
    QString result = process.readAllStandardOutput();
    QStringList list = result.split("\n");
    for (int i = 1; i < list.size() - 1; i++)
    {
        QString name = list.at(i).split("\t").at(0);
        if (!name.isEmpty())
        {
            devices.append(name);
        }
    }
    return devices;
}