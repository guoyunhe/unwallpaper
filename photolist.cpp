#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QUrlQuery>

#include "photo.h"
#include "photolist.h"

PhotoList::PhotoList(QObject *parent) : QObject(parent)
{

}

void PhotoList::fetch()
{
    QString path;

    if (curated) {
        path = QString("/photos/curated");
    } else {
        path = QString("/photos");
    }

    QUrlQuery query;
    query.addQueryItem("page", QString::number(page));
    query.addQueryItem("per_page", QString::number(perPage));

    switch (order) {
    case Order::Popular:
        query.addQueryItem("order_by", QString("popular"));
        break;
    case Order::Latest:
        query.addQueryItem("order_by", QString("latest"));
        break;
    case Order::Oldest:
        query.addQueryItem("order_by", QString("oldest"));
        break;
    }

    unsplash = new Unsplash();

    reply = unsplash->get(path, query);

    qDebug() << "reply";

    // Update progress while waiting response data
    connect(reply, &QNetworkReply::downloadProgress, this, &PhotoList::downloadProgress);

    // Response finished and data is ready to read
    connect(reply, &QNetworkReply::finished, this, &PhotoList::emptySlot);
}

void PhotoList::emptySlot()
{

}

void PhotoList::nextPage()
{
    page++;
    fetch();
}

/**
 * @brief Parse downloaded JSON of a list of photos.
 */
void PhotoList::parsePhotos()
{
    QString stringReply = (QString) reply->readAll();
    qDebug() << stringReply;
    QJsonDocument jsonResponse = QJsonDocument::fromJson(stringReply.toUtf8());
    QJsonArray array = jsonResponse.array();

    foreach (const QJsonValue & value, array) {
        QJsonObject object = value.toObject();

        emit photoParsed(new Photo(object));
    }

    emit allPhotosParsed();
}

PhotoList::Order PhotoList::getOrder()
{
    return order;
}

bool PhotoList::isCurated()
{
    return curated;
}

void PhotoList::setOrder(Order order)
{
    this->order = order;

    emit orderChanged(order);
}

void PhotoList::setCuratedStatus(bool curated)
{
    this->curated = curated;

    emit curatedStatusChanged(curated);
}
