class Read_bit:
    def __init__(self,namefile):
        self.namefile = namefile
        self.file = open(namefile,"rb")
        self.buffer=0;
        self.bits_in_buffer=0;
        self.CHAR_BIT = 8

    def read(self):
        bit=0
        if(self.bits_in_buffer==0):
            try:
                self.char = ord(self.file.read(1))
                self.bits_in_buffer = self.CHAR_BIT
            except:
                self.char = 0
        bit = self.char >> (self.CHAR_BIT-1)
        self.bits_in_buffer-=1
        self.char<<=1
        self.char&=0xFF
        return bit

    def close(self):
        self.file.close();
        return



