​
题目链接：小红的皇后_牛客题霸_牛客网

题目大意：在一个n*m的网格上，有若干障碍物，其中有三种走法：

∙ 向右：(x,y)→(x,y+k)；
∙ 向下：(x,y)→(x+k,y)；
∙ 向右下：(x,y)→(x+k,y+k)；

其中 k≥1，并且移动路径上不得出现障碍物。

求从（1，1）到（n,m)的最小移动步数，如果不能到达输出-1

题目思路：由于让我们求最小移动步数并且每一步移动代价相同，即最短路问题，我们可以用bfs求解.

朴素 BFS 的问题
如果皇后每走一步都枚举所有可能的 k（1,2,3,...），最坏情况复杂度 O(nm × max(n,m))，会超时。

优化思路

所以：

每个格子只需要入队一次

从当前格子出发，沿三个方向一直走到头，途中遇到未访问的格子就入队

遇到已访问的格子或障碍物就停止(即更优解）

原因如下：
如果前方格子已经访问过，说明已经有更短（或等长）的路径到达它

从它继续往后走的路径，通过当前路径走不会更优

所以不需要继续往前走了

此时对于每走一步都枚举所有可能的 k（1,2,3,...）降到常数级别

代码如下：

​
#include <bits/stdc++.h>
using namespace std;
using in128 = __int128_t;
#define int long long
bool in_bound(int x,int y,int n,int m){
    return 1 <= x && x <= n && 1 <= y && y <= m;
}
int bfs(int n,int m,vector<string>&grid){
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, -1));
    queue<pair<int, int>> q;
    q.push({1,1});
    dist[1][1] = 0;
    int dx[] = {0, 1, 1};
    int dy[] = {1, 0, 1};
    pair<int, int> u;
    while(!q.empty()){
        u = q.front();
        q.pop();
        int x = u.first;
        int y = u.second;
        int current_dist = dist[x][y];
        if(x==n&&y==m){
            return current_dist;
        }
        for (int dir = 0; dir < 3; dir++)
        {
            int k = 1;
            while(true){
                int nx = x + dx[dir] * k;
                int ny = y + dy[dir] * k;
                if(!in_bound(nx,ny,n,m)||grid[nx][ny]!='.'){
                    break;
                }
                if(dist[nx][ny]==-1){
                    dist[nx][ny] = current_dist + 1;
                    q.push({nx, ny});
                }else if(dist[nx][ny]<=current_dist)
                { // 如果已经有更优解，提前终止
                    break;
                }
                k++;
            }
        }
    }
    return -1;
}
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<string> grid(n + 1);
    for (int i = 1; i <= n;i++){
        cin >> grid[i];
        grid[i] = " " + grid[i];
    }
    cout << bfs(n, m, grid) << endl;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T =1;
    //cin >> T;
    while (T--)
    {
        solve();
    }

    return 0;
}

