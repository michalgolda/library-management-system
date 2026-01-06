#ifndef BOOKSINDEXSCREEN_H
#define BOOKSINDEXSCREEN_H

#include <QWidget>

namespace Ui {
class BooksIndexScreen;
}

class BooksIndexScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BooksIndexScreen(QWidget *parent);
    ~BooksIndexScreen();

private:
    Ui::BooksIndexScreen *ui;
};

#endif // BOOKSINDEXSCREEN_H
