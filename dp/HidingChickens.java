import java.util.*;
import java.io.*;

public class HidingChickens {

    class Point {
        double x, y;

        public Point(double _x, double _y) {
            x = _x;
            y = _y;
        }

        public void transpose(Point origin) {
            x -= origin.x;
            y -= origin.y;
        }

        public double dist() {
            return Math.sqrt(Math.pow(x, 2) + Math.pow(y, 2));
        }

        public Point subtract(Point other) {
            return new Point(x - other.x, y - other.y);
        }

        public String toString() {
            return String.format("%.6f %.6f", x, y);
        }

    }

    public void prayGod() throws IOException {
        Point origin = new Point(nextDouble(), nextDouble());
        int n = nextInt();

        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            points[i] = new Point(nextDouble(), nextDouble());
            points[i].transpose(origin);
        }

        origin.transpose(origin);

        double[][] distBetween = new double[n][n];
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                distBetween[i][j] = distBetween[j][i] = points[i].dist() + points[j].dist()
                        + points[i].subtract(points[j]).dist();
            }
        }

        double[] dp = new double[1 << n];
        for (int mask = (1 << n) - 2; mask >= 0; mask--) {
            dp[mask] = 1e9 + 10;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) {
                    dp[mask] = Math.min(dp[mask], dp[mask ^ (1 << i)] + distBetween[i][i]);
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    if ((mask & (1 << i)) != 0)
                        continue;
                    if ((mask & (1 << j)) != 0)
                        continue;
                    dp[mask] = Math.min(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + distBetween[i][j]);
                }
            }

        }

        double extraDist = 0;

        for (int i = 0; i < n; i++) {
            extraDist = Math.max(extraDist, distBetween[i][i]);
        }

        out.printf("%.7f\n", dp[0] - extraDist * 0.5);
    }

    public void printVerdict(boolean verdict) {
        if (verdict)
            out.println(VERDICT_YES);
        else
            out.println(VERDICT_NO);
    }

    static final String VERDICT_YES = "YES";
    static final String VERDICT_NO = "NO";
    static final boolean RUN_TIMING = true;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

    static int iinf = 0x3f3f3f3f;
    static long inf = (long) 1e18 + 10;
    static long mod = (long) 1e9 + 7;

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

    public static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
        out.println();
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

    public static void printArray(long[] arr) {
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
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
        for (int i = 0; i < n; i++)
            arr[i] = nextDouble();
        return arr;
    }

    public static void printArray(double[] arr) {
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
        out.println();
    }

    // Generic type
    public <T> void sort(T[] a) {
        shuffle(a);
        Arrays.sort(a);
    }

    public static <T> void printArray(T[] arr) {
        for (int i = 0; i < arr.length; i++)
            out.print(arr[i] + " ");
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
        new HidingChickens().prayGod();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
