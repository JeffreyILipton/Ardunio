import serial

class IRInterface:
    def __init__(self):
        self.ser = serial.Serial()
    def __del__(self):
        self.ser.close()
    def connect(self,port,baud):
        if (self.ser.isOpen()): self.ser.close()
        self.ser.setPort(port)
        self.ser.baudrate = baud
        self.ser.open()
    def isready(self):
        return self.ser.isOpen()
    def write(self,towrite):
        if (not self.isready()):
            return False;
        else:
            print "new: "+towrite
            self.ser.write(towrite)
    

if __name__ == '__main__':
    ir = IRInterface()
    ir.connect("COM10",9600)
    print ir.isready()
    loopVar=True
    while(loopVar):
        val = raw_input('Command:')
        ir.write(val)
        if (val == 'N'):
            loopVar = False