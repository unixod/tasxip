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

/*
  Used for loading js plugins and querying info in plugin file
  plugin file format:

  function plugin(){
    return [Plugin Object with required fileds];
  }

  Examples:

    function plugin(){
        return {
            minimum_required: "<minimum loader version>",
            version: "<plugin version number>",
            name: "<plugin name>",
            description: "<short plugin description>",
            invoke: function(iprange){   //plugins main function
                var result;
                for(var i = 0; i < iprange.length; i++){
                    result += iprange[i].from + "-" + iprange[i].to + ";";
                }
                return result;
            }
        }
    }

    function plugin(){
        return [{
            minimum_required: "<minimum loader version>",       //optional field (used by PluginsLoader only)
            version: "<plugin version>",                        //optional field
            name: "<plugin name>",                              //reuqired field
            description: "<short plugin description>",          //optional field
            invoke: function(iprange){                          //plugins main function
                ///...
            }
        },{
            name:"minimum required plugin",
            invoke: function(iprange){
                ///...
            }
        }];
    }
*/
/*
  PluginsLoader usage:
  //in context which have already loaded plugin

  var ldr = PluginsLoader();
  var names = ldr.names();      //return all names of plugins (in current context) which can be loaded
  var plg = ldr.load(name[i]);  //load plugin (index by default is 0)
  or equal:
  var plg = ldr.load(name[i], 0);

  //If plugin-file contains some of the same name plugins
  //load method can handle optional parameter - index
  for example:
  function plugin(){
    return [{
        name: "samename",
        version:"1.1.0"
        invoke:...
    }, {
        name: "samename",
        version:"1.1.0a"
        invoke:...
    }, {
        name: "samename",
        version:"1.1.0b"
        invoke:...
    }]
  }


  var plg = ldr.load(name[0], 1);   //return plugin with version "1.1.0a"
*/

function PluginsLoader(){
    return {
        version: "1.2.0",

        isValid: function(plg){
                     /*if(plg.minimum_required){	//if defined
                         var my_vertokens = this.version.split(".");
                         var plg_ver_tokens = plg.minimum_required.split(".");
                         var res = true;
                         for(var i = 0; (i < my_vertokens.length) && (i < plg_ver_tokens.length) && res; i++){
                             if(parseInt(plg_ver_tokens[i], 10) > parseInt(my_vertokens[i], 10)) res = false;
                         }
                     }*/
                     return plg.name && plg.invoke;
                 },

        names: function(){
                   var names = [];
                   if(typeof plugin == "function"){
                       var plg = plugin();
                       if(plg.length){
                           var j = 0;
                           for(var i = 0; i < plg.length; i++){
                               if(this.isValid(plg[i])) names[j++] = plg[i].name;
                           }
                       } else {
                           if(this.isValid(plg)) names[0] = plg.name;
                       }
                   }

                   return names;
               },

        load: function(name, idx){
                  if(typeof idx != "number") idx = 0;

                  if(typeof plugin == "function"){
                      var plg = plugin();
                      if(plg.length){
                          var j = 0;
                          for(var i = 0; i < plg.length; i++){
                              if(this.isValid(plg[i]) && (plg[i].name == name)){
                                  if(idx == 0) return plg[i];
                                  else idx--;
                              }
                          }
                      } else if(this.isValid(plg) && (plg.name == name) && (idx == 0)) return plg;
                  }

                  return null;
              }
    }
}
