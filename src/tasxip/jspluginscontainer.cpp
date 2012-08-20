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

#include "jspluginscontainer.h"
#include "jspluginsloader.h"
#include "jsplugin.h"
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <QDebug>

bool JSPluginsContainer::add(const QString &fName){
    bool ret = false;

    QFile file(fName);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);

        try{
            JSPluginsLoader ldr(in.readAll());
            const QStringList plgNames = ldr.names();

            for(auto name : plgNames){
                plugins.insert(std::make_pair(name, fName));
            }

            ret = !plgNames.isEmpty();
        } catch(const JSPluginsLoader::JSError &error) {
            qDebug() << error.what();
        }
    }

    return ret;
}

QStringList JSPluginsContainer::names() const {
    QStringList res;
    std::multimap<PluginName_t, PluginFileName_t>::const_iterator i;
    for(i = plugins.begin();i != plugins.end(); ++i)
        res.append(i->first);
    return res;
}

Plugin * JSPluginsContainer::load(const QString &name, int idx){
    std::multimap<QString, QString>::const_iterator i = plugins.lower_bound(name);
    std::multimap<QString, QString>::const_iterator end = plugins.upper_bound(name);

    int plgIdx = 0;
    for(std::map<QString, int> idxInFile; (i != end) && idx--; ++i)
        if((plgIdx = idxInFile[i->second])) ++plgIdx;

    return (i != end) ? new JSPlugin(i->second, name, plgIdx) : 0;
    /*QStringList plg_files = plugins.values(name);
    return idx < plg_files.size() ? new JSPlugin(plg_files[idx], name) : 0;*/
}

