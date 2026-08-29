// ​
// 题目链接：Who Can Win - 题目 - QOJ.ac

// 题目大意：

// ICPC 比赛中，记分牌在最后一小时冻结，冻结期间（时间 ≥ 240 分钟）的提交结果统一显示为 Unknown，它们实际上既可能是 Accepted，也可能是 Rejected。

// 现在给出若干场比赛的提交记录，每条记录包含：

// 队伍名
// 题号（A–Z）
// 提交时间（0–299）
// 结果（Accepted / Rejected / Unknown）
// 规则：

// 队伍分数由 解题数 决定，解题数相同再比较 罚时。
// 罚时 = 每个已解决题目的第一次 Accepted 时间，加上该题之前所有 Rejected 次数 × 20 分钟。
// 冠军是解题数最多、且在这些队伍中罚时最小的队伍；允许并列。
// 要求： 对每一场比赛，在所有 Unknown 提交可以被任意替换为 Accepted 或 Rejected 的情况下，判断哪些队伍有可能成为冠军，并按字典序输出这些队伍的名字。

// 题目思路：先对每个队伍进行预处理，然后统计其他队伍的基础成绩，接着贪心判断每个队伍是否可能夺冠：

// 不需要枚举所有 Unknown 的替换方案。只需要考虑一个对 i 最有利、对其他队伍最不利的场景：

// 把 i 的所有 Unknown 尽量设为 Accepted；
// 把其他队伍的所有 Unknown 都设为 Rejected。
// 如果在这个场景下 i 都不能夺冠，那么其他场景中其他队伍只会更强，i 更不可能夺冠。

// ，最后按字典序排序输出即可

// 代码如下：

