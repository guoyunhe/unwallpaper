#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QUrlQuery>

#include "photo.h"
#include "unsplash.h"

const QString Unsplash::APP_ID = QString("ff62b721ff7e37849733e4ef88b2330026e397dd858a0ecd9bd1fea124b7621d");

/**
 * @brief Unsplash::Unsplash
 * @param parent
 */
Unsplash::Unsplash(QObject *parent) : QObject(parent)
{
}

/**
 * @brief Unsplash::makeUrl
 * @param QString path
 * @param QurlQuery query
 * @return QUrl
 */
QUrl Unsplash::makeUrl(QString path, QUrlQuery query)
{
    QUrl url;
    url.setScheme("https");
    url.setHost("api.unsplash.com");
    url.setPath(path);
    query.addQueryItem(QString("client_id"), APP_ID);
    url.setQuery(query);

    return url;
}

/**
 * @brief Unsplash::get
 * @param path
 * @param query
 * @return
 */
QNetworkReply * Unsplash::get(QString path, QUrlQuery query)
{
    QUrl url = makeUrl(path, query);

    qDebug() << "GET" << url.toDisplayString();

    return network.get(QNetworkRequest(url));
}

/**
 * @brief Request photo list.
 * @param page
 * @param perPage
 * @param orderBy
 */
void Unsplash::getPhotos(int page, int perPage, QString orderBy)
{
    QUrlQuery query;
    query.addQueryItem("page", QString::number(page));
    query.addQueryItem("per_page", QString::number(perPage));
    query.addQueryItem("order_by", orderBy);
    reply = get(QString("/photos"), query);

    // Update progress while waiting response data
    connect(reply, &QNetworkReply::downloadProgress, this, &Unsplash::downloadProgress);

    // Response finished and data is ready to read
    connect(reply, &QNetworkReply::finished, this, &Unsplash::parsePhotos);
}

/**
 * @brief Parse downloaded JSON of a list of photos.
 */
void Unsplash::parsePhotos()
{
    QString stringReply = (QString) reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(stringReply.toUtf8());
    QJsonArray array = jsonResponse.array();

    foreach (const QJsonValue & value, array) {
        QJsonObject object = value.toObject();

        emit photoParsed(new Photo(object));
    }
}
