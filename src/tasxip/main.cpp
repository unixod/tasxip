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

    QCoreApplication::setOrganizationName("Unixod");
    QCoreApplication::setOrganizationDomain("unixod.github.com");
    QCoreApplication::setApplicationName("tasxip");
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    //Paths
    QString appDir = QDir::homePath() + "/." + a.applicationName();
    QString pluginsPath = appDir + "/plugins";

    //Loading plugis
    PluginsProvider *plgProvider = getPluginsProvider(pluginsPath);

    MainWindow w(plgProvider);
    w.show();

    return a.exec();
}
