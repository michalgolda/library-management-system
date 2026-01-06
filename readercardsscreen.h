#ifndef READERCARDSSCREEN_H
#define READERCARDSSCREEN_H

#include <QWidget>

namespace Ui {
class ReaderCardsScreen;
}

class ReaderCardsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit ReaderCardsScreen(QWidget *parent = nullptr);
    ~ReaderCardsScreen();

private:
    Ui::ReaderCardsScreen *ui;
};

#endif // READERCARDSSCREEN_H
