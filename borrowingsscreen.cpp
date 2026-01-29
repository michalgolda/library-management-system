#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include "borrowingsscreen.h"
#include "ui_borrowingsscreen.h"
#include "controller.h"
#include <QSqlQuery>
#include <QSqlError>

BorrowingsScreen::BorrowingsScreen(QSqlDatabase &db, Controller *appController, QWidget *parent)
    : QWidget(parent), ui(new Ui::BorrowingsScreen), db(db), appController(appController)
{
    ui->setupUi(this);

    selectingReader = true;
    selectedReaderId = -1;

    model = new QSqlTableModel(this, db);
    borrowingsModel = new QSqlQueryModel(this);
    showingBorrowings = false;
    model->setTable("readercards");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->hideColumn(0);

    connect(ui->backButton, &QPushButton::clicked,
            this, &BorrowingsScreen::handleBackButtonClick);

    connect(ui->nextButton, &QPushButton::clicked,
            this, &BorrowingsScreen::handleNextButtonClick);

    connect(ui->confirmButton, &QPushButton::clicked,
            this, &BorrowingsScreen::handleConfirmButtonClick);
    connect(ui->deleteButton, &QPushButton::clicked,
            this, &BorrowingsScreen::handleDeleteButtonClick);

    ui->confirmButton->setEnabled(false);
}

void BorrowingsScreen::handleBackButtonClick()
{
    if (showingBorrowings) {
        showingBorrowings = false;
        selectingReader = true;
        selectedReaderId = -1;

        model->setFilter("");
        model->setTable("readercards");
        model->select();

        ui->tableView->setModel(model);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableView->hideColumn(0);

        ui->confirmButton->setEnabled(false);
        ui->nextButton->setEnabled(true);

        ui->deleteButton->setText("Usuwanie");

        return;
    }

    appController->goTo(ScreenId::Menu);
}

void BorrowingsScreen::handleDeleteButtonClick()
{
    if (!showingBorrowings) {
        showingBorrowings = true;

        borrowingsModel->setQuery(
            "SELECT "
            "  borrowings.id, "
            "  books.title, "
            "  readercards.firstName, "
            "  readercards.lastName, "
            "  readercards.email "
            "FROM borrowings "
            "JOIN books ON books.id = borrowings.book_id "
            "JOIN readercards ON readercards.id = borrowings.readercard_id "
            "ORDER BY borrowings.id DESC",
            db
            );

        ui->tableView->setModel(borrowingsModel);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

        ui->tableView->hideColumn(0);

        ui->confirmButton->setEnabled(false);
        ui->nextButton->setEnabled(false);

        return;
    }

    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "Informacja", "Zaznacz wypożyczenia do usunięcia.");
        return;
    }

    for (const QModelIndex &idx : selectedRows) {
        int row = idx.row();

        int borrowingId = borrowingsModel->data(borrowingsModel->index(row, 0)).toInt();

        QSqlQuery query(db);
        query.prepare("DELETE FROM borrowings WHERE id = ?");
        query.addBindValue(borrowingId);

        if (!query.exec()) {
            QMessageBox::warning(this, "Błąd", "Nie udało się usunąć wypożyczenia.\n" + query.lastError().text());
            return;
        }
    }

    borrowingsModel->setQuery(
        "SELECT "
        "  borrowings.id, "
        "  books.title, "
        "  readercards.firstName, "
        "  readercards.lastName, "
        "  readercards.email "
        "FROM borrowings "
        "JOIN books ON books.id = borrowings.book_id "
        "JOIN readercards ON readercards.id = borrowings.readercard_id "
        "ORDER BY borrowings.id DESC",
        db
        );
}

void BorrowingsScreen::handleNextButtonClick()
{
    QModelIndexList selectedRows =
        ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "Informacja", "Zaznacz czytelnika.");
        return;
    }

    int row = selectedRows.first().row();
    selectedReaderId = model->index(row, 0).data().toInt();

    selectingReader = false;

    model->setTable("books");
    model->setFilter("id NOT IN (SELECT book_id FROM borrowings)");
    model->select();

    ui->tableView->clearSelection();
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->hideColumn(0);

    ui->confirmButton->setEnabled(true);
    ui->nextButton->setEnabled(false);
}
void BorrowingsScreen::handleConfirmButtonClick()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();

    if (selectedRows.isEmpty()) {
        QMessageBox::information(this, "Informacja", "Zaznacz książkę lub książki.");
        return;
    }

    int insertedCount = 0;

    for (const QModelIndex &idx : selectedRows) {
        int row = idx.row();
        int bookId = model->index(row, 0).data().toInt();

        QSqlQuery query(db);
        query.prepare("INSERT INTO borrowings (book_id, readercard_id) VALUES (:book_id, :readercard_id)");
        query.bindValue(":book_id", bookId);
        query.bindValue(":readercard_id", selectedReaderId);

        if (!query.exec()) {
            QMessageBox::warning(
                this,
                "Błąd",
                "Nie udało się dodać wypożyczenia.\n" + query.lastError().text()
                );
            return;
        }

        insertedCount++;
    }

    QMessageBox::information(this, "Informacja", "Dodano wypożyczenia: " + QString::number(insertedCount));
    selectingReader = true;
    selectedReaderId = -1;

    model->setTable("readercards");
    model->select();

    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->hideColumn(0);

    ui->confirmButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
}
BorrowingsScreen::~BorrowingsScreen()
{
    delete ui;
}
