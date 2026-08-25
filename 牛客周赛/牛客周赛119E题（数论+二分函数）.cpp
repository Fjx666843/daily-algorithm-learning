​
// 题目链接：E-小苯的三角计数_牛客周赛 Round 119

// 题目大意：有n 种木棍，其中第 i 种木棍的长度为 a[i]，有 b[i]根，他希望从中取出三根不同的木棍组成三角形，请问他可以组成多少种本质不同的非退化三角形。
// 【非退化三角形】即满足：任意两边长之和大于第三边。
// 【本质不同】我们认为两个三角形本质不同，当且仅当它们不是全等的。

// 题目思路：对于这道题来说，我们可以这样思考，对于每种长度的木棍的根数考虑情况应该是cnt=min(3,b[i]),因为一个非退化三角形最多只能使用3根，接下来我们对于某种长度的木棍的根数进行考虑：

// 如果是b[i]>=3,那么当使用3根木棍时，那么它就是一个等边三角形，ans++；

// 如果使用2根木棍时（等腰三角形），那么我们已知两条边，找第三条边，也就是a[i]+a[j]>a[k](a[i]==a[j])->2*a[i]-1>=a[k],用人话说就是a[k]小于一个固定的值，那么我们对a数组排序后，进行二分查找该值即可，具体的我们通过枚举每个a[i],对于每个a[i]用lower_bound函数查找a[k],但是最终ans需要减1，因为小于等于2*a[i]-1的数中，必然有a[i]，该值如果计入答案就相同于上面那种情况了

// 如果使用1根木棍（也就是一般三角形），我们就要枚举a[i],a[j]两种长度不同（其中a[i]<a[j])的木棍了，由于n的范围只有2000，那么O(n*n)是允许的，然后策略和上面是一样的，但这里最终ans不需减1，因为当a[i]+a[j]>a[k]时，它等价于一个更简单的必然判断：较短的两边之和必须大于最长的那条边。也就是说a[k]>a[j]>a[i],所以最后ans-j;

// b[i]为2或1时以此类推即可

// 代码如下：

​
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    vector<pair<int, int>> v(n + 1);
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        int a, b;
        cin >> a >> b;
        v[i] = {a, b};
        if (b >= 3)
        { // 等边三角形
            ans++;
        }
        // cout << ans << endl;
    }
    sort(v.begin() + 1, v.end());
    for (int i = 1; i <= n; i++)
    { // 等腰三角形
        pair<int, int> p = v[i];
        int x1 = p.first;
        int x2 = p.second;
        if (x2 >= 2) // 2*a[i]>a[k]
        {
            pair<int, int> t = {x1 * 2, -1};
            int pos = lower_bound(v.begin() + 1, v.end(), t) - v.begin() - 1;
            if (pos < 0)
            {
                continue;
            }
            ans += pos - 1;
        }
        // cout << ans << endl;
    }
    for (int i = 1; i <= n; i++)
    { // 一般三角形
        for (int j = i + 1; j <= n; j++)
        {
            pair<int, int> p1 = v[i];
            pair<int, int> p2 = v[j];
            int x1 = p1.first;
            int x2 = p2.first;
            pair<int, int> t = {x1 + x2, -1};
            int pos = lower_bound(v.begin() + 1, v.end(), t) - v.begin() - 1;
            pos = max(0LL, pos);
            pos = pos - j;
            ans += pos;
        }
    }
    cout << ans << endl;
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