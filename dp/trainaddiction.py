#!/usr/bin/env python
import os
import sys
from io import BytesIO, IOBase

# region fastio

BUFSIZE = 8192

class FastIO(IOBase):
    newlines = 0

    def __init__(self, file):
        self._fd = file.fileno()
        self.buffer = BytesIO()
        self.writable = "x" in file.mode or "r" not in file.mode
        self.write = self.buffer.write if self.writable else None

    def read(self):
        while True:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            if not b:
                break
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines = 0
        return self.buffer.read()

    def readline(self):
        while self.newlines == 0:
            b = os.read(self._fd, max(os.fstat(self._fd).st_size, BUFSIZE))
            self.newlines = b.count(b"\n") + (not b)
            ptr = self.buffer.tell()
            self.buffer.seek(0, 2), self.buffer.write(b), self.buffer.seek(ptr)
        self.newlines -= 1
        return self.buffer.readline()

    def flush(self):
        if self.writable:
            os.write(self._fd, self.buffer.getvalue())
            self.buffer.truncate(0), self.buffer.seek(0)

class IOWrapper(IOBase):
    def __init__(self, file):
        self.buffer = FastIO(file)
        self.flush = self.buffer.flush
        self.writable = self.buffer.writable
        self.write = lambda s: self.buffer.write(s.encode("ascii"))
        self.read = lambda: self.buffer.read().decode("ascii")
        self.readline = lambda: self.buffer.readline().decode("ascii")


sys.stdin, sys.stdout = IOWrapper(sys.stdin), IOWrapper(sys.stdout)
input = lambda: sys.stdin.readline().rstrip("\r\n")

# endregion
mod = 10**9+7

class Matrix:
    def __init__(self, r, c):
        self.n, self.m = r,c
        self.grid = [[0 for i in range(self.m)] for i in range(self.n)]
    
    def __mul__(self, other):
        ret = Matrix(self.n, other.m)
        for i in range(self.n):
            for j in range(other.m):
                for k in range(self.m):
                    ret[i][j] += self.grid[i][k] * other.grid[k][j] % mod
                    ret[i][j] %= mod
        return ret

    def __getitem__(self, idx):
        return self.grid[idx]

def expo(relation : Matrix, n : int) -> Matrix:
    if (n == 1): return relation
    ret = expo(relation, n//2)
    ret = ret*ret
    if (n&1): ret = ret*relation
    return ret

def main():
    t = int(input())
    while (t):
        data = list(map(int, input().split()))
        n, k = data[0], data[1]
        a = [data[i+2] for i in range(k)]
        maxVal = max(a)

        initial, relation = Matrix(1, maxVal), Matrix(maxVal, maxVal)
        initial[0][0] = 1
        
        for i in range(1, maxVal):
            relation[i][i-1] = 1
            for j in range(k):
                if (i >= a[j]): 
                    initial[0][i] += initial[0][i-a[j]]
                    initial[0][i] %= mod
        
        for i in range(k): relation[maxVal-a[i]][maxVal-1] += 1

        ret = 0
        if (n < maxVal): ret = initial[0][n]
        else:
            initial = initial * expo(relation, n-maxVal+1)
            ret = initial[0][-1]
        
        if (not ret): sys.stdout.write("IMPOSSIBLE" + '\n')
        else: sys.stdout.write(str(ret) + '\n')

        t -= 1


if __name__ == "__main__":
    main()
