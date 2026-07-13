//题目链接：https : // codeforces.com/contest/2242/problem/A

// 题目大意：定义字符串中的双字符是指一对相邻的字符，现在Monocarp有若干带有不同字母的卡牌，他想通过这些卡牌组成一个字符串，并且每一张卡牌只能用一次，最终组成的字符串必须至少包含两个相等的双字符，现在要我们判断是否可以组成合法字符串

// 题目思路：我们很容易可以想到，如果每一种字符的卡牌有3张以上，那么一定可以组成合法的字符串，如aaa，aa和aa符合条件，其次只要有两种字符的卡牌有2张以上也可以满足条件，如abab其中ab和ab符合条件，其余情况一定不满足情况。

//代码如下：

#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl "\n"

void solve()
{
    int k;
    cin >> k;
    int c[k + 1];
    int flag = 0;
    int cnt = 0;
    for (int i = 1; i <= k; i++)
    {
        cin >> c[i];
        if (c[i] >= 3)
        {
            flag = 1;
        }
        if (c[i] >= 2)
        {
            cnt++;
        }
    }
    if (flag || cnt >= 2)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
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