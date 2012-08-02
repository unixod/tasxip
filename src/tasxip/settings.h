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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QVariant>
#include <QSettings>
#include <QMetaEnum>

/**
  @brief Configuration access singleton

  Usage:
  @code
    ...
    ...
    //must be predefined somewhere in main
    QApplication::setOrganizationName("Organization name");
    QApplication::setApplicationName("App name");
    ...
    ...
    //default values can be configured by calling (config
    //string can be multyline):
    Settings::setDefaults("SomeKey: value1; SomeSection/SomeKey: value2");

    //or
    QFile f(":/defaults/config");
    f.open(QIODevice::ReadOnly);
    Settings::setDefaults(f.readAll());
    ...
    ...
    void fun(){
        ...
        QVariant val1 = Settings::get(Settings::SomeKey);
        Settings::set(Settings::SomeKey) = "new val1";
        ...
        QVariant val2 = Settings::get(Settings::SomeKey, Settings::SomeSection);
        Settings::set(Settings::SomeKey, , Settings::SomeSection) = "new val2";
        ...
    }
  @endcode
*/
class Settings : public QObject{
    Q_OBJECT
    Q_ENUMS(Section)
    Q_ENUMS(Key)
public:
    enum Section{
        General,
        Network,
        Proxy
    };

    enum Key{
        MRLGURI,
        MRLGRPostParams,
        LoadedPlugin,
        ProxyEnabled,
        ProxyAddress,
        ProxyPort,
        ProxyUser,
        ProxyPassword,
        ProxyAuthReq
    };

    class ValueRef{
    public:
        ValueRef(Settings &st, const QString &kp) :
            parent(st), keyPath(kp){}
        ValueRef & operator = (const QVariant &d);
    private:
        Settings &parent;
        const QString keyPath;
    };

    static void setDefaults(const QString &str);
    static QVariant get(Key, Section /*s*/ = General);
    static ValueRef set(Key, Section /*s*/ = General);

private:
    QString keyPath(Section, Key);

    static Settings & instance();
    QMetaEnum keys;
    QMetaEnum sections;
    QMap<QString, QVariant> defaults;
    QSettings conf;

    Settings();
    Settings(const Settings &);
    Settings & operator = (const Settings &);
};

#endif // SETTINGS_H
