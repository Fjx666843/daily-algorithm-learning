// 题目链接：https : // ac.nowcoder.com/acm/contest/136224/E

// 题目大意：定义一个受欢迎的字符串，当且仅当该字符串同时包含 greetgreet 和 inviteinvite 两个

// 字串，现在给定一个字符串s，可以进行以下操作任意次：

// ∙ 在字符串的任意一个位置插入任意一个小写字母。

// 现在要求我们计算出最少操作多少次可以使得s变得受欢迎。

// 题目思路：最终字符串必须同时包含 "greet" 和 "invite" 两个子串。由于只能插入字符，不能删除，所以原串中的字符可以被保留作为这两个目标串的一部分，且这两个目标串在最终串中互不重叠（因为二者没有公共子序列重叠的可能）。因此，我们只需要在原串中选取两个不相交的连续子串：一个作为 "greet" 的子序列，另一个作为 "invite" 的子序列。若这两个连续子串的总长度为 L，则最少插入次数为(5 + 6)−L = 11−L 问题转化为最大化可保留的字符总数。
#include <bits/stdc++.h>
using namespace std;

/**
 * 计算前缀数组 pref
 * pref[i] 表示原字符串 s 的前缀 s[0..i-1] 中，能够匹配模式串 pat 的连续子串的最大长度
 * 即：找到一个连续子串 s[l..r] (r < i)，使得该子串是 pat 的子序列，最大化 r-l+1
 */
vector<int> compute_pref(const string &s, const string &pat)
{
    int n = s.size();
    int m = pat.size();
    // end_max[r] 表示以位置 r 结尾的连续子串中，能够匹配 pat 的最大长度
    vector<int> end_max(n, 0);

    // 枚举所有连续子串 s[l..r]
    for (int l = 0; l < n; ++l)
    {
        // 长度最多为 m（因为超过 m 不可能成为 pat 的子序列）
        int max_len = min(m, n - l);
        for (int len = 1; len <= max_len; ++len)
        {
            int r = l + len - 1;
            // 检查 s[l..r] 是否是 pat 的子序列
            int p = 0; // pat 的指针
            for (int k = l; k <= r; ++k)
            {
                // 在 pat 中寻找当前字符
                while (p < m && pat[p] != s[k])
                    ++p;
                if (p == m)
                { // 无法匹配
                    p = -1;
                    break;
                }
                ++p; // 匹配成功，移动 pat 指针
            }
            if (p != -1)
            { // 匹配成功
                end_max[r] = max(end_max[r], len);
            }
        }
    }

    // 前缀最大值
    vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        pref[i] = max(pref[i - 1], end_max[i - 1]);
    }
    return pref;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    string greet = "greet";
    string invite = "invite";

    // 计算原串关于 greet 和 invite 的前缀最大匹配长度
    auto pref_greet = compute_pref(s, greet);
    auto pref_invite = compute_pref(s, invite);

    // 为了计算后缀最大匹配长度，将原串和模式串都反转
    // 原串的后缀 s[i..n-1] 反转后对应反转串的前缀 rs[0..n-i-1]
    string rs = s;
    reverse(rs.begin(), rs.end());

    string rg = greet;
    reverse(rg.begin(), rg.end()); // "teerg"
    string ri = invite;
    reverse(ri.begin(), ri.end()); // "etivni"

    auto pref_rg = compute_pref(rs, rg);
    auto pref_ri = compute_pref(rs, ri);

    // 根据反转串的 pref 构建原串的后缀数组 suff[i]
    // suff[i] 表示原串后缀 s[i..n-1] 中，能匹配 pat 的最大连续段长度
    vector<int> suff_greet(n + 1, 0), suff_invite(n + 1, 0);
    for (int i = 0; i <= n; ++i)
    {
        // rs 的前缀长度为 n-i，对应原串的后缀起始位置 i
        suff_greet[i] = pref_rg[n - i];
        suff_invite[i] = pref_ri[n - i];
    }

    int best = 0; // 两个连续段的最大总长度
    // 枚举分割点 i，左边是前缀 [0..i-1]，右边是后缀 [i..n-1]
    for (int i = 0; i <= n; ++i)
    {
        // 情况1：greet 在左边，invite 在右边
        best = max(best, pref_greet[i] + suff_invite[i]);
        // 情况2：invite 在左边，greet 在右边
        best = max(best, pref_invite[i] + suff_greet[i]);
    }

    // 最少插入次数 = 目标串总长度(5+6) - 最大可利用的字符数
    cout << 11 - best << '\n';
    return 0;
}
