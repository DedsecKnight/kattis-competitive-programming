import java.util.*;
import java.io.*;
import java.math.*;

public class Spiderman {
    int[] a;
    int[][] dp;
    int[][] maxHeight;
    String[][] state;

    public void prayGod() throws IOException {
        int t = ipar();
        while (t-- > 0) {
            int n = ipar();
            a = iapar(n);
            int total = 0;
            for (int i = 0; i<n; i++) total += a[i];
            
            dp = new int[n][total+1];
            maxHeight = new int[n][total+1];
            state = new String[n][total+1];

            for (int i = 0; i<n; i++) {
                for (int j = 0; j<total+1; j++) {
                    dp[i][j] = -1;
                    maxHeight[i][j] = 0;
                }
            }

            for (int i = 0; i<=total; i++) {
                dp[0][i] = 0;
                state[0][i] = "IMPOSSIBLE";
            }

            dp[0][a[0]] = 1;
            state[0][a[0]] = "U";
            maxHeight[0][a[0]] = a[0];

            out.println(solve(n-1, 0));

        }
    }
    
    String solve(int idx, int currHeight) {
        if (dp[idx][currHeight] != -1) return state[idx][currHeight];
        String temp = "";
        if (currHeight - a[idx] >= 0) {
            temp = solve(idx-1, currHeight - a[idx]);
            if (dp[idx-1][currHeight - a[idx]] == 1) {
                dp[idx][currHeight] = 1;
                state[idx][currHeight] = temp + "U";
                maxHeight[idx][currHeight] = maxHeight[idx-1][currHeight - a[idx]];
            }
        }
        if (currHeight + a[idx] >= 0) {
            temp = solve(idx-1, currHeight + a[idx]);
            if (dp[idx-1][currHeight + a[idx]] == 1) {
                if (dp[idx][currHeight] != 1 || maxHeight[idx][currHeight] > maxHeight[idx-1][currHeight + a[idx]]) {
                    dp[idx][currHeight] = 1;
                    state[idx][currHeight] = temp + "D";
                    maxHeight[idx][currHeight] = maxHeight[idx-1][currHeight + a[idx]];
                }
            }
        }

        if (dp[idx][currHeight] == 1) {
            maxHeight[idx][currHeight] = Math.max(maxHeight[idx][currHeight], currHeight);
            return state[idx][currHeight];
        }

        dp[idx][currHeight] = 0;
        return state[idx][currHeight] = "IMPOSSIBLE";
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
    public int ipar() throws IOException { return Integer.parseInt(spar()); }
    public int[] iapar(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = ipar();
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
    public long lpar() throws IOException { return Long.parseLong(spar()); }
    public long[] lapar(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = lpar();
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
    public double dpar() throws IOException {
        return Double.parseDouble(spar());
    }
    public double[] dapar(int n) throws IOException {
        double[] arr = new double[n];
        for (int i = 0; i < n; i++) arr[i] = dpar();
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

    public String spar() throws IOException {
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

    public String linepar() throws IOException {
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

    public boolean haspar() throws IOException {
        String line = linepar();
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
        if (FILE_INPUT) in = new PushbackReader(new BufferedReader(new FileReader(new File("test.txt"))), 1 << 20);
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new Spiderman().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
