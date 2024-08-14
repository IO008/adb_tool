#ifndef COMMAND_H
#define COMMAND_H

#include <QProcess>
#include <QList>
#include <QString>

class Command
{
private:
    QProcess process;

public:
    Command();
    ~Command();

    QList<QString> getDevices();

    void inputText(QString device, QString text);
    void keyEvent(QString device, QString key);
    void nextFocus(QString device);
    void hideKeyboard(QString device);
    void debugFragment(QString device);
    void deeplink(QString device, QString text, QString packageName);
    void customCommand(QString device, QString command);
    void uninstall(QString device, QString packageName);
};

#endif