#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>
#include "controller.h"

namespace Ui {
class MenuScreen;
}

class MenuScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MenuScreen(QWidget *parent, Controller *appController);
    ~MenuScreen();

public slots:
    void handleQuitButton();
    void handleBooksIndexPageButton();
    void handleReaderCardsPageButton();
    void handleBorrowingsPageButton();

private:
    Ui::MenuScreen *ui;
    Controller *appController;
};

#endif // MENUSCREEN_H
