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

# Edmonds-Karp algorithm to find max flow
def main():
    INF = 10**9 + 10
    n, m, s, t = map(int, input().split())
    
    capacity = [[0 for i in range(n)] for i in range(n)]
    graph = [[] for i in range(n)]
    used = [[False for i in range(n)] for i in range(n)]

    original_capacity = []

    for i in range(m):
        u, v, w = map(int, input().split())
        capacity[u][v] += w
        original_capacity.append((u, v, w))
        graph[u].append(v)
        graph[v].append(u)
    
    parent = [-1 for i in range(n)]

    def bfs(s, t):
        for i in range(n): parent[i] = -1
        curr_flow = [0 for i in range(n)]
        q = deque([s])
        curr_flow[s] = INF
        while (q):
            curr = q.popleft()
            if (curr == t): return curr_flow[t]
            for neighbor in graph[curr]:
                if (parent[neighbor] != -1 or capacity[curr][neighbor] <= 0): continue
                q.append(neighbor)
                parent[neighbor] = curr
                curr_flow[neighbor] = min(curr_flow[curr], capacity[curr][neighbor])
        return curr_flow[t]        

    local_flow, global_flow = bfs(s, t), 0

    while (local_flow > 0):
        curr = t
        while (curr != s):
            prev = parent[curr]
            capacity[curr][prev] += local_flow
            capacity[prev][curr] -= local_flow
            used[prev][curr] = True
            curr = prev
        global_flow += local_flow
        local_flow = bfs(s, t)
    
    used_edge = []
    for (u, v, w) in original_capacity:
        used_flow = w - capacity[u][v]
        if (not used[u][v] or used_flow <= 0): continue
        used_edge.append((u, v, used_flow))
    
    sys.stdout.write(str(n) + " " + str(global_flow) + " " + str(len(used_edge)) + '\n')

    for (u, v, w) in used_edge:
        sys.stdout.write(str(u) + " " + str(v) + " " + str(w) + '\n')


if __name__ == "__main__":
    main()
