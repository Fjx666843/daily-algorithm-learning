​ // 题目链接：https://www.nowcoder.com/practice/7c658c72c26643d681546085aa6dcd8b?channelPut=tracker3

    // 题目大意：给定两个整数x,y，可以进行以下操作任意次使得x变成y：

    // 1.x=x/2;

    // 2.选取任意一个整数z，x=x|z；

    // 输出最小操作次数

    // 题目思路：当x！=y时，我们可以根据x和y的二进制来分析，如果x是1001，y是1101，可以看出只有x的第三位和y的第三位不同，也就是y有x没有的且x有的y都有，那么（x|y）一定和y相等，如果x是1011，y是1101，可以看出x有的y没有，那么我们就要将其转化位上面的情况，我们可以使得x>>1,变为0101，通俗来说我们需要通过操作一让x的二进制成为y的子集即可

    // 代码如下：

#​include<bits / stdc++.h> 
using namespace std;
#define int long long
#define endl "\n"
void solve()
{
    int x, y;
    cin >> x >> y;
    int cnt = 0;
    while ((x | y) != y)
    {
        x = x >> 1;
        cnt++;
    }
    if (x == y)
    {
        cout << cnt << endl;
    }
    else
    {
        cout << cnt + 1 << endl;
    }
}
signed main()
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
