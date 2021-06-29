import os
import sys
from io import BytesIO, IOBase
from collections import deque

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
    nCr  = [[0 for i in range(17)] for i in range(17)]
    for i in range(17): nCr[i][0] = 1

    for i in range(1, 17):
        for j in range(1, 17):
            nCr[i][j] = nCr[i-1][j-1] + nCr[i-1][j]

    while (True):
        data = list(input().split())
        if (data[0] == '#' and data[1] == '0'): break
        s, idx = data[0], int(data[1])
        frequency = [0 for i in range(26)]
        
        for c in s: frequency[ord(c) - 65] += 1
        
        ret = ""

        for i in range(len(s)):
            pref_choose = []
            
            best = -1

            for j in range(26):
                if (not frequency[j]): continue
                curr_pref = 1
                remain = len(s) - i - 1
                frequency[j] -= 1

                for k in range(26):
                    if (not frequency[k]): continue
                    curr_pref *= nCr[remain][frequency[k]]
                    remain -= frequency[k]
                
                frequency[j] += 1
                if (pref_choose): 
                    curr_pref += pref_choose[-1][0]

                if (best == -1 and curr_pref >= idx): 
                    best = len(pref_choose)
                    pref_choose.append((curr_pref, j))
                    break

                for k in range(frequency[j]):
                    pref_choose.append((curr_pref, j))

            #print(pref_choose)

            if (best > 0): idx -= pref_choose[best-1][0]
            ret += chr(pref_choose[best][1] + 65)
            frequency[pref_choose[best][1]] -= 1

        print(ret)

    
                
if __name__ == "__main__":
    main()



