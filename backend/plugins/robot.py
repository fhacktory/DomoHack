# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random
import httplib

class Robot(restful.Resource, IPlugin):

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/rest/robot'

    def get(self):
        temperature = random()*6+17
        return {'temperature' : '%0.2f' % temperature}
