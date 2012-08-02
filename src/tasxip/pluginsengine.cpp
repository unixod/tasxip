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

#include "pluginsengine.h"
#include "jspluginscontainer.h"
#include <QDir>

PluginsProvider * getPluginsProvider(const QDir &dir){
    QStringList files = dir.entryList(QStringList() << "*.js",
                                      QDir::Readable | QDir::Files | QDir::CaseSensitive);

    if(files.isEmpty())
        return 0;

    JSPluginsContainer *provider = new JSPluginsContainer;
    for(auto plugin : files) provider->add(dir.path() + "/" + plugin);
    if(provider->names().isEmpty()){
        delete provider;
        provider = 0;
    }
    return provider;
}
