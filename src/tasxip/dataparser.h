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
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QList>
#include "uau/rangeset.h"

class QIODevice;

class DataParser{
public:
    typedef unsigned int IPBound;
    typedef std::pair<IPBound, IPBound> IPRange;

    void parse(QIODevice *);
    QList<IPRange> result() const;
    int resultCount() const;
    int parsedCount() const;

private:
    uau::RangeSet<IPBound, QList> ipr;
    int parsedCnt;
};

#endif // DATAPARSER_H
