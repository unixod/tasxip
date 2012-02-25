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

#include "jsplugin.h"
#include "jspluginsloader.h"
#include "ipv6rangeset.h"
#include <QString>
#include <QFile>
#include <QTextStream>

Q_DECLARE_METATYPE(JSPlugin*)
Q_DECLARE_METATYPE(IPv6RangeSet)


/*
Q_DECLARE_METATYPE(Pa)
Q_DECLARE_METATYPE(std::list<Pa>)

QScriptValue paToScriptValue(QScriptEngine *eng, const Pa &pa){
    QScriptValue obj = eng->newObject();
    obj.setProperty("a", pa.first);
    obj.setProperty("b", pa.second);
    return obj;
}
void paFromScriptValue(const QScriptValue &, Pa &){}
qScriptRegisterMetaType(&en, paToScriptValue, paFromScriptValue);
qScriptRegisterSequenceMetaType< std::list<Pa> >(&en);
*/

JSPlugin::JSPlugin(const QString &fName, const QString &plgName, int idx){
//    loader = new JSPluginsLoader();
    QFile file(fName);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        loader = new JSPluginsLoader(in.readAll());
        plugin = loader->load(plgName, idx);
        qScriptRegisterMetaType(loader->engine(), IPv6RangeSetToScriptValue, IPv6RangeSetFromScriptValue);

        //passed as the second parameter the plugin.invoke method (JS code)
//        out = loader->engine()->newFunction(outFunc);
//        out.setData(loader->engine()->toScriptValue(this));

        initProps();
    }
}

JSPlugin::~JSPlugin(){
    delete loader;
}

void JSPlugin::initProps(){
    QScriptValue prop;

    prop = plugin.property("version");
    if(prop.isValid()) _version = prop.toString();

    prop = plugin.property("name");
    if(prop.isValid()) _name = prop.toString();

    prop = plugin.property("description");
    if(prop.isValid()) _description = prop.toString();
}

QString JSPlugin::version() const {
    return _version;
}

QString JSPlugin::name() const {
    return _name;
}

QString JSPlugin::description() const {
    return _description;
}

QString JSPlugin::invoke(const IPv6RangeSet &range){
    QString out;

    QScriptValueList args;
    args << loader->engine()->toScriptValue(range);
    out = plugin.property("invoke").call(plugin, args).toString();

    return out;
}

//void JSPlugin::flush(const QString &out_data){
//}

//called from JS plugin's invoke method (representation of second parameter of the invoke method)
/*QScriptValue JSPlugin::outFunc(QScriptContext *ctx, QScriptEngine *){
    bool res = false;

    JSPlugin *me = qscriptvalue_cast<JSPlugin*>(ctx->callee().data());
    if(me){
        QString line;
        for(int i = 0; i < ctx->argumentCount(); ++i)
            line += ctx->argument(i).toString();

        me->flush(line);
        res = true;
    }

    return res;
}*/


QScriptValue JSPlugin::IPv6RangeSetToScriptValue(QScriptEngine *eng, const IPv6RangeSet &cont){
    QScriptValue a = eng->newArray();
    IPv6RangeSet::const_iterator begin = cont.begin();
    IPv6RangeSet::const_iterator end = cont.end();
    IPv6RangeSet::const_iterator it;
    int i;
    for (it = begin, i = 0; it != end; ++it, ++i){
        QScriptValue val = eng->newObject();
        val.setProperty("from", it->first);
        val.setProperty("to", it->second);
        a.setProperty(i, val);
    }
    return a;
}

void JSPlugin::IPv6RangeSetFromScriptValue(const QScriptValue &, IPv6RangeSet &){
}
