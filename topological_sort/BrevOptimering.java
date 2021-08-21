
/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/brevoptimering
TAGS: graph, topological sort
EXPLANATION:
- Notice: The Problem name is Letter Optimization, while the problem id is brevoptimering (which means the same thing, but in Norwegian)
- It can be seen that the relationship between the person who sends the envelope and that who receives can be modeled as a directed acyclic graph (DAG)
=> Therefore, it is guaranteed that a topological order exists (read Topological sort for more details)
- Approach:
    - Process each person in the topological order
    - For each person:
        + Determine whether the person meets the condition
        + Delegate the amount of envelope to the next person according to percentage rule established by the input
    - Print out the list of those that meets the condition in ascending order
END ANNOTATION
*/
import java.util.*;
import java.io.*;

public class BrevOptimering {

    class Person {
        int inDegree;
        double i, m;
        ArrayList<Integer> neighbor, percent;

        public Person() {
            m = -1;
            i = 0;
            inDegree = 0;
            neighbor = new ArrayList<>();
            percent = new ArrayList<>();
        }

    }

    Person[] people;

    public void run() throws IOException {
        int n = nextInt();
        people = new Person[n];

        for (int i = 0; i < n; i++) {
            people[i] = new Person();
        }

        for (int i = 0; i < n; i++) {
            people[i].m = nextDouble();
            int k = nextInt();
            for (int j = 0; j < k; j++) {
                int neighbor = nextInt() - 1, percent = nextInt();
                people[i].neighbor.add(neighbor);
                people[i].percent.add(percent);
                people[neighbor].inDegree++;
            }
        }

        Deque<Integer> q = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            if (people[i].inDegree == 0) {
                people[i].i = iinf;
                q.addLast(i);
            }
        }

        ArrayList<Integer> ret = new ArrayList<>();

        while (!q.isEmpty()) {
            int curr = q.pollFirst();
            if (people[curr].i >= people[curr].m) {
                ret.add(curr + 1);
            } else {
                people[curr].m = people[curr].i;
            }
            for (int i = 0; i < people[curr].neighbor.size(); i++) {
                int neighbor = people[curr].neighbor.get(i);
                people[neighbor].i += people[curr].m * people[curr].percent.get(i) / 100.0;
                if (--people[neighbor].inDegree == 0) {
                    q.addLast(neighbor);
                }
            }
        }

        Collections.sort(ret);

        for (Integer val : ret)
            out.printf("%d ", val);
        out.println();

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
        new BrevOptimering().run();
        time += System.nanoTime();

        if (RUN_TIMING)
            System.err.printf("%.3f ms%n", time / 1000000.0);

        out.flush();
        in.close();
    }
}
