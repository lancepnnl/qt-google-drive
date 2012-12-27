#ifndef ABOUTINFO_H
#define ABOUTINFO_H

#include "network/networkmanager.h"

class AccountInfo : public NetworkManager
{
    Q_OBJECT
public:
    enum EQueries
    {
      EUserInfoQuery = 0,
      EAboutInfoQuery
    };

    struct Data
    {
     QString name;
     QString email;        
     QString accessToken;
     QString refreshToken;
     QString domainSharingPolicy;
     QString permissionId;
     long long quotaBytesTotal;
     long long quotaBytesUsed;
     long long quotaBytesUsedInTrash;
    };

    AccountInfo(const QString &uiq, const QString &aiq, const QString &at, const QString &rt = QString());

signals:
   void signalAccountInfo(AccountInfo::Data&);

protected:
    void slotReplyFinished(QNetworkReply*);

public:
    void setInfo(void);
    Data getData(void) const;

private:
    void parseReply(void);

private:
    QString userInfoQuery;
    QString aboutInfoQuery;
    EQueries query;
    QString queryStr;
    Data accountData;
};

#endif // ABOUTINFO_H