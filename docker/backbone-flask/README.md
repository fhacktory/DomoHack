Docker for backbone and Flask
==============

This image is based on yougos666/nginx (dockerhub) 

Requirements
--------------

- docker: version 1.5

Installation
--------------

- Clone project
- Launch build: "docker build -t domohack/backbone-flask ."

Launch Docker container
--------------
docker run -d -p 80:80 -p 5000:5000 domohack/backbone-flask
