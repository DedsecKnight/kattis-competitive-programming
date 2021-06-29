import java.io.*;
import java.util.*;
import java.math.*;

public class BabyNames {
    static final int ALPHABET_SIZE = 26;

    class TrieNode {
        TrieNode[] children = new TrieNode[ALPHABET_SIZE];
        // leaf_count stores the number of names that ends after the current trie node
        // end_count stores the number of names that ends at the current trie node
        int leaf_count, end_count;

        TrieNode() {
            leaf_count = 0;
            end_count = 0;
            for (int i = 0; i<ALPHABET_SIZE; i++) children[i] = null;
        }
    }

    TrieNode male_root, female_root;

    void insert(String word, int gender) {
        TrieNode ptr = (gender == 1 ? male_root : female_root);
        for (int i = 0; i<word.length(); i++) {
            int idx = word.charAt(i) - 65;
            ptr.leaf_count++;
            if (ptr.children[idx] == null) ptr.children[idx] = new TrieNode();
            ptr = ptr.children[idx];
        }
        ptr.end_count++;
    }

    void remove(String word, int gender) {
        TrieNode ptr = (gender == 1 ? male_root : female_root);
        for (int i = 0; i<word.length(); i++) {
            int idx = word.charAt(i) - 65;
            ptr.leaf_count--;
            ptr = ptr.children[idx];
        }
        ptr.end_count--;
    }

    boolean exist(String word, int gender) {
        TrieNode ptr = (gender == 1 ? male_root : female_root);
        for (int i = 0; i<word.length(); i++) {
            int idx = word.charAt(i) - 65;
            if (ptr.children[idx] == null || ptr.children[idx].leaf_count + ptr.children[idx].end_count < 1) return false;
            ptr = ptr.children[idx];
        }
        return ptr.end_count >= 1;
    }

    int count(TrieNode curr, String prefix) {
        // Return the total number of names that the current trie node stores if prefix is blank
        if (prefix.length() == 0) return curr.end_count + curr.leaf_count;
        
        int ret = curr.end_count + curr.leaf_count;
        int curr_idx = prefix.charAt(0) - 65;

        // Ignore all nodes that are smaller than or equal to the prefix
        for (int i = 0; i<=curr_idx; i++) {
            if (curr.children[i] != null) {
                ret -= curr.children[i].leaf_count + curr.children[i].end_count;
                // Check for case 2
                if (i == curr_idx) ret += count(curr.children[curr_idx], prefix.substring(1));
            }
        }
        return ret;
    }

    public void prayGod() throws IOException {
        male_root = new TrieNode();
        female_root = new TrieNode();  

        int op = ipar();
        while (op != 0) {
            if (op == 1) {
                String name = spar();
                int gender = ipar();
                insert(name, gender);
            }
            else if (op == 2) {
                String name = spar();
                if (exist(name, 1)) remove(name, 1);
                if (exist(name, 2)) remove(name, 2);
            }
            else {
                String start = spar();
                String end = spar();
                int gender = ipar();
                int ret = 0;
                if (gender == 0 || gender == 2) ret += count(female_root, start) - count(female_root, end);
                if (gender == 0 || gender == 1) ret += count(male_root, start) - count(male_root, end);
                out.println(ret);
            }
            op = ipar();
        }
    } 

    static final boolean RUN_TIMING = true;
    static final boolean AUTOFLUSH = false;
    static final boolean FILE_INPUT = false;
    static final boolean FILE_OUTPUT = false;

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
    public double dpar() throws IOException { return Double.parseDouble(spar()); }
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
        new BabyNames().prayGod();
        time += System.nanoTime();
        
        if (RUN_TIMING) System.err.printf("%.3f ms%n", time / 1000000.0);
        
        out.flush();
        in.close();
    }
}
