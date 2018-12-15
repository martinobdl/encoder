from collections import defaultdict
import ctypes
import copy

class interval:
    def __init__(self,low,high,den):
        self.low = low
        self.high = high
        self.den = den
    def __repr__(self):
        return "("+str(self.low)+","+str(self.high)+","+str(self.den)+")"

class GrowingList(list):
    def __setitem__(self, index, value):
        if index >= len(self):
            self.extend([0]*(index + 1 - len(self)))
        list.__setitem__(self, index, value)
    def __getitem__(self, index):
        if index >= len(self):
            return 0
        return list.__getitem__(self,index)
    def pop(self,index):
        if len(self)==0:
            return 0
        return list.pop(self,index)

test = 1
f = open("/Users/Martino/Documents/.GitHub/encoder/enwiki6.txt","r")
txt = f.read().decode("ascii", "ignore")[:100]
S = map(ord,txt)
N = len(S)

if test:
    S = [2,1,0,0,1,3,1,1,2,1]
    N = len(S)

#get probabilities
d = defaultdict(int)
for s in S:
    d[s] += 1

#sort dict in increasing prob
#----------------------------
c = defaultdict(int)
v_old = 0
cum = 0
for k,v in zip(d.keys(),d.values()):
    cum += v
    c[k] = interval(v_old,cum,N)
    v_old = cum

# encode
def output_bit(bit):
    E.append(bit)

def output_bit_plus_pending(bit, pending_bits):
    output_bit( bit )
    while ( pending_bits ):
        output_bit( bit^1 )
        pending_bits -= 1

Max = 0xFFFFFFFF+1 #2**32
high = Max-1
low = 0
E = GrowingList()
pending_bits = 0
for s in S:
    l=high - low+1
    p = c[s]
    high = low + (l * p.high)/p.den-1
    low = low + (l * p.low)/p.den
    tt = 1
    while tt:
        if ( high < 0x80000000 ):
            output_bit_plus_pending(0,pending_bits)
            low = (low << 1)%Max
            high = ((high << 1)%Max)|1
        elif ( low >= 0x80000000 ):
            output_bit_plus_pending(1,pending_bits)
            low = (low << 1)%Max
            high = ((high << 1)%Max)|1
        elif (low >= 0x40000000  and high < 0xC0000000):
            pending_bits+=1
            low = (low << 1)%Max
            low &= 0x7FFFFFFF
            high = (high << 1)%Max
            high |= 0x80000001
        else:
            tt = 0
print E


# decode
chars = d.keys()
def get_char(count):
    x = N
    k = len(chars)-1
    s = chars[k]
    while x>count:
        k-=1
        s = chars[k]
        x = c[s].low
    return s

def output_char(s):
    D.append(s)

high = 0xFFFFFFFF
low = 0
value = 0
encod = copy.copy(E)
for i in range(32):
    value <<= 1
    value += encod.pop(0)
tt=1
D = GrowingList()
for _ in range(N):
    l = high -low+1
    count = ((value - low+1) * N -1)/l
    s = get_char(count)
    output_char(s)
    p = c[s]
    high = low + (l * p.high)/p.den-1
    low = low + (l*p.low)/p.den
    ttt=1
    print value < high and value > low
    while ttt:
        if ( low >= 0x80000000 or high < 0x80000000 ) :
            low = (low << 1)%Max
            high = ((high << 1)%Max)| 1
            value = (value << 1)%Max
            value += encod.pop(0)
        elif(low >= 0x40000000 and high < 0xC0000000 ):
            low = (low << 1)%Max
            low &= 0x7FFFFFFF;
            high = (high << 1)%Max
            high |= 0x80000001;
            value = (value << 1)%Max
            value += encod.pop(0)
        else:
            ttt=0






