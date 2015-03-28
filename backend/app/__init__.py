# -*- coding: utf-8 -*-
from flask import Flask, request
from flask.ext import restful
from config import config
from random import random

class BonjourLeRest(restful.Resource):
    def get(self):
        return {'value' : 'BonjourLeRest'}

    def put(self):
        value = request.form['value']
        return {'return': 'OK value = %s' % value}

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

class BouchonSonde(restful.Resource):
    def get(self, sondeId):
        temperature = random()*6+17
        return {'temperature' : '%0.2f' % temperature}

    def put(self, sondeId):
        value = request.form['value']
        return {'code' : 200,
                'value' : value}

class BouchonPrise(restful.Resource):
    def get(self, priseId):
        status = random()*2
        return {'status' : '%s' % int(status)}

    def put(self, priseId):
        value = request.form['value']
        return {'code' : 200,
                'value' : value}

def create_app(config_name):
    app = Flask(__name__)
    api = restful.Api(app)
    api.add_resource(BonjourLeRest,'/rest/hello')
    api.add_resource(ListDevices,'/rest/list')
    api.add_resource(BouchonSonde,'/rest/sonde/<string:sondeId>')
    api.add_resource(BouchonPrise,'/rest/prise/<string:priseId>')
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)
    return app


