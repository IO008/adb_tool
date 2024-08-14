#include "networkmanager.h"

#include <QDebug>
#include <QThread>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent)
{
    networkAccessManager.reset(new QNetworkAccessManager(this));
    connect(networkAccessManager.data(), &QNetworkAccessManager::finished, this, &NetworkManager::onFinished);
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::makeRequest(const QUrl &url)
{
    networkAccessManager->get(QNetworkRequest(url));
}

void NetworkManager::onFinished(QNetworkReply *reply)
{
    QString result = "";
    if (reply->error() == QNetworkReply::NoError)
    {
        result = reply->readAll();
    }
    else
    {
        qDebug() << "NetworkManager::onFinished error" << reply->errorString();
    }
    emit requestFinished(result);
    reply->deleteLater();
}
