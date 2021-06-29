#include <bits/stdc++.h>
using namespace std;

typedef unsigned int ui;
typedef long long ll;
typedef long double ld;
#define null NULL
#define umap unordered_map
#define len(a) int((a).size())
#define present(c, x) (c.find(x) != c.end())
#define inrange(val, start, end) (val >= start && val <= end)
#define PI 3.14159265

const int iinf = 0x3f3f3f3f;
const ll inf = 1e18;
const ll mod = 1e9 + 7;

#define var(args...)                           \
    {                                          \
        string _s = #args;                     \
        stringstream _ss;                      \
        string ccurr = "";                     \
        for (int zz = 0; zz < len(_s); zz++) { \
            if (_s[zz] == ' ') continue;       \
            if (_s[zz] == ',') {               \
                _ss << ' ' + ccurr;            \
                ccurr = "";                    \
            } else                             \
                ccurr += _s[zz];               \
        }                                      \
        _ss << ' ' + ccurr;                    \
        istream_iterator<string> _it(_ss);     \
        vars(_it, args);                       \
    }
#define debugDecimal(d) cerr << setprecision(d) << fixed

void vars(istream_iterator<string> it) { cerr << '\n'; }
template <typename T, typename... Args>
void vars(istream_iterator<string> it, T a, Args... args) {
    cerr << " [" << *it << ": " << a << "] ";
    vars(++it, args...);
}

#define printVerdict(verdict) \
    cout << (verdict ? "YES" : "NO") << '\n'
#define printDecimal(d) \
    cout << setprecision(d) << fixed
#define printCase(_) \
    cout << "Case #" << (_) << ": "

