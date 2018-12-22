from MarkovModel import MarkovModel
from MarkovCompressor import MarkovCompressor
from Read_bit import Read_bit
from MarkovDecompressor import MarkovDecompressor
import sys,os

filename = "MobyDick.txt"
#print model.c
print "----------compressing-----------"
model_c = MarkovModel()
c = MarkovCompressor(filename,model_c)
c.compress()
print "---------decompressing----------"
model_d = MarkovModel()
d = MarkovDecompressor(filename+".code",model_d)
d.decompress()





