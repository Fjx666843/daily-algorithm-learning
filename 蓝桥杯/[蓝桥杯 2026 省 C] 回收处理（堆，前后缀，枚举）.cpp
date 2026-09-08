​
题目链接：P16276 [蓝桥杯 2026 省 C] 回收处理 - 洛谷

题目描述：给定3*n个部件，并且依次排列，每个部件的价值为a[i]:若执行回收，该标价即为收益；若执行处理，该标价则计为成本。

小蓝的任务是从这 3N 个部件中挑选出两批特定组别：

回收组：挑选出恰好 N 个部件进行回收，总收益记为 R。
处理组：挑选出恰好 N 个部件进行处理，总成本记为 C。
挑选过程必须遵守严格的先后顺序：任何一个被回收的部件，其原始位置都必须早于所有被处理的部件（即若把回收部件的下标记为 p1​<p2​<⋯<pN​，处理部件的下标记为 q1​<q2​<⋯<qN​，则必须满足 pN​<q1​）。

在满足上述顺序的前提下，水线上剩下的 N 个部件将被直接弃置，不产生任何收益或成本。

现在，小蓝希望通过合理的方案，使得回收的总收益减去处理的总成本（R−C）尽可能大。对此，请你计算出这个差值的最大可能结果。

题目思路：我们需要求（R−C）最大，那么就是R尽可能大，C尽可能小，但是这里有一个限制，就是处理组必须在回收组后面,那么我们可以枚举每一个分界点i，对于[1,i]选取N个元素使得R最大，对于[i+1,3*N]选取N个元素使得R最小，其中i的范围是[N,2*N],因为要至少保留N个元素可选，现在我们可以通过堆来贪心处理[1,i]中最小的N个元素和[i+1,3*N]中最大的N个元素，具体的，我们可以每次尝试加入a[i]到堆里，比较堆顶和a[i]的大小就行了（当堆中元素个数超过N时），就能预处理出[1, i]中选n个数的最大或者最小值（当堆中元素个数等于N时）；后缀也是类似的道理，预处理前缀，后缀，再按上面的办法枚举就行了

代码如下：

​#include <bits/stdc++.h>
using namespace std;
using in128 = __int128_t;
#define int long long
const int INF = 4e18; // 定义一个很大的数，用于初始化
void solve()
{
    int N;
    cin >> N;
    int M = 3 * N;
    vector<int> a(M + 1);
    for (int i = 1; i <= M;i++){
        cin >> a[i];
    }
    // preMax[i]：表示从 [1, i] 中选出 N 个数的最大和
    // sufMin[i]：表示从 [i+1, M] 中选出 N 个数的最小和
    vector<int> preMax(M + 2, -INF); // 初始化为负无穷
    vector<int> sufMin(M + 2, INF);  // 初始化为正无穷
    //从左往右扫描，计算 preMax[i]维护前 i 个数中最大的 N 个数的和 使用小根堆（堆顶是最小的），堆里始终保留最大的 N 个数
    priority_queue<int, vector<int>, greater<int>> minHeap; // 小根堆
    int sum = 0;//当前堆中所有元素和
    for (int i = 1; i <= 2*N;i++){
        minHeap.push(a[i]);//踢掉堆顶（最小值）
        sum += a[i];
        if((int)minHeap.size()>N){
            sum -= minHeap.top();
            minHeap.pop();
        }
        // 当堆里恰好有N个元素时，记录preMax[i];
        if ((int)minHeap.size() == N){
            preMax[i] = sum;
        }
        // 如果不够 N 个，preMax[i] 保持 -INF（表示不合法）
    }
    // 第二步：从右往左扫描，计算 sufMin[i] 维护从 i+1 到 M 中最小的 N 个数的和使用大根堆（堆顶是最大的），堆里始终保留最小的 N 个数
    priority_queue<int> maxHeap;
    sum = 0;
    for (int i = M; i >= N+1;i--){
        maxHeap.push(a[i]);
        sum += a[i];
        // 如果堆中元素超过 N 个，就踢掉最大的那个
        // 这样堆里就始终保留着从 i 到 M 中最小的 N 个
        if ((int)maxHeap.size() > N)
        {
            sum -= maxHeap.top(); // 踢掉堆顶（最大值）
            maxHeap.pop();
        }

        // 当堆里恰好有 N 个元素时，记录 sufMin[i]
        if ((int)maxHeap.size() == N)
        {
            sufMin[i] = sum;
        }
        // 如果不够 N 个，sufMin[i] 保持 INF（表示不合法）
    }
    // 第三步：枚举分界点 i 回收组在[1, i] 中选 N 个，处理组在[i + 1, M] 中选 N 个 需要保证左边至少有 N 个，右边也至少有 N 个 所以 i 的范围是[N, 2N]
    int ans = -INF;
    for (int i = N; i <= 2 * N; i++)
    {
        // 回收收益 - 处理成本
        // 处理成本 = 选中的 N 个 a[i] 之和，所以贡献为负
        ans = max(ans, preMax[i] - sufMin[i + 1]);
        
    }
    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T=1;
    //cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}
