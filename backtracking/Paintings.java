import java.util.*;
import java.io.*;
import java.math.*;
 
public class Paintings {
    int n;
    int[][] dp;
    boolean[][] hate;
    int[] next;

    public void prayGod() throws IOException {
        int t = ipar();
        while (t-- > 0) {
            n = ipar();
            String[] colorList = new String[n];

            HashMap<String, Integer> colorMap = new HashMap<>();
            for (int i = 0; i<n; i++) {
                colorList[i] = spar();
                colorMap.put(colorList[i], i);
            }
            
            hate = new boolean[n][n];
            int m = ipar();

            for (int i = 0; i<m; i++) {
                String colorA = spar(), colorB = spar();
                hate[colorMap.get(colorA)][colorMap.get(colorB)] = hate[colorMap.get(colorB)][colorMap.get(colorA)] = true;
            }

            dp = new int[n][1<<n];
            for (int i = 0; i<n; i++) {
                for (int j = 0; j<(1<<n); j++) dp[i][j] = -1;
            }

            for (int i = 0; i<n; i++) dp[i][(1<<n)-1] = 1;
            int ret = 0;
            for (int i = 0; i<n; i++) ret += solve(i, 1<<i);
            
            next = new int[n];
            Arrays.fill(next, -1);
            int curr = -1;
            
            out.println(ret);

            for (int i = 0; i<n; i++) {
                if (possible(i, 1<<i)) {
                    curr = i;
                    break;
                }
            }

            for (int i = 0; i<n; i++) {
                out.print(colorList[curr] + " ");
                curr = next[curr];
            }
            out.println();
        }
    }

    public int solve(int currIdx, int currMask) {
        if (dp[currIdx][currMask] != -1) return dp[currIdx][currMask];
        int ret = 0;
        for (int i = 0; i<n; i++) {
            if ((currMask & (1<<i)) == 0 && !hate[currIdx][i]) ret += solve(i, currMask|(1<<i));
        }
        return dp[currIdx][currMask] = ret;
    }

    public boolean possible(int currIdx, int currMask) {
        if (currMask == (1<<n)-1 || next[currIdx] != -1) return true;
        for (int i = 0; i<n; i++) {
            if ((currMask & (1<<i)) == 0 && !hate[currIdx][i] && possible(i, currMask | (1<<i))) {
                next[currIdx] = i;
                return true;
            }
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
        new Paintings().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}