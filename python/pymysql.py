import pymysql,json
import random,sys

config = {
	'host':'rm-2ze62x5op893nrn34.mysql.rds.aliyuncs.com',
	'port':3306,
	'user':'root',
	'passwd':'ThinkVision00',
	'db':'search'
}
FACE_TABLE = 'faceFeature'
IMAGE_TABLE = 'image'


def test():
	connection = pymysql.connect(**config)
	with connection.cursor() as cursor:
		sql = 'select faceId from ' + FACE_TABLE + ' where status=%s'
		cursor.execute(sql,('true'))
		rows = cursor.fetchall()
		print rows

def dbInsertDet(faceId,detectionResult):
	with connection.cursor() as cursor:
		sql = 'update ' + FACE_TABLE + ' set detectionResult=%s,apiKey=%s where faceId = %s'#
		cursor.execute(sql,(detectionResult,apiKey,faceId))
		
def insertDet():
	map_det = {}
	data = [o.strip() for o in open('../db20170421/det20170421')]
	i = 0
	while(i < len(data) -1):
		map_det[data[i]] = data[i+1]
		i+=2

	print len(map_det.keys())
	faceIds = map_det.keys()
	random.shuffle(faceIds)

	for i in xrange(len(faceIds)):
		try:
			print faceIds[i],map_det[faceIds[i]]
			dbInsertDet(faceIds[i],map_det[faceIds[i]])
			if i %100 == 0:
				connection.commit()
				print 'commit',i

		except Exception,e:
			print e
			continue		

def dbInsertImageId(faceId,imageId,apiKey,path,name):
	with connection.cursor() as cursor:
		sql_1 = 'update ' + FACE_TABLE + ' set imageId=%s,apiKey=%s where faceId = %s'#
		cursor.execute(sql_1,(imageId,apiKey,faceId))

		sql_2 = 'insert into ' + IMAGE_TABLE + ' (imageId,apiKey,name,path) values(%s,%s,%s,%s) on duplicate key update apiKey=values(apiKey),name=values(name),path=values(path)'#
		cursor.execute(sql_2,(imageId,apiKey,name,path))



def insertImage():
	imageIdData =  [o.strip() for o in open('logs/getImageId')]
	faceIdOri = [o.strip().split()[0] for o in open('logs/insertImageId.log_1')]
	for i in xrange(len(imageIdData)):
		tmp = imageIdData[i].split()
		if tmp[0] in faceIdOri:
			continue
		else:
			faceId = tmp[0]
			imageId = tmp[1]
			imageName = tmp[2]
			imagePath = tmp[3]
			print imageIdData[i]
			dbInsertImageId(faceId,imageId,apiKey,imagePath,imageName)
			if i % 100 == 0:
				connection.commit()
				print 'commit',i 


def test():
	with connection.cursor() as cursor:
		sql =  'insert into ' + IMAGE_TABLE + ' (imageId,apiKey,name,path) values(%s,%s,%s,%s) on duplicate key'+ ' update ' + IMAGE_TABLE + ' apiKey=values(apiKey)'
		cursor.execute(sql,(imageId,apiKey,name,path))

if __name__ == '__main__':
	connection = pymysql.connect(**config)
	apiKey = 'omhb0QSUL6Cj7XtprIO0UGIxy5WUnHgu7j3ABrtY'

	if sys.argv[1] == 'image':
		insertImage()
	elif sys.argv[1] == 'detection':
		insertDet()
	
	# exit()



