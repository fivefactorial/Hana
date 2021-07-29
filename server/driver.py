import serial

ser = serial.Serial('/dev/ttyACM0', 9600, timeout=5)

print (ser.readline())

ser.write(b'20\n')
