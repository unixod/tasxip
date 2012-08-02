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

#include "dataparser.h"
#include <QRegExp>
#include <QFile>
#include <QTextStream>

void DataParser::parse(QIODevice *data){
    QRegExp rx("^[^0-9]{3}(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})(\\/(\\d{1,2}))?", Qt::CaseInsensitive);
    ipr.assign_range(0x00000000, 0xffffffff);

    QTextStream ds(data);
    QString ln;
    parsedCnt = 0;
    while(!ds.atEnd()){
        ln = ds.readLine();
        if(rx.indexIn(ln) != -1){
            int ip = 0;
            ip |= rx.cap(1).toInt() << 24;
            ip |= rx.cap(2).toInt() << 16;
            ip |= rx.cap(3).toInt() << 8;
            ip |= rx.cap(4).toInt();

            int range = 1 << (32 - rx.cap(6).toInt()); //(0, range)
            range -= 1;

            ip &= range ^ 0xffffffff;

            ++parsedCnt;

            ipr.exclude(ip, ip+range);
        }
    }
}

QList<DataParser::IPRange> DataParser::result() const {
    return ipr;
}

int DataParser::resultCount() const {
    return  ipr.size();
}

int DataParser::parsedCount() const {
    return parsedCnt;
}

