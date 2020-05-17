#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>

using namespace std;

// 网易：牛牛找工作
struct Work {
    int d, p;
    Work (int d, int p) : d(d), p(p) {}
};

bool Compare (Work w1, Work w2) {
    if (w1.d < w2.d) return true;
    else if (w1.d == w2.d && w1.p >= w2.p) return true;
    return false;
}

int NNFindJob () {
    int N, M;
    cin >> N >> M;
    vector<Work> w;
    for (int i = 0; i < N; i ++) {
        int di, pi;
        cin >> di >> pi;
        w.push_back ( Work (di, pi) );
    }

    // 按难度排序
    sort (w.begin(), w.end(), Compare);

    vector<pair<int, int>> A (M);
    for (int i = 0; i < M; i ++) {
        cin >> A[i].first;
        A[i].second = i;
    }
    // 按能力排序，但是需要记录伙伴位置
    sort (A.begin(), A.end());

    int result[M], pos1 = 0, pos2 = 0, cuSalary = 0;
    memset (result, 0, sizeof(result));
    while (pos1 < N && pos2 < M) {
        if (w[pos1].d <= A[pos2].first) {
            cuSalary = max (cuSalary, w[pos1++].p); // 该伙伴可以获得更高的工资
        }
        else {
            result[A[pos2 ++].second] = cuSalary; // 伙伴最高获得工资
        }
    }
    while (pos2 < M) result[A[pos2++].second] = cuSalary;
    for (int i = 0; i < M; i ++) cout << result[i] << endl;

    return 0;
}

// 网易：被3整除
int DivideBy3 () {
    int l, r;
    while (cin >> l >> r) {
        int sum = 0;
        for (int i = 0; i < l; i ++) {
            int k = i + 1;
            while (k % 10 != 0) {
                sum += k % 10;
                k /= 10;
            }
        }
        int count = 0;
        for (int i = l; i <= r; i ++) {
            if (sum % 3 == 0) count ++;
            int k = i + 1;
            while (k % 10 != 0) {
                sum += k % 10;
                k /= 10;
            }
        }
        cout << count << endl;
    }
    return 0;
}

// 网易：安置路灯
int StreetLamp () {
    int t;
    cin >> t;
    for (int i = 0; i < t; i ++) {
        int n;
        string road;
        cin >> n >> road;
        int light = 0;
        for (int j = 0; j < n;) {
            while (j < n && road[j] == 'X') j ++;
            if (j == n) break;
            light ++;
            j += 3;
        }
        cout << light << endl;
    }
    return 0;
}

// 网易：迷路的牛牛
int FindDirection () {
    int N;
    string str;
    // 0-L, 1-R, N-0, E-1, S-2, W-3
    int next[2][4] = {{3, 0, 1, 2}, {1, 2, 3, 0}};

    while (cin >> N >> str) {
        int direction = 0;
        for (int i = 0; i < N; i ++) {
            int lr = 0;
            if (str[i] == 'R') lr = 1;
            direction = next[lr][direction];
        }
        switch (direction) {
            case 0 : cout << "N" << endl; break;
            case 1 : cout << "E" << endl; break;
            case 2 : cout << "S" << endl; break;
            case 3 : cout << "W" << endl; break;
        }
    }
    return 0;
}

// 网易：数对
int NumberPairs () {
    int n, k;
    while (cin >> n >> k) {
        // k < y <= n
        // x = a*y + [k,y)
        // a <= n / y, a >= 0
        long count = 0;
        for (int y = k + 1; y <= n; y ++) {
            long a = n / y;
            count += a * (y - k); // a < n / y
            if (k == 0) count --;
            long p = n - a * y - k + 1;
            if (p > 0) count += p;
        }
        cout << count << endl;
    }
    return 0;
}

// 网易：矩形重叠
int MatrixOverlapping() {
    int n;
    cin >> n;
    int x1[n], y1[n], x2[n], y2[n];
    for (int i = 0; i < n; i ++) {
        cin >> x1[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> y1[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> x2[i];
    }
    for (int i = 0; i < n; i ++) {
        cin >> y2[i];
    }
    int result = 0;
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j ++) {
            // 每个重叠矩形必然包含某个点(x1[i], y1[j])
            // 所以只需要记录每个(x1[i], y1[j])点被多少矩形包含
            int cNum = 0;
            for (int k = 0; k < n; k ++) {
                if (x1[i] >= x1[k] && x1[i] < x2[k] && y1[j] >= y1[k] && y1[j] < y2[k]) {
                    cNum ++;
                }
            }
            result = max(result, cNum);
        }
    }
    cout << result << endl;
    return 0;
}

