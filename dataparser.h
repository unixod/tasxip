/*----------------------------------------------------------------------------+
|      ___   __                                                               |
|      //_/\//                                                                |
|    _// _//\\                                                                |
|                                                                             |
|   -=[ProfX]=-                                                               |
|   Created by Zakirov Eldar aka ProfX, 2011                                  |
|                                                                             |
|   Header:                                                                   |
|       TasIXP                                                                |
|   Description:                                                              |
|        IP    aa.bb.cc.dd/(ee)                          |
|         IP  ,                                          |
|            0.0.0.0 - 255.255.255.255                 |
|   Interface:                                                                |
|       void parse(QByteArray);                                               |
|                                                               |
|       void flushToFile(QStrin);                                             |
|                                                     |
|       int parsedCount();                                                    |
|             IP                               |
|       int resultCount();                                                    |
|                                     |
|   Dependiences:                                                             |
|       RangeSet<int>                                                         |
|   To Do:                                                                    |
+----------------------------------------------------------------------------*/


#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QIODevice>

template<class> class RangeSet;

class DataParser{
    RangeSet<unsigned int> *ipr;
    int parsedCnt;
    int resultCnt;
public:
    DataParser();
    ~DataParser();

    int resultCount() const;
    int parsedCount() const;

    void parse(QIODevice *);
    bool flushToFile(const QString &name) const;
};

#endif // DATAPARSER_H
