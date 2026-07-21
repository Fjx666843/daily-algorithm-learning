// 题目链接：https://www.nowcoder.com/practice/34e434465a3b46d29c581fee5d73bc81?channelPut=tracker3

// 题目大意：给定一个排列：1，2，3...n，要求我们对该排列进行k次操作，每次操作给出l，r（区间 [l, r] 的 l 和 r 都是非递减）并对[l,r]进行区间翻转，输出最终排列

// 题目思路：暴力解法很容易想出，但是会超时，所以我们可以使用双端队列 + 翻转标记来做。

// 核心思路是：

// 所有操作区间的左端点和右端点都单调不降，所以每次操作的区间可以看作一个向右滑动的窗口。

// 用双端队列 q 保存当前窗口内的元素。

// 用 rev 标记当前队列是否被整体翻转，这样翻转窗口只需要 rev = !rev，不用真的移动元素。

// 窗口左侧已经确定的部分存入答案数组 ans；右侧还未进入窗口的数字用指针 cur 表示。

// 代码如下：
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define endl "\n"
void solve()
{
    int n, k;
    cin >> n >> k;
    deque<int> q;     // 当前窗口中的元素
    bool rev = false; // true表示q中元素实际是反向存储的
    int L = 1, R = 0; // 当前窗口在数组中的下标范围，初始为空
    int cur = 1;      // 下一个还未进入窗口的原始数字
    vector<int> ans;
    while (k--)
    {
        int l, r;
        cin >> l >> r;
        // 窗口左边界移动到L，左边固定部分弹出到ans
        while (L < l)
        {
            if (L <= R)
            {
                // 窗口非空，根据rev方向弹出对应
                int x;
                if (!rev)
                {
                    x = q.front();
                    q.pop_front();
                }
                else
                {
                    x = q.back();
                    q.pop_back();
                }
                ans.push_back(x);
            }
            else
            {
                // 窗口为空，该位置从未被操作过，原始数字L直接固定
                ans.push_back(L);
                if (cur <= L)
                    cur = L + 1;
            }
            L++;
        }
        // 右边界右移：将新数字纳入窗口
        while (R < r)
        {
            R++;
            if (R >= L)
            {
                // 窗口有效，将下一个元素数字cur加入
                // 注意：根据rev方向，物理上要加到相反的一端
                if (!rev)
                {
                    q.push_back(cur);
                }
                else
                {
                    q.push_front(cur);
                }
                cur++;
            }
        }
        // 若R<L，说明窗口还未真正形成（左边界在右边），暂时不加入
        // 执行区间翻转：只改标记
        rev = !rev;
    }
    // 已固定的左侧部分
    for (int x : ans)
    {
        cout << x << " ";
    }
    if (!rev)
    {
        while (!q.empty())
        {
            cout << q.front() << " ";
            q.pop_front();
        }
    }
    else
    {
        while (!q.empty())
        {
            cout << q.back() << " ";
            q.pop_back();
        }
    }
    for (int x = cur; x <= n; x++)
    {
        cout << x << " ";
    }
    cout << endl;
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
