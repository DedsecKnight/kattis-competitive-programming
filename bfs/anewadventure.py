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

a = [-1, 1, 0, 0, 0]
b = [0, 0, -1, 1, 0]

def main():
    n, m = map(int, input().split())
    grid = [[c for c in input()] for i in range(n)]

    visited = [[False for i in range(m)] for i in range(n)]

    level = 0 

    q = deque([(0, 0)])  
    visited[0][0] = True

    while (q):
        q.append((-1, -1))
        while (True):
            i, j = q.popleft()
            if (i == -1): break
            if (i == n-1): 
                print(level + 1)
                return
            for k in range(5):
                new_x, new_y = i+a[k], (j+b[k]) % m
                if (new_x not in range(n)): continue
                new_pos = (new_y - 1) % m
                if (grid[new_x][new_pos] == 'M' or grid[new_x][(new_pos + 1) % m] == 'M' or visited[new_x][new_pos]): 
                    continue
                visited[new_x][new_pos] = True
                q.append((new_x, new_pos))
        level += 1
    
    print(-1)

                
if __name__ == "__main__":
    main()