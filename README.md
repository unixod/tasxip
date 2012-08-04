TasXIP
======

Scriptable IP filters generator (Multi-Router Looking Glass (MRLG) output (ip bgp) parser).


## About

**TasXIP** is a simple web-dumping tool that dumps info from [tas-ix mrlg][1], and make *ipfilter-file* for programs like **uTorrent**, **IP Blocker**, etc. Output format depends on the used plugin.

[1]: http://mrlg.tas-ix.uz/index.cgi "Multi-Router Looking Glass (MRLG)"


## Plugins

Plugins are written in JavaScript. Each plugin - is a text file that contains the definition of a JavaScript-function `plugin`, that exports the plugin-object(s):

```js
function plugin(){
    return <plugin_objects>;
}
```

where `<plugin_objects>` - JS object(s), which can have following fields:

   * `minimum_required`: minimum loader version **[optional field]**

   * `version`: plugin version **[optional field]**

   * `name`: plugin name

   * `description`: short plugin description **[optional field]**

   * `invoke(iprange)`: plugins main function

Complete plugin example:

```js
/*
  basicplugin.js
*/

function plugin(){
    return {
        name: "Plugin name",
        description: "Plugin description",
        version: "Plugin.Version.Number",
        invoke: function(iprange){
            var result = "";
            for(var i = 0; i < iprange.length; i++){
                result += iprange[i].from + '-' + iprange[i].to + '\n';
            }
            return result;
        }
    }
}
```

Several plugins, can be combined in a single file:

```js
/*
  multiplugin.js
*/

function plugin(){
    return [{
        name: "Plugin1",
        invoke: function(iprange){
            return ...;
        }
    }, {
        name: "Plugin2",
        invoke: function(iprange){
            return ...;
        }
    }];
}
```

### Plugins location

The search path for **TasXIP** plugins is:

   * {USER_HOME}/.tasxip/plugins

   * {EXECUTABLE_BIN_PATH}/plugins


## BUILDING

   1. Clone this repository with --recursive option:

        git clone --recursive git://github.com/unixod/tasxip.git

   2. Follow the steps described in the BUILD file.


## Contributing

Do the usual github fork and pull request dance.


## License

Released under the GPLv3 license.


<pre>
  ___   __  
  //_/\//   
_// _//\\  
</pre>
Copyright (C) 2011-2012, Eldar Zakirov <unixod@gmail.com>