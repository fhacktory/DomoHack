# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from random import random
import httplib

class Yana(restful.Resource, IPlugin):

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/yana-server/action.php?action=GET_SPEECH_COMMAND&token=b6bf2783483406bf7427fe51cc1bbc0b32e3df53'

    def get(self):
        temperature = random()*6+17
        return {'temperature' : '%0.2f' % temperature}
