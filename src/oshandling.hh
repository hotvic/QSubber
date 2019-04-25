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

#include "config.h"

#include "subdata.hh"
#include "httptransport.hh"
#include "rest.hh"

#include <QtCore>

#ifndef OSHANDLING_H
#define OSHANDLING_H

using namespace std;

namespace QSubber
{
    class OSHandling : public QObject
    {
        Q_OBJECT

        Rest rest;
        QString token;

        void queueCall(QString name=QString(), QVariantList args=QVariantList());
        void postLogIn();
        void postSearch();
        void postSubLanguages();

    public:
        OSHandling(QObject* parent=nullptr);
        bool isLoggedIn();
        void LogIn(QString username, QString password);
        void fetchSubLanguages(QString locale = QString());
        void Search(QVariantMap& params);

    private slots:
        void doneSearching(QVariantList subs);
    };
}

#endif // OSHANDLING_H
