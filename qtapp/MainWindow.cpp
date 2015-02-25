#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QtWebKitWidgets/QWebFrame>
#include <QtWebKitWidgets/QWebInspector>

#include <QUrl>

// Подключаем заголовок нашего класса Host
#include "Host.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // Получаем указатель на главный фрейм нашего WebView
  QWebFrame* mainFrame = ui->webView->page()->mainFrame();

  //QString applicationDirPath = QApplication::applicationDirPath();
  QString webAppRootDirPath = "/Users/serge/Projects/Personal/artem_samarov/webapp";
  QUrl url = QUrl::fromLocalFile(webAppRootDirPath + "/index.html");

  qDebug() << "URL:" << url;

  mainFrame->setUrl(url);

  // "Регистрируем" этот фрейм
  registerFrame(mainFrame);

  // Разрешаем использование веб инспектора
  ui->webView->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

  // Создаем и показываем окно веб инспектора
  m_webInspector = new QWebInspector();
  m_webInspector->setPage(ui->webView->page());
  m_webInspector->show();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::registerFrame(QWebFrame *frame)
{
  // Создаем объект класса Host
  Host *host = new Host(frame);
  // просим этот объект привязаться к фрейму
  host->setWebFrame(frame);

  // Хитрым способом сохраняем указатель на host
  // в объекте фрейма
  QObject *hostObject = host;
  QVariant hostObjectV = QVariant::fromValue(hostObject);
  frame->setProperty("hostObject", hostObjectV);

  // Привязываем событие фрейма javaScriptWindowObjectCleared
  // к нашему обработчику. Мы не можем встроить наш объект Host
  // в фрейм в любой момент, нужно подождать, когда он будет готов.
  // Именно для этого мы подцепляемся к нужному сигналу.
  connect(frame, SIGNAL(javaScriptWindowObjectCleared()),
          this, SLOT(frameJavaScriptWindowObjectCleared()));
}

void MainWindow::frameJavaScriptWindowObjectCleared()
{
  // Извлекаем указатель на host, хитрым образом сохраненный
  // в методе registerFrame
  QVariant v = sender()->property("hostObject");
  QObject* hostObject = v.value<QObject*>();
  Host *host = qobject_cast<Host*>(hostObject);

  // Вызываем функцию прикрепления. По факту, мы встраиваем
  // интерфейс объекта Host в JavaScript окружение доступное
  // в нашем фрейме.
  host->attachObject();
}
