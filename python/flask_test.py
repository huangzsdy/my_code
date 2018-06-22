#coding:utf-8
import requests
from threading import Thread,Semaphore
from flask import Flask,request,jsonify

app = Flask(__name__)
def process():
	print 'start process!'

@app.route('/here/<id>',methods=['POST'])
def here(id):
	if 'video' in request.form:
		return jsonify({'id':id})

if __name__ == '__main__':
	app.run(host='0.0.0.0',port=5000,threaded=True,debug=True)