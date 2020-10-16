FROM node:12

WORKDIR /node
COPY src/package*.json ./
COPY src/app.js ./
RUN npm install

COPY src/flag /flag
RUN chmod 777 /flag

COPY src/run.sh /run.sh
RUN chmod +x /run.sh

EXPOSE 80

CMD ["/run.sh"]
