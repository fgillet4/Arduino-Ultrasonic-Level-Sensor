import serial

connected = False

# Establish connection to the serial port that your arduino is connected to
locations=['/dev/ttyUSB0','/dev/ttyUSB1','/dev/ttyUSB2’,’/dev/ttyUSB3']
arduinoData = serial.Serial('COM3',9600)
for device in locations:
    try:
        print(f'Trying… {device}')
        ser = serial.Serial(device, 9600)
        break
    except:
        print(f'Failed to connect on, {device}')
while not connected:
    serin = serial.read()
    connected = True

with open('data.txt', 'at') as text_file:
    while connected:
        arduinoString = arduinoData.readline().decode();
        dataArray = arduinoString.split(',');
        text_file.write(dataArray)
