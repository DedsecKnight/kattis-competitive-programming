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
const double PI = 2 * acos(0.0);

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

const double EPS = 1e-9;
const int INF = 2;  // it doesn't actually have to be infinity or a big number

int gauss(vector<vector<double>> a, vector<double> &ans, int &free) {
    int n = (int)a.size();
    int m = (int)a[0].size() - 1;

    vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i)
            if (abs(a[i][col]) > abs(a[sel][col]))
                sel = i;
        if (abs(a[sel][col]) < EPS)
            continue;
        for (int i = col; i <= m; ++i)
            swap(a[sel][i], a[row][i]);
        where[col] = row;

        for (int i = 0; i < n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j = col; j <= m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j)
            sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i = 0; i < m; ++i)
        if (where[i] == -1) {
            free = i;
            return INF;
        }
    return 1;
}

void prayGod() {
    vector<vector<string>> elements;
    map<string, int> max_idx;
    int lcount = 0;

    // Read input
    while (true) {
        string side;
        int sz;
        cin >> side >> sz;
        if (side == "0" && sz == 0) break;
        vector<string> data{side, to_string(sz)};
        for (int i = 0; i < sz; i++) {
            string e, c;
            cin >> e >> c;
            data.push_back(e);
            data.push_back(c);
            if (!present(max_idx, e)) {
                max_idx[e] = lcount++;
            }
        }
        elements.push_back(data);
    }

    // Construct matrix
    vector<vector<double>> original_matrix(len(max_idx), vector<double>(len(elements) + 1, 0.0));

    int idx = 0;
    for (const vector<string> &e : elements) {
        int ptr = 2;
        for (int j = 0; j < stoi(e[1]); j++) {
            if (e[0] == "+1") {
                original_matrix[max_idx[e[ptr]]][idx] += stoi(e[ptr + 1]);
            } else {
                original_matrix[max_idx[e[ptr]]][idx] -= stoi(e[ptr + 1]);
            }
            ptr += 2;
        }
        idx++;
    }

    // Create a duplicate matrix because gauss function will destroy the matrix after execution
    vector<vector<double>> matrix_copy = original_matrix;
    vector<double> ans;
    int free = -1;

    int g = gauss(matrix_copy, ans, free);

    // Assert that a solution exists
    assert(g != 0);

    // If there is 1 solution, print it out
    if (g == 1) {
        cout << ans << '\n';
        return;
    }

    // Else, there are infinitely many solution
    // Since only 1 valid solution exists with minimum number, it can be assumed that there are only 1 free variable
    // Therefore, we can bruteforce all possible values for the free variable until an all-integer solution is found
    for (int t = 1; t <= 100000; t++) {
        // Construct new matrix after converting the free variable to constant
        matrix_copy.assign(len(original_matrix), {});
        for (int i = 0; i < len(matrix_copy); i++) {
            double b = 0.0;
            for (int j = 0; j < len(original_matrix[i]) - 1; j++) {
                if (j == free) {
                    b -= original_matrix[i][j] * t;
                } else
                    matrix_copy[i].push_back(original_matrix[i][j]);
            }
            matrix_copy[i].push_back(b);
        }

        int temp_free = -1;
        g = gauss(matrix_copy, ans, temp_free);

        // If only 1 solution exists
        if (g == 1) {
            ans.insert(ans.begin() + free, double(t));
            bool ok = true;

            // If difference between ans[i] and its rounded value is small enough (1e-12 in this solution)
            // then it is possible to say that the value is close enough to be an integer
            const ld eps = 1e-12;
            for (int i = 0; i < len(ans); i++) {
                if (abs(ans[i] - round(ans[i])) > eps) ok = false;
            }

            if (ok) {
                cout << ans << '\n';
                return;
            }
        }
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