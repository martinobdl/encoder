from Model import Model
from Compressor import Compressor
from Read_bit import Read_bit
from Decompressor import Decompressor
import sys,os

mode = sys.argv[1]
filename = sys.argv[2]
model = Model(filename.split(".")[0]+'.txt')
#print model.c
if mode == "-c":
    print "----------compressing-----------"
    c = Compressor(filename,model)
    c.compress()
elif mode == "-d":
    print "---------decompressing----------"
    d = Decompressor(filename,model)
    d.decompress()





