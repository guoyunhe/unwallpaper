#ifndef UNSPLASH_H
#define UNSPLASH_H

#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include "photo.h"

class Unsplash : public QObject
{
    Q_OBJECT
public:
    explicit Unsplash(QObject *parent = 0);

    QUrl makeUrl(QString path, QUrlQuery query);
    QNetworkReply * get(QString path, QUrlQuery query);

    static const QString APP_ID;

signals:
    void photoParsed(Photo *photo);
    void downloadProgress(qint64 bytesRead, qint64 totalBytes);

public slots:
    void getPhotos(int page = 1, int perPage = 10, QString orderBy = QString("latest"));
    void parsePhotos();

private:
    QNetworkAccessManager network;
    QNetworkReply* reply;
};

#endif // UNSPLASH_H
