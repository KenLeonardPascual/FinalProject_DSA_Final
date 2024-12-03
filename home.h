#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>
#include <QList>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private slots:
    void searchInventory();
    void resetTableView();
    void filterByListView();

private:
    void loadInventoryData();
    void filterInventory(const QDate &date, const QString &item);

    Ui::Home *ui;
    QStandardItemModel *inventoryModel;

    // Static sales data list
    struct Sale {
        QDate date;
        QString item;
        int quantity;
        double totalSales;

        Sale(QDate date, QString item, int quantity, double totalSales)
            : date(date), item(item), quantity(quantity), totalSales(totalSales) {}
    };

    // Declare static salesData (initialize in home.cpp)
    static QList<Sale> salesData;
};

#endif // HOME_H
