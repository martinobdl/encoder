class int32:
    def __init__(self,bits = [0]*32):
        self.bits = [0]*32
        self.bits[-min(len(bits),32):] = bits[-min(len(bits),32):]
        self.check(bits)

    def value(self):
        res = 0
        for n,bit in enumerate(self.bits):
            res += bit*2**(31-n)
        return res

    def check(self,bits):
        for i in bits:
            if i not in [0,1]:
                print "err. bits are 0 or 1."
                self.bits = [0]*32

    def __repr__(self):
        return str(self.value())

    def __len__(self):
        return len(self.bits)

    def __add__(self,other):
        res = int32()
        carry = 0
        for i in range(31,-1,-1):
            s = self.bits[i]^other.bits[i]^carry
            res.bits[i] = s
            carry = (self.bits[i] & other.bits[i]) | (other.bits[i] & carry) | (self.bits[i] & carry)
        return res

    def max():
        self.bits = [1]*32

    def __lshift__(self,n):
        res = int32(self.bits)
        for i in range(n):
            _ = res.bits.pop(0)
            res.bits.append(0)
        return res

    def __rshift__(self,n):
        res = int32(self.bits)
        for i in range(n):
            _ = res.bits.pop(-1)
            res.bits.insert(0,0)
        return res

    def __mul__(self,other):
        res = int32()
        a = int32(self.bits)
        for i in range(31,-1,-1):
            if other.bits[i]:
                res = res + (a << (32-i-1))
        return res

    def num_of_bits(self):
        return 32-self.bits.index(1)

    def print_bits(self):
        if not self.num_of_bits():
            return str(0)
        return "".join(map(str,self.bits[-self.num_of_bits():]))

    def __lt__(self,other):
        return self.value() < other.value()

    def __le__(self,other):
        return self.value() <= other.value()

    def __eq__(self,other):
        return self.value() == other.value()

    def __ne__(self,other):
        return self.value() != other.value()

    def __ge__(self,other):
        return self.value() >= other.value()

    def __gt__(self,other):
        return self.value() > other.value()

    def __neg__(self):
        res = int32()
        for i in range(32):
            res.bits[i] = self.bits[i]^1
        return res+int32([1])

    def __sub__(self,other):
        return self+(-other)

    def __div__(self,other):
        Q = int32()
        R = int32(self.bits)
        while R >= other:
            Q = Q + int32([1])
            R = R - other
        return Q

    def from_int(self,N):
        return int32(map(int,list("{0:b}".format(N))))
