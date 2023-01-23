import os
import sys
from io import BytesIO, IOBase
import time
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
    ret = []
    MX = 2**63 - 1

    def ask(l, r):
        sys.stdout.write(f"q {l} {r}\n")
        sys.stdout.flush()
        return int(input())

    def find(low, high, target):
        best, lb = -1, low
        while low <= high:
            mid = low + (high - low) // 2
            v = ask(lb, mid)
            if v >= target:
                best = mid
                high = mid-1
            else:
                low = mid+1
        return best

    first_bit_position = find(0, MX, 1)
    if first_bit_position == -1:
        sys.stdout.write("a 0\n")
        sys.stdout.flush()
        return

    ret.append(first_bit_position)
    while len(ret) < 1024:
        curr_bit_position = find(ret[-1], MX, 2)
        if curr_bit_position == -1:
            break
        ret.append(curr_bit_position)

    sys.stdout.write(f'a {len(ret)} {" ".join(str(c) for c in ret)}\n')
    sys.stdout.flush()


if __name__ == "__main__":
    start_time = time.time()
    main()
    print(f'Execution time: {time.time() - start_time} s', file=sys.stderr)
