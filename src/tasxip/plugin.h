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

#ifndef PLUGIN_H
#define PLUGIN_H

#include <QList>

class QString;
class QIODevice;

class Plugin{
public:
    typedef unsigned int IPBound;
    typedef std::pair<IPBound, IPBound> IPRange;
    typedef QList<IPRange> IPv6RangeSet;

    virtual QString version() const = 0;    //0x00MjMiMc - Mj - major byte, Mi - minor, Mc - micro
    virtual QString name() const = 0;
    virtual QString description() const = 0;
    virtual QString invoke(const IPv6RangeSet &) = 0;
    virtual ~Plugin(){}
};

#endif // PLUGIN_H
