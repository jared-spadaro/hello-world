import * as http from 'http';
import * as filesystem from 'fs';

const hostname = '127.0.0.1';
const port = 3001;

const server = http.createServer((req, res) => {
   console.log(req.url);
   res.writeHead(200, {'Content-Type':'text/html'});
   res.end(myCallback);
});

function myCallback() {
   console.log('page fetch complete');
}

server.listen(port, hostname, () => {
   console.log(`Server running at http://${hostname}:${port}/`);
});
