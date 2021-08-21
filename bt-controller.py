import serial
import time

serialcomm = serial.Serial('COM8', 9600)
serialcomm.timeout = 1

while True:
    i = input("Input: ").strip()
    if i == "exit":
        break
    serialcomm.write(i.encode())
    time.sleep(0.5)
    print(serialcomm.readline().decode('ascii'))

serialcomm.close
