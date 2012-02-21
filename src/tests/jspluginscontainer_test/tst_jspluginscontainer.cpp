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
#include "jspluginscontainer.h"
#include "plugin.h"

class JSPluginsContainer_Test : public QObject{
    Q_OBJECT
    QStringList plugins;
    JSPluginsContainer container;
public:
    JSPluginsContainer_Test();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void names_test();
    void load_test();
};

JSPluginsContainer_Test::JSPluginsContainer_Test(){
    plugins << ":/plugins/minimum_plg.js"       //Minimum required plugin
               << ":/plugins/multi_plg.js";     //Multi-plugin
}

//Test cases---------------------------------------------------------------------------------------
void JSPluginsContainer_Test::initTestCase(){
    foreach(const QString &plugin, plugins){
        QVERIFY(container.add(plugin));
    }
}

void JSPluginsContainer_Test::cleanupTestCase(){
}

void JSPluginsContainer_Test::names_test(){
    //loading plugins names by reading test-time plugin_names var from scripts
    QStringList plugin_names;
    foreach(const QString &plugin, plugins){
        QScriptEngine en;
        QFile f(plugin);
        f.open(QIODevice::ReadOnly);
        en.evaluate(f.readAll());
        plugin_names << qscriptvalue_cast<QStringList>(en.globalObject().property("plugin_names"));
    }

    QStringList names = container.names();
    names.sort();
    plugin_names.sort();
    QVERIFY(names == plugin_names);
}

void JSPluginsContainer_Test::load_test(){
    QStringList plg_names = container.names();
    foreach(const QString &name, plg_names){
        Plugin *plg = container.load(name);
        QVERIFY2(plg->name() == name, QString("%1 != %2").arg(plg->name()).arg(name).toUtf8());
        delete plg;
    }
}

QTEST_MAIN(JSPluginsContainer_Test)

#include "tst_jspluginscontainer.moc"
