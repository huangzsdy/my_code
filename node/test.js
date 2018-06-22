var fs = require('fs');
var request = require('request');

var img_url = process.argv[2];
var img_path = 'a.jpg';
request({
  method: 'GET',
  uri: img_url,
  timeout: 2 * 1000,
  encoding: null // otherwise the response body will be a string!
}, function(err, response, body) {
  if(err)
   console.log('error ' + err);
  else{
   fs.open(img_path,'w',function(err,fd){
    if(err)
     console.log('open file error',err);
   else{
     fs.createWriteStream(null,{fd:fd}).write(body);
     fs.fsync(fd,function(err){
       if(err)
         console.log('fsync error ' +err);
       fs.close(fd,function(err){
         if(err)
           console.log('close error ' +err);
       });
     });
    }
   });
  }
});

