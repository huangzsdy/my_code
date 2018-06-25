import requests
url ='http://localhost:40000'
res = requests.post(url)
print res.content
