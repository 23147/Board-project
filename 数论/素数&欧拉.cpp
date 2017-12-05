//质因数分解
int fac(ll tot) {
    int num = 0;
    ll tmp = floor(sqrt(tot) + 0.5);
    for (ll i = 2; i <= tmp; i++) {
        if (tot % i == 0) {
            p[++num] = i;
            while (tot % i == 0) {
                tot /= i;
            }
        }
    }
    if (tot > 1) {
        p[++num] = tot;
    }
    return num;
}

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
//线性筛素数O(n)
//每个合数仅被它的最小素因子筛去恰好一次
memset(vis, true, sizeof(vis));
int num = 0;
for (int i = 2; i <= n; i++) {
    if (vis[i] == true) {
        num++;
        prime[num] = i;
    }
    for (int j = 1; j <= num && i * prime[j] <= n; j++) {
        vis[i * prime[j]] = false;
        if (i % prime[j] == 0) break;
    }
}

//线性欧拉O(n)
memset(vis, true, sizeof(vis));
phi[1] = 1;
int num = 0;
for (int i = 2; i <= n; i++) {
    if (vis[i] == true) {
        num++;
        prime[num] = i;
        phi[i] = i - 1;
    }
    for (int j = 1; j <= num && i * prime[j] <= n; j++) {
        vis[i * prime[j]] = false;
        if (i % prime[j] == 0) {
            phi[i * prime[j]] = phi[i] * prime[j];
            //如果prime[j]已经是i的因数
            break;
        } else
            phi[i * prime[j]] = phi[i] * (prime[j] - 1);
        //如果prime[j]不是i的因数
    }
}
