// ​
// 题目链接：https://codeforces.com/contest/2254/problem/C2

// 题目大意：给定a,b两个01字符串，可以执行以下任意操作：

// 在a中选择字串001变100，或者100变001

// 在a中选择字串110变011，或者011变110

// 求出a变b的最小操作次数，否则输出-1

// 题目思路：由题意可知道，不管如何操作，任意一个1的位置的奇偶性不变，那么我们只需要分别统计和记录a，b字符串中1的奇数位和偶数位的数量和位置，如果odd_A != odd_B || even_A != even_B则输出-1，否则贪心统计ans（即从0到A_odd.size()）。

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    string a, b;
    cin >> n >> a >> b;

    vector<int> A_odd, B_odd, A_even, B_even;
    int odd_A = 0, even_A = 0;
    int odd_B = 0, even_B = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == '1')
        {
            if (i & 1)
            {
                odd_A++;
                A_odd.push_back(i);
            }
            else
            {
                even_A++;
                A_even.push_back(i);
            }
        }
        if (b[i] == '1')
        {
            if (i & 1)
            {
                odd_B++;
                B_odd.push_back(i);
            }
            else
            {
                even_B++;
                B_even.push_back(i);
            }
        }
    }

    // 可行性检查
    if (odd_A != odd_B || even_A != even_B)
    {
        cout << -1 << endl;
        return;
    }
    int ans = 0;
    for (int i = 0; i < A_odd.size(); i++)
    {
        ans += (abs(B_odd[i] - A_odd[i]) / 2);
    }
    for (int i = 0; i < A_even.size(); i++)
    {
        ans += (abs(B_even[i] - A_even[i]) / 2);
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