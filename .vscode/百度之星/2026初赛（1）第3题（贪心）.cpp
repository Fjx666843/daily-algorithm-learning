// 题目大意：给定一个a数组，其中-1表示票数未知，总票为n，求出最高票数的同学的可能编号(恰好只有1位)

// 题目思路：我们先求出已知ma以及已知已知sum和，然后求出未知可用票数d=n-sum,如果d<=ma,那么毋庸置疑，最大票数只能是ma，如果d>ma,那么最大票数可能在已知最大中，也可能在未知中，对于未知数组中，我们可以让一人获得d票，其余人全0票，那么每个位置都可能是ans，接下来我们要考虑ans是否在已知ma中，那么我们可以最小化未知最大值，也就x=（d+unknow_cnt-1)/unknown_cnt,如果x>ma，说明x就是全局最大值，ma不计入ans，如果x=ma,此时会出现至少两个最大值，也不计入，如果x<ma,此时如果ma的数量=1，才计入ans

// 代码如下：
// ————————————————
// 版权声明：本文为CSDN博主「吞下星星的少年·-·」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/2501_94316951/article/details/164004915
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    int a[n + 1];
    int ma = 0;
    int pos = 0;
    int sum = 0;
    int unknow_cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (a[i] != -1)
        {
            sum += a[i];
        }
        else
        {
            unknow_cnt++;
        }
        if (a[i] >= ma)
        {
            ma = a[i];
            pos = i;
        }
    }
    int ma_cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] == ma)
        {
            ma_cnt++;
        }
    }
    int d = n - sum;
    if (d > ma)
    {
        int x = (d + unknow_cnt - 1) / unknow_cnt;
        if (x < ma && ma_cnt == 1)
        {
            for (int i = 1; i <= n; i++)
            {
                if (a[i] == -1)
                {
                    if (pos < i)
                    {
                        cout << pos << " " << i << " ";
                    }
                    else
                    {
                        cout << i << " ";
                    }
                }
            }
        }
        else
        {
            for (int i = 1; i <= n; i++)
            {
                if (a[i] == -1)
                {
                    cout << i << " ";
                }
            }
        }
    }
    else
    {
        cout << pos << endl;
    }
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