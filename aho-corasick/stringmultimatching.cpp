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
#define printCase(_) cout << "Case #" << (_) << ": "

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

const int UNDEFINED = -1;

struct TrieNode {
    static const int ALPHABET_SIZE = 100;

    vector<int> end_idx;
    TrieNode *link, *exit_link;
    vector<TrieNode*> children, next;
    
    TrieNode() {
        link = nullptr;
        exit_link = nullptr;
        children.assign(ALPHABET_SIZE, nullptr);
        next.assign(ALPHABET_SIZE, nullptr);
    }
};


struct AhoCorasick {
    TrieNode *root;
    vector<string> dictionary;

    static const int SMALLEST_ASCII = 32;

    AhoCorasick() {
        root = new TrieNode();
        root->link = root;
        root->exit_link = root;
    }

    void populate_dictionary(string s) {
        dictionary.push_back(s);
        TrieNode *ptr = root;
        for (char c : s) {
            int idx = c - SMALLEST_ASCII;
            if (!ptr->children[idx]) ptr->children[idx] = new TrieNode();
            ptr = ptr->children[idx];
        }
        ptr->end_idx.push_back(len(dictionary)-1);
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
        if (!ptr->end_idx.empty()) return ptr->exit_link = ptr;
        TrieNode* curr_ptr = ptr;
        while (true) {
            curr_ptr = curr_ptr->link;
            if (curr_ptr->exit_link != nullptr) return ptr->exit_link = curr_ptr->exit_link;
            if (curr_ptr == root || !curr_ptr->end_idx.empty()) return ptr->exit_link = curr_ptr;
        }
    }

    void search_pattern(string s) {
        int s_size = len(s);
        TrieNode* ptr = root;
        vector<vector<int>> ret_pos(len(dictionary));

        for (int i = 0; i<s_size; i++) {
            ptr = next_node(ptr, s[i] - SMALLEST_ASCII);
            TrieNode *curr_ptr = ptr;

            while (true) {
                curr_ptr = get_exit_link(curr_ptr);
                if (curr_ptr == root) break;
                int sz = len(dictionary[curr_ptr->end_idx[0]]);
                for (int idx : curr_ptr->end_idx) ret_pos[idx].push_back(i-sz+1);
                curr_ptr = curr_ptr->link;
            }
        }

        for (const vector<int> &r : ret_pos) {
            for (int idx : r) cout << idx << " ";
            cout << '\n';
        }
    }
    
};

void prayGod() {
    string s;
    while (getline(cin, s)) {
        if (s == "") break;
        int n = stoi(s);
        AhoCorasick aho;
        for (int i = 0; i<n; i++) {
            getline(cin, s);
            aho.populate_dictionary(s);
        }
        string pattern; getline(cin, pattern);
        aho.build_link();
        aho.search_pattern(pattern);
    }
}
 
int main() {
    clock_t start = clock();
    
    std::ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    if (EXTERNAL_INPUT) freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT) freopen(OUTPUT_FILE, "w", stdout);
    
    prayGod();
    
    clock_t end = clock();
    
    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME) debugDecimal(5) << time_taken << " s" << '\n';
}

