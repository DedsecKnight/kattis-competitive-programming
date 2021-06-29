import os
import sys
import math
from random import randint
from io import BytesIO, IOBase
from queue import PriorityQueue

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

def check_board():
    pos_list = [[], []]
    for i in range(3):
        s = input()
        for j in range(3):
            if (s[j] == 'X'): pos_list[1].append((i, j))
            elif (s[j] == 'O'): pos_list[0].append((i, j))
    
    board = [['' for i in range(3)] for i in range(3)]
    valid = [False]

    mark = ['O', 'X']
    visited = [[False for i in pos_list[0]], [False for i in pos_list[1]]]

    def winner_found():
        for i in range(3):
            if (board[i][0] != '' and board[i][0] == board[i][1] and board[i][0] == board[i][2]): return True
            if (board[0][i] != '' and board[0][i] == board[1][i] and board[0][i] == board[2][i]): return True
        
        if (board[0][0] == board[1][1] and board[0][0] == board[2][2] and board[0][0] != ''): return True
        if (board[0][2] == board[1][1] and board[0][2] == board[2][0] and board[0][2] != ''): return True
        
        return False
    
    def check_remain(is_x):
        for p in visited[is_x]:
            if (not p): return True
        return False

    def solve(is_x):
        no_move = True
        
        for (p, pos) in enumerate(pos_list[is_x]):
            if (visited[is_x][p]): continue
            visited[is_x][p] = True
            no_move = False
            i, j = pos
            board[i][j] = mark[is_x]
            if (winner_found()):
                if (not check_remain(1) and not check_remain(0)): valid[0] = True
            else: solve(is_x^1)
            visited[is_x][p] = False
            board[i][j] = ''
        
        if (no_move):
            if (not check_remain(is_x ^ 1)): valid[0] = True
            return
            
    solve(1)
    print("yes" if valid[0] else "no")

def main():
    n = int(input())
    for _ in range(n):
        check_board()
        input()


if __name__ == "__main__":
    main()
