# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random

class BouchonSonde(restful.Resource, IPlugin):

    def route(self):
        return '/rest/sonde/<string:sondeId>'

    def get(self, sondeId):
        temperature = random()*6+17
        return {'temperature' : '%0.2f' % temperature}

    def put(self, sondeId):
        value = request.form['value']
        return {'code' : 200,
                'value' : value}
