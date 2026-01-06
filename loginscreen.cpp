#include <QMessageBox>
#include "loginscreen.h"
#include "ui_loginscreen.h"


LoginScreen::LoginScreen(QWidget *parent, State *appState, UserRepository userRepository, Controller *appController)
    : QWidget(parent)
    , ui(new Ui::LoginScreen), appState(appState), userRepository(userRepository), appController(appController)
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

    std::optional<UserEntity> existingUser = userRepository.getByUsername(username);
    if (!existingUser.has_value())
    {
        QMessageBox::information(this, "Logowanie", "Użytkownik o podanej nazwie użytkownika nie istnieje.");
        return;
    }

    bool passwordIsValid = existingUser->validatePassword(password);
    if (!passwordIsValid)
    {
        QMessageBox::information(this, "Logowanie", "Podane hasło jest nieprawidłowe.");
        return;
    }

    appState->setCurrentUser(existingUser);
    appController->goTo(ScreenId::Menu);

    qDebug() << "Nazwa użytkownika: " << username;
    qDebug() << "Hasło: " << password;
    qDebug() << "Zalogowany: " << appState->isAuthenticated();
    qDebug() << "Indeks aktualnej strony: " << appController->getCurrentPageIndex();
}
