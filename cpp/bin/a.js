fs = require('fs');

fs.readFile('tmp.txt',{encoding: 'utf8'},function(err,result){
    if(err)
        console.log(err);
    else{
        console.log('--content---');
        var tmp = JSON.parse(result);
        console.log(tmp.data[0]);
        
    }
});
