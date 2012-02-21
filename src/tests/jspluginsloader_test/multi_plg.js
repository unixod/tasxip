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

function plugin(){
    return [{
        minimum_required: "1.2.0",
        version: "0.0.1",
        name: "multi_plg1",
        description: "<short plugin description>",
        invoke: function(iprange){
            var result = "multi_plg1:";
            for(var i = 0; i < iprange.length; i++){
                result += iprange[i].from + "-" + iprange[i].to + ";";
            }
            return result;
        }
    },{
        name:"multi_plg2",
        invoke: function(iprange){
            var result = "multi_plg2:";
            for(var i = 0; i < iprange.length; i++){
                result += iprange[i].from + "-" + iprange[i].to + ";";
            }
            return result;
        }
    }];
}

//FOR TESTING
//names_test
var plugin_names = ["multi_plg1", "multi_plg2"]
