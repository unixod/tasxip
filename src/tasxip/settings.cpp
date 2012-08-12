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

#include "settings.h"
#include <QSettings>
#include <QMetaEnum>
#include <QRegExp>
#include <QStringList>

Settings::Settings(){
    const QMetaObject &mo = staticMetaObject;
    int idx = mo.indexOfEnumerator("Key");
    keys = mo.enumerator(idx);

    idx = mo.indexOfEnumerator("Section");
    sections = mo.enumerator(idx);
}

QVariant Settings::get(Key k, Section s){
    Settings &self = instance();
    QString key = self.keyPath(s, k);
    return self.conf.value(key, self.defaults[key]);
}

Settings::ValueRef Settings::set(Key k, Section s){
    Settings &self = instance();
    return ValueRef(self, self.keyPath(s, k));
}

void Settings::setDefaults(const QString &str){
    Settings &self = instance();

    // section/key : value;
    // section - optional
    QRegExp rxRecord("^\\s*(((\\w+)/)?(\\w+))\\s*:\\s*([^\\s].{0,})\\b\\s*$");

    auto kvs = str.split(QRegExp(";\\W*"), QString::SkipEmptyParts); //key-values
    for(auto kv : kvs){
        if(rxRecord.indexIn(kv) != -1){
            QString section = rxRecord.cap(3);
            QString key = rxRecord.cap(4);
            QString value = rxRecord.cap(5);

            int iKey = self.keys.keyToValue(key.toLocal8Bit().data());
            if(iKey != -1){
                int iSection = self.sections.keyToValue(section.toLocal8Bit().data());
                if(section.isEmpty() || iSection != -1){
                    self.defaults[rxRecord.cap(1)] = value;
                }
            }
        }
    }
}

//Settings::ValueRef-----------------------------------------------------------
Settings::ValueRef &Settings::ValueRef::operator = (const QVariant &data){
    parent.conf.setValue(keyPath, data);
    return *this;
}


//PRIVATE METHODS--------------------------------------------------------------
QString Settings::keyPath(Settings::Section s, Settings::Key k){
    auto szSection = sections.valueToKey(s);
    auto szKey = keys.valueToKey(k);
    return QString(s == General ? "%1" : "%2/%1").arg(szKey).arg(szSection);
}

Settings & Settings::instance(){
    static Settings singleton;
    return singleton;
}



