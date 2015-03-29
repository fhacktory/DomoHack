# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random
import httplib

class RobotW(restful.Resource, IPlugin):

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/rest/robotw/<string:value>'

    def put(self, value):
        connection =  httplib.HTTPConnection('192.168.3.98')
        body_content = ''
        connection.request('PUT', '/servo/%s' % value, body_content)
        return {'code' : 200}