//
#include <bits/stdc++.h>
using namespace std;
// using i128 = __int128;
// #define int long long
#define endl "\n"
// 存储一条提交记录
struct Submission
{
    int time; // 提交时间
    int prob; // 提交编号
    int type; // 0: Accepted, 1: Rejected, 2: Unknown
};
void solve()
{
    int s;
    cin >> s;
    // 队伍名称到编号的映射，编号从 0 开始
    unordered_map<string, int> id;
    id.reserve(s * 2);
    vector<string> names;            // 编号对应的队伍名称
    vector<vector<Submission>> subs; // 每个队伍的所有提交
    names.reserve(s);
    subs.reserve(s);
    // 读取所有提交并分配队伍编号
    // 读取所有提交记录，构建每个队伍的提交列表
    for (int i = 0; i < s; ++i)
    {
        string team, res;
        char prob;
        int time;

        // 读取一条提交：队伍名、题目、提交时间、结果
        cin >> team >> prob >> time >> res;

        // 根据队伍名获取其编号，若不存在则分配新编号
        int idx;
        auto it = id.find(team);
        if (it == id.end())
        {
            // 新队伍：编号为当前队伍数量
            idx = (int)names.size();
            id[team] = idx;        // 建立队伍名 → 编号 的映射
            names.push_back(team); // 保存队伍名
            subs.emplace_back();   // 为该队伍创建一个空的提交列表
        }
        else
        {
            // 已有编号，直接使用
            idx = it->second;
        }

        // 将结果字符串转换为枚举类型，便于后续处理
        // 0 表示 Accepted，1 表示 Rejected，2 表示 Unknown
        int type;
        if (res == "Accepted")
            type = 0;
        else if (res == "Rejected")
            type = 1;
        else
            type = 2;

        // 将这条提交加入对应队伍的列表中
        // 题目编号由字母转换为 0~25（A→0，B→1，……，Z→25）
        subs[idx].push_back({time, prob - 'A', type});
    }
    int n = (int)names.size(); // 队伍总数
    // baseSolved: 已知 Accepted 解决的题目数
    // basePenalty: 已知解决的题目的罚时总和
    // extraCnt: 未知提交最多还能额外解决的题目数（每个题最多算一个）
    // extraSum: 将这些额外题目全部按最优方式（第一个 Unknown 设为 Accepted）解决时，额外增加的罚时总和
    vector<int> baseSolved(n), basePenalty(n), extraCnt(n), extraSum(n);
    // 对每个队伍处理其提交
    for (int i = 0; i < n; ++i)
    {
        // 按时间从小到大排序
        sort(subs[i].begin(), subs[i].end(),
             [](const Submission &a, const Submission &b)
             {
                 return a.time < b.time;
             });
        bool accepted[26] = {};      // 该题是否已被 Accepted
        bool hasUnknown[26] = {};    // 该题是否已出现第一个 Unknown 提交
        int pendingRejects[26] = {}; // 该题在未 Accepted 之前累计的 Rejected 数
        int solved = 0;              // 已知解决的题数
        int penalty = 0;             // 已知解决的罚时
        int unknownCnt = 0;          // 额外可解决题数
        int unknownSum = 0;          // 额外罚时总和
        for (const Submission &sub : subs[i])
        {
            int p = sub.prob;
            if (sub.type == 1)
            {
                // Rejected：如果该题尚未 Accepted，则累加到待计算的 Rejected 数
                if (!accepted[p])
                {
                    pendingRejects[p]++;
                }
            }
            else if (sub.type == 0)
            {
                // Accepted：如果该题之前未 Accepted，则记录解决并计算罚时
                if (!accepted[p])
                {
                    accepted[p] = true;
                    solved++;
                    penalty += sub.time + 20 * pendingRejects[p];
                }
            }
            else
            {
                // Unknown：只考虑每个题的第一个 Unknown（若该题未 Accepted 且之前没有 Unknown）
                if (!accepted[p] && !hasUnknown[p])
                {
                    hasUnknown[p] = true;
                    unknownCnt++;
                    // 假设将此 Unknown 设为 Accepted，增加的罚时 = 该 Unknown 的时间 + 已知 Rejected 的罚时
                    unknownSum += sub.time + 20 * pendingRejects[p];
                }
            }
        }
        baseSolved[i] = solved;
        basePenalty[i] = penalty;
        extraCnt[i] = unknownCnt;
        extraSum[i] = unknownSum;
    }
    // 找出基础题数的最大值 max1、次大值 max2 以及最大值的出现次数
    int max1 = -1, max2 = -1, cntMax1 = 0;
    for (int i = 0; i < n; ++i)
    {
        int b = baseSolved[i];
        if (b > max1)
        {
            max2 = max1;
            max1 = b;
            cntMax1 = 1;
        }
        else if (b == max1)
        {
            cntMax1++;
        }
        else if (b > max2)
        {
            max2 = b;
        }
    }
    const int INF = 1e9;
    // val1[题数]：该题数下的最小基础罚时
    // idx1[题数]：达到该最小罚时的队伍编号
    // val2[题数]：该题数下的次小基础罚时
    // idx2[题数]：达到该次小罚时的队伍编号
    vector<int> val1(27, INF), val2(27, INF);
    vector<int> idx1(27, -1), idx2(27, -1);
    for (int i = 0; i < n; ++i)
    {
        int b = baseSolved[i], p = basePenalty[i];
        // 更新最小和次小罚时
        if (p < val1[b])
        {
            val2[b] = val1[b];
            idx2[b] = idx1[b];
            val1[b] = p;
            idx1[b] = i;
        }
        else if (p < val2[b])
        {
            val2[b] = p;
            idx2[b] = i;
        }
    }
    vector<string> champions;
    // 判断每个队伍是否可能成为冠军
    for (int i = 0; i < n; ++i)
    {
        if (n == 1)
        {
            champions.push_back(names[i]);
            continue;
        }
        // M：其他队伍最终可能达到的最大题数
        // 如果当前队伍的基础题数已经是全局最大且唯一，则其他队伍最多只能达到次大
        // 否则其他队伍可以达到最大
        int M;
        if (baseSolved[i] == max1 && cntMax1 == 1)
        {
            M = max2;
        }
        else
        {
            M = max1;
        }
        if (M == -1)
        {
            // 没有其他队伍能达到任何题数
            champions.push_back(names[i]);
            continue;
        }
        // 若当前队伍通过所有额外的 Unknown 提交后，题数超过 M，则一定可以成为冠军
        if (baseSolved[i] + extraCnt[i] > M)
        {
            champions.push_back(names[i]);
        }
        // 若题数恰好等于 M，则需要比较罚时
        else if (baseSolved[i] + extraCnt[i] == M)
        {
            // 找出其他队伍达到 M 题时的最小基础罚时（排除自己）
            int bestOtherPenalty = (idx1[M] != i ? val1[M] : val2[M]);
            // 当前队伍达到 M 题的最小罚时 = 基础罚时 + 额外罚时
            int minPenalty = basePenalty[i] + extraSum[i];
            // 如果当前队伍的最小罚时不超过其他队伍的最小罚时，则可以成为冠军（可并列）
            if (minPenalty <= bestOtherPenalty)
            {
                champions.push_back(names[i]);
            }
        }
        // 若题数小于 M，则不可能成为冠军
    }
    // 按字典序排序
    sort(champions.begin(), champions.end());
    // 输出
    for (int i = 0; i < (int)champions.size(); ++i)
    {
        if (i)
            cout << ' ';
        cout << champions[i];
    }
    cout << '\n';
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