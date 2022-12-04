import java.util.*;
import java.io.*;

public class MarchOfPenguins {

    class Position {
        int x, y;
        int n, m;

        public Position(int _x, int _y, int _n, int _m) {
            x = _x;
            y = _y;
            n = _n;
            m = _m;
        }

        public double dist(Position other) {
            return Math.sqrt(Math.pow(x - other.x, 2) + Math.pow(y - other.y, 2));
        }
    }

    class MaxFlow {
        int[][] originalCap, currCap;
        int[] level, ptr;
        ArrayList<Integer>[] graph;

        int source, sink, vertexCount;
        final static int INF = (int) 1e9 + 10;

        public MaxFlow(int n) {
            this.source = 0;
            this.vertexCount = n;
            graph = new ArrayList[2 * n + 1];
            level = new int[2 * n + 1];
            ptr = new int[2 * n + 1];
            for (int i = 0; i < 2 * n + 1; i++) {
                graph[i] = new ArrayList<Integer>();
            }
            originalCap = new int[2 * n + 1][2 * n + 1];
            currCap = new int[2 * n + 1][2 * n + 1];
        }

        public void addEdge(int u, int v) {
            originalCap[2 * u + 2][2 * v + 1] = INF;
            originalCap[2 * v + 2][2 * u + 1] = INF;
            graph[2 * u + 2].add(2 * v + 1);
            graph[2 * v + 1].add(2 * u + 2);
            graph[2 * v + 2].add(2 * u + 1);
            graph[2 * u + 1].add(2 * v + 2);
        }

        public void addPosition(Position pos, int index) {
            originalCap[0][2 * index + 1] += pos.n;
            originalCap[2 * index + 1][2 * index + 2] += pos.m;
            graph[0].add(2 * index + 1);
            graph[2 * index + 1].add(0);
            graph[2 * index + 1].add(2 * index + 2);
            graph[2 * index + 2].add(2 * index + 1);
        }

        public void setSink(int newSinkIndex) {
            this.sink = 2 * newSinkIndex + 1;
        }

        private boolean bfs() {
            Arrays.fill(level, -1);
            Deque<Integer> q = new ArrayDeque<>();
            q.add(this.source);
            level[this.source] = 0;

            while (!q.isEmpty()) {
                int curr = q.pollFirst();
                for (int neighbor : graph[curr]) {
                    if (level[neighbor] != -1 || currCap[curr][neighbor] <= 0) {
                        continue;
                    }
                    q.addLast(neighbor);
                    level[neighbor] = level[curr] + 1;
                }
            }
            return level[this.sink] != -1;
        }

        private int dfs(int currPos, int currFlow) {
            if (currFlow == 0)
                return 0;
            if (currPos == this.sink)
                return currFlow;
            while (ptr[currPos] < graph[currPos].size()) {
                int neighbor = graph[currPos].get(ptr[currPos]);
                if (level[neighbor] != level[currPos] + 1 || currCap[currPos][neighbor] <= 0) {
                    ptr[currPos]++;
                    continue;
                }
                int deltaFlow = dfs(neighbor, Math.min(currFlow, currCap[currPos][neighbor]));
                if (deltaFlow == 0) {
                    ptr[currPos]++;
                    continue;
                }
                currCap[currPos][neighbor] -= deltaFlow;
                currCap[neighbor][currPos] += deltaFlow;
                return deltaFlow;
            }
            return 0;
        }

        public int compute() {
            for (int i = 0; i < originalCap.length; i++) {
                for (int j = 0; j < originalCap.length; j++) {
                    currCap[i][j] = originalCap[i][j];
                }
            }
            int finalFlow = 0;
            while (true) {
                if (!bfs())
                    break;
                Arrays.fill(ptr, 0);
                while (true) {
                    int newFlow = dfs(this.source, INF);
                    if (newFlow == 0)
                        break;
                    finalFlow += newFlow;
                }
            }
            return finalFlow;
        }
    }

    public void run() throws IOException {
        int n = nextInt();
        double d = nextDouble();

        MaxFlow ds = new MaxFlow(n);
        int totalPenguin = 0;

        Position[] positions = new Position[n];
        for (int i = 0; i < n; i++) {
            positions[i] = new Position(nextInt(), nextInt(), nextInt(), nextInt());
            ds.addPosition(positions[i], i);
            totalPenguin += positions[i].n;
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double currDist = positions[i].dist(positions[j]);
                if (currDist <= d) {
                    ds.addEdge(i, j);
                }
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            ds.setSink(i);
            int currMaxFlow = ds.compute();
            if (currMaxFlow == totalPenguin) {
                ans.add(i);
            }
        }

        if (ans.isEmpty()) {
            out.println(-1);
            return;
        }

        for (Integer v : ans) {
            out.printf("%d ", v);
        }
        out.println();
    }

    static final boolean RUN_TIMING = false;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

    static int iinf = 0x3f3f3f3f;
    static long inf = (long) 1e18 + 10;
    static int mod = (int) 1e9 + 7;

    static char[] inputBuffer = new char[1 << 20];
    static PushbackReader in = new PushbackReader(new BufferedReader(new InputStreamReader(System.in)), 1 << 20);
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)), AUTOFLUSH);

    // int data-type
    public int nextInt() throws IOException {
        return Integer.parseInt(next());
    }

    public int[] nextIntArray(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextInt();
        return arr;
    }

    public void sort(int[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    // long data-type
    public long nextLong() throws IOException {
        return Long.parseLong(next());
    }

    public long[] nextLongArray(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextLong();
        return arr;
    }

    public void sort(long[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    // double data-type
    public double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }

    public double[] nextDoubleArray(int n) throws IOException {
        double[] arr = new double[n];
        for (int i = 0; i < n; i++)
            arr[i] = nextDouble();
        return arr;
    }

    // Generic type
    public <T> void sort(T[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    public String next() throws IOException {
        int len = 0;
        int c;
        do {
            c = in.read();
        } while (Character.isWhitespace(c) && c != -1);
        if (c == -1) {
            throw new NoSuchElementException("Reached EOF");
        }
        do {
            inputBuffer[len] = (char) c;
            len++;
            c = in.read();
        } while (!Character.isWhitespace(c) && c != -1);
        while (c != '\n' && Character.isWhitespace(c) && c != -1) {
            c = in.read();
        }
        if (c != -1 && c != '\n') {
            in.unread(c);
        }
        return new String(inputBuffer, 0, len);
    }

    public String nextLine() throws IOException {
        int len = 0;
        int c;
        while ((c = in.read()) != '\n' && c != -1) {
            if (c == '\r') {
                continue;
            }
            inputBuffer[len] = (char) c;
            len++;
        }
        return new String(inputBuffer, 0, len);
    }

    public boolean hasNext() throws IOException {
        String line = nextLine();
        if (line.isEmpty()) {
            return false;
        }
        in.unread('\n');
        in.unread(line.toCharArray());
        return true;
    }

    public void shuffle(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int) (Math.random() * (n - i));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(long[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int) (Math.random() * (n - i));
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(Object[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int) (Math.random() * (n - i));
            Object temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public static void main(String[] args) throws IOException {
        if (FILE_INPUT)
            in = new PushbackReader(new BufferedReader(new FileReader(new File("output.txt"))), 1 << 20);
        if (FILE_OUTPUT)
            out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new MarchOfPenguins().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
