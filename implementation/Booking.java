import java.util.*;
import java.io.*;

public class Booking {

    final int[] dayMonth = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    class Event implements Comparable<Event> {
        int year, month, day;
        int hour, minute;

        public Event(String date, String time) {
            // Parse date
            year = Integer.parseInt(date.substring(0, 4));
            month = Integer.parseInt(date.substring(5, 7));
            day = Integer.parseInt(date.substring(8));

            // Parse time
            hour = Integer.parseInt(time.substring(0, 2));
            minute = Integer.parseInt(time.substring(3));
        }

        public void subtractTime(int min) {
            minute -= min;
            if (minute >= 0) return;

            while (minute < 0) {
                minute += 60;
                hour--;
            }
            if (hour >= 0) return;

            int subtractVal = 0;
            while (hour < 0) {
                hour += 24;
                subtractVal++;
            }
            
            subtractDate(subtractVal);
        }

        public void subtractDate(int d) {
            boolean isLeapYear = (year == 2016);
            day -= d;
            if (day >= 1) return;

            int yearSubtract = 0;
            while (day < 1) {
                month--;
                if (month < 1) {
                    yearSubtract++;
                    month += 12;
                }
                if (month == 2 && isLeapYear) day += 29;
                else day += dayMonth[month];
            }

            year -= yearSubtract;
        }

        @Override
        public int compareTo(Event other) {
            if (year != other.year) return Integer.compare(year, other.year);
            if (month != other.month) return Integer.compare(month, other.month);
            if (day != other.day) return Integer.compare(day, other.day);

            if (hour != other.hour) return Integer.compare(hour, other.hour);
            return Integer.compare(minute, other.minute);
        }
    };

    class Reservation {
        Event arrive, depart;
        public Reservation(Event a, Event d) {
            arrive = a;
            depart = d;
        }
    }

    public void run() throws IOException {
        int t = nextInt();
        while (t-- > 0 ) {
            int n = nextInt(), c = nextInt();
            int neededRoom = 0, availableRoom = 0;

            ArrayList<Reservation> reservations = new ArrayList<>();
            for (int i = 0; i<n; i++) {
                String id = next();
                
                Event arrivalDate = new Event(next(), next());
                Event departDate = new Event(next(), next());

                reservations.add(new Reservation(arrivalDate, departDate));
            }

            Collections.sort(reservations, new Comparator<Reservation>() {
                public int compare(Reservation a, Reservation b) {
                    return a.arrive.compareTo(b.arrive);
                }
            });

            PriorityQueue<Event> pq = new PriorityQueue<>((Event a, Event b)->{
                return a.compareTo(b);
            });

            for (int i = 0; i<n; i++) {
                
                Event arrivalDate = reservations.get(i).arrive;
                Event departDate = reservations.get(i).depart;

                arrivalDate.subtractTime(c);
                while (!pq.isEmpty() && pq.peek().compareTo(arrivalDate) <= 0) {
                    pq.poll();
                    availableRoom++;
                }

                if (availableRoom <= 0) neededRoom++;
                else availableRoom--;

                pq.add(departDate);
            }

            out.println(neededRoom);
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
        new Booking().run();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}

