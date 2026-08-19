// ​
// 题目链接：F-小月的纸带_牛客周赛 Round 157

// 题目大意：维护一个由 A, B, C 组成的字符串，支持区间循环变换，并随时查询“连续 A 段的个数”。

// 题目思路：用线段树每个节点存储 3 种偏移下的 A 段数，通过循环移位实现区间变换的快速更新，从而高效处理区间修改和全局查询。

// 代码如下：

// ​
#include <bits/stdc++.h>
using namespace std;
//#define int long long
#define endl "\n"
int n, m;
const int N = 2e5 + 10;
string s;
// 线段树的结点结构
struct Node
{
    int l, r;
    int cnt[3];   // cnt[k]表示整体加k后的A段数量
    int lazy_tag; // lazy_tag==0说明该节点对应的区间没有被修改过，!=0被修改过
    int lch, rch; // 区间最左和最右的字符(0:A,1:B,2:C);
} tree[N << 2];
void pushup(int i)
{ // 合并左右子节点的信息到父节点
    tree[i].lch = tree[2 * i].lch;
    tree[i].rch = tree[2 * i + 1].rch;
    for (int k = 0; k < 3; k++)
    {
        tree[i].cnt[k] = tree[2 * i].cnt[k] + tree[2 * i + 1].cnt[k];
        if ((tree[2 * i].rch + k) % 3 == 0 && (tree[2 * i + 1].lch + k) % 3 == 0)
        { // 如果左子树的右端和右子树的左端都是A，则中间会合并成一段，需要减1
            tree[i].cnt[k]--;
        }
    }
}
void apply(int i, int x)
{ // 将懒标记应用到当前节点
    // 对节点i整体应用一次循环变换
    tree[i].lch = (tree[i].lch + x) % 3;
    tree[i].rch = (tree[i].rch + x) % 3;
    int tep[3];
    for (int k = 0; k < 3; k++)
    {
        tep[k] = tree[i].cnt[(k + x) % 3]; // 循环右移x位
    }
    for (int k = 0; k < 3; k++)
    {
        tree[i].cnt[k] = tep[k];
    }
    tree[i].lazy_tag = (tree[i].lazy_tag + x) % 3; // 有可能连续多次修改
}
void pushdown(int i)
{
    if (tree[i].lazy_tag != 0)
    {
        apply(2 * i, tree[i].lazy_tag);
        apply(2 * i + 1, tree[i].lazy_tag);
        tree[i].lazy_tag = 0;
    }
}
void Build(int i, int le, int ri) // 构建第i号节点，对应的区间[le,ri],时间复杂度O(n);
{                                 // 建立线段树
    tree[i].l = le;
    tree[i].r = ri;
    if (le == ri)
    { // 区间中只有一个数据 叶子节点
        int val = s[le] - 'A';
        tree[i].lch = tree[i].rch = val;
        // 如果当前字符是A，则这段是一个连续的A段，否则不是
        for (int k = 0; k < 3; k++)
        {
            tree[i].cnt[k] = ((val + k) % 3 == 0 ? 1 : 0);
        }
        return;
    }
    // 区间中有多个数据 非叶子节点
    int mid = (le + ri) / 2;
    Build(2 * i, le, mid);
    Build(2 * i + 1, mid + 1, ri);
    pushup(i);
}

void Update(int i, int le, int ri)
{
    // 引入懒标记->保持在O(logn);
    if (tree[i].l >= le && tree[i].r <= ri)
    { // 第i个节点对应的区间被要修改的区间完全覆盖
        apply(i, 1);
        return;
    }
    else
    {
        pushdown(i); // 下传懒标记，把第i个节点的两个孩子对应的区间把之前欠的先修改了
        int mid = (tree[i].l + tree[i].r) / 2;
        if (le <= mid)
        {
            Update(2 * i, le, ri);
        }
        if (ri >= mid + 1)
        {
            Update(2 * i + 1, le, ri);
        }
        pushup(i);
    }
}
int query()
{
    return tree[1].cnt[0];
}
void solve()
{
    cin >> n >> m;
    cin >> s;
    s = " " + s;
    Build(1, 1, n); // 从根节点开始建树 根节点1号节点[1,n];
    int q, x, y;
    while (m--)
    {
        cin >> q;
        if (q == 1)
        {
            cin >> x >> y;
            Update(1, x, y);
        }
        else
        {
            int ans = query();
            cout << ans << endl;
        }
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
