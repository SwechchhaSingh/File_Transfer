

import socket
import threading
import os

def RetrFile(name, sock):
    filename = sock.recv(1024)
    filename=filename.decode()
    if os.path.isfile(filename):
        data="EXISTS " + str(os.path.getsize(filename))
        try:
            sock.send(data.encode())
            userResponse = sock.recv(1024)
            userResponse=userResponse.decode()
            if userResponse[:2] == 'OK':
                with open(filename, 'rb') as f:
                    bytesToSend = f.read(1024)
                    sock.send(bytesToSend)
                    while bytesToSend != "":
                        bytesToSend = f.read(1024)
                        sock.send(bytesToSend)
        except:
            print("Connection Error")
    else:
        sock.send("ERR ".encode())

    sock.close()
    print("Connection Closed")

def Main():
    host = '127.0.0.1'
    port = 5000


    s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    s.bind((host,port))

    s.listen(5)

    print ("Server Started.")
    while True:
        c, addr = s.accept()
        print ("client connedted ip:<" + str(addr) + ">")
        t = threading.Thread(target=RetrFile, args=("RetrThread", c))
        t.start()
         
    s.close()

Main()





