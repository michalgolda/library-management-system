#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include "state.h"

namespace Ui {
class LoginScreen;
}

class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit LoginScreen(State appState, QWidget *parent = nullptr);
    ~LoginScreen();

private:
    Ui::LoginScreen *ui;
    State appState;
private slots:
    void handleSubmitForm();
};

#endif // LOGINSCREEN_H
