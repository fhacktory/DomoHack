DomoHack : Backend
==================

Installation
------------

* Clone repo
* Install requirement

.. code-block:: bash

    pip install -f requirements.txt


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
