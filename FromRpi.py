import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
    while True:
        CmdInput: str = CmdInput("CmdInput ur command!")
        CmdInput = CmdInput.upper()
        if CmdInput == "W":
            ser.write(b"W\n")

        elif CmdInput == "S":
            ser.write(b"S\n")

        elif CmdInput == "A":
            ser.write(b"A\n")

        elif CmdInput == "D":
            ser.write(b"D\n")

        elif CmdInput == "STOP":
            ser.write(b"STOP\n")
        else:
            raise IOError
