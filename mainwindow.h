#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "loginscreen.h"
#include "state.h"
#include "menuscreen.h"
#include <QSqlDatabase>
#include "userrepository.h"
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    UserRepository userRepository;
    State appState;
    Controller *appController = nullptr;
    LoginScreen *loginScreen = nullptr;
    MenuScreen *menuScreen = nullptr;
};
#endif // MAINWINDOW_H
