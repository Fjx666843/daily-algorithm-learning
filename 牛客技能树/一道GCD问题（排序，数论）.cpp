​ // 题目链接：https://www.nowcoder.com/practice/4bd77fafb14847b58ec78c8c1198b1d9?channelPut=tracker3

    // 题目大意：

    // 我们有一个数组 a1,a2,...,an，给每个数都加上同一个非负整数 k，得到新数组：

    // a1+k, a2+k, ..., an+k

    // 我们想让这个新数组的最大公约数（gcd）尽可能大，并求出对应的最小的 k。

    // 题目思路：

    // 数组统一加 k 后，任意两数之差不变，所以最大公约数 g 必须整除所有原始差值；排序后取相邻差值的最大公约数即为 gmax​，再选择数组任意元素加上 k 成为 g 的倍数，最小的 k就是 (g−a0 mod g) mod g。

    // 代码如下：

​#include<bits / stdc++.h> using namespace std;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);
    int g = 0;
    for (int i = 1; i < n; i++)
    {
        g = gcd(g, a[i] - a[i - 1]);
    }
    int k = (g - a[1] % g) % g;
    cout << g << " " << k << endl;
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    // cin>>T;
    while (T--)
    {
        solve();
    }
    return 0;
}
