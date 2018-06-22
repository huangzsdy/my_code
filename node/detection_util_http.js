var fs = require("fs");
var net = require("net");
var path = require('path');
var thisConfig = require('./config.js').detection;
var http = require('http');

var tmpPath = mainConfig.tmpDir;
var thisPosition = 'v2/detection/utils/detection_5_util';

var async = require('async');

/**
 * deifne the batch processor constructor
 * @constructor
 */
function BatchProcessor(taskBatch, callback, resource) {
    this._sockCmd = null;
    this._taskBatch = taskBatch;
    this._callback = callback;
    this._port = resource['port'];
    this._host = resource['host'];
}

BatchProcessor.prototype._error = function (err) {
    for (var taskIndex in this._taskBatch) {
        this._taskBatch[taskIndex].callback(err);
    }
    this._callback(err);
};

BatchProcessor.prototype._success = function (result) {
    var that = this;
    var resultArr = JSON.parse(result);

    if (resultArr.length != that._taskBatch.length) {
        sysout.sysErr(thisPosition + ": result's length (" + resultArr.length + ") does not match task's length (" + that._taskBatch.length + "). _sockCmd: " + that._sockCmd);
        that._error(statusCode.INTERNAL_ERROR);
        return;
    }

    for (var i in that._taskBatch) {
        var thisResult = resultArr[i];
        that._taskBatch[thisResult.id].callback(null, thisResult);
    }

    that._callback(null);
};

BatchProcessor.prototype.work = function () {
    var times = [Date.now()];
    var timeIndex = 1;
    var that = this;

    //sysout.sysDebug('detect util batch num :' + that._taskBatch.length);

    var imagePathArr = [];
    for (var i in that._taskBatch) {
        imagePathArr.push(that._taskBatch[i].data);
        imagePathArr[i].id = i;
    }

    sysout.sysDebug(thisPosition + ' batch num: ' + that._taskBatch.length + ' resource: ' + that._host + ':' + that._port);

    var tmpHash = Date.now() + "" + Math.random();
    var inputPath = path.join(tmpPath, tmpHash + ".v2.detect.input.json");
    var outputPath = path.join(tmpPath, tmpHash + ".v2.detect.output.json");
    that._httpContent = inputPath + "#" + outputPath + "#detect";

    fs.writeFile(inputPath, JSON.stringify(imagePathArr), function (err) {
        if (err) {
            sysout.sysErr(thisPosition + ' write input: ' + err + '. _sockCmd: ' + that._sockCmd);
            that._error(statusCode.INTERNAL_ERROR);
            return;
        }

        times[timeIndex] = Date.now();
        sysout.sysDebug('detect util write input file time : ' + (times[timeIndex] - times[timeIndex-1])); // 0.01
        ++timeIndex;

        var options = {
            hostname:that._port,
            port:that._host,
            method:'POST',
        };
        var connectionBody = "";
        var req = http.request(options,function(res){
            res.on('data',function(chunk){
                connectionBody += chunk;
            });
            res.on('end',function(){
                console.log('here');
                process.exit(0);
                if (connectionBody != 'finished') {
                    sysout.sysErr(thisPosition + ' end http got this data: ' + connectionBody + '. _httpContent: ' + that._httpContent + ' resource: ' + that._host + ':' + that._port);
                    that._error(statusCode.INTERNAL_ERROR);
                    return;
                }

                times[timeIndex] = Date.now();
                sysout.sysDebug('detect util get result time : ' + (times[timeIndex] - times[timeIndex-1])); // 0.5
                ++timeIndex;

                fs.readFile(outputPath, function (err, result) {
                    if (err) {
                        sysout.sysErr(thisPosition + ' read output error: ' + err + '. _httpContent: ' + that._httpContent);
                        that._error(statusCode.INTERNAL_ERROR);
                        return;
                    }

                    times[timeIndex] = Date.now();
                    sysout.sysDebug('detect util read output time : ' + (times[timeIndex] - times[timeIndex-1])); // 0
                    ++timeIndex;

                    that._success(result);
                });
            });
        });

        times[timeIndex] = Date.now();
        sysout.sysDebug('detect util http request time : ' + (times[timeIndex] - times[timeIndex-1])); // 0
        ++timeIndex;

        req.setTimeout(2,function(){
            sysout.sysErr(thisPosition + ' http timeout. _httpContent: ' + that._httpContent);
        });
        req.on('error',function(err){
            if (err) {
                sysout.sysErr(thisPosition + ' http error: ' + err + '. _httpContent: ' + that._httpContent);
                that._error(statusCode.INTERNAL_ERROR);
            }
        });
        req.write(that._httpContent);
        req.end();













        var socketConnection = new net.Socket();
        var connectionBody = "";
        socketConnection.connect(that._port, that._host);
        socketConnection.setTimeout(60 * 1000, function() {
            sysout.sysErr(thisPosition + ' socket timeout. _sockCmd: ' + that._sockCmd);
            socketConnection.destroy();
        });

        times[timeIndex] = Date.now();
        sysout.sysDebug('detect util write socket time : ' + (times[timeIndex] - times[timeIndex-1])); // 0
        ++timeIndex;

        socketConnection.on('data', function (d) {
            connectionBody += d;
        });

        socketConnection.on("close", function (had_error) {
            if (had_error) {
                sysout.sysErr(thisPosition + ' close socket err had_error. _sockCmd: ' + that._sockCmd + ' resource: ' + that._host + ':' + that._port);
                that._error(statusCode.INTERNAL_ERROR);
                return;
            }
            if (connectionBody != 'finished') {
                sysout.sysErr(thisPosition + ' close socket got this data: ' + connectionBody + '. _sockCmd: ' + that._sockCmd + ' resource: ' + that._host + ':' + that._port);
                that._error(statusCode.INTERNAL_ERROR);
                return;
            }

            times[timeIndex] = Date.now();
            sysout.sysDebug('detect util get result time : ' + (times[timeIndex] - times[timeIndex-1])); // 0.5
            ++timeIndex;

            fs.readFile(outputPath, function (err, result) {
                if (err) {
                    sysout.sysErr(thisPosition + ' read output error: ' + err + '. _sockCmd: ' + that._sockCmd);
                    that._error(statusCode.INTERNAL_ERROR);
                    return;
                }

                times[timeIndex] = Date.now();
                sysout.sysDebug('detect util read output time : ' + (times[timeIndex] - times[timeIndex-1])); // 0
                ++timeIndex;

                that._success(result);
            });
        });

        socketConnection.on('error', function (err) {
            if (err) {
                sysout.sysErr(thisPosition + ' socket error: ' + err + '. _sockCmd: ' + that._sockCmd);
                that._error(statusCode.INTERNAL_ERROR);
            }
        });

        socketConnection.end(that._sockCmd);






    });
};
/*
end of constructor definition
 */


var pool = new processUtils.Pool(thisConfig.resources, BatchProcessor);
pool.start();

exports.detection = function (imagePath, callback) {
    var cacheKey = imagePath.path;
    cache.get(cacheKey, function (err, result) {
        if (result) {
            callback(null, result);
            return;
        }

        pool.pushTask({
            data: imagePath,
            callback: function (err, result) {
                if (err) {
                    callback(err);
                    return;
                }

                cache.set(cacheKey, result);
                callback(null, result);
            }
        });
    });
};