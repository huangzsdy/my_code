# -*- coding: utf-8 -*-
import smtplib
from email.mime.text import MIMEText
import os
import sys
import time

_user = "lengyuenanfeng@163.com"
_pwd  = "huangzesang3018"
_to   = "1224106361@qq.com"

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print('Usage: python mail.py process_num [msg]')
        exit(0)

    _process_id = sys.argv[1]
    _msg = None
    if len(sys.argv) > 2:
        _msg = sys.argv[2]

    #使用MIMEText构造符合smtp协议的header及body
    send_msg = 'process_id: ' + _process_id + ' finished!'
    if _msg is not None:
        send_msg += '\nmsg: ' + _msg
    msg = MIMEText(send_msg)
    msg["Subject"] = "finish work"
    msg["From"]    = _user
    msg["To"]      = _to

    # 监控进程
    while os.path.exists('/proc/' + _process_id) :
        time.sleep(2)

    s = smtplib.SMTP("smtp.163.com", timeout=30)#连接smtp邮件服务器,端口默认是25
    s.login(_user, _pwd)#登陆服务器
    s.sendmail(_user, _to, msg.as_string())#发送邮件
    s.close()
