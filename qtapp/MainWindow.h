#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QWebFrame;
class QWebInspector;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QWebInspector *m_webInspector;
  void registerFrame(QWebFrame *frame);

private slots:
  void frameJavaScriptWindowObjectCleared();
};

#endif // MAINWINDOW_H
