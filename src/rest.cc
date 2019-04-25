#include "rest.hh"

namespace QSubber
{
Rest::Rest(QString url, QString ua)
  : m_transport(ua)
{
  this->m_url = url;

  connect(&this->m_transport, &HttpTransport::replyFinished, this, &Rest::proccessReply);
}

void Rest::search(QVariantMap params)
{
  if (params.empty()) {
    qWarning() << "Can't search without params!";
  }

  QList<QString> components;

  QVariantMap::const_iterator it;
  for (it = params.constBegin(); it != params.constEnd(); ++it)
  {
    QString comp(it.key());
    comp.push_back('-');

    if (comp == "moviebytesize-")
    {
      comp.push_back(QString::number(it.value().toLongLong()));
    }
    else if (comp == "moviehash-" || comp == "query-" || comp == "sublanguageid-" || comp == "episode-"
             || comp == "season-")
    {
      comp.push_back(QUrl::toPercentEncoding(it.value().toString()));
    }

    components.append(comp);
  }

  components.sort();

  qDebug() << "Path components:" << components;

  QUrl url(this->m_url);

  url.setPath(QString("/search/") + components.join("/"));

  qDebug() << url.toString();

  this->m_transport.get(url);
}

void Rest::handleSearch(QByteArray data)
{
  QJsonParseError err;

  if (data.isEmpty()) {
    qDebug() << "Empty response from server";
    return;
  }

  auto doc = QJsonDocument::fromJson(data, &err);

  if (doc.isNull()) {
    qDebug() << "Json Parsing Error:" << err.errorString();
    qDebug() << "Invalid Json:" << data;

    return;
  }

  if (doc.isArray())
  {
    emit doneSearch(doc.array().toVariantList());
  }
  else
  {
    qWarning() << "Unknown reply from server!";
  }
}

void Rest::proccessReply(QUrl url, QByteArray data)
{
  qDebug() << "Got reply from:" << url.toString();

  if (url.path().startsWith("/search"))
  {
    this->handleSearch(data);
  }
}
}
