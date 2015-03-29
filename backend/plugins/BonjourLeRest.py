# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful

class BonjourLeRest(restful.Resource, IPlugin):

    def register_app(self,app):
        self.app = app

    def route(self):
        return '/rest/hello'

    def get(self):
        return {'value' : 'BonjourLeRest'}

    def put(self):
        value = request.form['value']
        return {'return': 'OK value = %s' % value}


