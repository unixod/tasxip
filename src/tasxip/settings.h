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
    //default values can be configured by by calling the (config
    //string can be multyline):
    Settings::setDefaults("SomeKey: somekey value; OtherKey: 2");

    //or
    QFile f(":/defaults/config");
    f.open(QIODevice::ReadOnly);
    Settings::setDefaults(f.readAll());
    ...
    ...
    void fun(){
        ...
        QVariant val = Settings::get(Settings::SomeKey);
        Settings::set(Settings::SomeKey) = "some value";
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
