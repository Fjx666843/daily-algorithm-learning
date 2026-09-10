// ​
// 题目链接：Make Max - 题目 - QOJ.ac

// 题目描述：


// 题目思路：

// 操作只会把区间内的数变成区间最大值，因此每个数只会越变越大。

// 核心想法是：对于位置 i，如果把它当成某次操作的“最大值”，它最多能影响左右两边连续比它小的数，直到遇到第一个 大于等于 a[i] 的数为止。相同值的连续段需要去重，只让每段最左边那个位置计算贡献。

// 用单调栈求出：

// L[i]：左边最近的 a[L[i]] >= a[i] 的位置；没有则为边界。
// R[i]：右边最近的 a[R[i]] >= a[i] 的位置；没有则为边界。
// 代码如下：复杂度 O(n)。

// ​
#include <bits/stdc++.h>
using namespace std;
using in128 = __int128_t;
#define int long long

void solve()
{
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    vector<int> l(n, 0), r(n, n - 1);

    // 左边第一个 >= a[i] 的位置
    vector<int> st;
    for (int i = 0; i < n; ++i)
    {
        while (!st.empty() && a[i] > a[st.back()])
        {
            st.pop_back();
        }

        if (!st.empty())
        {
            if (a[i] == a[st.back()])
            {
                // 相同值去重：这一段相等值由最左边的位置计算
                l[i] = i;
            }
            else
            {
                l[i] = st.back() + 1;
            }
        }

        st.push_back(i);
    }

    // 右边第一个 >= a[i] 的位置
    st.clear();
    for (int i = n - 1; i >= 0; --i)
    {
        while (!st.empty() && a[i] > a[st.back()])
        {
            st.pop_back();
        }

        if (!st.empty())
        {
            r[i] = st.back() - 1;
        }

        st.push_back(i);
    }

    long long ans = 0;
    for (int i = 0; i < n; ++i)
    {
        ans += r[i] - l[i];
    }

    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}
