#coding:utf-8

__author__ = 'hzs'

import gevent
from gevent import monkey
monkey.patch_all()

#from tests import TestAPI
import time,smtplib
from email.mime.text import MIMEText

sleepMin = 5
image_base_dir = 'images'

def send_mail(sub,text):
    _user ='lengyuenanfeng@163.com'
    _pwd  = 'Huang2016'
    _to = 'zesang.huang@faceall.cn'
    msg = MIMEText(text)
    msg['Subject'] = 'qingyun_heartbeat api tester - %s' % sub
    msg['To'] = _to
    try:
        s = smtplib.SMTP_SSL('smtp.163.com',465,timeout = 10)
        s.ehlo()
        s.starttls()
        s.ehlo()
        s.login(_user,_pwd)
        s.sendmail(_user,_to,msg.as_string())
        s.close()
    except Exception as e:
        print 'faild to send email: ',e

def send_mail2(sub,text):
    _user = 'lengyuenanfeng@163.com'
    _pwd = 'Huang2016'
    _to = 'zesang.huang@faceall.cn'
    msg = MIMEText(text,'plain','utf-8')
    msg['From'] = 'lengyuenanfeng@163.com'
    msg['Subject'] = 'qingyun_heartbeat api tester - %s' % sub
    msg['To'] = _to
    try:
        s = smtplib.SMTP('smtp.163.com',25)
        s.login(_user,_pwd)
        s.sendmail(_user,[_to],msg.as_string())
        s.quit()
    except smtplib.SMTPException as e:
        print 'error: ',e

def main(base_url,fout):
    send_mail2('test1','hello')
#    send_mail('test2','olleh')

if __name__ == '__main__':
    main(1,2)
