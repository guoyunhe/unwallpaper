#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "photo.h"

Photo::Photo(QObject *parent) : QObject(parent)
{

}

Photo::Photo(QJsonObject json, QObject *parent) : QObject(parent)
{
    this->json = json;

    id = json["id"].toString();

    QJsonObject urls = json["urls"].toObject();
    rawUrl = QUrl(urls["raw"].toString());
    fullUrl = QUrl(urls["full"].toString());
    regularUrl = QUrl(urls["regular"].toString());
    smallUrl = QUrl(urls["small"].toString());
    thumbUrl = QUrl(urls["thumb"].toString());

    QJsonObject links = json["links"].toObject();
    apiUrl = QUrl(links["self"].toString());
    pageUrl = QUrl(links["html"].toString());
    downloadUrl = QUrl(links["download"].toString());

    QJsonObject user = json["user"].toObject();
    userFullName = user["name"].toString();
}

void Photo::download()
{
    QNetworkAccessManager *network = new QNetworkAccessManager;
    QNetworkReply *reply = network->get(QNetworkRequest(fullUrl));
    connect(reply, &QNetworkReply::finished, this, &Photo::saveAsWallpaper);
}

void Photo::saveAsWallpaper()
{
    qDebug("Downloaded!");

    emit wallpaperSaved();
}

QString Photo::getId()
{
    return id;
}

QUrl Photo::getRawUrl()
{
    return rawUrl;
}

QUrl Photo::getFullUrl()
{
    return fullUrl;
}

QUrl Photo::getRegularUrl()
{
    return regularUrl;
}

QUrl Photo::getSmallUrl()
{
    return smallUrl;
}

QUrl Photo::getThumbUrl()
{
    return thumbUrl;
}

QUrl Photo::getApiUrl()
{
    return apiUrl;
}

QUrl Photo::getPageUrl()
{
    return pageUrl;
}

QUrl Photo::getDownloadUrl()
{
    return downloadUrl;
}

QString Photo::getUserFullName()
{
    return userFullName;
}

QJsonObject Photo::getJson()
{
    return json;
}

void Photo::setId(QString id)
{
    this->id = id;
    emit idChanged(id);
}

void Photo::setRawUrl(QUrl rawUrl)
{
    this->rawUrl = rawUrl;
    emit rawUrlChanged(rawUrl);
}

void Photo::setFullUrl(QUrl fullUrl)
{
    this->fullUrl = fullUrl;
    emit fullUrlChanged(fullUrl);
}

void Photo::setRegularUrl(QUrl regularUrl)
{
    this->regularUrl = regularUrl;
    emit regularUrlChanged(regularUrl);
}

void Photo::setSmallUrl(QUrl smallUrl)
{
    this->smallUrl = smallUrl;
    emit smallUrlChanged(smallUrl);
}

void Photo::setThumbUrl(QUrl thumbUrl)
{
    this->thumbUrl = thumbUrl;
    emit thumbUrlChanged(thumbUrl);
}

void Photo::setApiUrl(QUrl apiUrl)
{
    this->apiUrl = apiUrl;
    emit apiUrlChanged(apiUrl);
}

void Photo::setPageUrl(QUrl pageUrl)
{
    this->pageUrl = pageUrl;
    emit pageUrlChanged(pageUrl);
}

void Photo::setDownloadUrl(QUrl downloadUrl)
{
    this->downloadUrl = downloadUrl;
    emit downloadUrlChanged(downloadUrl);
}

void Photo::setUserFullName(QString userFullName)
{
    this->userFullName = userFullName;
    emit userFullNameChanged(userFullName);
}
