#ifndef HOST_H
#define HOST_H

#include <QObject>

class QWebFrame;

class Host : public QObject
{
  Q_OBJECT
public:
  explicit Host(QObject *parent = 0);
  ~Host();
  void setWebFrame(QWebFrame* frame);
  void attachObject();

signals:

public slots:
  void debug(const QString &message);
  void processCellClick(const QString &name, const QString &distance);

private:
  QWebFrame* m_frame;


};

#endif // HOST_H
