// ​
// 题目链接：https://codeforces.com/gym/105911/problem/D

// 题目大意：给定三维空间内的若干条线段，限制其端点在一给定长方体上，求对于任意与坐标轴垂直的平面最多能和多少条线段相交。

// 题目思路：考虑垂直于x轴切一刀的情况：对于一条线段从x1到x2，它能被x=c 切断当且仅当x1≤c≤x2。 所以问题转化为，给定n条线段，求最多有多少条线段覆盖同一位置。 那么我们将线段离散化，考虑差分，对于x1到x2，把x1加上1，x2+1 减去1，然后求一遍前缀和即可。 y, z 轴同理

// 代码如下:时间复杂度（O(nlogn)）

//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
struct segment
{
    int x1, y1, z1;
    int x2, y2, z2;
};
int maxoverlap(vector<pair<int, int>> &intervals)
{
    if (intervals.empty())
    {
        return 0;
    }
    // 1.收集所有需要离散化的坐标点
    vector<int> coords;
    for (auto &p : intervals)
    {
        coords.push_back(p.first);      // L
        coords.push_back(p.second + 1); // R+1
    }
    // 2.排序+去重
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    // 3.差分数组
    vector<int> diff(coords.size(), 0);
    for (auto &p : intervals)
    {
        int L = p.first;
        int R = p.second;
        int idxL = lower_bound(coords.begin(), coords.end(), L) - coords.begin();
        int idxR = lower_bound(coords.begin(), coords.end(), R + 1) - coords.begin();
        diff[idxL]++;
        diff[idxR]--;
    }
    // 4.前缀和求最大值
    int cur = 0;
    int ans = 0;
    for (auto &i : diff)
    {
        cur += i;
        ans = max(ans, cur);
    }
    return ans;
}
void solve()
{
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    vector<segment> segs(n);
    for (int i = 0; i < n; i++)
    {
        cin >> segs[i].x1 >> segs[i].y1 >> segs[i].z1;
        cin >> segs[i].x2 >> segs[i].y2 >> segs[i].z2;
    }
    int ans = 0;
    // 处理x方向
    vector<pair<int, int>> intervals_x;
    for (auto &s : segs)
    {
        int L = min(s.x1, s.x2);
        int R = max(s.x1, s.x2);
        intervals_x.push_back({L, R});
    }
    ans = max(ans, maxoverlap(intervals_x));
    // 处理y方向
    vector<pair<int, int>> intervals_y;
    for (auto &s : segs)
    {
        int L = min(s.y1, s.y2);
        int R = max(s.y1, s.y2);
        intervals_y.push_back({L, R});
    }
    ans = max(ans, maxoverlap(intervals_y));
    // 处理z方向
    vector<pair<int, int>> intervals_z;
    for (auto &s : segs)
    {
        int L = min(s.z1, s.z2);
        int R = max(s.z1, s.z2);
        intervals_z.push_back({L, R});
    }
    ans = max(ans, maxoverlap(intervals_z));
    cout << ans << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}