#include "tilitapahtumatlib.h"

TilitapahtumatLib::TilitapahtumatLib()
{

}

QString TilitapahtumatLib::getDate() const
{
    return transactionDate;
}

QString TilitapahtumatLib::getAmount() const
{
    return transactionAmount;
}

void TilitapahtumatLib::setDate(const QString &newDate)
{
    transactionDate = newDate;
}

void TilitapahtumatLib::setAmount(const QString &newAmount)
{
    transactionAmount = newAmount;
}
