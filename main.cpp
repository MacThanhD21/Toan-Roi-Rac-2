#include<bits/stdc++.h>

using namespace std;

#define MAX 1000

int n, c[MAX][MAX], f[MAX][MAX];
int trace[MAX];
bool visited[MAX];

bool BFS(int s, int t)
{
    queue<int> Q;
    Q.push(s);
    visited[s] = true;
    while (Q.size())
    {
        int u = Q.front(); Q.pop();
        for (int v = 1; v <= n; v++)
        {
            if (visited[v] == false && c[u][v] > f[u][v])
            {
                Q.push(v); visited[v] = true;
                trace[v] = u;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int Ford_Fulkerson(int s, int t)
{
    int max_flow = 0;
    while (BFS(s, t))
    {
        int delta = INT_MAX;
        for (int v = t; v != s; v = trace[v])
        {
            int u = trace[v];
            delta = min(delta, c[u][v] - f[u][v]);
        }
        for (int v = t; v != s; v = trace[v])
        {
            int u = trace[v];
            f[u][v] += delta;
            f[v][u] -= delta;
        }
        max_flow += delta;
        for (int i = 1; i <= n; i++) visited[i] = false;
    }
    return max_flow;
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("DT.INP.txt", "r", stdin);
    // nhap du lieu
    /*
    6
    0 5 5 0 0 0
    0 0 0 6 3 0
    0 0 0 3 1 0
    0 0 0 0 0 6
    0 0 0 0 0 6
    0 0 0 0 0 0
    */
    freopen("DT.OUT.txt", "w", stdout);
    /*
    - Kết quả:
    9
    0 5 4 0 0 0 
    0 0 0 3 2 0 
    0 0 0 3 1 0 
    0 0 0 0 0 6 
    0 0 0 0 0 3 
    0 0 0 0 0 0 
    */
    #endif

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> c[i][j];
        }
    }

    int max_flow = Ford_Fulkerson(1, n);
    // In ra giá trị luồng cực đại
    cout << "val : " << max_flow << "\n\n";

    // In ra đồ thị f sau khi thực hiện xong thuật toán
    cout << "Đồ thị f : \n";
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if(i >= j) f[i][j] = 0;
            cout << f[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
