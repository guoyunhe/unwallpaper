#ifndef PHOTOLIST_H
#define PHOTOLIST_H

#include <QObject>

class PhotoList : public QObject
{
    Q_OBJECT
public:
    explicit PhotoList(QObject *parent = 0);

signals:

public slots:
};

#endif // PHOTOLIST_H
