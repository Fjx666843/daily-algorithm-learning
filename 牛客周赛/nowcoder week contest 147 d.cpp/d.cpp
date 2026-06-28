// 题目链接：https : // ac.nowcoder.com/acm/contest/136224/D
// 题目大意：定义一个数组b是好的，当且仅当b[i] 是b[i - 1] 的倍数，且b[i] /
// b[i - 1] 是质数，特殊的，长度为1的数组都是好的，现在给定一个长为n的数组a，找到一个a的最长子序列，满足是好的
// 题目思路：本题本质上还是LIS问题，不过我们需要维护b[i] 是b[i - 1] 的倍数，且b[i] /
// b[i - 1] 是质数，那么可以通过欧拉筛和质因数分解来解决，同时还多了一个int pre[MAXN],
// 也就是表示以数值v结尾的最长合法子序列的前一个数值，以及int pos[MAXN]，也就是每个值对应的下标
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

// ============ 全局数组 ============
int a[200005];        // 存储原数组，n最大2e5
int dp_pos[MAXN];     // dp_pos[i]: 位置 i 的前一个位置（用于回溯）
int dp_max[MAXN];     // dp_max[i]: 以位置 i 结尾的最长合法子序列长度
bool not_prime[MAXN]; // not_prime[i] = true 表示 i 不是质数（合数）
int pos[MAXN];        // pos[v]: 数值 v 在原数组中最后一次出现的位置
int p[MAXN];          // p数组用来存储所有质数
int sum = 0;          // sum统计质数个数

// ============ 欧拉筛（线性筛）预处理 1e6 以内的所有质数 ============
void shai()
{
    int n = 1000005;
    not_prime[1] = 1; // 1 不是质数，标记为 1

    for (int i = 2; i <= n; i++)
    {
        // 如果 i 是质数（not_prime[i] == 0），加入质数表
        if (not_prime[i] == 0)
        {
            sum++;
            p[sum] = i;
        }

        // 用当前 i 乘以所有已找到的质数，标记合数
        for (int j = 1; j <= sum; j++)
        {
            int x = i * p[j];
            if (x > n)
                break;        // 超出范围，停止
            not_prime[x] = 1; // 标记 x 为合数

            // 核心：保证每个合数只被其最小质因子标记一次
            // 如果 i 能被 p[j] 整除，说明 p[j] 是 i 的最小质因子
            // 再往后乘就不是最小质因子了，直接 break
            if (i % p[j] == 0)
                break;
        }
    }
}

// ============ 获取 n 的所有质因子（去重） ============
// 注意：这个函数找的是质因子，不是非质数因子
// 例如：anti_prime(12) -> {2, 3}
// 因为题目要求：b[i] = b[i-1] * 质数
// 所以从 x 往前推：y = x / 质数，这个质数就是 x 的质因子
vector<int> anti_prime(int n)
{
    vector<int> vec;

    // 如果 n 不是质数（是合数），说明它有质因子
    // 但这里用 !not_prime[n] 判断是质数才加入 1
    // 实际上这里应该是找质因子，代码逻辑可能有点问题
    // 正确的应该是：枚举质数表，判断是否能整除 n
    if (!not_prime[n])    // 如果 n 是质数
        vec.push_back(1); // 质数只能从 1 转移（1 × 质数 = n）

    // 枚举所有因子，找质因子
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i != 0)
            continue; // i 不是因子，跳过

        // 如果 i 是质数，那么 n/i 是前一个数（n = (n/i) × i）
        if (!not_prime[i])
            vec.push_back(n / i);

        if (i * i == n)
            continue; // 避免重复添加平方根

        // 如果 n/i 是质数，那么 i 是前一个数（n = i × (n/i)）
        if (!not_prime[n / i])
            vec.push_back(i);
    }
    return vec;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 1. 预处理质数
    shai();

    // 2. 读入数据
    int n;
    cin >> n; // 读取数组长度
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i]; // 读取第 i 个数

        // 3. 初始化 DP
        pos[a[i]] = i;  // 记录数值 a[i] 的最新位置
        dp_max[i] = 1;  // 每个位置至少可以构成长度为 1 的子序列
        dp_pos[i] = -1; // -1 表示没有前驱

        // 4. 尝试从 a[i] 的质因子转移
        vector<int> vec = anti_prime(a[i]);
        for (int j : vec) // j 是前一个可能的数值
        {
            if (pos[j] == 0)
                continue; // j 还没出现过，跳过

            // 如果从 pos[j] 转移过来能得到更长的长度
            if ((dp_max[pos[j]] + 1) > dp_max[i])
            {
                dp_max[i] = (dp_max[pos[j]] + 1); // 更新长度
                dp_pos[i] = pos[j];               // 记录前一个位置
            }
        }
    }

    // 5. 找到最长子序列的末尾位置
    int maxn = 1, anspos = 1;
    for (int i = 1; i <= n; i++)
    {
        if (dp_max[i] > maxn)
        {
            maxn = dp_max[i];
            anspos = i;
        }
    }

    // 6. 回溯构造答案
    vector<int> res;
    while (anspos != -1)
    {
        res.push_back(a[anspos]); // 将当前数值加入答案
        anspos = dp_pos[anspos];  // 跳到前一个位置
    }

    // 7. 反转并输出（因为回溯是从后往前的）
    reverse(res.begin(), res.end());
    cout << maxn << "\n";
    for (int i : res)
        cout << i << " ";

    return 0;
}