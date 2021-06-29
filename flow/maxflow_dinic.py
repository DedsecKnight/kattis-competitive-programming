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

INF = 10**9 + 10

class Dinic:
    def __init__(self, n):
        self.vertex_count = n
        self.graph = [[] for i in range(n)]
        self.capacity = [[0 for i in range(n)] for i in range(n)]
        self.used = [[False for i in range(n)] for i in range(n)]
        self.level = [-1 for i in range(n)]
        self.ptr = [0 for i in range(n)]
    
    def add_edge(self, u, v, w):
        self.capacity[u][v] += w
        self.graph[u].append(v)
        self.graph[v].append(u)
    
    def bfs(self, s, t):
        q = deque([s])
        self.level = [-1 for i in range(self.vertex_count)]
        self.level[s] = 0
        while (q):
            curr = q.popleft()
            for neighbor in self.graph[curr]:
                if (self.level[neighbor] != -1 or self.capacity[curr][neighbor] <= 0): continue
                self.level[neighbor] = self.level[curr] + 1
                q.append(neighbor)
        return self.level[t] != -1
    
    def dfs(self, dest, curr, curr_flow):
        if (not curr_flow): return 0
        if (dest == curr): return curr_flow
        while (self.ptr[curr] < len(self.graph[curr])):
            neighbor = self.graph[curr][self.ptr[curr]]
            if (self.level[neighbor] != self.level[curr] + 1 or self.capacity[curr][neighbor] <= 0): 
                self.ptr[curr] += 1
                continue
            delta_flow = self.dfs(dest, neighbor, min(curr_flow, self.capacity[curr][neighbor]))
            if (not delta_flow):
                self.ptr[curr] += 1
                continue
            self.capacity[curr][neighbor] -= delta_flow
            self.capacity[neighbor][curr] += delta_flow
            self.used[curr][neighbor] = True
            return delta_flow
        return 0
    
    def get_flow(self, s, t):
        final_flow = 0
        while (True):
            if (not self.bfs(s, t)): break
            self.ptr = [0 for i in range(self.vertex_count)]
            while (True):
                new_flow = self.dfs(t, s, INF)
                if (not new_flow): break
                final_flow += new_flow
        return final_flow


def main():
    n, m, s, t = map(int, input().split())

    dinic = Dinic(n)
    original_edge = []

    for i in range(m):
        u, v, w = map(int, input().split())
        dinic.add_edge(u, v, w)
        original_edge.append((u, v, w))
    
    ret = dinic.get_flow(s, t)

    used_edge = []
    for (u, v, w) in original_edge:
        if (not dinic.used[u][v] or w <= dinic.capacity[u][v]): continue
        used_edge.append((u, v, w - dinic.capacity[u][v]))

    print(str(n) + " " + str(ret) + " " + str(len(used_edge)))

    for (u, v, w) in used_edge:
        print(str(u) + " " + str(v) + " " + str(w))
    

                
if __name__ == "__main__":
    main()



