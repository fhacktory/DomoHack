import os

basedir = os.path.abspath(os.path.dirname(__file__))

class Config:
    SECRET_KEY = 'fHacktory C trop de la bombe'

    @staticmethod
    def init_app(app):
        pass

class DevConfig(Config):
    DEBUG = False
    IP_ROBOT = '192.168.3.98' 

config = {
    'devel' : DevConfig,
    'default' : DevConfig,
}
