def inputs():
    return map(int, input().split())


class fen:
    def __init__(self, x):
        self.n = x
        self.BIT = [0 for _ in range(self.n + 1)]
    
    def upd(self, idx, val):
        while idx<=self.n:
            self.BIT[idx] += val
            idx += (idx&-idx)
    
    def prefsum(self, idx):
        tot = 0
        while idx>=1:
            tot += self.BIT[idx]
            idx -= (idx&-idx)
        return tot
    
    def RQ(self, l, r):
        return self.prefsum(r) - self.prefsum(l-1)