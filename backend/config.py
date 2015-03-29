import os

basedir = os.path.abspath(os.path.dirname(__file__))

class Config:
    SECRET_KEY = 'fHacktory C trop de la bombe'

    @staticmethod
    def init_app(app):
        pass

class DevConfig(Config):
    DEBUG = False

config = {
    'devel' : DevConfig,
    'default' : DevConfig,
}
