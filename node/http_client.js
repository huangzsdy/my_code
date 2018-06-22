var http = require('http');
var options = { 
hostname: 'localhost', 
port: 30000, 
// path: null, 
method: 'POST' 
}; 
 
var req = http.request(options, function(res) { 
console.log('STATUS: ' + res.statusCode); 
console.log('HEADERS: ' + JSON.stringify(res.headers)); 
res.setEncoding('utf8');
data = ""; 
res.on('data', function (chunk) { 
console.log('BODY: ' + chunk); 
data += chunk;
}); 
res.on('end',function(){
	console.log(data);
});
}); 
 
req.on('error', function(e) { 
console.log('problem with request: ' + e.message); 
}); 
 
// write data to request body 
req.write('data\n'); 
req.write('data\n'); 
req.end();
