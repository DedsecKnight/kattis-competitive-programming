import java.util.*;
import java.io.*;

public class AlienIntegers {

    public void prayGod() throws IOException {
        long n = nextLong();
        String s = String.valueOf(n);
        int[] cnt = new int[10];
        for (char c : s.toCharArray()) {
            cnt[c - 48]++;
        }
        long left = -1, right = inf;
        int smallestAvailable = -1, highestAvailable = -1;

        for (int d = 0; d < 10; d++) {
            if (cnt[d] > 0)
                continue;
            if (smallestAvailable == -1)
                smallestAvailable = d;
        }

        for (int d = 9; d >= 0; d--) {
            if (cnt[d] > 0)
                continue;
            if (highestAvailable == -1)
                highestAvailable = d;
        }

        if (smallestAvailable == -1) {
            out.println("Impossible");
            return;
        }

        for (int d = 0; d < 10; d++) {
            if (cnt[d] > 0)
                continue;
            long currLow = d, currHigh = d;
            while (true) {
                if (currLow * 10 + highestAvailable > n || currLow * 10 + highestAvailable == currLow)
                    break;
                currLow = currLow * 10 + highestAvailable;
            }
            while (true) {
                if (currHigh > n)
                    break;
                if (currHigh * 10 + smallestAvailable == currHigh)
                    break;
                currHigh = currHigh * 10 + smallestAvailable;
            }
            if (currLow < n)
                left = Math.max(left, currLow);
            if (currHigh > n)
                right = Math.min(right, currHigh);
        }

        if (left != -1 && right != inf) {
            if (left != right) {
                if (Math.abs(left - n) > Math.abs(right - n)) {
                    out.println(right);
                } else if (Math.abs(left - n) < Math.abs(right - n)) {
                    out.println(left);
                } else {
                    out.printf("%d %d\n", left, right);
                }
            } else {
                out.println(left);
            }
        } else if (left != -1) {
            out.println(left);
        } else if (right != -1) {
            out.println(right);
        } else {
            out.println("Impossible");
        }

    }

    public void printVerdict(boolean verdict) {
        if (verdict)
            out.println("YES");
        else
            out.println("NO");
    }

    static final boolean RUN_TIMING = true;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

    static int iinf = 0x3f3f3f3f;
    static long inf = (long) 1e18 + 10;
    static long mod = 998244353L;

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
        new AlienIntegers().prayGod();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
