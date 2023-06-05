
import serial, time, sys, datetime
from datetime import datetime

print("Press Ctrl+C to save and stop the logging")
baud_rate = 115200  
default = time.strftime("log1_%Y%m%d_%H%M.csv")
serial_port = "/dev/ttyACM1"  #  listening port, type ls /dev/ttyUSB* in shell for available ports
if len(sys.argv) == 2:
    logfile_name = sys.argv[1]
else:
    logfile_name = default

output_file = open(logfile_name, "a+")
ser = serial.Serial(serial_port, baud_rate)
count = 0

try:
    while True:
        line = ser.readline()
        line = line.decode("utf-8")  
        timeNow = datetime.now()
        outputline = "".join((str(timeNow), ", ", line))

        if line != "\n":			# not record an empty line
            print(timeNow,line)
            output_file.write(outputline)
            count += 1
        else:
            continue
            #  print("\nnothing here")
        if count >= 10:
            output_file.close()
            output_file = open(logfile_name, "a+")
            count = 0
		
except KeyboardInterrupt:
    print(">> Ctrl+C pressed, stop logging to {} file".format(logfile_name))
    output_file.close()
    raise SystemExit
