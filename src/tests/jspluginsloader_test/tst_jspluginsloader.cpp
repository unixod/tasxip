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

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include "jspluginsloader.h"


class JSPluginsLoader_Test : public QObject{
    Q_OBJECT
    QStringList plugins;
public:
    JSPluginsLoader_Test();

private:
    void addPlugin(const QString &);
    
private Q_SLOTS:
    void names_test();
    void load_test();
};


JSPluginsLoader_Test::JSPluginsLoader_Test(){
    //Minimum required plugin
    addPlugin(":/plugins/minimum_plg.js");

    //Multi-plugin
    addPlugin(":/plugins/multi_plg.js");
}

void JSPluginsLoader_Test::addPlugin(const QString &plg_name){
    QFile plg(plg_name);
    plg.open(QIODevice::ReadOnly);
    plugins << plg.readAll();
}


//Test cases---------------------------------------------------------------------------------------
void JSPluginsLoader_Test::names_test(){
    foreach(const QString &plugin, plugins){
        JSPluginsLoader ldr(plugin);
        QStringList plugin_names = qscriptvalue_cast<QStringList>(ldr.engine()->globalObject().property("plugin_names"));

        QCOMPARE(ldr.names(), plugin_names);
    }
}

void JSPluginsLoader_Test::load_test(){
    foreach(const QString &plugin, plugins){
        JSPluginsLoader ldr(plugin);
        QStringList plugin_names = qscriptvalue_cast<QStringList>(ldr.engine()->globalObject().property("plugin_names"));

        foreach(const QString &name, plugin_names){
            QString plg_name = ldr.load(name).property("name").toString();
            QCOMPARE(plg_name, name);
        }
    }
}

QTEST_MAIN(JSPluginsLoader_Test)

#include "tst_jspluginsloader.moc"
