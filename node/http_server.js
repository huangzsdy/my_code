var http = require('http');

var server = http.createServer(function(req,res){
    res.writeHeader(200,{'Content-Type':'text/plain'});
    res.end('hello world');
});



server.setTimeout(0,function(){
    console.log('timeout');
});

server.listen(30000,'localhost',function(){
    console.log('listening port 3000');
});
