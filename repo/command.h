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
};

#endif