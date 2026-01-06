#include <QSqlDatabase>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QCloseEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "state.h"
#include "loginscreen.h"
#include "userrepository.h"
#include "schema.h"
#include "controller.h"
#include "booksindexscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), db(QSqlDatabase::addDatabase("QSQLITE")), userRepository(db), appState(State())
{
    ui->setupUi(this);
    appController = new Controller(ui->stackedWidget);

    QString databaseName = QDir::currentPath() + QString("/main.sqlite");
    db.setDatabaseName(databaseName);
    db.open();

    initSchema(db);

    menuScreen = new MenuScreen(this, appController);
    loginScreen = new LoginScreen(this, &appState, userRepository, appController);
    booksIndexScreen = new BooksIndexScreen(this);
    readerCardsScreen = new ReaderCardsScreen(this);

    appController->registerScreen(ScreenId::Menu, menuScreen);
    appController->registerScreen(ScreenId::Login, loginScreen);
    appController->registerScreen(ScreenId::BooksIndex, booksIndexScreen);
    appController->registerScreen(ScreenId::ReaderCards, readerCardsScreen);


    appController->goTo(ScreenId::Login);

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
    delete appController;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    const auto result = QMessageBox::question(
        this,
        "Zamykanie aplikacji",
        "Czy na pewno chcesz zamknąć aplikację?"
        );

    if (result == QMessageBox::Yes) {
        event->accept();
    } else {
        event->ignore();
    }
}
