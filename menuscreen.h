#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>

namespace Ui {
class MenuScreen;
}

class MenuScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MenuScreen(QWidget *parent = nullptr);
    ~MenuScreen();

private:
    Ui::MenuScreen *ui;
};

#endif // MENUSCREEN_H