// 网易：牛牛的闹钟
int ClockOfNN() {
    int N;
    int X;
    pair<int, int> AB;
    const int minutesPerHour = 60;
    const int minutesPerDay = 24 * 60;
    while (cin >> N) {
        vector<pair<int, int>> clock (N);
        for (int i = 0; i < N; i ++) {
            cin >> clock[i].first >> clock[i].second;
        }
        cin >> X;
        cin >> AB.first >> AB.second;
        // 从零点开始算，到上课的分钟数
        int tmp = AB.first * minutesPerHour + AB.second;
        if (tmp - X >= 0) {
            // 可以在今天起床
            tmp = tmp - X;
        }
        else {
            // 需要提前一天起床
            tmp = minutesPerDay + tmp - X;
        }
        sort(clock.begin(), clock.end());
        pair<int, int> result;
        for (int i = 0; i < N; i ++) {
            if (clock[i].first * minutesPerHour + clock[i].second <= tmp) {
                result = clock[i];
            }
            else break;
        }
        cout << result.first << " " << result.second << endl;
    }
    return 0;
}

// 网易：牛牛的背包问题
long NNsBackpackDp(long *x, long n, long w);
int NNsBackpack() {
    long n, w;
    while (cin >> n >> w) {
        long result = 0;
        long v[n];
        long long sum = 0;
        for (long i = 0; i < n; i ++) {
            cin >> v[i];
            sum += v[i];
        }
        // 第i种零食放+第i种零食不放
        if (sum <= w) {
            // 部分用例可以用此判定条件筛除来减少运行时间
            cout << (1 << n) << endl;
        }
        else cout << NNsBackpackDp(v, n, w) << endl;
    }
    return 0;
}
long NNsBackpackDp(long *v, long n, long w) {
    if (w < 0) return 0;
    else if (n == 0) return 1;

    return (NNsBackpackDp(v + 1, n - 1, w) + NNsBackpackDp(v + 1, n - 1, w - v[0]));
}

// 网易：俄罗斯方块
int Tetris() {
    int n, m;
    while (cin >> n >> m) {
        // 记录每列落下了多少方块
        int tmp;
        int c[n] = {};
        for (int i = 0; i < m; i ++) {
            cin >> tmp;
            c[tmp - 1] ++;
        }
        int result = m;
        for (int i = 0; i < n; i ++) result = min(result, c[i]);
        cout << result << endl;
    }
    return 0;
}

// 网易：瞌睡
int Sleep() {
    int n, k;
    while (cin >> n >> k) {
        int a[n] = {};
        for (int i = 0; i < n; i ++) cin >> a[i];
        int t[n] = {};
        int interestWithNoWake = 0;
        for (int i = 0; i < n; i ++) {
            cin >> t[i];
            if (t[i] == 1) interestWithNoWake += a[i];
        }
        // 第0分钟叫醒的收益
        int income = 0;
        for (int i = 0; i < k && i < n; i ++) {
            if (t[i] == 0) income += a[i];
        }
        int result = interestWithNoWake + income;
        for (int i = 1; i < n && i + k - 1 < n; i ++) {
            if (t[i - 1] == 0) income -= a[i - 1];
            if (t[i + k - 1] == 0) income += a[i + k - 1];
            // 每分钟叫醒的收益
            result = max(result, interestWithNoWake + income);
        }
        cout << result << endl;
    }
    return 0;
}

// 网易：丰收
int Harvest() {
    int n;
    while (cin >> n) {
        int a[n];
        int sum = 0;
        for (int i = 0; i < n; i ++) {
            cin >> a[i];
            a[i] += sum;
            sum = a[i];
        }
        int m;
        cin >> m;
        vector<pair<int, int>> q (m);
        for (int i = 0; i < m; i ++) {
            cin >> q[i].first;
            q[i].second = i;
        }
        // 对询问排序，后面使用两个指针交替在两个数组上移动来确定堆数
        // 时间复杂度：O(m + n)
        sort(q.begin(), q.end());

        int result[m] = {};
        int posA = 0, posQ = 0;
        while (posA < n && posQ < m) {
            if (a[posA] < q[posQ].first) posA ++;
            else {
                result[q[posQ].second] = posA + 1;
                posQ ++;
            }
        }
        for (int i = 0; i < m; i ++) cout << result[i] << endl;
    }
    return 0;
}