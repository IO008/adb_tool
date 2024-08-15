#ifndef OTP_CODE_REPO_H
#define OTP_CODE_REPO_H

#include <QString>

class OtpCodeRepo
{
public:
    QString getOtpCode(const QString userName, const QString &json);
};

#endif // OTP_CODE_REPO_H