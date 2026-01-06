#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include "state.h"
#include "userrepository.h"
#include "controller.h"
#include <QWidget>

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(QWidget *parent, State *appState, UserRepository userRepository, Controller *appController);
    ~LoginScreen();

private:
    Ui::LoginScreen *ui;
    State *appState;
    UserRepository userRepository;
    Controller *appController;
private slots:
    void handleSubmitForm();
};

#endif // LOGINSCREEN_H
