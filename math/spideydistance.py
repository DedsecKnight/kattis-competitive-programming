import os
import time
import sys
from io import BytesIO, IOBase 
import threading
import math
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
def input(): return sys.stdin.readline().rstrip("\r\n")

# endregion
def timing(f):
    def wrapper():
        start_time = time.time()
        f()
        print(f'Execution time: {time.time() - start_time} s', file=sys.stderr)
    return wrapper

@timing
def main():
    t, s = map(int, input().split())
    S, ST = -1, -1
    for i in range(s+1):
        cnt = min(i-1, (s - i) * 2) + max(s - (i + 1) // 2 - i + 1, 0) + 1
        if i == 0:
            S += 2 * cnt
        else:
            if cnt >= 1:
                S += 2
            S += 4 * max(cnt - 1, 0)
        cnt = min(i-1, (s - i) * 2, t - i) + max(min(s - (i + 1) // 2, t - i) - i + 1, 0) + 1
        if i == 0:
            ST += 2 * cnt
        else:
            if cnt >= 1:
                ST += 2
            ST += 4 * max(cnt - 1, 0)
    g = math.gcd(ST, S)
    if g == S:
        print(ST // S)
    else:
        print(f"{ST//g}/{S//g}")

if __name__ == "__main__":
    main()
