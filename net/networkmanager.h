#ifndef NET_NETWORKMANAGER_H
#define NET_NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QScopedPointer>
#include <QNetworkReply>
#include <QUrl>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void makeRequest(const QUrl &url);

private:
    QScopedPointer<QNetworkAccessManager> networkAccessManager;

signals:
    void requestFinished(const QString &result);

private slots:
    void onFinished(QNetworkReply *reply);
};

#endif // NET_NETWORKMANAGER_H