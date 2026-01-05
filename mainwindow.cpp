#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include "state.h"
#include "loginscreen.h"
#include "userrepository.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), db(QSqlDatabase::addDatabase("QSQLITE")), userRepository(db), appState(State())
{
    ui->setupUi(this);

    QString databaseName = QDir::currentPath() + QString("/main.sqlite");
    db.setDatabaseName(databaseName);
    db.open();

    QStringList schema = {
        R"(
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT NOT NULL UNIQUE,
                password TEXT NOT NULL
            )
        )"
    };
    QSqlQuery schemaQuery;
    for (const QString& sql : schema) {
        if (!schemaQuery.exec(sql)) {
            qDebug() << schemaQuery.lastError().text();
        }
    }

    loginScreen = new LoginScreen(appState, this);
    menuScreen = new MenuScreen(this);

    ui->stackedWidget->addWidget(loginScreen);
    ui->stackedWidget->addWidget(menuScreen);

    std::optional<UserEntity> user = userRepository.getByUsername("admin");
    if (!user.has_value())
    {
        UserEntity user;
        user.username = "admin";
        user.password = "admin";

        std::optional<int> createdUserId = userRepository.create(user);
        if (!createdUserId.has_value())
        {
            qDebug() << "Wystąpił nieoczekiwany problem podczas tworzenia konta administratora.";
        }
    } else
    {
        qDebug() << "Konto administratora już istnieje.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
