import java.util.*;
import java.io.*;
import java.math.*;

public class ClosestPair2 {
    class Point {
        double x,y;
        public Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
        public String toString() {
            return this.x + " " + this.y;
        }
    }

    static double dist(Point a, Point b) {
        return Math.sqrt(Math.pow(a.x - b.x, 2) + Math.pow(a.y - b.y, 2));
    }

    public void prayGod() throws IOException {
        int n = ipar();
        while (n != 0) {
            Point[] points = new Point[n];
            for (int i = 0; i<n; i++) {
                double x = dpar(), y = dpar();
                points[i] = new Point(x, y);
            }

            shuffle(points);
            Arrays.sort(points, (Point a, Point b)->{
                return Double.compare(a.x, b.x);
            });

            TreeSet<Point> sortedY = new TreeSet<Point>((Point a, Point b)->{
                return Double.compare(a.y, b.y);
            });

            sortedY.add(points[0]);
            sortedY.add(points[1]);
            
            int leftmost = 0;
            double ret = dist(points[0], points[1]);
            Point p1 = points[0], p2 = points[1];

            for (int i = 2; i<n; i++) {
                while (leftmost < i && Math.abs(points[leftmost].x - points[i].x) > ret) {
                    sortedY.remove(points[leftmost]);
                    leftmost++;
                }

                Point head = new Point(points[i].x, points[i].y - ret);
                Point tail = new Point(points[i].x, points[i].y + ret);
                
                for (Point point : sortedY.subSet(head, tail)) {
                    double currDist = dist(point, points[i]);
                    if (currDist < ret) {
                        ret = currDist;
                        p1 = point;
                        p2 = points[i];
                    }
                }
                
                sortedY.add(points[i]);
            }
            out.format("%.3f %.3f %.3f %.3f%n", p1.x, p1.y, p2.x, p2.y);
            n = ipar();
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
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("ClosestPair2.txt")));

        long time = 0;
        time -= System.nanoTime();
        new ClosestPair2().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
