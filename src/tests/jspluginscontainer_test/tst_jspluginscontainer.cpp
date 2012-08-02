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

#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QtCore/QCoreApplication>
#include "jspluginscontainer.h"
#include "plugin.h"

class JSPluginsContainer_Test : public QObject{
    Q_OBJECT
    QStringList plgModules;
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
    plgModules << ":/plugins/minimum_plg.js"    //Minimum required plugin
               << ":/plugins/multi_plg.js";     //Multi-plugin
}

//Test cases---------------------------------------------------------------------------------------
void JSPluginsContainer_Test::initTestCase(){
    for(auto module : plgModules){
        QVERIFY(container.add(module));
    }
}

void JSPluginsContainer_Test::cleanupTestCase(){
}

void JSPluginsContainer_Test::names_test(){
    //loading plugins names by reading test-time plugin_names var from scripts
    QStringList plgNamesProp;
    for(auto module : plgModules){
        QScriptEngine en;
        QFile f(module);
        f.open(QIODevice::ReadOnly);
        en.evaluate(f.readAll());
        plgNamesProp << qscriptvalue_cast<QStringList>(en.globalObject().property("plugin_names"));
    }

    QStringList plgNames = container.names();
    plgNames.sort();
    plgNamesProp.sort();
    QVERIFY(plgNames == plgNamesProp);
}

void JSPluginsContainer_Test::load_test(){
    QStringList plgNames = container.names();
    for(auto name : plgNames){
        Plugin *plg = container.load(name);
        QVERIFY2(plg->name() == name, QString("%1 != %2").arg(plg->name()).arg(name).toUtf8());
        delete plg;
    }
}

QTEST_MAIN(JSPluginsContainer_Test)

#include "tst_jspluginscontainer.moc"
