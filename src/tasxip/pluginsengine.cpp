#include "pluginsengine.h"
#include "jspluginscontainer.h"
#include <QDir>

PluginsProvider * getPluginsProvider(const QDir &dir){
    QStringList files = dir.entryList(QStringList() << "*.js",
                                      QDir::Readable | QDir::Files | QDir::CaseSensitive);

    if(files.isEmpty())
        return 0;

    JSPluginsContainer *provider = new JSPluginsContainer;
    foreach(const QString plugin, files) provider->add(dir.path() + "/" + plugin);
    return provider;
}
