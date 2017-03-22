#ifndef PHOTO_H
#define PHOTO_H

#include <QJsonObject>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>

class Photo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged)

    Q_PROPERTY(QUrl rawUrl READ getRawUrl WRITE setRawUrl NOTIFY rawUrlChanged)
    Q_PROPERTY(QUrl fullUrl READ getFullUrl WRITE setFullUrl NOTIFY fullUrlChanged)
    Q_PROPERTY(QUrl regularUrl READ getRegularUrl WRITE setRegularUrl NOTIFY regularUrlChanged)
    Q_PROPERTY(QUrl smallUrl READ getSmallUrl WRITE setSmallUrl NOTIFY smallUrlChanged)
    Q_PROPERTY(QUrl thumbUrl READ getThumbUrl WRITE setThumbUrl NOTIFY thumbUrlChanged)

    Q_PROPERTY(QUrl apiUrl READ getApiUrl WRITE setApiUrl NOTIFY apiUrlChanged)
    Q_PROPERTY(QUrl pageUrl READ getPageUrl WRITE setPageUrl NOTIFY pageUrlChanged)
    Q_PROPERTY(QUrl downloadUrl READ getDownloadUrl WRITE setDownloadUrl NOTIFY downloadUrlChanged)

    Q_PROPERTY(QString userFullName READ getUserFullName WRITE setUserFullName NOTIFY userFullNameChanged)

    Q_PROPERTY(QJsonObject json READ getJson NOTIFY jsonChanged)

public:
    explicit Photo(QObject *parent = 0);
    explicit Photo(QJsonObject json, QObject *parent = 0);

    QString getId();
    QUrl getRawUrl();
    QUrl getFullUrl();
    QUrl getRegularUrl();
    QUrl getSmallUrl();
    QUrl getThumbUrl();
    QUrl getApiUrl();
    QUrl getPageUrl();
    QUrl getDownloadUrl();
    QString getUserFullName();
    QJsonObject getJson();

    void setId(QString id);
    void setRawUrl(QUrl rawUrl);
    void setFullUrl(QUrl fullUrl);
    void setRegularUrl(QUrl regularUrl);
    void setSmallUrl(QUrl smallUrl);
    void setThumbUrl(QUrl thumbUrl);
    void setApiUrl(QUrl apiUrl);
    void setPageUrl(QUrl pageUrl);
    void setDownloadUrl(QUrl downloadUrl);
    void setUserFullName(QString userFullName);

signals:
    void idChanged(QString id);
    void rawUrlChanged(QUrl rawUrl);
    void fullUrlChanged(QUrl fullUrl);
    void regularUrlChanged(QUrl regularUrl);
    void smallUrlChanged(QUrl smallUrl);
    void thumbUrlChanged(QUrl thumbUrl);

    void apiUrlChanged(QUrl apiUrl);
    void pageUrlChanged(QUrl pageUrl);
    void downloadUrlChanged(QUrl downloadUrl);

    void userFullNameChanged(QString userFullName);

    void jsonChanged(QJsonObject json);

    void wallpaperSaved();

public slots:
    void saveAsWallpaper();
    void download();

private:
    QString id;
    QUrl rawUrl;
    QUrl fullUrl;
    QUrl regularUrl;
    QUrl smallUrl;
    QUrl thumbUrl;
    QUrl apiUrl;
    QUrl pageUrl;
    QUrl downloadUrl;
    QString userFullName;
    QJsonObject json;
};

#endif // PHOTO_H
