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

#include "oshandling.hh"

#include "application.hh"
#include "utils.hh"

namespace QSubber
{
OSHandling::OSHandling(QObject *parent) : QObject(parent)
, m_rest(REST_URL, USER_AGENT)
{
  connect(&this->m_rest, &Rest::doneLogin, this, &OSHandling::doneLogin);
  connect(&this->m_rest, &Rest::doneSearch, this, &OSHandling::doneSearching);
}

void OSHandling::Search(QVariantMap& params)
{
  Application* app = dynamic_cast<Application*>(qApp);

  app->updateStatus("Searching...");

  dynamic_cast<Application*>(qApp)->setCurrentJob("Search");

  params["sublanguageid"] = app->settings->getConfig("current_lang", "all");

  this->m_rest.search(params);
}

void OSHandling::fetchSubLanguages(QString locale)
{
  // TODO: Fix me with REST
  Application* app = static_cast<Application*>(qApp);

  if (locale.isEmpty()) locale = app->settings->getConfig("current_locale", "en");

  if (!app->settings->hasLocale(locale))
  {
    QVariantList paramList;

    paramList.append(locale);

    // queueCall("GetSubLanguages", paramList);
  }
}

void OSHandling::login(QString username, QString password)
{
  this->m_rest.login(username, password);
}

void OSHandling::doneLogin(QVariantMap data)
{
  bool result = data.value("success").toInt() == 1;

  emit loginResult(result, result ? data.value("session_id").toString() : "");
}

void OSHandling::postSubLanguages()
{
  //  Application* app = static_cast<Application*>(qApp);

  //  QVariantList data = reply.get("params.0.data").toList();

  //  for (int i = 0; i < data.size(); ++i)
  //  {
  //    QVariantMap lang = data.at(i).toMap();
  //    QString locale = app->settings->getConfig("current_locale", "en");

  //    app->settings->setLangCode(locale,
  //                               lang["SubLanguageID"].toString(),
  //        lang["LanguageName"].toString());
  //  }
}

void OSHandling::doneSearching(QVariantList subs)
{
  qDebug() << subs;

  dynamic_cast<Application*>(qApp)->popCurrentJob();

  Application* app = static_cast<Application*>(qApp);

  if (subs.isEmpty())
  {
    app->setSubList(subs);
    app->updateStatus("Searching... done. No Results!", 1500);
    return;
  }

  app->setSubList(subs);

  app->updateStatus("Searching... done!", 1500);
}
}
