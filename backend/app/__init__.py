# -*- coding: utf-8 -*-
from flask import Flask, request
from flask.ext import restful
from config import config

class BonjourLeRest(restful.Resource):
    def get(self):
        return {'value' : 'BonjourLeRest'}

    def put(self):
        value = request.form['value']
        return {'return': 'OK value = %s' % value}

def create_app(config_name):
    app = Flask(__name__)
    api = restful.Api(app)
    api.add_resource(BonjourLeRest,'/rest/hello')
    app.config.from_object(config[config_name])
    config[config_name].init_app(app)
    return app

