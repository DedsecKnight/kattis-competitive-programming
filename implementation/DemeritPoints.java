import java.util.*;
import java.io.*;

public class DemeritPoints {
    class Event implements Comparable<Event> {
        int year, month, date, demerit;
        public Event(String s, int d) {
            demerit = d;
            year = Integer.parseInt(s.substring(0, 4));
            month = Integer.parseInt(s.substring(4, 6));
            date = Integer.parseInt(s.substring(6));
        }
        public int compareTo(Event other) {
            if (year != other.year) return Integer.compare(year, other.year);
            if (month != other.month) return Integer.compare(month, other.month);
            return Integer.compare(date, other.date);
        }
    }

    public void printNothing(Event e) {
        out.printf("%d-%02d-%02d No merit or demerit points.\n", e.year, e.month, e.date);
    }

    public void printMerit(Event e, int merit) {
        out.printf("%d-%02d-%02d %d merit point(s).\n", e.year, e.month, e.date, merit);
    }

    public void printDemerit(Event e, int demerit) {
        out.printf("%d-%02d-%02d %d demerit point(s).\n", e.year, e.month, e.date, demerit);
    }

    public void run() throws IOException {
        int currDemerit = 0, currMerit = 0;
        Event currEvent = new Event(next(), 0);

        printNothing(currEvent);

        while (hasNext()) {
            Event newEvent = new Event(next(), nextInt());

            int yearsFromLastOffense = 0;
            while (true) {
                currEvent.year++;
                if (currEvent.compareTo(newEvent) > 0) break;
                yearsFromLastOffense++;
                if (currDemerit > 0) {
                    currDemerit -= Math.max((currDemerit + 1) / 2, 2);
                    currDemerit = Math.max(currDemerit, 0);
                    if (currDemerit > 0) printDemerit(currEvent, currDemerit);
                    else {
                        printNothing(currEvent);
                        yearsFromLastOffense = 0;
                    }
                }
                else if (yearsFromLastOffense % 2 == 0 && currMerit < 5) {
                    currMerit += 1;
                    printMerit(currEvent, currMerit);
                }
            }
            currEvent = newEvent;
            currDemerit += currEvent.demerit;

            if (currDemerit <= 2*currMerit) {
                currMerit -= (currDemerit + 1)/2;
                currDemerit = 0;
                yearsFromLastOffense = 0;
                if (currMerit > 0) printMerit(currEvent, currMerit);
                else printNothing(currEvent);
            }
            else {
                currDemerit -= 2*currMerit;
                currMerit = 0;
                if (currDemerit > 0) printDemerit(currEvent, currDemerit);
                else printNothing(currEvent);
            }
        }

        int yearsFromLastOffense = 0;
        while (currMerit < 5) {
            yearsFromLastOffense++;
            currEvent.year++;
            if (currDemerit > 0) {
                currDemerit -= Math.max((currDemerit + 1) / 2, 2);
                currDemerit = Math.max(currDemerit, 0);
                if (currDemerit > 0) printDemerit(currEvent, currDemerit);
                else {
                    printNothing(currEvent);
                    yearsFromLastOffense = 0;
                }
            }
            else if (yearsFromLastOffense % 2 == 0) {
                currMerit += 1;
                printMerit(currEvent, currMerit);
            }
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
        new DemeritPoints().run();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}

