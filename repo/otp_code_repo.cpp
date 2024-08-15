#include "otp_code_repo.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QDebug>

QString OtpCodeRepo::getOtpCode(const QString userName, const QString &json)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toUtf8());

    if (!jsonDoc.isNull() && jsonDoc.isObject())
    {
        QJsonObject jsonObject = jsonDoc.object();

        QJsonArray resultList = jsonObject["result_list"].toArray();

        for (const QJsonValue &value : resultList)
        {
            QJsonObject resultObject = value.toObject();

            QString delivered = resultObject["delivered"].toString();
            QString otpCode = resultObject["otp_code"].toString();
            qDebug() << "Delivered:" << delivered;
            qDebug() << "OTP Code:" << otpCode;
            if (delivered != userName)
            {
                qDebug() << "Delivered user name" << delivered << " is not same as " << userName;
                continue;
            }

            return otpCode;
        }
    }
    else
    {
        qDebug() << "Failed to create JSON doc.";
    }
    return "";
}