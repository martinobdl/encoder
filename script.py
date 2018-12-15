import io
from collections import Counter
from matplotlib import pyplot as plt
import copy
import math
import numpy as np

class GrowingList(list):
    def __setitem__(self, index, value):
        if index >= len(self):
            self.extend([0]*(index + 1 - len(self)))
        list.__setitem__(self, index, value)
    def __getitem__(self, index):
        if index >= len(self):
            return 0
        return list.__getitem__(self,index)

def bin2float(b):
    b=str(b)
    s, f = b.find('.')+1, int(b.replace('.',''), 2)
    return f/2.**(len(b)-s) if s else f

def float2bin(f):
    if f >= 1:
        g = int(math.log(f, 2))
    else:
        g = -1
    h = g + 1
    ig = math.pow(2, g)
    st = ""
    while f > 0 or ig >= 1:
        if f < 1:
            if len(st[h:]) >= 64: #64 fractional digits max
                   break
        if f >= ig:
            st += "1"
            f -= ig
        else:
            st += "0"
        ig /= 2
    st = st[:h] + "." + st[h:]
    return float("0"+st)

f = open("/Users/Martino/Documents/.GitHub/encoder/enwiki6.txt","r")

txt = f.read().decode("ascii", "ignore")

Omega = set(txt)

count = Counter(txt)

S = list(txt)[:18]

test = 0
if test: S= [2,1,0,0,1,3,3,3,3,3,3,0,0,0]

chars = np.array(count.keys())
if test: chars = np.arange(4)
p = np.array(count.values())/float(np.sum(count.values()))
if test: p = np.array([0.2,0.5,0.2,0.1])
dict_p = dict(zip(chars,p))
from decimal import *

cs = p.cumsum()
c = np.insert(cs,0,0)
dict_c = dict(zip(chars,c))
dict_c1 = dict(zip(chars,cs))

N = len(S)

#### encoding #####
def interval_update(s,b,l):
    if s==chars[-1]: y=l+b
    else: y=b+l*dict_c1[s]
    b=b+dict_c[s]*l
    l=y-b
    return (b,l)

def propagate_carry(t,d):
    n = t
    while d[n]:
        d[n] = 0
        n-=1
    d[n]=1
    return d

def encode_renormalization(b,l,t,d):
    while l<=0.5:
        t+=1
        l*=2
        if b>=0.5:
            d[t]=1
            b = 2*b-1
        else:
            d[t] = 0
            b*=2
    return (b,l,t,d)

def code_value_selection(b,t,d):
    t+=1
    if b<=0.5:
        d[t]=1
    else:
        d[t]=0
        d = propagate_carry(t-1,d)
    return d

d = GrowingList()
b=0; l=1
t = -1;
for s in S:
    b,l = interval_update(s,b,l)
    if b>1:
        b -= 1
        d = propagate_carry(t,d)
    if l<0.5:
        b,l,t,d = encode_renormalization(b,l,t,d);
    print s,b,l
d = code_value_selection(b,t,d)

with open('/Users/Martino/Documents/.GitHub/encoder/encoded.txt', 'wb') as f:
    for s in d:
        f.write(str(s))

v = bin2float(float("0."+"".join(map(str,d))))

print " "
##### decoding ########
def interval_selection(v,b,l):
    i = len(chars)-1
    s = chars[i]
    x = b+l*dict_c[s]
    y = b+l
    while x>v:
        i-=1
        s = chars[i]
        y = x
        x = b+l*dict_c[s]
    b = x
    l = y-b
    return s,b,l

def decoder_renormalization(v,b,l,t,d):
    while l<=0.5:
        if b>=0.5:
            b = 2*b -1
            v = 2*v -1
        else:
            b = 2*b
            v = 2*v
        t+=1
        v+=(2**-(P))*d[t-1]
        l*=2
    return b,l,v,t

P = 8
b=0; l=1

t = P
v = np.sum(np.array([2**-(n+1) * d[n] for n in range(P)]))
D = []

for k in range(N-5):
    s,b,l = interval_selection(v,b,l)
    if b>=1:
        b-=1;
        v-=1;
    if l<=0.5:
        b,l,v,t = decoder_renormalization(v,b,l,t,d)
    D.append(s)
    print s,b,l,v,(v>b and v<b+l)

assert(D == S)
