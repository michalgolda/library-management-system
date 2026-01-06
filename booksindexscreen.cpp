#include "booksindexscreen.h"
#include "ui_booksindexscreen.h"

BooksIndexScreen::BooksIndexScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BooksIndexScreen)
{
    ui->setupUi(this);
}

BooksIndexScreen::~BooksIndexScreen()
{
    delete ui;
}
