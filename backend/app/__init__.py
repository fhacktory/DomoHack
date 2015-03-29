# -*- coding: utf-8 -*-
import os
from flask import Flask, request
from flask import jsonify
from flask.ext import restful
from config import config
from yapsy.PluginManager import PluginManagerSingleton

class ListDevices(restful.Resource):
    def get(self):
        list = {
	    'sonde1' : {
                'famille' : 'sonde',
                'type' : 'temperature',
                'unite' : '°C'
            },
            'sonde2' : {
                'famille' : 'sonde',
                'type' : 'lumiere',
                'unite' : 'LUX'
            },
            'prise1' : {
                'famille' : 'prise',
                'type' : 'on/off',
                'unite' : 'boolean'
            }
        }
        return list

def create_app(config_name):
    app = Flask(__name__, static_url_path='/static')


    api = restful.Api(app)
    plugins = PluginManagerSingleton.get()
    plugins.setPluginPlaces(
        ['%s/../plugins/' % os.path.dirname(os.path.realpath(__file__))]
    )
    plugins.collectPlugins()
    for plugin in plugins.getAllPlugins():
        plugins.activatePluginByName(plugin.name)
        api.add_resource(plugin.plugin_object.__class__, plugin.plugin_object.route())
    api.add_resource(ListDevices,'/rest/list')
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)


    @app.route('/rest/prise/<int:id>/<int:value>', methods=['PUT'])
    def set_prise(id, value):
        node = zwave.network.nodes[id]
        prise = node.get_switches()[72057594109837312L]
        if value == 1:
            prise.data = True
        else:
            prise.data = False
        return jsonify({'code':200})

    from .zwave.zwavenetwork import ZWave
    zwave = ZWave(app)

    return app
