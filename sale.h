// sale.h

#ifndef SALE_H
#define SALE_H

#include <QString>

class Sale {
public:
    QString date;
    QString item;
    int quantity;
    double totalSales;

    Sale(const QString &d, const QString &i, int q, double t)
        : date(d), item(i), quantity(q), totalSales(t) {}
};

#endif // SALE_H
