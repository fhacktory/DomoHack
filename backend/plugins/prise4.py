# -*- coding: utf-8 -*-
from yapsy.IPlugin import IPlugin
from flask.ext import restful
from flask import jsonify
from random import random

class Prise(restful.Resource, IPlugin):
    app = None

    def register_app(self, app):
        self.app = app

    def route(self):
        return '/rest/prise4/<string:value>'

    def get(self, value):
        status = random()*2
        return {'status' : '%s' % int(status)}

    def put(self, value):
        node = self.app.zwave.network.nodes[4]
        prise = node.get_switches()[72057594109837312L]
        if value == 1:
            prise.data = True
        else:
            prise.data = False
        return jsonify({'code':200})

