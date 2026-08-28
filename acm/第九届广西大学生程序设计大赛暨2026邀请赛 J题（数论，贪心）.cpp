// ​​
// 题目链接：https://ac.nowcoder.com/acm/contest/136617/J

// 题目大意：

// 给你一个初始数组和一个目标数组，你可以对非最大值+1、对非最小值-1，问能否以及最少几步实现转化。

// 具体来说，你有两个长度均为 N 的整数序列 A（初始）和 B（目标）。你可以对 A 重复执行以下两种操作：



// 每次操作代价为1。你需要判断能否把 A 变成 B，并求出最小操作次数；如果不可能，输出 -1。

// 题目思路：这道题的核心是极值约束下的最小操作数问题。关键在于：最大值不能升、最小值不能降，因此目标极值必须落在初始极值范围内，否则无解。在满足该条件下，每个元素理论上可以独立移动到目标值，总步数为所有 |a[i]-b[i]| 之和。唯一例外是n=2时两个元素恰好要互换（一个从最大值变最小值，另一个从最小值变最大值），会形成死锁；若 n≥3，则可选第三个元素作为“垫子”临时充当前极值来解锁，此时只需在总和上加上该垫子绕路相比直达的最小额外代价。其他所有情况（包括多极值）均可直接输出总和。

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"
const int N = 4e5 + 10;
int n;
int a[N], b[N];
int sum;
void solve()
{
    cin >> n;
    sum = 0;
    // 初始化极值
    int amx = -1e9 - 1, amn = 1e9 + 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        amx = max(amx, a[i]);
        amn = min(amn, a[i]);
    }
    int bmx = -1e9 - 1, bmn = 1e9 + 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> b[i];
        bmx = max(bmx, b[i]);
        bmn = min(bmn, b[i]);
    }
    // 1.可行性判断：目标极值不能超过初始极值范围
    if (amx < bmx || amn > bmn)
    {
        cout << -1 << endl;
        return;
    }
    // 2.强制截断a[i]到[bmn,bmx]范围内，累计基础代价
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > bmx)
        {
            sum += a[i] - bmx;
            a[i] = bmx;
        }
        if (a[i] < bmn)
        {
            sum += bmn - a[i];
            a[i] = bmn;
        }
    }
    // 3.如果目标值全部相同，直接输出（此时所有a[i]已被截断到该值）
    if (bmx == bmn)
    {
        // 但注意：如果目标全相等，sum已经是截断代价，还需要加上到目标值的差值
        // 但截断后a[i]已经等于bmx，所以差值为0，直接输出即可
        cout << sum << endl;
        return;
    }
    // 4.统计互换配对
    int cnt1 = 0, cnt2 = 0;
    int i1 = 0, i2 = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == bmx && b[i] == bmn)
        {
            cnt1++;
            i1 = i;
        }
        if (a[i] == bmn && b[i] == bmx)
        {
            cnt2++;
            i2 = i;
        }
        // 累计每个点从截断后到目标值的代价
        sum += abs(a[i] - b[i]);
    }
    // 5.处理唯一的互换死锁
    if (cnt1 == 1 && cnt2 == 1)
    {
        if (n == 2)
        {
            cout << -1 << endl;
            return;
        }
        // n>=3,找到一个‘垫子’点，计算最小额外代价
        int extra = LLONG_MAX;
        for (int i = 1; i <= n; i++)
        {
            if (i == i1 || i == i2)
            {
                continue;
            }
            // 直达代价
            int direct = abs(a[i] - b[i]);
            // 垫子先走到bmx，再走到自己目标b[i];
            int cost_to_bmx = abs(a[i] - bmx) + abs(bmx - b[i]);
            // 垫子先走到bmN，再走到自己目标b[i];
            int cost_to_bmn = abs(a[i] - bmn) + abs(bmn - b[i]);
            // 额外代价=绕路总代价-直达代价
            int cur_extra = min(cost_to_bmx - direct, cost_to_bmn - direct);
            extra = min(extra, cur_extra);
        }
        // 理论上n>=3一定能找到垫子，extra必定有效
        sum += extra;
        cout << sum << endl;
        return;
    }
    // 6.其他所有情况直接输出即可
    cout << sum << endl;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}