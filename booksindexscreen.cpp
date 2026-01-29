#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QAbstractItemView>
#include <QStyledItemDelegate>
#include "booksindexscreen.h"
#include "ui_booksindexscreen.h"
#include "controller.h"
#include "bookrepository.h"

BooksIndexScreen::BooksIndexScreen(QWidget *parent, QSqlDatabase db, Controller *appController)
    : QWidget(parent)
    , ui(new Ui::BooksIndexScreen), db(db), appController(appController), readyForCreateRow(false)
{
    ui->setupUi(this);

    ui->backButton->setToolTip("Powrót do głównego ekranu");
    connect(ui->backButton, &QPushButton::clicked, this, &BooksIndexScreen::handleBackButtonClick);

    ui->deleteRowsButton->setToolTip("Usuwa zaznaczone wiersze");
    connect(ui->deleteRowsButton, &QPushButton::clicked, this, &BooksIndexScreen::handleDeleteRowsButtonClick);


    ui->addRowButton->setToolTip("Dodaje pusty wiersz a ponowne kliknięcie dodaje nowy rekord");
    connect(ui->addRowButton, &QPushButton::clicked, this, &BooksIndexScreen::handleAddRowButtonClick);

    ui->refreshButton->setToolTip("Odświeża dane w tabeli");
    connect(ui->refreshButton, &QPushButton::clicked, this, &BooksIndexScreen::handleRefreshButtonClick);

    model = new QSqlTableModel(this, db);
    model->setTable("books");
    model->select();

    model->setHeaderData(0, Qt::Horizontal, "ID");
    model->setHeaderData(1, Qt::Horizontal, "Tytuł");
    model->setHeaderData(2, Qt::Horizontal, "Opis");
    model->setHeaderData(3, Qt::Horizontal, "Ilość stron");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->hideColumn(0);
}

BooksIndexScreen::~BooksIndexScreen()
{
    delete ui;
}

void BooksIndexScreen::handleBackButtonClick()
{
    appController->goTo(ScreenId::Menu);
}

void BooksIndexScreen::handleDeleteRowsButtonClick()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    int selectedIndexesLength = selectedIndexes.length();
    if (selectedIndexesLength == 0)
    {
        QMessageBox::information(this, "Usuwanie wierszy", "Zaznacz wiersze, które chcesz usunąć");
        return;
    } else {
        const auto result = QMessageBox::question(
            this,
            "Usuwanie wierszy",
            QString("Czy na pewno chcesz usunąć %1 wiersz/y?").arg(selectedIndexesLength)
        );

        if (result == QMessageBox::Yes) {
            for (const QModelIndex &index : selectedIndexes)
            {
                int row = index.row();
                model->removeRow(row);
            }

            model->submitAll();
            model->select();
        } else {
            return;
        }
    }

}

void BooksIndexScreen::handleAddRowButtonClick()
{
    if (!readyForCreateRow)
    {
        int row = model->rowCount();
        model->insertRow(row);
        readyForCreateRow = true;
        return;
    }

    const auto result = QMessageBox::question(
        this,
        "Dodawanie wiersza",
        "Czy na pewno chcesz dodać wiersz?"
    );

    if (result == QMessageBox::Yes) {
        if (!model->submitAll())
        {
            QMessageBox::warning(
                this,
                "Dodawanie wiersza",
                "Wystąpił błąd podczas dodawania nowego wiersza, sprawdź dane i spróbuj ponownie."
            );
            return;
        }

        model->select();
        readyForCreateRow = false;
    }
}

void BooksIndexScreen::handleRefreshButtonClick()
{
    model->select();
}
