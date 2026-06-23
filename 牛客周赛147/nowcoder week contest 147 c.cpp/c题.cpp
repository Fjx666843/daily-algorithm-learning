// 题目链接：https://ac.nowcoder.com/acm/contest/136224/C

// 题目大意：定义一个数组b的权值为，现在给定一个数组a，对其进行q次操作，每一次操作给出两个整数l，r（1<=l<=r<=n），将a数组的[l,r]区间加1，求每次操作后的权值并且输出，每次操作不独立

// 题目思路：根据给定的权值求法，可以看出和差分有关，因此我们可以根据原有公式进行转化，最后权值公式变为，其中d[i]=a[i]-a[i-1],因此我们每次操作只需要维护差分数组即可，因为每一次区间加法，只有d[l]++,d[r+1]--,其他不变，时间复杂度就降到O（1），但是要注意，可能会取到d[1]和d[n+1],所以需要我们初始化一下，以防计多

#include <bits/stdc++.h>
using namespace std;
int a[200005];
int d[200005];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i=2;i<=n;i++) {
        d[i]=a[i]-a[i-1];
        d[i]%=5;
        d[i]+=5;
        d[i]%=5;
        ans+=d[i];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        ans-=(d[l]+d[r+1]);
        d[l]++;
        d[r+1]--;
        d[l]%=5,d[r+1]%=5;
        d[l]+=5,d[r+1]+=5;
        d[l]%=5,d[r+1]%=5;
        d[1]=0,d[n+1]=0;
        ans+=(d[l]+d[r+1]);
        cout<<ans<<endl;
    }
    return 0;
}

