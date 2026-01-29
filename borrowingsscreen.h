#ifndef BORROWINGSSCREEN_H
#define BORROWINGSSCREEN_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include "controller.h"
#include <QSqlQueryModel>

namespace Ui {
class BorrowingsScreen;
}

class BorrowingsScreen : public QWidget
{
    Q_OBJECT

public:
    explicit BorrowingsScreen(QWidget *parent, QSqlDatabase db, Controller *appController);
    ~BorrowingsScreen();

private:
    Ui::BorrowingsScreen *ui;
    Controller *appController;
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQueryModel *borrowingsModel;
    bool showingBorrowings;

    bool selectingReader;
    int selectedReaderId;

private slots:
    void handleBackButtonClick();
    void handleNextButtonClick();
    void handleConfirmButtonClick();
    void handleDeleteButtonClick();
};

#endif // BORROWINGSSCREEN_H
