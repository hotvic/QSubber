/*
 * This file is part of QSubber.
 *
 * QSubber is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QSubber is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QSubber.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtCore>
#include <QDomDocument>
#include <QDomElement>
#include <QtNetwork>

#ifndef QSUBBER_XMLRPC
#define QSUBBER_XMLRPC

namespace QSubber
{
class HttpTransport : public QObject
{
  Q_OBJECT

  QNetworkAccessManager manager;
  QString useragent;

public:
  HttpTransport(QString useragent = QString());

  QString getUserAgent();
  void    setUserAgent(QString useragent);

  void get(QUrl url);
  void post(QUrl url, QByteArray data);

signals:
  void dataReady(QUrl url, QByteArray data);
  void replyFinished(QUrl url, QByteArray data);

private slots:
  void on_manager_finished(QNetworkReply* reply);
  void on_reply_error(QNetworkReply::NetworkError code);
  void on_reply_readyRead();
  void on_reply_downloadProgress(qint64 total, qint64 done);
};
}

#endif /* QSUBBER_XMLRPC */
