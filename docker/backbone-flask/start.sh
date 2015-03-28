#!/bin/bash
# start all the services

pip install -r /opt/backend/requirements.txt

/usr/bin/supervisord -n
