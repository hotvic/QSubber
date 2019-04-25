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
, rest(REST_URL, USER_AGENT)
{
  connect(&rest, &Rest::doneSearch, this, &OSHandling::doneSearching);
}

bool OSHandling::isLoggedIn()
{
  if (token.isEmpty()) return false;

  return true;
}

void OSHandling::queueCall(QString name, QVariantList args)
{
  // TODO: Fix this or delete if uneeded any more.
//  typedef struct
//  {
//    QString name;
//    QVariantList args;
//    bool working;
//  } MethodCall;

//  static QQueue<MethodCall> queue;

//  if (!name.isNull())
//  {
//    MethodCall call { name, args, false };
//    queue.enqueue(call);

//    if (queue.size() == 1) queueCall();
//  }
//  else {
//    if (queue.isEmpty()) return;

//    MethodCall* call = &queue.head();

//    if (call->working)
//    {
//      queue.dequeue();
//      queueCall();
//    }
//    else {
//      call->working = true;

//      rpc.Call(call->name, call->args);

//      static_cast<Application*>(qApp)->setCurrentJob(call->name);
//    }
//  }
}

void OSHandling::Search(QVariantMap& params)
{
  Application* app = dynamic_cast<Application*>(qApp);

  app->updateStatus("Searching...");

  // dynamic_cast<Application*>(qApp)->setCurrentJob("Search");

  params["sublanguageid"] = app->settings->getConfig("current_lang", "all");

  rest.search(params);
}

void OSHandling::fetchSubLanguages(QString locale)
{
  Application* app = static_cast<Application*>(qApp);

  if (locale.isEmpty()) locale = app->settings->getConfig("current_locale", "en");

  if (!app->settings->hasLocale(locale))
  {
    QVariantList paramList;

    paramList.append(locale);

    queueCall("GetSubLanguages", paramList);
  }
}

void OSHandling::LogIn(QString username, QString password)
{
  Application* app = static_cast<Application*>(qApp);

  app->updateStatus("Logging in...");

  QVariantList args;

  args << username;
  args << password;
  args << QString("eng");
  args << QString(USER_AGENT);

  queueCall("LogIn", args);
}

void OSHandling::postLogIn()
{
//  Application* app = static_cast<Application*>(qApp);

//  if (reply.get("params.0.status") == "200 OK")
//  {
//    qDebug() << "Logged in, token:" << reply.get("params.0.token").toString();

//    token = reply.get("params.0.token").toString();

//    app->updateStatus("Logged in!!!", 3000);
//  }
//  else {
//    QString status("Failed to login, server error: %0");

//    app->updateStatus(status.arg(reply.get("params.0.status").toString()));
//  }
}

void OSHandling::postSearch()
{
//  Application* app = static_cast<Application*>(qApp);

//  if (reply.get("params.0.status") == "200 OK")
//  {
//    QVariantList data = reply.get("params.0.data").toList();

//    if (data.isEmpty())
//    {
//      app->setSubList(QVariantList());
//      app->updateStatus("Searching... done. No Results!", 1500);
//      return;
//    }

//    app->setSubList(data);
//  }

//  app->updateStatus("Searching... done!", 1500);
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

  Application* app = static_cast<Application*>(qApp);

  if (subs.isEmpty())
  {
    app->setSubList(QVariantList());
    app->updateStatus("Searching... done. No Results!", 1500);
    return;
  }

  app->setSubList(subs);

  app->updateStatus("Searching... done!", 1500);
}
}
