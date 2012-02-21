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

#ifndef JSPLUGIN_H
#define JSPLUGIN_H

#include <QScriptValue>
#include "plugin.h"

class QScriptContext;
class JSPluginsLoader;

class JSPlugin : public Plugin{
public:
    JSPlugin(const QString &f_name, const QString &name);
    ~JSPlugin();

    //Plugin implementation
    inline QString version() const;
    inline QString name() const;
    inline QString description() const;
    QString invoke(const IPv6RangeSet &);

private:
    void initProps();
//    void flush(const QString &);
//    static QScriptValue outFunc(QScriptContext *, QScriptEngine *);


    static QScriptValue IPv6RangeSetToScriptValue(QScriptEngine *eng, const IPv6RangeSet &);
    static void IPv6RangeSetFromScriptValue(const QScriptValue &, IPv6RangeSet &);

private:
    JSPluginsLoader *loader;
    QScriptValue plugin;
//    QScriptValue out;
    QString _version;
    QString _name;
    QString _description;
};

#endif // JSPLUGIN_H
