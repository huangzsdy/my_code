# coding:utf8

import socket
import subprocess
import sys


class Server:
    def __init__(self, port):
        self._port = port
        self._process = None

    def start(self):
        print 'start'
        cmd = './ad_server 0.0.0.0 {}'.format(self._port).split(' ')
        self._process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, shell=False)
        lines_iterator = iter(self._process.stdout.readline, b'')
        for line in lines_iterator:
            if line.startswith('load model'):
                print 'success'
                return 'success'

    def stop(self):
        self._process.terminate()
        com = self._process.communicate()
        print 'stopped:', com

    def det(self, buf):
        ret = 'complicated'
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            print 'send to', ('127.0.0.1', self._port)
            sock.connect(('127.0.0.1', self._port))
            sock.settimeout(15)
            sock.send(buf)
            sock.shutdown(socket.SHUT_WR)
            ret = sock.recv(1024)
        except Exception as e:
            print 'det', Exception, e
        finally:
            sock.close()
            return ret

def go(port):
    server_ip = "0.0.0.0"
    server_port = port
    underlying_server_port = port + 10
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((server_ip, server_port))
    sock.listen(1)

    server = Server(underlying_server_port)
    server.start()

    while True:
        result = ''
        connection, address = sock.accept()
        try:
            connection.settimeout(10)  
            buf = connection.recv(1024 * 1024)
            print 'recv from client', buf
            result = server.det(buf)
            connection.sendall(result)
        except Exception as e:
            print 'go', Exception, e
            try:
                connection.sendall('ERROR: ' + str(e)[:64])
            except: pass
        finally:
            connection.close()
            if result == 'complicated':
                server.stop()
                server.start()

if __name__ == "__main__":
    port = int(sys.argv[1])
    go(port)
