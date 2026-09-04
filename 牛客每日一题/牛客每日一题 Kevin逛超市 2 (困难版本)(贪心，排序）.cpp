​
题目链接：Kevin逛超市 2 (困难版本)_牛客题霸_牛客网

题目大意：总共买了n件商品，每件商品是p[i]，有1和2两种类型的优惠卷a和b张，对于1的优惠:p[i]*%x,对于2的优惠：p[i]-y，每个商品最多使用一张优惠卷，求出花费的最小值

题目思路：对于每件商品来说，商品的价值越大，对于1的优惠效果越大，所以我们可以先将p数组从大到小排序，优先处理价值高的商品，接着对前a+b件商品考虑使用哪一种类型的优惠卷（不考虑每种优惠卷数目限制）最优，在逐件决策后，需要检查两种券的使用数量是否符合限制。如果不符合，选择改用另一种券代价最小的商品进行调整。

代码如下：时间复杂度O(nlogn)

​#include <bits/stdc++.h>
using namespace std;
using in128 = __int128_t;
#define int long long

void solve()
{
    int n,a,b,x,y;
    cin>>n>>a>>b>>x>>y;
    vector<int>p(n+1);
    for(int i=1;i<=n;i++){
        cin>>p[i];
    }
    //从小到大排序
    sort(p.begin()+1,p.end(),greater<int>());
    //只需考虑前a+b件商品
    int m=min(n,a+b);
    //计算每件商品使用两种劵后的价格
    vector<double>discount_price(m+1);//折扣后价格
    vector<double>diff_price(m+1);//立减后价格
    vector<int>choice(m+1);//0:折扣劵 1：立减劵
    int cnta=0,cntb=0;
    double total=0;
    for(int i=1;i<=m;i++){
        discount_price[i]=p[i]*x/100.0;
        diff_price[i] = max(0LL, p[i] - y);
        //选择价格更低的优惠方法
        if(discount_price[i]<diff_price[i]){
            choice[i] = 0;//折扣优
            cnta++;
            total += discount_price[i];
        }
        else
        {
            choice[i] = 1; // 立减券更优或相等
            cntb++;
            total += diff_price[i];
        }
    }
    //如果折扣劵用多了，调整为立减劵
    if(cnta>a){
        int need = cnta - a;
        vector<double> cost;
        for (int i = 1; i <= m;i++){
            if (choice[i] == 0)
            {
                // 从折扣券改为立减券的代价
                double delta = diff_price[i] - discount_price[i];
                cost.push_back(delta);
            }
        }
        //升序，选择代价最小的
        sort(cost.begin(), cost.end());
        for (int i = 0; i < need ; i++)
        {
            total += cost[i];
            cnta--;
            cntb++;
        }
    }
    // 如果立减券用多了，调整为折扣券
    else if (cntb > b)
    {
        int need = cntb - b;
        vector<double> cost;

        for (int i = 1; i <= m; i++)
        {
            if (choice[i] == 1)
            {
                // 从立减券改为折扣券的代价
                double delta = discount_price[i] - diff_price[i];
                cost.push_back(delta);
            }
        }

        sort(cost.begin(), cost.end()); // 升序，选代价最小的

        for (int i = 0; i < need ; i++)
        {
            total += cost[i];
            cnta++;
            cntb--;
        }
    }
    // 加上剩余商品（不用券）的价格
    for (int i = m + 1; i <= n; i++)
    {
        total += p[i];
    }
    cout << fixed << setprecision(10) << total << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T ;
    cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}