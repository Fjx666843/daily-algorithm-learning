// ​
// 题目链接：B-冰碧帝皇蝎·冰帝之螯_河南萌新联赛2026第（五）场：信息工程大学

// 题目大意：在给定的初始原料下，通过反复使用若干种“配方”（每种配方消耗固定原料、生成1个构件），判断能否将原料全部恰好用完，并求出能生产的最少构件数。

// 题目思路：枚举所有配方的使用次数组

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;

#define int long long // 将 int 定义为 long long，防止整数溢出
#define endl "\n"     // 使用 \n 代替 endl，提高输出效率

int n, m;                   // n: 原料种类数, m: 配方种类数
vector<int> init;           // init[i]: 第 i 种原料的初始数量
vector<vector<int>> recipe; // recipe[i][j]: 第 i 个配方消耗第 j 种原料的数量
int ans = INT_MAX;          // 记录最小构件数，初始化为最大值

/*
 * DFS 枚举所有配方的使用次数组合
 * idx: 当前考虑第几个配方（0 ~ m-1）
 * remaining: 当前剩余的各种原料数量
 * total: 目前已生产的构件总数
 */
void dfs(int idx, vector<int> remaining, int total)
{
    // 剪枝：如果当前总构件数已经 >= 已知最优解，不必继续搜索
    if (total >= ans)
    {
        return;
    }

    // 所有配方都考虑完了
    if (idx == m)
    {
        // 检查是否所有原料都恰好用完
        bool allzero = true;
        for (int x : remaining)
        {
            if (x != 0)
            {
                allzero = false;
                break;
            }
        }
        // 如果恰好用完，更新最小构件数
        if (allzero)
        {
            ans = min(ans, total);
        }
        return;
    }

    /*
     * 计算当前配方最多能使用几次
     * 对于每种原料 j，如果该配方需要消耗 recipe[idx][j] 个，
     * 则最多能用 remaining[j] / recipe[idx][j] 次
     * 取所有原料限制的最小值，就是该配方的最大使用次数
     */
    int maxuse = INT_MAX;
    for (int j = 0; j < n; j++)
    {
        if (recipe[idx][j] > 0)
        {
            maxuse = min(maxuse, remaining[j] / recipe[idx][j]);
        }
    }

    // 健壮性处理：如果配方不消耗任何原料（理论上不会发生），直接跳过
    if (maxuse == INT_MAX)
    {
        dfs(idx + 1, remaining, total);
        return;
    }

    /*
     * 枚举当前配方的使用次数 k
     * k 从 0 到 maxuse，表示当前配方用 0 次、1 次、...、maxuse 次
     */
    for (int k = 0; k <= maxuse; k++)
    {
        // 复制一份当前剩余原料状态
        vector<int> newremaining = remaining;

        // 减去使用 k 次配方消耗的原料
        for (int j = 0; j < n; j++)
        {
            newremaining[j] -= k * recipe[idx][j];
        }

        // 递归到下一个配方，总构件数增加 k
        dfs(idx + 1, newremaining, total + k);
    }
}

void solve()
{
    // 读入原料种类数和配方种类数
    cin >> n >> m;

    // 初始化原料数组
    init.resize(n);
    unordered_map<string, int> id; // 原料名称 → 索引 的映射

    // 读入每种原料的名称和初始数量
    for (int i = 0; i < n; i++)
    {
        string name;
        int cnt;
        cin >> name >> cnt;
        id[name] = i;  // 建立名称到索引的映射
        init[i] = cnt; // 记录初始数量
    }

    // 初始化配方数组，recipe[i] 是长度为 n 的向量，初始全为 0
    recipe.resize(m, vector<int>(n, 0));

    // 读入每个配方的消耗
    for (int i = 0; i < m; i++)
    {
        int t; // 该配方需要多少种不同的原料
        cin >> t;
        for (int j = 0; j < t; j++)
        {
            string name;
            int cnt;
            cin >> name >> cnt;
            recipe[i][id[name]] = cnt; // 根据原料名称找到对应的列索引
        }
    }

    // 重置全局答案
    ans = INT_MAX;

    // 从第 0 个配方开始 DFS，初始剩余原料为 init，当前总构件数为 0
    dfs(0, init, 0);

    // 如果 ans 仍是 INT_MAX，说明没有找到可行方案
    if (ans == INT_MAX)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << ans << endl;
    }
}

signed main()
{
    // 输入输出优化，加速 cin/cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;  // 如果有多组测试数据，取消注释
    while (T--)
    {
        solve();
    }
    return 0;
}