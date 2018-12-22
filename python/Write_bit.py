class Write_bit:
    def __init__(self,namefile):
        self.namefile = namefile
        self.file = open(namefile,"wb")
        self.buffer=0;
        self.bits_in_buffer=0;
        self.CHAR_BIT = 8

    def write(self,bit):
        if(bit):
            self.buffer |= (1<<(self.CHAR_BIT-(self.bits_in_buffer+1)))
        self.bits_in_buffer+=1
        if(self.bits_in_buffer == self.CHAR_BIT):
            self.file.write(chr(self.buffer))
            self.buffer=0
            self.bits_in_buffer=0
        return

    def close(self):
        for i in range(self.bits_in_buffer, self.CHAR_BIT):
            self.write(0)
        #self.file.write("\x00")
        self.file.close();
        return



