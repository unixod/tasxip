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

#ifndef PLUGININFODLG_H
#define PLUGININFODLG_H

#include <QDialog>

namespace Ui {
class PluginInfoDlg;
}

class Plugin;

class PluginInfoDlg : public QDialog{
    Q_OBJECT

public:
    static void showModal(Plugin *);

private:
    explicit PluginInfoDlg(Plugin *, QWidget *parent = 0);
    ~PluginInfoDlg();
    
private:
    Ui::PluginInfoDlg *ui;
};

#endif // PLUGININFODLG_H
