import java.util.*;
import java.io.*;
import java.math.*;

public class MallMania {
    
    class Point {
        int x, y;
        public Point(int x1, int y1) {
            this.x = x1;
            this.y = y1;
        }
    }

    final int[] a = {-1, 1, 0, 0};
    final int[] b = {0, 0, -1, 1};

    public void prayGod() throws IOException {
        int perimeter1 = ipar();
        while (perimeter1 != 0) {
            int maxx = -1, maxy = -1;

            Point[] mall1 = new Point[perimeter1];
            for (int i = 0; i<perimeter1; i++) {
                mall1[i] = new Point(ipar(), ipar());
                maxx = Math.max(maxx, mall1[i].x);
                maxy = Math.max(maxy, mall1[i].y);
            }
            
            int perimeter2 = ipar();
            Point[] mall2 = new Point[perimeter2];
            for (int i = 0; i<perimeter2; i++) {
                mall2[i] = new Point(ipar(), ipar());
                maxx = Math.max(maxx, mall2[i].x);
                maxy = Math.max(maxy, mall2[i].y);
            }
            
            int[][] dist = new int[maxx+1][maxy+1];
            for (int i = 0; i<=maxx; i++) {
                for (int j = 0; j<=maxy; j++) dist[i][j] = iinf;
            }

            Deque<Integer> q = new LinkedList<Integer>();
            
            for (int i = 0; i<perimeter1; i++) {
                dist[mall1[i].x][mall1[i].y] = 0;
                q.add(mall1[i].x * (maxy+1) + mall1[i].y);
            }
            
            while (!q.isEmpty()) {
                int curr = q.pollFirst();
                int i = curr/(maxy+1), j = curr%(maxy+1);
                for (int k = 0; k<4; k++) {
                    int new_x = i+a[k], new_y = j+b[k];
                    if (new_x < 0 || new_x > maxx || new_y < 0 || new_y > maxy) continue;
                    if (dist[new_x][new_y] > dist[i][j] + 1) {
                        dist[new_x][new_y] = dist[i][j] + 1;
                        q.add(new_x * (maxy+1) + new_y);
                    }
                }
            }

            int ret = iinf;
            for (int i = 0; i<perimeter2; i++) {
                ret = Math.min(ret, dist[mall2[i].x][mall2[i].y]);
            }
            out.println(ret);
            perimeter1 = ipar();
        }
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
        new MallMania().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
