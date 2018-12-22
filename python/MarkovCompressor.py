from Write_bit import Write_bit
from specs import SPECS

class MarkovCompressor:
    def __init__(self,namefile,model):
        self.read_file = open(namefile, "rb")
        self.write_file = Write_bit(namefile+'.code')
        self.model = model

    def compress(self):
        high = SPECS["MAX"]
        low = 0
        pending_bits = 0
        s_old = 0
        while True:
            char = self.read_file.read(1)
            print char
            if not char:
                break
            s=ord(char)
            p = self.model.get_prob(s_old,s)
            l = high - low
            high = low + (l * p[1])/self.model.get_denom(s_old)
            low = low + (l * p[0])/self.model.get_denom(s_old)
            check = True
            while(check):
                print low,high,p,"\t",self.model.get_denom(s_old)
                if(high < SPECS["HALF"]):
                    self.emit(0,pending_bits)
                    high <<= 1
                    low <<= 1
                    pending_bits = 0
                elif(low > SPECS["HALF"]):
                    self.emit(1,pending_bits)
                    high = 2*(high - SPECS["HALF"])
                    low = 2*(low - SPECS["HALF"])
                    pending_bits = 0
                elif(low>SPECS["QUARTER"] and high<SPECS["TQUARTER"]):
                    pending_bits+=1
                    high = 2*(high - SPECS["QUARTER"])
                    low = 2*(low - SPECS["QUARTER"])
                else: check = False
            self.model.update(s_old,s)
            s_old = s
        s+=1
        if high < SPECS["QUARTER"]:
            self.emit(0,pending_bits)
        else:
            self.emit(1,pending_bits)
        self.read_file.close()
        self.write_file.close()

    def emit(self,bit,pending_bits):
        self.write_file.write(bit)
        for i in range(pending_bits):
            self.write_file.write(bit^1)
        pending_bits=0




