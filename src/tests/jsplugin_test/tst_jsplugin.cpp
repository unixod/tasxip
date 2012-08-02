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
#include <QTime>
#include "jspluginscontainer.h"
#include "plugin.h"
#include "uau/rangeset.h"

class JSPlugin_Test : public QObject{
    Q_OBJECT
    QStringList plgModules;
    JSPluginsContainer container;
public:
    JSPlugin_Test();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void invoke_test();
};

JSPlugin_Test::JSPlugin_Test(){
    plgModules << ":/plugins/minimum_plg.js"    //Minimum required plugin
               << ":/plugins/multi_plg.js";     //Multi-plugin
}

//Test cases---------------------------------------------------------------------------------------
void JSPlugin_Test::initTestCase(){
    for(auto module : plgModules){
        QVERIFY(container.add(module));
    }
}

void JSPlugin_Test::cleanupTestCase(){
}

void JSPlugin_Test::invoke_test(){
    QStringList plgNames = container.names();
    for(auto name : plgNames){
        Plugin *plg = container.load(name);
        QCOMPARE(plg->name(),name);

        //preparing input args
        uau::RangeSet<unsigned int, QList> range;
        range.assign_range(0, 0xFFFFFFFF);
        qsrand(QTime::currentTime().msec());
        int d1 = qrand();
        int d2 = qrand();
        range.exclude(std::min(d1, d2), std::max(d1,d2));

        //c++ equal invoke method
        QString result = name + ":";
        for(auto i : range){
            result += QString("%1-%2;").arg(i.first).arg(i.second);
        }

        QCOMPARE(plg->invoke(range), result);
        delete plg;
    }
}

QTEST_MAIN(JSPlugin_Test)

#include "tst_jsplugin.moc"
