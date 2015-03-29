DomoHack : Backend
==================

Installation
------------

* Clone repo
* Install requirement

.. code-block:: bash

    pip install -f requirements.txt

* Démarrage du serveur

.. code-block:: bash

    python manage.py runserver


Architecture
------------

* Python + Framework Flask


TEST
----

HelloWorld 
~~~~~~~~~~~

* Get

.. code-block:: bash

    curl http://localhost:5000/rest/hello -X GET

* Put

.. code-block::

     curl http://localhost:5000/rest/hello -d "value=christophe" -X PUT


Sonde
~~~~~

* Get 

.. code-block::

    curl http://localhost:5000/rest/sonde/[Nom de la sonde] -X GET

* PUT

.. code-block::

     curl http://localhost:5000/rest/sonde/[Nom de la sonde] -d "value=3" -X PUT

Prise
~~~~~

* Get : Retourne le status de la prise (0,1)

.. code-block::

    curl http://localhost:5000/rest/prise/[Nom de la prise] -X GET

* PUT : Mettre dans Value 1, ou 0

.. code-block::

     curl http://localhost:5000/rest/prise/[Nom de la prise] -d "value=0" -X PUT


Docker
------

docker run -d -p 8083:8083 -p 8084:8084 -e PRE_CREATE_DB="domohack" tutum/influxdb

