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

#include "datadumper.h"
#include "rangeset.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>

///////////////////
/*
  Helper formating functors
*/
#define IP4_TO_STR(_a) (_a >> 24) << '.' << ((_a >> 16) & 0xFF) << '.' << ((_a >> 8) & 0xFF) << '.' << (_a & 0xFF)

template<class OutStream>
struct fmt_base{
    fmt_base(OutStream &s) : out(s){}

    virtual void operator()(RangeSet<unsigned int>::const_reference range) = 0;

protected:
    OutStream &out;
};

template<class OutStream>
struct fmt_simple : public fmt_base<OutStream>{
    fmt_simple(OutStream &s) : fmt_base<OutStream>(s){}

    void operator()(RangeSet<unsigned int>::const_reference range){
        this->out << IP4_TO_STR(range.first) << " - " << IP4_TO_STR(range.second) << endl;
    }
};

template<class OutStream>
struct fmt_p2p : public fmt_base<OutStream>{
    fmt_p2p(OutStream &s) : fmt_base<OutStream>(s){}

    void operator()(RangeSet<unsigned int>::const_reference range){
        this->out << ":" << IP4_TO_STR(range.first) << "-" << IP4_TO_STR(range.second) << endl;
    }
};
///////////////////

bool DataDumper::flushToFile(const QString &f_name) const {
    QFile file(f_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);

    switch(fmt){
    case SIMPLE:
        std::for_each(ipr->begin(), ipr->end(), fmt_simple<QTextStream>(out));
        break;
    case P2P:
        std::for_each(ipr->begin(), ipr->end(), fmt_p2p<QTextStream>(out));
        break;
    default:
        return false;
    }

    return true;
}
