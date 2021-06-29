import java.util.*;
import java.io.*;

public class CheatingBooleanTree {

    class Vertex {
        boolean isLeaf, changeable;
        int[] cost, operation;

        public Vertex(boolean leaf, int val, boolean change) {
            this.changeable = change;
            
            // cost[i] - min cost required to get curr vertex value of i
            cost = new int[2];
            Arrays.fill(cost, iinf);

            // Operation[1] is AND gate, operation[0] is OR gate 
            operation = new int[2];
            
            if (leaf) {
                isLeaf = true;
                cost[val] = 0;
            }
            else {
                isLeaf = false;
                operation[val^1]= (changeable ? 1 : iinf);
                operation[val] = 0;
            }

        };

    };

    Vertex[] vertex;

    public void run() throws IOException {
        int t = nextInt();
        for (int zzz = 1; zzz <= t; zzz++) {
            int n = nextInt(), v = nextInt();
            vertex = new Vertex[n];
            
            int ptr = 0;

            for (int i = 0; i<(n-1)/2; i++) {
                int g = nextInt(), c = nextInt();
                vertex[ptr++] = new Vertex(false, g, (c == 1 ? true : false));
            }

            for (int i = 0; i<(n+1)/2; i++) {
                int val = nextInt();
                vertex[ptr++] = new Vertex(true, val, false);
            }
            
            dfs(0);
            out.printf("Case #%d: ", zzz);
            if (vertex[0].cost[v] >= iinf) out.println("IMPOSSIBLE");
            else out.println(vertex[0].cost[v]);
        }
    }

    public void dfs(int idx) {
        if (vertex[idx].isLeaf) return;
        
        dfs(idx*2 + 1);
        dfs(idx*2 + 2);

        for (int i = 0; i<2; i++) {
            for (int j = 0; j<2; j++) {
                vertex[idx].cost[i&j] = Math.min(vertex[idx].cost[i&j], vertex[idx*2 + 1].cost[i] + vertex[idx*2 + 2].cost[j] + vertex[idx].operation[1]);
                vertex[idx].cost[i|j] = Math.min(vertex[idx].cost[i|j], vertex[idx*2 + 1].cost[i] + vertex[idx*2 + 2].cost[j] + vertex[idx].operation[0]);
            }
        }
    }

    static final boolean RUN_TIMING = false;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

    static int iinf = 100000000;
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

    // long data-type
    public long nextLong() throws IOException { return Long.parseLong(next()); }
    public long[] nextLongArray(int n) throws IOException {
        long[] arr = new long[n];
        for (int i = 0; i < n; i++) arr[i] = nextLong();
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
        for (int i = 0; i < n; i++) arr[i] = nextDouble();
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
        new CheatingBooleanTree().run();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}

