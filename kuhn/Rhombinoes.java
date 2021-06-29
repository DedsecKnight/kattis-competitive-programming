import java.util.*;
import java.io.*;

public class Rhombinoes {
    int[][] alive, index;
    boolean[] used;
    int[] matched;
    ArrayList<ArrayList<Integer>> graph;

    final int[] a = {-1, 1, 0, 0};
    final int[] b = {0, 0, -1, 1};

    public void prayGod() throws IOException {
        int m = nextInt(), n = nextInt(), k = nextInt();
        alive = new int[n][m];
        index = new int[n][m];
        
        for (int i = 0; i<n; i++) {
            Arrays.fill(alive[i], 1);
            Arrays.fill(index[i], -1);
        }

        for (int i = 0; i<k; i++) {
            int y = nextInt(), x = nextInt();
            alive[x][y] = 0;
        }

        int countUp = 0, countDown = 0;

        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                if (alive[i][j] == 0) continue;
                if (pointUp(i, j)) index[i][j] = countUp++;
                else index[i][j] = countDown++;
            }
        }

        matched = new int[countDown];
        Arrays.fill(matched, -1);

        graph = new ArrayList<>();
        for (int i = 0; i<countUp; i++) graph.add(new ArrayList<Integer>());

        for (int i = 0; i<n; i++) {
            for (int j = 0; j<m; j++) {
                if (!pointUp(i, j)) continue;
                for (int z = 0; z<4; z++) {
                    int newX = i+a[z], newY = j+b[z];
                    if (newX < 0 || newY < 0 || newX >= n || newY >= m) continue;
                    if (validRhombino(i, j, newX, newY)) graph.get(index[i][j]).add(index[newX][newY]);
                }
            }
        }

        int ret = 0;

        for (int i = 0; i<countUp; i++) {
            used = new boolean[countUp];
            kuhn(i);
        }

        for (int i = 0; i<countDown; i++) {
            if (matched[i] != -1) ret++;
        }

        out.println(ret);
        
    }

    public boolean kuhn(int idx) {
        if (used[idx]) return false;
        used[idx] = true;
        for (int neighbor : graph.get(idx)) {
            if (matched[neighbor] == -1 || kuhn(matched[neighbor])) {
                matched[neighbor] = idx;
                return true;
            }
        }
        return false;
    }

    public boolean pointUp(int x, int y) {
        return (x + y) % 2 == 0;
    }
 
    public boolean validRhombino(int x1, int y1, int x2, int y2) {
        if (alive[x1][y1] == 0 || alive[x2][y2] == 0) return false; 
        if (x1 == x2) return true;
        if (y1 == y2) {
            if (x1 < x2) return !pointUp(x1, y1);
            return !pointUp(x2, y2);
        }
        return false;
    }

    static final boolean RUN_TIMING = true;
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
    public int nextInt() throws IOException { return Integer.parseInt(next()); }
    public int[] nextIntArray(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = nextInt();
        return arr;
    }
    public void sort(int[] a) {
        shuffle(a);
        Arrays.sort(a);
    }
    public static void printArray(int[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }

    // long data-type
    public long nextLong() throws IOException { return Long.parseLong(next()); }
    public long[] nextLongArray(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = nextLong();
        return arr;
    }
    public static void printArray(long[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
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
        for (int i = 0; i < n; i++) arr[i] = nextDouble();
        return arr;
    }
    public static void printArray(double[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
    }

    // Generic type
    public <T> void sort(T[] a) {
        shuffle(a);
        Arrays.sort(a);
    }
    public static <T> void printArray(T[] arr) {
        for (int i = 0; i<arr.length; i++) out.print(arr[i] + " ");
        out.println();
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
            inputBuffer[len] = (char)c;
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
            inputBuffer[len] = (char)c;
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
            int j = (int)(Math.random() * (n-i));
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(long[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int)(Math.random() * (n-i));
            long temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public void shuffle(Object[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int j = (int)(Math.random() * (n-i));
            Object temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    public static void main(String[] args) throws IOException {
        if (FILE_INPUT) in = new PushbackReader(new BufferedReader(new FileReader(new File("output.txt"))), 1 << 20);
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new Rhombinoes().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}

