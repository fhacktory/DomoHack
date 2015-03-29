# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random

class Rfid(restful.Resource, IPlugin):

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/rest/rfid/<string:carteId>'

    def get(self, carteId):
        temperature = random()*6+17
        return {'temperature' : '%0.2f' % temperature}

    def put(self, carteId):
        return {'code' : 200}
