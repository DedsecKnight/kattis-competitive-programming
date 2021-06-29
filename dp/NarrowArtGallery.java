import java.util.*;
import java.io.*;

public class NarrowArtGallery {

    public void prayGod() throws IOException {
        while (true) {
            int n = nextInt(), k = nextInt();
            if (n == 0 && k == 0)
                break;
            int[][] rows = new int[n][2];
            for (int i = 0; i < n; i++)
                rows[i] = nextIntArray(2);

            int[][][] dp = new int[n + 1][k + 1][3];
            for (int i = 1; i <= k; i++) {
                dp[0][i][0] = dp[0][i][1] = dp[0][i][2] = -iinf;
            }

            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= k; j++) {
                    dp[i][j][1] = dp[i][j][2] = -iinf;

                    dp[i][j][0] = Math.max(dp[i - 1][j][0], Math.max(dp[i - 1][j][1], dp[i - 1][j][2]));
                    if (dp[i][j][0] != -iinf)
                        dp[i][j][0] += rows[i - 1][0] + rows[i - 1][1];

                    if (j > 0) {
                        dp[i][j][1] = Math.max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1]);
                        if (dp[i][j][1] != -iinf)
                            dp[i][j][1] += rows[i - 1][0];

                        dp[i][j][2] = Math.max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][2]);
                        if (dp[i][j][2] != -iinf)
                            dp[i][j][2] += rows[i - 1][1];
                    }

                }
            }

            out.println(Math.max(dp[n][k][0], Math.max(dp[n][k][1], dp[n][k][2])));
        }

    }

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
            in = new PushbackReader(new BufferedReader(new FileReader(new File("input.txt"))), 1 << 20);
        if (FILE_OUTPUT)
            out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new NarrowArtGallery().prayGod();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}