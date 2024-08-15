#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    QString email;
    QString password;

    Account(QString email, QString password) : email(email), password(password) {};
};

#endif // ACCOUNT_H