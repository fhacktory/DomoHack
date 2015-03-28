# -*- coding: utf-8 -*-
import os
from flask import Flask, request
from flask.ext import restful
from config import config
from yapsy.PluginManager import PluginManagerSingleton

class ListDevices(restful.Resource):
    def get(self):
        list = {
            {
                'id' : 'sonde1',
                'famille' : 'sonde',
                'type' : 'temperature',
                'unite' : '°C'
            },
            {
                'id' : 'sonde2',
                'famille' : 'sonde',
                'type' : 'lumiere',
                'unite' : 'LUX'
            },
            {
                'id' : 'prise1',
                'famille' : 'prise',
                'type' : 'on/off',
                'unite' : 'boolean'
            }
        }
        return list

def create_app(config_name):
    app = Flask(__name__)
    api = restful.Api(app)
    #api.add_resource(BonjourLeRest,'/rest/hello')
    plugins = PluginManagerSingleton.get()
    plugins.setPluginPlaces(
        ['%s/../plugins/' % os.path.dirname(os.path.realpath(__file__))]
    )
    plugins.collectPlugins()
    print plugins.getAllPlugins()
    for plugin in plugins.getAllPlugins():
        plugins.activatePluginByName(plugin.name)
        api.add_resource(plugin.plugin_object.__class__, plugin.plugin_object.route())
    api.add_resource(ListDevices,'/rest/list')
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)
    return app


