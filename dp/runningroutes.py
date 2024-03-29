from collections import Counter
import os
import sys
import time
from io import BytesIO, IOBase
from functools import lru_cache
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

# endregionS


def main():
    n = int(input())
    ok = [list(map(int, input().split())) for _ in range(n)]

    @lru_cache(maxsize=None, typed=False)
    def solve(i, j):
        nonlocal n
        if i >= n or i > j:
            return 0
        if i-j == 1:
            return ok[i][j]
        ret = solve(i+1, j)
        for k in range(i+1, j+1):
            if ok[i][k]:
                ret = max(ret, solve(i+1, k-1) + solve(k+1, j) + 1)
        return ret

    print(solve(0, n-1))


if __name__ == "__main__":
    start_time = time.time()
    main()
    print(f'Execution time: {time.time() - start_time} s', file=sys.stderr)
