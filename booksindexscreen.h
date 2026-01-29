#ifndef BOOKSINDEXSCREEN_H
#define BOOKSINDEXSCREEN_H

#include <QWidget>
#include <QSqlTableModel>
#include "bookrepository.h"
#include "controller.h"

namespace Ui {
class BooksIndexScreen;
}

class BooksIndexScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BooksIndexScreen(QWidget *parent, QSqlDatabase db, Controller *appController);
    ~BooksIndexScreen();

private:
    Ui::BooksIndexScreen *ui;
    QSqlDatabase db;
    Controller *appController;

    QSqlTableModel *model;
    bool readyForCreateRow;

private slots:
    void handleBackButtonClick();
    void handleDeleteRowsButtonClick();
    void handleAddRowButtonClick();
    void handleRefreshButtonClick();
};

#endif // BOOKSINDEXSCREEN_H
