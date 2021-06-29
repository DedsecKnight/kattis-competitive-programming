#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end()) 
#define printVerdict(verdict) cout << (verdict ? "YES": "NO") << '\n'
#define printDecimal(d) cout << setprecision(d) << fixed
#define debugDecimal(d) cerr << setprecision(d) << fixed
#define inrange(val, start, end) (val >= start && val <= end)
#define var(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
#define PI 3.14159265
 
const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
const ll mod = 1e9 + 7;
 
 
template <class T1, class T2, class T3> 
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
void printPair(const pair<T1, T2> &p) { cout << p.first << " " << p.second << '\n'; }
template <class T>
void printArray(const vector<T> &arr) { for (int i = 0; i<len(arr); i++) {cout << arr[i] << " ";} cout << '\n'; }
template<class T>
void read(vector<T> &a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T> 
void read(T* a, int n) { for (int i= 0; i<n; i++) cin >> a[i]; }
template<class T>
void readIdx(vector<pair<T, int>> &a, int n) { for (int i = 0; i<n; i++) { cin >> a[i].first; a[i].second = i; }} 
template<class T>
void printGrid(const vector<vector<T>> &grid) {for (int i =0; i<len(grid); i++) {for (int j =0; j<len(grid[i]); j++) { cout << grid[i][j] << " ";}cout << '\n';}}
template<class T1, class T2>
void readPair(pair<T1, T2> &a) { cin >> a.first >> a.second; }
 
const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;
 
const char* INPUT_FILE = "input.txt";
const char* OUTPUT_FILE = "output.txt";

struct TrieNode {
    static const int ALPHABET_SIZE = 26;

    int end_idx, vowel_count;
    TrieNode *link, *exit_link;
    vector<TrieNode*> children;
    vector<TrieNode*> next;

    TrieNode() {
        end_idx = vowel_count = -1;
        link = nullptr;
        exit_link = nullptr;
        children.assign(ALPHABET_SIZE, nullptr);
        next.assign(ALPHABET_SIZE, nullptr);
    }
};

struct AhoCorasick {
    TrieNode *root;
    vector<string> dictionary;

    AhoCorasick(int n) {
        root = new TrieNode();
        root->link = root;
        dictionary.resize(n);
        root->exit_link = root;
    }

    static bool vowel(char c) {
        return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'; 
    }

    void populate_dictionary(int i) {
        cin >> dictionary[i];
        TrieNode *ptr = root;
        int vowel_cnt = 0;
        for (char c : dictionary[i]) {
            if (vowel(c)) {
                vowel_cnt++;
                continue;
            }
            int idx = c - 'A';
            if (!ptr->children[idx]) ptr->children[idx] = new TrieNode();
            ptr = ptr->children[idx];
        }
        if (ptr->vowel_count < vowel_cnt || ptr->vowel_count == -1) {
            ptr->end_idx = i;
            ptr->vowel_count = vowel_cnt;
        }
    }

    void build_link() {
        deque<TrieNode*> q;

        for (int i = 0; i< TrieNode::ALPHABET_SIZE; i++) {
            if (!root->children[i]) {
                root->children[i] = root;
                continue;
            }
            root->children[i]->link = root;
            q.push_back(root->children[i]);
        }   

        while (!q.empty()) {
            TrieNode *curr = q.front(); q.pop_front();
            for (int i = 0; i<TrieNode::ALPHABET_SIZE; i++) {
                if (!curr->children[i]) continue;
                TrieNode* ptr = curr->link;
                while (!ptr->children[i]) ptr = ptr->link;
                curr->children[i]->link = ptr->children[i];
                q.push_back(curr->children[i]);
            }
        }
    }

    TrieNode* next_node(TrieNode *curr_node, int idx) {
        if (curr_node->next[idx]) return curr_node->next[idx];
        TrieNode* ptr = curr_node;
        while (!ptr->children[idx]) ptr = ptr->link;
        return curr_node->next[idx] = ptr->children[idx];
    }

    TrieNode* get_exit_link(TrieNode* ptr) {
        if (ptr->exit_link) return ptr->exit_link;
        if (ptr->end_idx != -1) return ptr->exit_link = ptr;
        TrieNode* curr_ptr = ptr;
        while (true) {
            curr_ptr = curr_ptr->link;
            if (curr_ptr->exit_link != nullptr) return ptr->exit_link = curr_ptr->exit_link;
            if (curr_ptr == root || curr_ptr->end_idx != -1) return ptr->exit_link = curr_ptr;
        }
    }

};

void prayGod() {
    int n; cin >> n;
    AhoCorasick aho_automaton(n);
    for (int i = 0; i<n; i++) {
        aho_automaton.populate_dictionary(i);
    }
    aho_automaton.build_link();

    string pattern; cin >> pattern;

    TrieNode *ptr = aho_automaton.root;
    
    int m = len(pattern);

    int curr = -1, best = -1;
    vector<int> next(m, -2), str_idx(m, -1), dp(m, -1);
    
    for (int i = 0; i<m; i++) {
        ptr = aho_automaton.next_node(ptr, pattern[i] - 'A');
        TrieNode *curr_ptr = ptr;

        while (true) {
            curr_ptr = aho_automaton.get_exit_link(curr_ptr);
            if (curr_ptr == aho_automaton.root) break;
            int sz = len(aho_automaton.dictionary[curr_ptr->end_idx]) - curr_ptr->vowel_count - 1;
            int start = i-sz;
            int prev_state = (start - 1 >= 0 ? dp[start-1] : 0) + curr_ptr->vowel_count;

            if (dp[i] < prev_state && next[start-1] != -2) {
                next[i] = start - 1;
                str_idx[i] = curr_ptr->end_idx;
                dp[i] = prev_state;
            }

            curr_ptr = curr_ptr->link;
        }

        if (best <= dp[i]) {
            best = dp[i];
            curr = i;
        }
    }
    
    // assert(best >= 0);
    // cerr << var(curr) << var(best) << '\n';

    stack<int> idx_list;
    while (inrange(curr, 0, m-1)) {
        idx_list.push(curr);
        curr = next[curr];
    }
    
    while (!idx_list.empty()) {
        int pos = idx_list.top();
        idx_list.pop();
        if (str_idx[pos] != -1) cout << aho_automaton.dictionary[str_idx[pos]] << " ";
    }

    cout << '\n';

}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT) freopen(OUTPUT_FILE, "w", stdout);
    
    try {
        prayGod();
    }
    catch (exception& e) {
        cerr << e.what() << '\n';
    }
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}

