#include "readercardsscreen.h"
#include "ui_readercardsscreen.h"

ReaderCardsScreen::ReaderCardsScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReaderCardsScreen)
{
    ui->setupUi(this);
}

ReaderCardsScreen::~ReaderCardsScreen()
{
    delete ui;
}
