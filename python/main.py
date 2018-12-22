from Model import Model
from Compressor import Compressor
from Read_bit import Read_bit
from Decompressor import Decompressor

filename = "enwiki6"
model = Model(filename+".txt")
print model.c
print "\n----------compressing-----------"
c = Compressor(filename+".txt",model)
c.compress()
print "\n---------decompressing----------"
d = Decompressor(filename+".code",model)
d.decompress()





