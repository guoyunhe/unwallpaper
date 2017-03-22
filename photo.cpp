#include <Magick++.h>

#include <QDir>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "photo.h"
#include "photosavethread.h"

using namespace Magick;

Photo::Photo(QObject *parent) : QObject(parent)
{

}

Photo::Photo(QJsonObject json, QObject *parent) : QObject(parent)
{
    this->json = json;

    id = json["id"].toString();

    width = json["width"].toInt();
    height = json["height"].toInt();

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
    reply = network->get(QNetworkRequest(fullUrl));

    PhotoSaveThread *thread = new PhotoSaveThread(this);
    connect(reply, &QNetworkReply::downloadProgress, this, &Photo::downloadProgress);
    connect(reply, &QNetworkReply::finished, this, &Photo::downloaded);
    connect(reply, &QNetworkReply::finished, thread, &PhotoSaveThread::save);
    connect(reply, static_cast<void(QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &Photo::downloadFailed);

    connect(thread, &PhotoSaveThread::saved, this, &Photo::saved);
}

void Photo::save()
{
    emit downloaded();
    qDebug("Downloaded!");

    QDir *dir = new QDir;
    dir->mkpath(getImagesPath()); // Create directory if not exists
    QFile *file = new QFile;
    file->setFileName(getSaveFileName(width, height));
    file->open(QIODevice::ReadWrite); // Create file if not exists
    file->write(reply->readAll());

    emit saveProgress(1, 10);

    generateSize(3840, 2160); // 4K/UHD, popular desktop monitor resolution

    emit saveProgress(2, 10);

    generateSize(2560, 1440); // 2K/QHD, popular desktop monitor resolution
    emit saveProgress(3, 10);
    generateSize(1920, 1080); // FHD, most popular desktop and gaming laptop screen resolution
    emit saveProgress(4, 10);
    generateSize(1600, 900); // Not very popular laptop screen resolution
    emit saveProgress(5, 10);
    generateSize(1366, 768); // HD, most popular laptop screen resolution
    emit saveProgress(6, 10);
    generateSize(1280, 1024); // Legacy desktop monitor resolution
    emit saveProgress(7, 10);
    generateSize(1024, 768); // Legacy laptop screen resolution
    emit saveProgress(8, 10);

    generateSize(400, 250, getScreenshotFileName()); // Screenshot used in desktop configuration
    emit saveProgress(9, 10);

    QFile metafile(getMetadataFileName());

    if (metafile.open(QIODevice::ReadWrite)) {
        QTextStream stream(&metafile);
        stream << "[Desktop Entry]" << endl;
        stream << "Encoding=UTF-8" << endl;
        stream << "Name=Unsplash " << id << endl;
        stream << "X-KDE-PluginInfo-Name=Unsplash " << id << endl;
        stream << "X-KDE-PluginInfo-Author=" << userFullName << endl;
        stream << "X-KDE-PluginInfo-License=CC0" << endl;
        stream << "X-KDE-PluginInfo-Website=https://unsplash.com/" << endl;
        stream << endl;
    }

    emit saveProgress(10, 10);

    emit saved();

    emit localStatusChanged(true);
}

void Photo::generateSize(int width, int height, QString path)
{
    int resizeWidth;
    int resizeHeight;

    if (width * this->height  > this->width * height) {
        resizeWidth = width;
        resizeHeight = (int) (resizeWidth * this->height * 1.0 / this->width + 0.5); // Round up
    } else {
        resizeHeight = height;
        resizeWidth = (int) (resizeHeight * this->width * 1.0 / this->height + 0.5); // Round up
    }

    QFile *file = new QFile;
    file->setFileName(getSaveFileName(width, height));
    file->open(QIODevice::ReadWrite); // Create file if not exists

    Image image;

    try {
        // Read full size photo
        image.read(getSaveFileName(this->width, this->height).toUtf8().constData());

        image.resize(Geometry(resizeWidth, resizeHeight));

        image.crop(Geometry(width, height, (resizeWidth - width) / 2, (resizeHeight - height) / 2));

        if (path.isNull() || path.isEmpty()) {
            image.write(getSaveFileName(width, height).toUtf8().constData());
        } else {
            image.write(path.toUtf8().constData());
        }
    } catch ( Exception &error ) {
      qDebug() << "Caught exception: " << error.what();
      return;
    }
}

void Photo::remove()
{
    QDir dir(getSavePath());
    dir.removeRecursively();

    emit localStatusChanged(false);
}

QString Photo::getId()
{
    return id;
}

int Photo::getWidth()
{
    return width;
}

int Photo::getHeight()
{
    return height;
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

QString Photo::getSavePath ()
{
    return QDir::homePath() + QString("/.local/share/wallpapers/Unsplash-") + id;
}

QString Photo::getContentsPath ()
{
    return getSavePath() + QString("/contents");
}

QString Photo::getImagesPath ()
{
    return getContentsPath() + QString("/images");
}

QString Photo::getSaveFileName(int width, int height)
{
    return getImagesPath() + QString("/") + QString::number(width) + QString("x") + QString::number(height) + QString(".jpg");
}

QString Photo::getMetadataFileName()
{
    return getSavePath() + QString("/metadata.desktop");
}

QString Photo::getScreenshotFileName()
{
    return getContentsPath() + QString("/screenshot.jpg");
}

bool Photo::isLocal()
{
    QFile meta(getMetadataFileName());
    return meta.exists();
}

void Photo::setId(QString id)
{
    this->id = id;
    emit idChanged(id);
}

void Photo::setWidth(int width)
{
    this->width = width;
    emit widthChanged(width);
}

void Photo::setHeight(int height)
{
    this->height = height;
    emit heightChanged(height);
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
