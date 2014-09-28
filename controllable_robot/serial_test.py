import sys
import serial
import tank_drive_test
import time
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=0)
ser2 = serial.Serial('/dev/rfcomm0', 9600, timeout=1)
print "is open:", ser.isOpen()
print "is open:", ser2.isOpen()
while True:
    ser.write("D")
    s = ser.readline()
    if s != '':
        try:
            t = s.split(',')
        except:
            pass
        else:
            if len(t) == 14:
                x, y = int(t[9]), int(t[10])
                left, right  = tank_drive_test.tankdrive(x, y)
                left_conv = min(255, max(0, abs(int(left)/2)))
                right_conv  = min(255, max(0, abs(int(right)/2)))
                if left < 0:
                    left_s = 'BACKWARD'
                else:
                    left_s = 'FORWARD'
                if right < 0:
                    right_s = 'BACKWARD'
                else:
                    right_s = 'FORWARD'
                cmd = "%s %d %s %d\r" % (left_s, left_conv, right_s, right_conv)
                print cmd
                ser2.write(cmd)
    time.sleep(0.1)
#    sys.stdout.write(s)

