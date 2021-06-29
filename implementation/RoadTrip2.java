import java.util.*;
import java.io.*;

public class RoadTrip2 {
    class Pair<T1, T2> {
        T1 first;
        T2 second;
        public Pair(T1 o1, T2 o2) {
            first = o1;
            second = o2;
        }
    }

    class City {
        String name;
        long visitedTime, lastVisited;
        ArrayList<Pair<Integer, Long>> neighbors;
        public City(String s, long v) {
            name = s;
            visitedTime = v;
            lastVisited = -inf;
            neighbors = new ArrayList<Pair<Integer, Long>>();
        }
    }

    public void solve() throws IOException {
        int n = nextInt(), totalEdge = nextInt();
        long cooldown = nextLong(), maxDuration = nextLong();
        int startCity = nextInt();

        City[] cities = new City[n];
        for (int i = 0; i<n; i++) {
            int index = nextInt();
            String name = next();
            long v = nextLong();
            cities[index] = new City(name, v);
        }

        for (int i = 0; i<totalEdge; i++) {
            int u = nextInt(), v = nextInt();
            long dist = nextLong();
            cities[u].neighbors.add(new Pair<Integer, Long>(v, dist));
            cities[v].neighbors.add(new Pair<Integer, Long>(u, dist));
        }

        long finalTime = 0;
        int currPos = startCity;

        while (true) {
            finalTime += cities[currPos].visitedTime;
            cities[currPos].lastVisited = finalTime;
            
            out.printf("%s ", cities[currPos].name);

            long currClosest = inf;
            int bestNeighbor = -1;

            for (Pair<Integer, Long> neighbor : cities[currPos].neighbors) {
                long nextTime = finalTime + neighbor.second;

                if (nextTime - cities[neighbor.first].lastVisited < cooldown) continue;
                nextTime += cities[neighbor.first].visitedTime;

                if (nextTime > maxDuration) continue;
                if (currClosest > neighbor.second) {
                    currClosest = neighbor.second;
                    bestNeighbor = neighbor.first;
                }
            }

            if (bestNeighbor == -1) break;
            currPos = bestNeighbor;
            finalTime += currClosest;
        }

        out.printf("\n%d\n", finalTime);
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
    public int nextInt() throws IOException { return Integer.parseInt(next()); }
    public int[] nextIntArray(int n) throws IOException {
        int[] arr = new int[n];
        for (int i = 0; i < n; i++) arr[i] = nextInt();
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
    public long nextLong() throws IOException { return Long.parseLong(next()); }
    public long[] nextLongArray(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = nextLong();
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
    public double nextDouble() throws IOException {
        return Double.parseDouble(next());
    }
    public double[] nextDoubleArray(int n) throws IOException {
        double[] arr = new double[n];
        for (int i = 0; i < n; i++) arr[i] = nextDouble();
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

    public String nextLine() throws IOException {
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
        if (FILE_INPUT) in = new PushbackReader(new BufferedReader(new FileReader(new File("output.txt"))), 1 << 20);
        if (FILE_OUTPUT) out = new PrintWriter(new FileWriter(new File("output.txt")));

        long time = 0;
        time -= System.nanoTime();
        new RoadTrip2().solve();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}

