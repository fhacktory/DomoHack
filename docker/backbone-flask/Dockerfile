FROM yougos666/docker-nginx

RUN apt-get update && \
	mkdir -p  /usr/share/nginx/html/js && \	
	apt-get install -y python python-pip  && \
	pip install flask && \
	apt-get autoremove && \
	apt-get clean

ADD start.sh /usr/local/bin/start.sh
RUN chmod -v +x /usr/local/bin/start.sh

ADD default /etc/nginx/sites-available/default

ADD supervisord.conf /etc/supervisord.conf

EXPOSE 80 5000

CMD ["/usr/local/bin/start.sh"] 
