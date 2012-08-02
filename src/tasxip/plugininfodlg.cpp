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

#include "plugininfodlg.h"
#include "ui_plugininfodlg.h"
#include "plugin.h"

PluginInfoDlg::PluginInfoDlg(Plugin *plugin, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginInfoDlg)
{
    ui->setupUi(this);

    ui->lblName_val->setText(plugin->name());
    ui->lblVersion_val->setText(plugin->version());
    ui->tedDescr->setText(plugin->description());
}

PluginInfoDlg::~PluginInfoDlg(){
    delete ui;
}


void PluginInfoDlg::showModal(Plugin *plugin){
    PluginInfoDlg dlg(plugin);
    dlg.exec();
}