template <class T1, class T2, class T3>
void printTuple(const tuple<T1, T2, T3> &t) { cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n'; }
template <class T1, class T2>
ostream &operator<<(ostream &out, const pair<T1, T2> &p) { return out << p.first << " " << p.second; }
template <class T>
ostream &operator<<(ostream &out, const vector<T> &arr) {
    for (const T &a : arr) out << a << " ";
    return out;
}
template <class T>
ostream &operator<<(ostream &out, const vector<vector<T>> &grid) {
    for (const vector<T> &row : grid) out << row << '\n';
    return out;
}
template <class T>
istream &operator>>(istream &in, vector<T> &arr) {
    for (T &a : arr) in >> a;
    return in;
}
template <class T>
void readIdx(vector<pair<T, int>> &a, int n) {
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
}
template <class T1, class T2>
istream &operator>>(istream &in, pair<T1, T2> &a) {
    in >> a.first >> a.second;
    return in;
}

const bool PRINT_EXEC_TIME = true;
const bool EXTERNAL_INPUT = false;
const bool EXTERNAL_OUTPUT = false;

const char *INPUT_FILE = "input.txt";
const char *OUTPUT_FILE = "output.txt";

const int nax = 100000;

const vector<vector<vector<string>>> keyboard = {
    {{"Q", "q"}, {"W", "w"}, {"E", "e"}, {"R", "r"}, {"T", "t"}, {"Y", "y"}, {"U", "u"}, {"I", "i"}, {"O", "o"}, {"P", "p"}},
    {{"A", "a"}, {"S", "s"}, {"D", "d"}, {"F", "f"}, {"G", "g"}, {"H", "h"}, {"J", "j"}, {"K", "k"}, {"L", "l"}, {":", ";"}},
    {{"Z", "z"}, {"X", "x"}, {"C", "c"}, {"V", "v"}, {"B", "b"}, {"N", "n"}, {"M", "m"}, {"<", ","}, {">", "."}, {"?", "/"}},
    {{"Shift", "Shift"}, {"Shift", "Shift"}, {" ", " "}, {" ", " "}, {" ", " "}, {" ", " "}, {" ", " "}, {" ", " "}, {"Shift", "Shift"}, {"Shift", "Shift"}},
};

const int dx[] = {-2, -1, 1, 2};
const int dy[] = {-2, -1, 1, 2};

void prayGod() {
    set<string> normal;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) normal.insert(keyboard[i][j][1]);
    }

    while (true) {
        string s;
        getline(cin, s);
        if (s == "*") break;

        int n = len(s);
        vector<vector<vector<bool>>> visited(40, vector<vector<bool>>(40, vector<bool>(n + 1, false)));

        deque<pair<pair<int, int>, int>> q;
        q.emplace_back(make_pair(30, 39), 0);
        visited[30][39][0] = true;

        function<bool(int, int, int, bool)> uppercase_possible = [&](int left_pos, int right_pos, int idx, bool left_move) {
            if (!left_move) swap(left_pos, right_pos);

            int left_x = left_pos / 10, left_y = left_pos % 10;
            int right_x = right_pos / 10, right_y = right_pos % 10;

            if (keyboard[right_x][right_y][0] == "Shift" && keyboard[left_x][left_y][0] == s.substr(idx, 1)) return true;
            return false;
        };

        function<bool(int, int, int, bool)> normal_possible = [&](int left_pos, int right_pos, int idx, bool left_move) {
            if (!left_move) swap(left_pos, right_pos);

            int left_x = left_pos / 10, left_y = left_pos % 10;
            int right_x = right_pos / 10, right_y = right_pos % 10;

            if (s[idx] == ' ') {
                return keyboard[left_x][left_y][1] == " ";
            } else {
                if (keyboard[left_x][left_y][1] == s.substr(idx, 1) && keyboard[right_x][right_y][1] != "Shift") return true;
                return false;
            }
        };

        while (!q.empty()) {
            pair<pair<int, int>, int> curr = q.front();
            q.pop_front();

            int left_pos = curr.first.first, right_pos = curr.first.second, idx = curr.second;
            visited[left_pos][right_pos][idx] = true;

            int left_x = left_pos / 10, left_y = left_pos % 10;
            int right_x = right_pos / 10, right_y = right_pos % 10;

            bool norm = present(normal, s.substr(idx, 1));

            vector<pair<int, int>> left_dest, right_dest;
            for (int x : dx) {
                for (int y : dy) {
                    if (abs(x) == abs(y)) continue;
                    int new_lx = left_x + x, new_ly = left_y + y;
                    int new_left = new_lx * 10 + new_ly;
                    if (inrange(new_lx, 0, 3) && inrange(new_ly, 0, 9)) {
                        if (norm) {
                            if (normal_possible(new_left, right_pos, idx, true))
                                left_dest.emplace_back(new_left, 1);
                            else if (keyboard[new_lx][new_ly][0] == "Shift")
                                left_dest.emplace_back(new_left, 0);
                        } else {
                            if (uppercase_possible(new_left, right_pos, idx, true))
                                left_dest.emplace_back(new_left, 1);
                            else if (keyboard[new_lx][new_ly][0] == "Shift")
                                left_dest.emplace_back(new_left, 0);
                        }
                    }

                    int new_rx = right_x + x, new_ry = right_y + y;
                    int new_right = new_rx * 10 + new_ry;
                    if (inrange(new_rx, 0, 3) && inrange(new_ry, 0, 9)) {
                        if (norm) {
                            if (normal_possible(left_pos, new_right, idx, false))
                                right_dest.emplace_back(new_right, 1);
                            else if (keyboard[new_rx][new_ry][0] == "Shift")
                                right_dest.emplace_back(new_right, 0);
                        } else {
                            if (uppercase_possible(left_pos, new_right, idx, false))
                                right_dest.emplace_back(new_right, 1);
                            else if (keyboard[new_rx][new_ry][0] == "Shift")
                                right_dest.emplace_back(new_right, 0);
                        }
                    }
                }
            }

            for (int i = 0; i < len(left_dest); i++) {
                if (left_dest[i].first == right_pos) continue;
                if (!visited[left_dest[i].first][right_pos][idx + left_dest[i].second]) {
                    visited[left_dest[i].first][right_pos][idx + left_dest[i].second] = true;
                    q.emplace_back(make_pair(left_dest[i].first, right_pos), idx + left_dest[i].second);
                }
            }

            for (int i = 0; i < len(right_dest); i++) {
                if (right_dest[i].first == left_pos) continue;
                if (!visited[left_pos][right_dest[i].first][idx + right_dest[i].second]) {
                    visited[left_pos][right_dest[i].first][idx + right_dest[i].second] = true;
                    q.emplace_back(make_pair(left_pos, right_dest[i].first), idx + right_dest[i].second);
                }
            }
        }

        bool possible = false;
        for (int i = 0; i < 40; i++) {
            for (int j = 0; j < 40; j++) {
                if (i == j) continue;
                if (visited[i][j][n]) {
                    possible = true;
                }
            }
        }

        cout << possible << '\n';
    }
}

int main() {
    clock_t start = clock();

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (EXTERNAL_INPUT)
        freopen(INPUT_FILE, "r", stdin);
    if (EXTERNAL_OUTPUT)
        freopen(OUTPUT_FILE, "w", stdout);

    prayGod();

    clock_t end = clock();

    double time_taken = double(end - start) / CLOCKS_PER_SEC;
    if (PRINT_EXEC_TIME)
        debugDecimal(5) << time_taken << " s" << '\n';
}