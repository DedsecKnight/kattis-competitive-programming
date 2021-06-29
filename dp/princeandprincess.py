'''
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/princeandprincess
TAGS: dp
EXPLANATION:
    - Create an array call map_idx
    - For each value X in the first array:
        If X is in the second array: then add index of X in second array into map_idx
    - The result will be the longest increasing subsequence of map_idx
END ANNOTATION
'''
import os
import sys
import math
from random import randint
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
# ~ sys.stdin = open('social.in', 'r')  
input = lambda: sys.stdin.readline().rstrip("\r\n")

# endregion
        
def main():
    t = int(input())
    for _ in range(1, t+1):
        n, p, q = map(int, input().split())
        
        p += 1
        q += 1

        a = list(map(int, input().split()))
        seen = { c : i for (i, c) in enumerate(list(map(int, input().split()))) }

        map_idx = [-1 for i in range(p)]
        for i in range(p):
            if (a[i] in seen): map_idx[i] = seen[a[i]]
        
        aux = [10**9 for i in range(p+1)]
        aux[0] = -aux[0]
        ret = 0

        for i in range(p):
            if (map_idx[i] == -1): continue
            low, high, curr = 0, p, 0
            while (low <= high):
                mid = low + (high - low)//2
                if (aux[mid] >= map_idx[i]): curr, high = mid, mid-1
                else: low = mid+1
            ret = max(ret, curr)
            aux[curr] = map_idx[i]
        
        print(f'Case {_}: {ret}')
    

if __name__ == "__main__":
    main()
