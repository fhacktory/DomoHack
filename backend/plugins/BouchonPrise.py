# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random

class BouchonPrise(restful.Resource, IPlugin):

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/rest/prise/<string:priseId>'

    def get(self, priseId):
        status = random()*2
        return {'status' : '%s' % int(status)}

    def put(self, priseId):
        value = request.form['value']
        return {'code' : 200,
                'value' : value}

