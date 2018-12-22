import os
from Read_bit import Read_bit
from specs import SPECS

class Decompressor:
    def __init__(self,namefile,model):
        self.write_file = open(os.path.splitext(namefile)[0]+'.decode', "wb")
        self.read_file = Read_bit(namefile)
        self.model = model

    def decompress(self):
        high = SPECS["MAX"]
        low = 0
        value = 0
        for i in range(SPECS["PRECISION"]):
            value<<=1
            value+=self.read_file.read()
        for ii in range(self.model.count):
            l = high - low
            # high_tmp = high
            # low_tmp = low
            # for k in self.model.keys:
            #     (lower,upper) = self.model.c[k]
            #     high_tmp = low + (l * upper)/self.model.count
            #     low_tmp = low + (l * lower)/self.model.count
            #     if(low_tmp <= value and value < high_tmp):
            #         s = k
            s = self.get_char(low,value,high)
            print chr(s)
            self.write_file.write(chr(s))
            p = self.model.c[s]
            high = low + (l * p[1])/self.model.count
            low = low + (l * p[0])/self.model.count
            check = True
            while(check):
                print low,high
                if(high < SPECS["HALF"]):
                    high <<= 1
                    low <<= 1
                    value <<= 1
                    value += self.read_file.read()
                elif(low > SPECS["HALF"]):
                    high = (high - SPECS["HALF"])<<1
                    value = (value - SPECS["HALF"])<<1
                    low = (low - SPECS["HALF"])<<1
                    value += self.read_file.read()
                elif(low>SPECS["QUARTER"] and high<SPECS["TQUARTER"]):
                    high = (high - SPECS["QUARTER"])<<1
                    low = (low - SPECS["QUARTER"])<<1
                    value = (value - SPECS["QUARTER"])<<1
                    value += self.read_file.read()
                else: check = False
        self.read_file.close()
        self.write_file.close()

    def get_char(self,low,value,high):
        l = high - low
        for k in self.model.keys:
            (lower,upper) = self.model.c[k]
            high_tmp = low + (l * upper)/self.model.count
            low_tmp = low + (l * lower)/self.model.count
            if(low_tmp <= value and value < high_tmp):
                return k
        return k
