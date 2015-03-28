FROM domofwk/nginx

RUN apt-get update && \
	mkdir -p  /usr/share/nginx/html/js && \	
	apt-get install -y python python-pip  && \
	pip install flask && \
	apt-get autoremove && \
	apt-get clean

EXPOSE 80 5000

CMD ["/usr/local/bin/start.sh"] 