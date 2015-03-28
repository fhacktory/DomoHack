from flask import Blueprint

zwave = Blueprint('zwave', __name__)

from . import views, errors

