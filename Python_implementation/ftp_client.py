import socket
import sys
import os
import time
def Main():
    host = '127.0.0.1'
    port = 5000
    start=0
    end=0
    s = socket.socket()
    s.connect((host, port))

    filename = input("Enter Filename -> ")
    if filename != 'q':
        s.send(filename.encode())
        data = s.recv(1024)
        data=data.decode()
        if data[:6] == 'EXISTS':
            filesize = int(data[6:])
            message = input("File exists, " + str(filesize) +" Bytes, download? (Y/N)? -> ")
            if message == 'Y':
                s.send("OK".encode())
                start=time.clock()
                f = open(filename, 'wb')
                data = s.recv(1024)
                totalRecv = len(data)
                f.write(data)
                while totalRecv < filesize:
                    data = s.recv(1024)
                    totalRecv += len(data)
                    f.write(data)
                    if sys.platform=='linux' or sys.platform=='linux2':
                        os.system('clear')
                    else:
                        os.system('cls')
                    print ("{0:.2f}".format((totalRecv/float(filesize))*100)+ "% Downloading Done")
                end=time.clock()
                end=(end-start)/60
                print ("Download Completed! Downloading took %.4f minutes"%end)
                end=end*60
                speed=(filesize/1024)/end
                print("Average Download Speed:%.2f Kbps"%speed)
                time.sleep(6)
                f.close()
            else:
                print("Program Terminated")
                time.sleep(2)
                
        else:
            print ("File Does Not Exist!")
            time.sleep(2)

    s.close()
    
Main()
