from collections import defaultdict

class MarkovModel:
    def __init__(self):
        self.c = defaultdict(lambda: defaultdict(lambda: [0,0]))
        self.count = defaultdict(lambda: 258)
        for i in range(258):
            for j in range(258):
                self.c[i][j] = [j,j+1]
        self.keys = self.c.keys()

    def get_prob(self,s1,s2):
        return self.c[s1][s2]

    def update(self,s1,s2):
        self.c[s1][s2][1]+=1
        for i in range(min(s2+1,258),258):
            self.c[s1][i][0] += 1
            self.c[s1][i][1] += 1
        self.count[s1] += 1

    def get_denom(self,s1):
        return self.count[s1]
