from collections import defaultdict

class Model:
    def __init__(self,namefile):
        self.namefile = namefile
        self.init()

    def init(self):
        self.file = open(self.namefile, "rb")
        self.p = defaultdict(int)
        while True:
            char = self.file.read(1)
            if not char:
                break
            self.p[ord(char)] += 1;
        self.keys = self.p.keys()
        self.c = {}
        s = 0
        old_s = s
        for k in self.keys:
            s += self.p[k]
            self.c[k] = (old_s,s)
            old_s = s
        self.count = s

