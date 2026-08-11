​
// 题目链接：https://www.matiji.net/exam/brushquestion/81/4777/C98C14523F069FECB0DEED64F00CEAB0

// 题目大意：给定一个字符串s，其中每个字符对应一个分数a[i]，现在可以进行以下操作任意次：

// 选择字符串中的一个子串ab，将该子串删除，剩下的字符按照原来的相对顺序拼接成一个新的字符串。
// 选择字符串中的一个子串ac，将该子串删除，剩下的字符按照原来的相对顺序拼接成一个新的字符串。
// 注意，可以看成初始的每个字符s[i]和对应的分数a[i]​绑定在一起的，不会发生子串被删除之后新的字符串每个字符的分数重新按照a[1]∼a[n]​的顺序重新分配。
// 现在问你，经过任意次操作（可以不操作）之后，所有剩余字符的分数之和的最大值是多少？

// 题目思路：先定义dp状态,dp[i]表示前i个字符经过任意次操作后可以获得的最大分数，并且用栈来维护每个a的位置的入栈与出栈

// 代码如下：

// ​
#include <bits/stdc++.h>
    using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = " " + s;
    int a[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int dp[n + 1] = {0};
    stack<int> stk;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = dp[i - 1] + a[i];
        if (s[i] == 'a')
        {
            stk.push(i);
        }
        else
        {
            if (!stk.empty())
            {
                int pos = stk.top();
                stk.pop();
                dp[i] = max(dp[i], dp[pos - 1]);
            }
        }
    }
    cout << dp[n] << endl;
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
