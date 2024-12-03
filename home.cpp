#include "home.h"
#include "./ui_home.h"
#include <QStandardItemModel>

Home::Home(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Home)
{
    ui->setupUi(this);

    inventoryModel = new QStandardItemModel(this);
    ui->tableView->setModel(inventoryModel);

    inventoryModel->setHorizontalHeaderLabels({"Date", "Item Sold", "Quantity", "Total Sales"});

    ui->tableView->setSortingEnabled(true);

    // Initialize QListView with categories and items
    QStandardItemModel *listModel = new QStandardItemModel(this);
    listModel->appendRow(new QStandardItem("Cheesy Burger Sandwich"));
    listModel->appendRow(new QStandardItem("Cheesy Hotdog Sandwich"));
    listModel->appendRow(new QStandardItem("Beef Burger Sandwich"));
    listModel->appendRow(new QStandardItem("Cheesy Hungarian Sandwich"));
    listModel->appendRow(new QStandardItem("Cheesy Footlong Sandwich"));
    listModel->appendRow(new QStandardItem("Egg Sandwich"));
    listModel->appendRow(new QStandardItem("Cheese"));
    listModel->appendRow(new QStandardItem("Egg"));
    listModel->appendRow(new QStandardItem("Bacon"));
    listModel->appendRow(new QStandardItem("Pepsi"));
    listModel->appendRow(new QStandardItem("Mountain Dew"));
    listModel->appendRow(new QStandardItem("7UP"));

    ui->listView->setModel(listModel);

    loadInventoryData();

    connect(ui->pushButton, &QPushButton::clicked, this, &Home::searchInventory);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Home::resetTableView);
    connect(ui->listView->selectionModel(), &QItemSelectionModel::currentChanged, this, &Home::filterByListView);
}

Home::~Home()
{
    delete ui;
}

void Home::loadInventoryData()
{
    inventoryModel->clear();
    inventoryModel->setHorizontalHeaderLabels({"Date", "Item Sold", "Quantity", "Total Sales"});

    for (const Sale &sale : salesData) {
        QList<QStandardItem*> row;
        row.append(new QStandardItem(sale.date.toString("yyyy-MM-dd")));
        row.append(new QStandardItem(sale.item));
        row.append(new QStandardItem(QString::number(sale.quantity)));
        row.append(new QStandardItem(QString::number(sale.totalSales)));
        inventoryModel->appendRow(row);
    }
}

void Home::searchInventory()
{
    QDate searchDate = ui->dateEdit->date();
    QString searchItem = ui->listView->currentIndex().data().toString();

    if (!searchDate.isValid()) {
        searchDate = QDate();
    }

    filterInventory(searchDate, searchItem);
}

void Home::resetTableView()
{
    inventoryModel->clear();
    inventoryModel->setHorizontalHeaderLabels({"Date", "Item Sold", "Quantity", "Total Sales"});
    loadInventoryData();
}

void Home::filterInventory(const QDate &date, const QString &item)
{
    inventoryModel->clear();
    inventoryModel->setHorizontalHeaderLabels({"Date", "Item Sold", "Quantity", "Total Sales"});

    for (const Sale &sale : salesData) {
        bool dateMatch = false;

        if (!date.isNull()) {
            dateMatch = (sale.date.year() == date.year() && sale.date.month() == date.month());
        } else {
            dateMatch = true;
        }

        bool itemMatch = item.isEmpty() || sale.item.contains(item, Qt::CaseInsensitive);

        if (dateMatch && itemMatch) {
            QList<QStandardItem*> row;
            row.append(new QStandardItem(sale.date.toString("yyyy-MM-dd")));
            row.append(new QStandardItem(sale.item));
            row.append(new QStandardItem(QString::number(sale.quantity)));
            row.append(new QStandardItem(QString::number(sale.totalSales)));
            inventoryModel->appendRow(row);
        }
    }
}

void Home::filterByListView()
{
    // Get the selected item from the list view
    QModelIndex currentIndex = ui->listView->currentIndex();

    if (currentIndex.isValid()) {
        QString selectedItem = currentIndex.data().toString();

        // Use the selected item to filter the inventory
        filterInventory(QDate(), selectedItem); // Pass QDate() to indicate no filtering by date
    } else {
        // If no item is selected, you can either reset or handle it differently
        filterInventory(QDate(), ""); // Reset filter by passing an empty string for item
    }
}

// Initialize static sales data outside the constructor in .cpp file
QList<Home::Sale> Home::salesData = {
    Home::Sale(QDate(2024, 12, 3), "Cheesy Burger Sandwich", 2, 100.00),
    Home::Sale(QDate(2024, 12, 2), "Cheesy Hotdog Sandwich", 3, 111.00),
    Home::Sale(QDate(2024, 12, 1), "Beef Burger Sandwich", 1, 40.00),
    Home::Sale(QDate(2024, 11, 30), "Cheesy Hungarian Sandwich", 2, 140.00),
    Home::Sale(QDate(2024, 11, 29), "Cheesy Footlong Sandwich", 1, 56.00),
    Home::Sale(QDate(2024, 11, 28), "Egg Sandwich", 4, 80.00),
    Home::Sale(QDate(2024, 11, 27), "Cheese", 10, 50.00),
    Home::Sale(QDate(2024, 11, 26), "Egg", 5, 75.00),
    Home::Sale(QDate(2024, 11, 25), "Bacon", 3, 75.00),
    Home::Sale(QDate(2024, 11, 24), "Pepsi", 8, 200.00),
    Home::Sale(QDate(2024, 11, 23), "Mountain Dew", 6, 150.00),
    Home::Sale(QDate(2024, 11, 22), "7UP", 5, 80.00),
    Home::Sale(QDate(2024, 12, 22), "7UP", 5, 80.00)
};
