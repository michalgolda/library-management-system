#include "loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(State appState, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginScreen), appState(appState)
{
    ui->setupUi(this);

    connect(ui->submitButton, &QPushButton::clicked, this, &LoginScreen::handleSubmitForm);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::handleSubmitForm()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    qDebug() << "Nazwa użytkownika: " << username;
    qDebug() << "Hasło: " << password;
    qDebug() << "Zalogowany: " << this->appState.isAuthenticated();
}
