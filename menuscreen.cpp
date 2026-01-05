#include "menuscreen.h"
#include "ui_menuscreen.h"

MenuScreen::MenuScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuScreen)
{
    ui->setupUi(this);
}

MenuScreen::~MenuScreen()
{
    delete ui;
}
