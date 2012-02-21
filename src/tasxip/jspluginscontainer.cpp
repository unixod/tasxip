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

#include "jspluginscontainer.h"
#include "jspluginsloader.h"
#include "jsplugin.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>

bool JSPluginsContainer::add(const QString &f_name){
    bool ret = false;

    QFile file(f_name);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        JSPluginsLoader ldr(in.readAll());
        const QStringList names_lst = ldr.names();

        foreach(const QString &plg_name, names_lst){
            plugins.insert(plg_name, f_name);
        }

        ret = !names_lst.isEmpty();
    }

    return ret;
}

QStringList JSPluginsContainer::names() const {
    return plugins.keys();
}

Plugin * JSPluginsContainer::load(const QString &name, int idx){
    QStringList plg_files = plugins.values(name);
    return idx < plg_files.size() ? new JSPlugin(plg_files[idx], name) : 0;
}

