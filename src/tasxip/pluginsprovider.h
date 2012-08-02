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

#ifndef PLUGINSPROVIDER_H
#define PLUGINSPROVIDER_H

class QString;
class QStringList;
class Plugin;

class PluginsProvider{
public:
//    virtual bool add(const QString &plgfile) = 0;
    virtual QStringList names() const = 0;
    virtual Plugin * load(const QString &name, int idx = 0) = 0;
    virtual ~PluginsProvider(){}
};

#endif // PLUGINSPROVIDER_H
