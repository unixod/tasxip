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

#include "jspluginsloader.h"
#include <QScriptEngine>
#include <QFile>
#include <QStringList>

QString JSPluginsLoader::loader;

JSPluginsLoader::JSPluginsLoader(const QScriptProgram &plugin){
    if(loader.isEmpty()){
        QFile ldr(":/jshelper/jspluginsloader.js");
        ldr.open(QIODevice::ReadOnly);
        loader = ldr.readAll();
    }
    eng.evaluate(loader);
    eng.evaluate(plugin);
}

QStringList JSPluginsLoader::names() const {
    QScriptContext *ctx = eng.currentContext();
    QScriptValue jsldr = ctx->activationObject().property("PluginsLoader").call();                  //var jsldr = PluginsLoader();
    QStringList names_lst = qscriptvalue_cast<QStringList>(jsldr.property("names").call(jsldr));    //names_lst = jsldr.names();
    return names_lst;
}

QScriptValue JSPluginsLoader::load(const QString &name) const {
    QScriptContext *ctx = eng.currentContext();
    QScriptValue jsldr = ctx->activationObject().property("PluginsLoader").call();      //var jsldr = PluginsLoader();

    QScriptValueList args;
    args << name;
    QScriptValue plugin = jsldr.property("load").call(jsldr, args);                     //var plugin = jsldr.load(name);
    return plugin;
}
