import java.util.*;
import java.io.*;

public class Shrine {

    public void run() throws IOException {
        while (true) {
            int w = nextInt();
            if (w == 0)
                break;
            int n = nextInt(), d = nextInt();
            int[] divisor = nextIntArray(d);

            ArrayList<Integer> sacredPoints = new ArrayList<>();

            for (int i = 1; i <= n; i++) {
                boolean isSacred = false;
                for (int div : divisor) {
                    if (i % div == 0) {
                        isSacred = true;
                        break;
                    }
                }
                if (isSacred)
                    sacredPoints.add(i % n);
            }

            double[] x = new double[n];
            double[] y = new double[n];

            x[0] = 0.0;
            y[0] = 1000.0;

            for (int i = 1; i < n; i++) {
                double theta = 2 * Math.PI * i / n;
                y[i] = 1000.0 * Math.cos(theta);
                x[i] = Math.sqrt(Math.pow(1000.0, 2) - Math.pow(y[i], 2)) * (i > n / 2 ? -1.0 : 1.0);
            }

            double[] pref = new double[sacredPoints.size() * 2];
            for (int i = 1; i < sacredPoints.size() * 2; i++) {
                int idx = i % sacredPoints.size();
                int prev = (i - 1 + sacredPoints.size()) % sacredPoints.size();
                pref[i] = pref[i - 1] + euclidDistance(x[sacredPoints.get(idx)], y[sacredPoints.get(idx)],
                        x[sacredPoints.get(prev)], y[sacredPoints.get(prev)]);
            }

            double lowDist = 2000, highDist = 1e9 + 10;
            for (int __ = 0; __ < 100; __++) {
                double midDist = lowDist + (highDist - lowDist) / 2;

                int[] maxJump = new int[sacredPoints.size()];
                Arrays.fill(maxJump, 1);

                for (int i = 0; i < maxJump.length; i++) {
                    int low = 1, high = maxJump.length;
                    while (low <= high) {
                        int mid = low + (high - low) / 2;
                        double currDist = pref[i + mid - 1] - pref[i] + 2000.0;
                        if (currDist <= midDist) {
                            maxJump[i] = mid;
                            low = mid + 1;
                        } else
                            high = mid - 1;
                    }
                }

                boolean possible = false;
                for (int i = 0; i < maxJump.length && !possible; i++) {
                    int coveredShrine = 0, currPos = i;
                    for (int j = 0; j < w; j++) {
                        coveredShrine += maxJump[currPos];
                        currPos = (currPos + maxJump[currPos]) % maxJump.length;
                    }
                    if (coveredShrine >= maxJump.length)
                        possible = true;
                }

                if (possible)
                    highDist = midDist;
                else
                    lowDist = midDist;
            }

            out.printf("%.1f\n", highDist);

        }
    }

    public double euclidDistance(double x1, double y1, double x2, double y2) {
        return Math.sqrt(Math.pow(x1 - x2, 2) + Math.pow(y1 - y2, 2));
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
        new Shrine().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
