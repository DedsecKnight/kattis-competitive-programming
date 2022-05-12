import java.util.*;
import java.io.*;

public class BreakingCake {
    int a, b, c;

    class Point implements Comparable<Point> {
        int x, y, z;
        int index;

        public Point(int x, int y, int z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public int compareTo(Point other) {
            if (x != other.x)
                return Integer.compare(x, other.x);
            if (y != other.y)
                return Integer.compare(y, other.y);
            return Integer.compare(z, other.z);
        }

        public String toString() {
            return String.format("%d %d %d", x, y, z);
        }
    }

    class Pair {
        int index;
        Point start, end;

        public Pair(Point s, Point e) {
            start = s;
            end = e;
        }

        public String toString() {
            return String.format("%s %s", start.toString(), end.toString());
        }
    }

    public ArrayList<Pair> solveZ(ArrayList<Point> points, int lowX, int highX, int lowY, int highY) {
        ArrayList<Pair> ret = new ArrayList<>();
        if (points.size() == 1) {
            ret.add(new Pair(new Point(lowX, lowY, 1), new Point(highX, highY, c)));
            ret.get(0).index = points.get(0).index;
            return ret;
        }
        int prevZ = 1;
        for (int i = 0; i < points.size(); i++) {
            ret.add(new Pair(new Point(lowX, lowY, prevZ),
                    new Point(highX, highY, i == points.size() - 1 ? c : points.get(i).z)));
            ret.get(i).index = points.get(i).index;
            prevZ = points.get(i).z + 1;
        }
        return ret;
    }

    public ArrayList<Pair> solveY(ArrayList<Point> points, int lowX, int highX) {
        ArrayList<Pair> ret = new ArrayList<>();
        if (points.size() == 1) {
            ret.add(new Pair(new Point(lowX, 1, 1), new Point(highX, b, c)));
            ret.get(0).index = points.get(0).index;
            return ret;
        }
        int currY = points.get(0).y, prevY = 1;

        ArrayList<Point> curr = new ArrayList<>();
        for (Point p : points) {
            if (p.y != currY) {
                ret.addAll(solveZ(curr, lowX, highX, prevY, currY));
                curr.clear();
                prevY = currY + 1;
                currY = p.y;
            }
            curr.add(p);
        }
        ret.addAll(solveZ(curr, lowX, highX, prevY, b));
        return ret;
    }

    public ArrayList<Pair> solveX(ArrayList<Point> points) {
        ArrayList<Pair> ret = new ArrayList<>();
        ArrayList<Point> curr = new ArrayList<>();

        int currX = points.get(0).x, prevX = 1;

        for (Point p : points) {
            if (p.x != currX) {
                ret.addAll(solveY(curr, prevX, currX));
                curr.clear();
                prevX = currX + 1;
                currX = p.x;
            }
            curr.add(p);
        }

        ret.addAll(solveY(curr, prevX, a));

        return ret;
    }

    public void run() throws IOException {
        while (true) {
            a = nextInt();
            if (a == -1)
                break;
            b = nextInt();
            c = nextInt();
            int n = nextInt();

            ArrayList<Point> points = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                points.add(new Point(nextInt(), nextInt(), nextInt()));
                points.get(i).index = i;
            }
            Collections.sort(points);

            ArrayList<Pair> ret = solveX(points);

            Collections.sort(ret, (Pair a, Pair b) -> {
                return Integer.compare(a.index, b.index);
            });

            out.println("YES");
            for (Pair p : ret) {
                out.println(p);
            }
        }
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
        new BreakingCake().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
