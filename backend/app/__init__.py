# -*- coding: utf-8 -*-
import os
from flask import Flask, request
from flask import jsonify
from flask.ext import restful
from flask.ext.cors import CORS, cross_origin
from config import config
from yapsy.PluginManager import PluginManagerSingleton
from influxdb import InfluxDBClient

list = {
	    'sonde1' : {
                'name' : 'sonde1',
                'famille' : 'sonde',
                'type' : 'temperature',
                'unite' : '°C'
            },
            'sonde2' : {
                'name' : 'sonde2',
                'famille' : 'sonde',
                'type' : 'lumiere',
                'unite' : 'LUX'
            },
            'prise1' : {
                'name' : 'prise1',
                'famille' : 'prise',
                'type' : 'on/off',
                'unite' : 'boolean'
            },
            'prise4' : {
                'name' : 'prise4',
                'id' : 4,
                'famille' : 'prise',
                'type' : 'on/off',
                'switch': 72057594109837312L,
                'unite' : 'boolean' 
            },
            'robot' : {
                'name' : 'robot',
                'id' : 8,
                'famille' : 'robot',
                'type' : 'intelligent',
            }
}



def create_app(config_name):
    app = Flask(__name__, static_url_path='/static')

    client = InfluxDBClient('192.168.3.32', 8086, 'root', 'root', 'domohack')
       

    api = restful.Api(app)
    plugins = PluginManagerSingleton.get()
    plugins.setPluginPlaces(
        ['%s/../plugins/' % os.path.dirname(os.path.realpath(__file__))]
    )
    plugins.collectPlugins()
    for plugin in plugins.getAllPlugins():
        plugins.activatePluginByName(plugin.name)
        api.add_resource(plugin.plugin_object.__class__, plugin.plugin_object.route())
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)

    @app.route('/rest/prise4', methods=['GET'])
    @cross_origin()
    def get_prise4():
        name = 'prise4'
        switch = list[name]
        node = app.zwave.network.nodes[switch['id']]
        prise = node.get_switches()[switch['switch']]
        json_return =  jsonify({'value':prise.data})
        json_body = {
            'name' : 'prise4',
            'fields' : {
                 'value' : prise.data
            }
        }
        #client.write_points(json_body)
        return json_return

    @app.route('/rest/prise4/<int:value>', methods=['PUT'])
    @cross_origin()
    def set_prise4(value):
        node = app.zwave.network.nodes[4]
        prise = node.get_switches()[72057594109837312L]
        if value == 1:
            prise.data = True
        else:
            prise.data = False
        return jsonify({'code':200})

    @app.route('/rest/prise/<int:id>/<int:value>', methods=['PUT'])
    def set_prise(id, value):
        node = app.zwave.network.nodes[id]
        prise = node.get_switches()[72057594109837312L]
        if value == 1:
            prise.data = True
        else:
            prise.data = False
        return jsonify({'code':200})

    from .zwave.zwavenetwork import ZWave
    app.zwave = ZWave(app)

    def introspect(network):
        print network.nodes
        node7 = network.nodes[7]
        print node7

    introspect(app.zwave.network)


    @app.route('/rest/list', methods=['GET'])
    @cross_origin()
    def get_list():
        return jsonify(list)


    return app
