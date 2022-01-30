
/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/genefolding
TAGS: manacher
EXPLANATION:
- This is another approach for solving problem using Manacher's algorithm 
instead of rolling hash (refer to Suraj Mathashery's solution for more details)
- Some observations to solve this problem: 
    + The optimal answer can be achieved by continuously folding from the left end until it is no longer possible,
    and then do the same from the right end. (I wrote a bruteforce DP solution to figure out this observation)
    + Given a position i and all sub-palindromes that has i as starting point, it can be shown that 
    the smallest fold will be resulted from the sub-palindrome which center is the closest to i
    + Manacher's algorithm ensures that all sub-palindromes will be discovered in ascending order of its center
- Solution sketch:
    + Initialize 2 pointers: currLeft and currRight. These pointer will be the starting and ending point of the 
    optimal folded string
    + Running Manacher algorithm on the given string, everytime we find a new sub-palindrome that covers currLeft, we
    will move currLeft to the center of that newly-found subpalindrome
    + After establish currLeft, we will do the same process for currRight, but now the sub-palindromes will be processed
    in decreasing order of its center. 
- Note: 
    + When trying to find the optimal currRight, make sure to only consider palindromes that are within s[currLeft:]
END ANNOTATION
*/
import java.util.*;
import java.io.*;

public class GeneFolding {

    public void prayGod() throws IOException {
        String s = next();
        int n = s.length();
        int[] dp = new int[n];

        int l = 0, r = -1;
        int currLeft = 0, currRight = n - 1;

        for (int i = 0; i < n; i++) {
            dp[i] = (i + 1 > r ? 0 : Math.min(dp[l + r - i - 1], r - i - 1));
            while (i - dp[i] >= 0 && i + dp[i] + 1 < n && s.charAt(i - dp[i]) == s.charAt(i + dp[i] + 1)) {
                dp[i]++;
            }
            if (i + dp[i] > r) {
                r = i + dp[i];
                l = i - dp[i] + 1;
            }
            if (i - dp[i] + 1 <= i + dp[i]) {
                if (currLeft >= i - dp[i] + 1)
                    currLeft = i + 1;
            }
        }

        for (int i = n - 1; i >= currLeft; i--) {
            int left = i - dp[i] + 1, right = i + dp[i];
            if (left > right || left < currLeft)
                continue;
            if (currRight <= right)
                currRight = i;
        }

        out.println(currRight - currLeft + 1);
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
    static long mod = (long) 998244353;

    static char[] inputBuffer = new char[1 << 24];
    static PushbackReader in = new PushbackReader(new BufferedReader(new InputStreamReader(System.in)), 1 << 24);
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
            in = new PushbackReader(new BufferedReader(new FileReader(new File("output.txt"))), 1 << 24);
        if (FILE_OUTPUT)
            out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new GeneFolding().prayGod();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
