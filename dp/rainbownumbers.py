import os
import sys
import math
from io import BytesIO, IOBase
from typing import DefaultDict

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

# endregionS


def main():
    l, u = input(), input()
    mod = 998244353

    def solve(val):
        n = len(val)
        dp = [[0 for i in range(12)] for i in range(n)]
        unbounded = [[0 for i in range(12)] for i in range(n)]

        for i in range(10):
            unbounded[-1][i] = 1
            unbounded[-1][11] = (unbounded[-1][11] + 1) % mod
        
        for i in range(n-2, -1, -1):
            unbounded[i][10] = unbounded[i+1][11]
            unbounded[i][11] = (unbounded[i][11] + unbounded[i][10]) % mod

            curr_total = (unbounded[i+1][11] - unbounded[i+1][10]) % mod
            if (i < n-2): curr_total = (curr_total + unbounded[i+1][0]) % mod
            
            for j in range(10):
                unbounded[i][j] = (curr_total - unbounded[i+1][j]) % mod
                if (j): unbounded[i][11] = (unbounded[i][11] + unbounded[i][j]) % mod

        curr_bound = ord(val[-1]) - 48
        for i in range(curr_bound + 1):
            dp[-1][i] = 1
            dp[-1][11] = (dp[-1][11] + 1) % mod
        
        for i in range(n-2, -1, -1):
            curr_bound = ord(val[i]) - 48

            curr_total = (unbounded[i+1][11] - unbounded[i+1][10]) % mod
            if (i < n-2): curr_total = (curr_total + unbounded[i+1][0]) % mod
           
            for j in range(curr_bound):
                dp[i][j] = (dp[i][j] + curr_total - unbounded[i+1][j]) % mod;
                if (j > 0): dp[i][11] = (dp[i][11] + dp[i][j]) % mod;
            
            if (not curr_bound): dp[i][10] = dp[i+1][11]
            else: dp[i][10] = unbounded[i+1][11]

            for j in range(10):
                if (j == curr_bound): continue
                dp[i][curr_bound] = (dp[i][curr_bound] + dp[i+1][j]) % mod
            
            dp[i][11] = (dp[i][11] + dp[i][10] + dp[i][curr_bound]) % mod
        
        return dp[0][11]
    
    def valid(val):
        for i in range(len(val)-1):
            if (val[i] == val[i+1]): return 0
        return 1

    print((solve(u) - solve(l) + valid(l)) % mod)


if __name__ == "__main__":
    main()

