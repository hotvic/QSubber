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

#pragma once

#include "httptransport.hh"

#include <QObject>

namespace QSubber
{
class Rest : public QObject
{
  Q_OBJECT

public:
  Rest(QString url, QString ua);

  void login(QString username, QString password);
  void search(QVariantMap params);

protected:
  void handleLogin(QByteArray data);
  void handleSearch(QByteArray data);

private:
  HttpTransport m_transport;
  QString m_url;

signals:
  void doneLogin(QVariantMap data);
  void doneSearch(QVariantList subs);

private slots:
    void proccessReply(QUrl url, QByteArray data);
};
}
