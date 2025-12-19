#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QString databaseName = QDir::currentPath() + QString("/main.sqlite");
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    bool dbIsOpen = db.open();

    qDebug() << "Database open result: " << dbIsOpen;
    qDebug() << databaseName;
}

MainWindow::~MainWindow()
{
    delete ui;
}
