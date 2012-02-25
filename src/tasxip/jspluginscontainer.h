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

#ifndef JSPLUGINSCONTAINER_H
#define JSPLUGINSCONTAINER_H

#include "pluginsprovider.h"
#include <QScriptEngine>
#include <QMap>
#include <map>

class JSPluginsContainer : public PluginsProvider{
    typedef QString PluginFileName_t;
    typedef QString PluginName_t;
//    QMultiMap<PluginName_t, PluginFileName_t> plugins;
    std::multimap<PluginName_t, PluginFileName_t> plugins;
public:
    //PluginsContainer implementation
    bool add(const QString &fName);
    QStringList names() const;
    Plugin * load(const QString &name, int idx = 0);
};

#endif // JSPLUGINSCONTAINER_H
