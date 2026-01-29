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
    explicit BorrowingsScreen(QSqlDatabase &db, Controller *appController, QWidget *parent = nullptr);
    ~BorrowingsScreen();

private:
    Ui::BorrowingsScreen *ui;
    Controller *appController;
    QSqlDatabase &db;
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
