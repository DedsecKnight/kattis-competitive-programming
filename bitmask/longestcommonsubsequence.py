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

# endregionS

def main():
    n, k = map(int, input().split())
    a = [input() for i in range(n)]

    clear_bit = [0] * k
    
    for s in a:
        curr_clear = 0
        for c in s:
            curr_idx = ord(c) - 65
            clear_bit[curr_idx] |= curr_clear
            curr_clear |= (1 << curr_idx)

    init_mask = (1<<(k+1)) - 1
    
    def solve(remain_len, curr_mask):
        if (not remain_len): return True
        if (not curr_mask): return False

        
        ret = False

        for i in range(k):
            if (curr_mask & (1<<i)):
                ret |= solve(remain_len - 1, (curr_mask ^ (1 << i)) & ~clear_bit[i])
                if (ret): return True
        
        return ret 

    # Time complexity: O(n*k*log(k))
    low, high, best = 1, k, 1
    while (low <= high):
        mid = low + (high - low)//2
        if (solve(mid, init_mask)): 
            best = mid
            low = mid+1
        else: high = mid-1
    
    print(best)
                
if __name__ == "__main__":
    main()



