import java.util.*;
import java.io.*;

public class ShoppingMalls {
    int[] floor, x, y;
    int[][] next;

    public void run() throws IOException {
        int n = nextInt(), m = nextInt();

        floor = new int[n];
        x = new int[n];
        y = new int[n];
        next = new int[n][n];

        for (int i = 0; i < n; i++) {
            floor[i] = nextInt();
            x[i] = nextInt();
            y[i] = nextInt();
        }

        double[][] dist = new double[n][n];

        for (int i = 0; i < n; i++) {
            Arrays.fill(dist[i], 1e9 + 10);
            Arrays.fill(next[i], -1);
        }

        for (int i = 0; i < m; i++) {
            int start = nextInt(), end = nextInt();
            String type = next();
            if (type.equals("walking") || type.equals("stairs")) {
                dist[start][end] = dist[end][start] = euclidDist(start, end);
                next[end][start] = start;
                next[start][end] = end;
            } else if (type.equals("lift")) {
                dist[start][end] = dist[end][start] = 1.0;
                next[end][start] = start;
                next[start][end] = end;
            } else {
                // escalator
                dist[start][end] = 1.0;
                dist[end][start] = euclidDist(start, end) * 3.0;
                next[end][start] = start;
                next[start][end] = end;
            }
        }

        for (int i = 0; i < n; i++) {
            dist[i][i] = 0.0;
            next[i][i] = i;
        }

        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][j] > dist[i][k] + dist[k][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }

        int q = nextInt();
        while (q-- > 0) {
            int from = nextInt(), to = nextInt();
            if (next[from][to] == -1)
                System.exit(1);
            out.printf("%d ", from);
            while (from != to) {
                from = next[from][to];
                out.printf("%d ", from);
            }
            out.println();
        }

    }

    public double euclidDist(int i, int j) {
        double sqX = Math.pow(x[i] - x[j], 2);
        double sqY = Math.pow(y[i] - y[j], 2);
        double sqZ = Math.pow((floor[i] - floor[j]) * 5, 2);
        return Math.sqrt(sqX + sqY + sqZ);
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
        new ShoppingMalls().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
