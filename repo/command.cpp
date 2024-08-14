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
    if (list.size() < 2)
    {
        qDebug() << "No found devices";
        return devices;
    }

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

void Command::inputText(QString device, QString text)
{
    process.start("adb", QStringList() << "-s" << device << "shell" << "input" << "text" << text);
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to execute adb shell input text command.";
    }
}

void Command::keyEvent(QString device, QString key)
{
    process.start("adb", QStringList() << "-s" << device << "shell" << "input" << "keyevent" << key);
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to execute adb shell input keyevent command.";
    }
}

void Command::nextFocus(QString device)
{
    keyEvent(device, "KEYCODE_TAB");
}

void Command::hideKeyboard(QString device)
{
    keyEvent(device, "KEYCODE_BACK");
}

void Command::debugFragment(QString device)
{
    process.start("adb", QStringList() << "-s" << device << "shell" << "setprop" << "log.tag.FragmentManager" << "DEBUG");
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to execute debugFragment command.";
    }
}

void Command::deeplink(QString device, QString text, QString packageName)
{
    process.start("adb", QStringList() << "-s" << device << "shell" << "am" << "start" << "-W" << "-a" << "android.intent.action.VIEW" << "-d" << text << packageName);
    if (!process.waitForFinished())
    {
        qDebug() << "Failed to execute deeplink command.";
    }
}