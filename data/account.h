#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    Account(QString email, QString password) : email(email), password(password) {};
    QString email;
    QString password;
};

#endif // ACCOUNT_H