#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include "readercardsscreen.h"
#include "controller.h"
#include "screenid.h"
#include "ui_readercardsscreen.h"

ReaderCardsScreen::ReaderCardsScreen(QWidget *parent, QSqlDatabase db, Controller *appController)
    : QWidget(parent)
    , ui(new Ui::ReaderCardsScreen), appController(appController), db(db), readyForCreateRow(false)
{
    ui->setupUi(this);

    model = new QSqlTableModel(this, db);
    model->setTable("readercards");
    model->select();

    model->setHeaderData(2, Qt::Horizontal, "Nazwisko");
    model->setHeaderData(1, Qt::Horizontal, "Imię");
    model->setHeaderData(3, Qt::Horizontal, "E-mail");
    model->setHeaderData(4, Qt::Horizontal, "Wiek");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->hideColumn(0);

    ui->backButton->setToolTip("Powrót do głównego ekranu");
    connect(ui->backButton, &QPushButton::clicked, this, &ReaderCardsScreen::handleBackButtonClick);

    ui->deleteRowsButton->setToolTip("Usuwa zaznaczone wiersze");
    connect(ui->deleteRowsButton, &QPushButton::clicked, this, &ReaderCardsScreen::handleDeleteRowsButtonClick);

    ui->addRowButton->setToolTip("Dodaje pusty wiersz a ponowne kliknięcie dodaje nowy rekord");
    connect(ui->addRowButton, &QPushButton::clicked, this, &ReaderCardsScreen::handleAddRowButtonClick);

    ui->refreshButton->setToolTip("Odświeża dane w tabeli");
    connect(ui->refreshButton, &QPushButton::clicked, this, &ReaderCardsScreen::handleRefreshButtonClick);
}

ReaderCardsScreen::~ReaderCardsScreen()
{
    delete ui;
}

void ReaderCardsScreen::handleBackButtonClick()
{
    appController->goTo(ScreenId::Menu);
}

void ReaderCardsScreen::handleDeleteRowsButtonClick()
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

void ReaderCardsScreen::handleAddRowButtonClick()
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

void ReaderCardsScreen::handleRefreshButtonClick()
{
    model->select();
}
