#include <QMessageBox>
#include "menuscreen.h"
#include "ui_menuscreen.h"

MenuScreen::MenuScreen(QWidget *parent, Controller *appController)
    : QWidget(parent)
    , ui(new Ui::MenuScreen), appController(appController)
{
    ui->setupUi(this);

    connect(ui->quitButton, &QPushButton::clicked, this, &MenuScreen::handleQuitButton);
    connect(ui->booksIndexPageButton, &QPushButton::clicked, this, &MenuScreen::handleBooksIndexPageButton);
    connect(ui->readerCardsPageButton, &QPushButton::clicked, this, &MenuScreen::handleReaderCardsPageButton);
    connect(ui->borrowingsPageButton, &QPushButton::clicked, this, &MenuScreen::handleBorrowingsPageButton);
}

MenuScreen::~MenuScreen()
{
    delete ui;
}

void MenuScreen::handleQuitButton()
{
    QApplication::quit();
}

void MenuScreen::handleBooksIndexPageButton()
{
    appController->goTo(ScreenId::BooksIndex);
}

void MenuScreen::handleReaderCardsPageButton()
{
    appController->goTo(ScreenId::ReaderCards);
}

void MenuScreen::handleBorrowingsPageButton()
{
    appController->goTo(ScreenId::Borrowings);
}
