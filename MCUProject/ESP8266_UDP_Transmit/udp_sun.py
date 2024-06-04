from socket import AF_INET, SOCK_DGRAM, socket

HOST = ''
PORT = 12345

s = socket(AF_INET, SOCK_DGRAM)

s.bind((HOST, PORT))

while True:
    rcv_data, addr = s.recvfrom(1024)
    print("receive data : [{}]  from {}".format(rcv_data, addr))

s.close()
