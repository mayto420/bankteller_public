#ifndef TILITAPAHTUMATLIB_H
#define TILITAPAHTUMATLIB_H

#include "tilitapahtumatLib_global.h"
#include <QString>

class TILITAPAHTUMATLIB_EXPORT TilitapahtumatLib
{
public:
    TilitapahtumatLib();

    QString transactionDate;
    QString transactionAmount;
    //int postTransactionTotal;

    // getterit:
    QString getDate() const;
    QString getAmount() const;
    //int getTotal() const;

    // setterit:
    void setDate(const QString &newDate);
    void setAmount(const QString &newAmount);
    //void setTotal(const int &newTotal);

};

#endif // TILITAPAHTUMATLIB_H
