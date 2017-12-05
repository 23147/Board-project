//线性筛选求莫比乌斯反演函数
void init() {
  memset(vis, 0, sizeof(vis));
  mu[1] = 1;
  cnt = 0;
  for (int i = 2; i < N; i++) {
    if (!vis[i]) {
      prime[cnt++] = i;
      mu[i] = -1;
    }
    for (int j = 0; j < cnt && i * prime[j] < N; j++) {
      vis[i * prime[j]] = 1;
      if (i % prime[j])
        mu[i * prime[j]] = -mu[i];
      else {
        mu[i * prime[j]] = 0;
        break;
      }
    }
  }
}

//给定两个数n和m，其中1<=x<=n，1<=y<=m，求gcd(x,y)为质数(x,y)的有多少对？其中n和m的范围是[1,10^7];
#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;
typedef long long LL;
const int N = 10000005;

bool vis[N];
int p[N];
int cnt;
int g[N], u[N], sum[N];

void Init() {
  memset(vis, 0, sizeof(vis));
  u[1] = 1;
  cnt = 0;
  for (int i = 2; i < N; i++) {
    if (!vis[i]) {
      p[cnt++] = i;
      u[i] = -1;
      g[i] = 1;
    }
    for (int j = 0; j < cnt && i * p[j] < N; j++) {
      vis[i * p[j]] = 1;
      if (i % p[j]) {
        u[i * p[j]] = -u[i];
        g[i * p[j]] = u[i] - g[i];
      } else {
        u[i * p[j]] = 0;
        g[i * p[j]] = u[i];
        break;
      }
    }
  }
  sum[0] = 0;
  for (int i = 1; i < N; i++)
    sum[i] = sum[i - 1] + g[i];
}

int main() {
  Init();
  int T;
  scanf("%d", &T);
  while (T--) {
    LL n, m;
    cin >> n >> m;
    if (n > m)
      swap(n, m);
    LL ans = 0;
    for (int i = 1, last; i <= n; i = last + 1) {
      last = min(n / (n / i), m / (m / i));
      ans += (n / i) * (m / i) * (sum[last] - sum[i - 1]);
    }
    cout << ans << endl;
  }
  return 0;
}