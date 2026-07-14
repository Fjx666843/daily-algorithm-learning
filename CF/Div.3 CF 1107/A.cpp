​ // 题目链接：https://codeforces.com/contest/2241/problem/A

// 题目大意：给定两个正整数x，y，可以进行以下操作任意次：

// 选定一个正整数z,并且x%z==0，使得x=x/z

// 现在要求我们判断x是否可以变为y

// 题目思路：可以知道如果y>x,那么x永远不能变为y，如果x>=y,我们只需要看x%y==0是否成立，如果成立说明可以，否则不可以，因为如果x可以被y整除，那么就说明y是x的因子，也就是x/y也是因子，那么符合上述操作条件

// 代码如下：

#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl "\n"

void solve()
{
    int x, y;
    cin >> x >> y;
    if (x < y)
    {
        cout << "No" << endl;
        return;
    }
    if (x % y == 0)
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