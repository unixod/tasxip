#ifndef PLUGINSENGINE_H
#define PLUGINSENGINE_H

#include "pluginsprovider.h"
class QDir;

PluginsProvider * getPluginsProvider(const QDir &);

#endif // PLUGINSENGINE_H
