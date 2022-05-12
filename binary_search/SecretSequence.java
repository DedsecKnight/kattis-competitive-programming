import java.util.*;
import java.io.*;

public class SecretSequence {

    class Query implements Comparable<Query> {
        int a, b, c, d;

        public Query(int a, int b, int c, int d) {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
        }

        public int compareTo(Query other) {
            if (a != other.a)
                return Integer.compare(a, other.a);
            if (b != other.b)
                return Integer.compare(b, other.b);
            if (c != other.c)
                return Integer.compare(c, other.c);
            return Integer.compare(d, other.d);
        }
    }

    TreeMap<Query, Integer> hashMap;

    public void prayGod() throws IOException {
        hashMap = new TreeMap<>();
        int n = nextInt();
        out.printf("! %d\n", solve(0, n - 1));
    }

    public int query(int a, int b, int c, int d) throws IOException {
        Query obj = new Query(a, b, c, d);
        if (hashMap.containsKey(obj))
            return hashMap.get(obj);
        out.printf("? %d %d %d %d\n", a, b, c, d);
        out.flush();
        int response = nextInt();
        hashMap.put(obj, response);
        return response;
    }

    public int solve(int low, int high) throws IOException {
        if (low > high)
            return 0;
        int originalLow = low, originalHigh = high;
        if (low == high) {
            int ret = query(low, high + 1, high + 1, high + 1);
            return Math.abs(ret);
        }
        int bestZero = -1, boundVal = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int res = query(originalLow, mid + 1, mid + 1, originalHigh + 1);
            if (res >= 0) {
                bestZero = mid;
                boundVal = res;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        int totalSize = originalHigh - originalLow + 1;
        int leftSize = bestZero - originalLow + 1;
        if (boundVal == 0) {
            if (leftSize < totalSize - leftSize)
                return solve(originalLow, bestZero) * 2;
            return solve(bestZero + 1, originalHigh) * 2;
        }
        if (leftSize < totalSize - leftSize)
            return solve(originalLow, bestZero) * 2 + 1;
        return solve(bestZero + 1, originalHigh) * 2 - 1;
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
        new SecretSequence().prayGod();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
