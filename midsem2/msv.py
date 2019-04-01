import socket
import os

s1 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print("created")

s1.bind(('',8888))
s2.bind(('',8080))

print("binded")

while(1):

	d = s1.recvfrom(4096)
	addr = d[1]
	arg = d[0].decode().split()[1]

	cmd = d[0].decode().split()[0]

	if cmd == "rwd" :
		path = arg
		if os.path.isdir(path):
			os.chdir(path)
			print("path changed to" + str(os.getcwd()))
		else :
			print("Directory not found")

	if cmd == "send" :
		fname = arg
		print(fname)
		s1.sendto("OK".encode(),addr)
		fl = ""
		f = open(fname,"wb")
		fl = s2.recvfrom(4096)
		f.write(fl[0])
		f.close()

	if cmd == "store" :
		if os.path.isfile(arg):
			s1.sendto("OK".encode(), addr)
			f = open(arg,"rb")
			dat = f.read()
			adds = s2.recvfrom(4096)[1]
			# print(adds)
			s2.sendto(dat, adds)
		else :
			s1.sendto("nf".encode(), addr)