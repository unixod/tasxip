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

#include <QtGui/QApplication>
#include "mainwindow.h"
#include "pluginsengine.h"
#include <QDebug>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("unixod");
    QCoreApplication::setOrganizationDomain("unixod.github.com");
    QCoreApplication::setApplicationName("tasxip");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //Preparing dirs
    QString appDataDir = QDir::homePath() + "/." + a.applicationName();
    QString pluginsDir = "plugins";
    if(!QFile::exists(appDataDir + "/" + pluginsDir))
        QDir().mkpath(appDataDir + "/" + pluginsDir);

    //Paths, where plugins dir will be search
    QStringList pluginsDirSearchPaths;
    pluginsDirSearchPaths << QCoreApplication::applicationDirPath()
                          << appDataDir;

    //Loading plugis
    PluginsProvider *plgProvider;
    foreach(const QString &dir, pluginsDirSearchPaths){
        if(plgProvider = getPluginsProvider(dir + "/" + pluginsDir)){
            pluginsDir.prepend(dir + "/");
            break;
        }
    }

    if(!plgProvider){
        pluginsDir.prepend(appDataDir + "/");

        QFile::copy(":/plugins/basicplugin.js", pluginsDir + "/basicplugin.js");
        plgProvider = getPluginsProvider(pluginsDir);
        if(!plgProvider){
            qDebug() << "Can't read/write from " + pluginsDir;
            return 1;
        }
    }

    MainWindow w(plgProvider);
    w.show();

    return a.exec();
}
