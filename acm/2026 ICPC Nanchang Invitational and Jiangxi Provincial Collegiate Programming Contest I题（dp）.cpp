// ​
// 题目链接：
// Problem - I - Codeforces
// https://codeforces.com/gym/106551/problem/I

// 题目大意：你有4个蛋，它们叠成一个塔，从下到上分别叫 A、B、C、D（D在最顶上）。
// 这个塔站在一条长度为 l 的轨道上，轨道从坐标 0 到坐标 l，分成 l 段，每段有不同的地形。
// 每走一段（从 x 到 x+1），要花时间，时间由那段地形决定：

// 平地：t0 秒

// 泥坑：t1 秒

// 加速垫：t2 秒




// 你可以做两种操作

// 正常往前走一步
// 整个塔一起从 x 走到 x+1，花费对应地形的时间。

// 超级扔蛋（只能用于高度 ≥ 2 的塔）

// 最底下的那个蛋（比如一开始的 A）留在原地消失。

// 它上面的所有蛋（比如 B、C、D）一次性飞到前面 d 距离处（但不能超过终点 l）。

// 这个操作不花时间（0秒），而且飞过去的蛋仍然保持原来的上下顺序。




// 目标
// 让最顶上的蛋 D 到达终点坐标 l，问最少需要多少秒。

// 题目思路：这是一道最短路径问题但由于状态转移具有单向性（位置只增不减），可以转化为DAG上的动态规划。定义dp状态 dp[j][x] 表示：在位置x，塔的高度为j（有j个蛋）时的最短时间，其中dp[4][0] = 0;接着按照位置从小到达进行状态转移即可，转移分2种，一是正常前行，二是超级起步，最后遍历到达l后每种蛋的剩余数的dp[j][l]即可找到最小值

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;
#define int long long
#define endl "\n"
const int INF = (1LL << 62);

void solve()
{
    int l, d;
    cin >> l >> d;
    int t0, t1, t2;
    cin >> t0 >> t1 >> t2;
    string S;
    cin >> S;

    // cost[i] 对应第i段 (0-index)，从坐标i到i+1的代价
    vector<int> cost(l);
    for (int i = 0; i < l; ++i)
    {
        if (S[i] == '0')
            cost[i] = t0;
        else if (S[i] == '1')
            cost[i] = t1;
        else
            cost[i] = t2;
    }

    // dp[j][x] 表示：在位置x，塔的高度为j（有j个蛋）时的最短时间
    // j: 1..4, x: 0..l
    vector<vector<int>> dp(5, vector<int>(l + 1, INF));
    dp[4][0] = 0; // 初始状态：4个蛋在位置0

    // 按位置从小到大遍历
    // 因为所有转移都是向前（x增加或不变），所以这是拓扑序
    for (int x = 0; x < l; ++x)
    {
        for (int j = 1; j <= 4; ++j)
        {
            if (dp[j][x] == INF)
                continue;

            // 转移1: 正常前进（整个塔一起走一步）
            // 从x走到x+1，代价由地形决定
            dp[j][x + 1] = min(dp[j][x + 1], dp[j][x] + cost[x]);
            // 转移2: 超级起步（扔蛋）
            // 条件：至少2个蛋才能扔
            // 最下面的蛋留在原地消失，上面的j-1个蛋飞到min(l, x+d)
            // 代价为0
            if (j >= 2)
            {
                dp[j - 1][min(l, x + d)] = min(dp[j - 1][min(l, x + d)], dp[j][x]);
            }
        }
    }

    // 答案：到达位置l时，任意高度都可以
    // 因为只要最顶端的蛋D到达l就算成功
    int ans = INF;
    for (int j = 1; j <= 4; ++j)
        ans = min(ans, dp[j][l]);

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