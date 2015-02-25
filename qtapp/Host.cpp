#include "Host.h"

#include <QDebug>
#include <QtWebKitWidgets/QWebFrame>

Host::Host(QObject *parent) : QObject(parent)
{
  // Инициализируем указатели
  m_frame = 0;
}

Host::~Host()
{

}

void Host::setWebFrame(QWebFrame *frame)
{
  m_frame = frame;
}

void Host::attachObject()
{
  if (m_frame)
  {
    m_frame->addToJavaScriptWindowObject(QString("Host"), this);
  }
}

void Host::debug(const QString &message)
{
  qDebug() << "JS-DEBUG> " << message;
}

void Host::processCellClick(const QString &name, const QString &distance)
{
  qDebug() << "CELL CLICK. NAME = > " << name << "; DISTANCE = " << distance << ";";
}

