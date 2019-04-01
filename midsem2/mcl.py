import socket
import sys
import os


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

s2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
 
host = 'localhost'
port1 = 8888
port2 = 8080

def foo(name):
    with open(name, 'rb') as f:
        return f.read()



while (1) :

	msg = input("Enter cmd : ")

	cmd = msg.split()[0]

	if(cmd == "cwd") :
		if os.path.isdir(msg.split()[1]):
			os.chdir(msg.split()[1])
			print(os.getcwd())
			print("path changed to" + str(os.getcwd()))
		else:
			print("Directory not Found")
	
	if(cmd == "rwd") :
		s.sendto(msg.encode(), (host,port1))

	if(cmd == "send") :
		s.sendto(msg.encode(), (host,port1))
		rep = s.recvfrom(1024)
		data = rep[0].decode()
		addr = rep[1]
		print(data)
		# if os.path.isfile(msg.split()[1]):
		f = open(msg.split()[1],"rb")
		dat = f.read()
		s.sendto(dat, (host,port2))
		# else:
			# print("FILE NOT FOUND")
	
	if(cmd == "store") :
		s.sendto(msg.encode(), (host,port1))

		f = open(msg.split()[1],"wb")

		err = s.recvfrom(4096)
		if err != "nf":
			s2.sendto("Send".encode(), (host,port2))

			dat = s2.recvfrom(4096)

			f.write(dat[0])

			f.close()
		else :
			print("FILE NOT FOUND")