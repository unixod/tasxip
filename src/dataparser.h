/*
    TasXIP - ipfilter files generator
    Copyright (C) 2011-2012, Eldar Zakirov <unixod@gmail.com>

    This file is part of TasXIP.

    TasXIP is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TasXIP is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
  DataParser - parse ip's ranges from input data stream;
*/

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
