#include <thread>
#include "subdownloader.h"
#include "config.h"

SubDownloader::SubDownloader(QObject *parent) : QObject(parent)
  , manager(this)
{
    request.setRawHeader("User-Agent", USER_AGENT);
}

void SubDownloader::Download(QUrl url, QString destfile, qint64 filesize) {
    request.setUrl(url);
    this->currentSize = filesize;
    this->currentFile = destfile;

    reply = manager.get(request);

    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error),
                     this, &SubDownloader::replyError);
    QObject::connect(reply, &QNetworkReply::downloadProgress, this, &SubDownloader::downloadProgress);
    QObject::connect(reply, &QNetworkReply::finished, this, &SubDownloader::replyFinished);
}

/* Slots */
void SubDownloader::replyError(QNetworkReply::NetworkError err) {
    qDebug() << err;
    reply->deleteLater();
}

void SubDownloader::downloadProgress(qint64 br, qint64 bt) {
    int timeout = 0;

    if (bt != Q_INT64_C(-1))
        this->currentSize = bt;

    QString status;
    if (this->currentSize > Q_INT64_C(0)) {
        qint64 progress = (br / this->currentSize) * 100;
        if(progress == Q_INT64_C(100)) timeout = 1500;

        status = QString::asprintf("Downloading... %lld%%", progress);
    }
    else {
        status = QString::asprintf("Downloading... %lld bytes", br);
    }

    emit update_status(status, timeout);
}

void SubDownloader::replyFinished() {
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }

    QByteArray subfile = reply->readAll();

    QFile outfile(this->currentFile);
    if(outfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        outfile.write(subfile);
        outfile.close();
    } else {
        qDebug() << "Failed to open " << this->currentFile << ":" << outfile.error();
    }
}