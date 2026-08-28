// ​
// 题目链接：B-Flower_Rainbow_and_Victory_牛客练习赛156

// 题目大意：给定n张牌和字符串s，t，对于第i张牌的数字是s[i],花色是t[i],数字为 0的卡牌与花色为 B的卡牌对 Rainbow「有效」，数字为 1 的卡牌与花色为 R 的卡牌对 Flower「有效」。
// 游戏开始时，两人手里都没有卡牌。Rainbow 先手，两人轮流从牌堆中任意选择一张牌放到自己手中，当牌堆上的 n张卡牌被全部挑完后，游戏结束。两人分别统计自己手中对自己「有效」的卡牌的数量，数量多的一方获胜；若数量相等，则为平局。
// Rainbow 和 Flower 都绝顶聪明，都使用最优策略进行游戏，请你判断游戏的结果。

// 题目思路：根据已知推结果

// 可以将牌分为三种类型：

// 1.数字为0花色为B

// 2.数字为1花色为R

// 3.数字为0花色为R和数字为1花色为B

// 对于每一回合玩家的最优决策优先级如下：

// 1.获取类型3的牌

// 2.获取自己的专属牌

// 3.获取对方的专属牌

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
// using i128 = __int128;
// #define int long long
#define endl "\n"

void solve()
{
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    int cnt0B = 0, cnt1R = 0, both = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0' && t[i] == 'B')
        {
            cnt0B++;
        }
        else if (s[i] == '1' && t[i] == 'R')
        {
            cnt1R++;
        }
        else
        {
            both++;
        }
    }
    int Rainbow_Score = 0, Flower_Score = 0;
    for (int i = 0; i < n; i++)
    {
        if (i & 1)
        {
            if (both)
            {
                Flower_Score++;
                both--;
            }
            else if (cnt1R)
            {
                Flower_Score++;
                cnt1R--;
            }
            else if (cnt0B)
            {
                cnt0B--;
            }
        }
        else
        {
            if (both)
            {
                Rainbow_Score++;
                both--;
            }
            else if (cnt0B)
            {
                Rainbow_Score++;
                cnt0B--;
            }
            else if (cnt1R)
            {
                cnt1R--;
            }
        }
    }
    if (Rainbow_Score > Flower_Score)
    {
        cout << "Rainbow" << endl;
    }
    else if (Rainbow_Score < Flower_Score)
    {
        cout << "Flower" << endl;
    }
    else
    {
        cout << "Draw" << endl;
    }
}

int main()
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