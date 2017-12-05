#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

//求区间和
using namespace std;
const int MA = 50000 + 20;
int sum[MA << 2] = {0};

//单点更新
void pushup(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }
void build(int l, int r, int rt) {
  if (l == r) {
    cin >> sum[rt];
    return;
  }
  int m = (l + r) >> 1;
  build(lson);
  build(rson);
  pushup(rt);
}
void update(int t, int w, int l, int r, int rt) // t为索引，w为值
{
  if (l == r) {
    sum[rt] += w;
    return;
  }
  int m = (l + r) >> 1;
  if (t <= m)
    update(t, w, lson);
  else
    update(t, w, rson);
  pushup(rt);
  return;
}
int query(int L, int R, int l, int r, int rt) //求[L,R]的和
{
  if (L <= l && R >= r) {
    return sum[rt];
  }
  int ret = 0;
  int m = (l + r) >> 1;
  if (L <= m)
    ret += query(L, R, lson);
  if (m < R)
    ret += query(L, R, rson);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  int t;
  int k = 1;
  cin >> t;
  int n;
  while (t--) {
    cin >> n;
    build(1, n, 1);
    cout << "Case " << k << ":" << endl;
    k++;
    string s;
    while (cin >> s && s[0] != 'E') {
      if (s[0] == 'Q') {
        int L, R;
        cin >> L >> R;

        int x = query(L, R, 1, n, 1);
        cout << x << endl;
      } else if (s[0] == 'A') {
        int t, w;
        cin >> t >> w;
        update(t, w, 1, n, 1);
      } else if (s[0] == 'S') {
        int t, w;
        cin >> t >> w;
        update(t, -w, 1, n, 1);
      }
    }
  }
  return 0;
}

//区间更新&区间查询
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
const int maxn = 2e5 + 5;

int sum[maxn << 2], mx[maxn << 2], mn[maxn << 2];
int col[maxn << 2];

void pushup(int rt) {
  sum[rt] = sum[rt << 1] + sum[rt << 1 | 1] mx[rt] =
                max(mx[rt << 1], mx[rt << 1 | 1]) mn[rt] =
                    min(mn[rt << 1], mn[rt << 1 | 1])
}
void pushdown(int rt, int m) {
  // add
  col[rt << 1] += col[rt];
  col[rt << 1 | 1] += col[rt];
  sum[rt << 1] += col[rt] * (m - (m >> 1));
  sum[rt << 1 | 1] += col[rt] * (m >> 1);
  //以上 replace 时 +=  -->  =

  mx[rt << 1] += col[rt];
  mn[rt << 1 | 1] += col[rt];
  col[rt] = 0;
}
void build(int l, int r, int rt = 1) {
  col[rt] = 0;
  if (l == r) {
    sum[rt] = 0;
    mx[rt] = 0;
    mn[rt] = inf;
    return;
  }
  int m = (l + r) >> 1;
  build(lson);
  build(rson);
  pushup(rt);
}

void update(int L, int R, int c, int l, int r, int rt = 1) {
  if (L <= l && R >= r) {
    // add
    col[rt] += c;
    sum[rt] += c * (r - l + 1);
    mx[rt] += c;
    mn[rt] += c;
    // replace
    col[rt] = c;
    sum[rt] = c * (r - l + 1);
    mx[rt] = max(mx[rt], c);
    mn[rt] = min(mn[rt], c);
    //
    return;
  }
  pushdown(rt, r - l + 1);
  int m = (l + r) >> 1;
  if (L <= m)
    update(L, R, c, lson);
  if (m < R)
    update(L, R, c, rson);
  pushup(rt);
}

query(int L, int R, int l, int r, int rt = 1) {
  if (L <= l && r >= r) {
    return ___[rt];
  }
  pushdown(rt, r - l + 1);
  int ans;
  int m = (l + r) >> 1;
  if (l <= m)
    ans = ___ query(L, R, lson);
  if (m < R)
    ans = ___ query(L, R, rson);
  return ans;
}

//线段树维护前k小数和
#define lson l, m, rt << 1
#define rson m + !, r, rt << 1 | 1
const maxn = 10005;

int sum[maxn << 2], size[maxn << 2];

void pushup(int rt) {
  sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
  size[rt] = size[rt << 1] + size[rt << 1 | 1];
}

void build(int l, int r, int rt = 1) {
  if (l == r) {
    sum[rt] = 0;
    size[rt] = 0;
    return;
  }
  int m = (l + r) >> 1;
  build(lson);
  build(rson);
  pushup(rt);
}

void update(int L, int c, int l, int r, int rt = 1) {
  if (l == r) {
    sum += L * C;
    size += c;
    return;
  }
  int m = (l + r) >> 1;
  if (L <= m)
    update(L, c, lson);
  else
    update(L, c, rson);
  pushup(rt);
}

int query(int k, int l, int r, int rt = 1) {
  if (k <= 0) {
    return 0;
  }
  if (size[rt] <= k)
    return sum[rt];
  if (l == r)
    return min(size[rt], k) * l;
  int m = (l + r) >> 1;
  if (size[rt << 1] <= k)
    return sum[rt << 1] + query(k - size[rt << 1], rson);
  else
    return query(k, lson);
}