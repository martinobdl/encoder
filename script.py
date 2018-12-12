import io
from collections import Counter
from matplotlib import pyplot as plt
import copy
import math
import numpy as np

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

f = open("/Users/Martino/Documents/GitHub/arithmeticEnc/enwiki6.txt","r")

txt = f.read().decode("ascii", "ignore")

Omega = set(txt)

count = Counter(txt)

S = list(txt)[:100]

#S= [2,1,0,0,1,3]

chars = np.array(count.keys())
#chars = np.arange(4)
p = np.array(count.values())/float(np.sum(count.values()))
#p = np.array([0.2,0.5,0.2,0.1])
dict_p = dict(zip(chars,p))

#p = {0:0.2, 1:0.5, 2:0.2, 3:0.1}
c = np.insert(p.cumsum(),0,0)
dict_c = dict(zip(chars,c))

b0=0; l0=1;
b=b0; l=l0; k=0
for s in S:
    k+=1
    b=b+dict_c[s]*l
    l=dict_p[s]*l
    #print k,s,b,l

Bmin = int(math.ceil(math.log(l,2)*(-1)))

x = (b0+l0/2)
k=1
while x < b or x > b+l:
    k+=1
    if x < b:
        x+=l0*2**(-k)
    if x > b+l:
        x-=l0*2**(-k)

float2bin(x)

enc = x

decoded = np.array([])
v = (x-b0)/l0
for cnt in range(len(S)):
    tmp = (c<v)
    a = tmp.argmin()-1
    s = chars[a]
    decoded = np.append(decoded,str(s))
    v = (v-dict_c[s])/dict_p[s]

print decoded
