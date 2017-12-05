//中国剩余定理
//用于解决一元线性同余方程组问题
// r[]存放余数 w[]存放两两互素的数  0~n-1
int Chinese_Remainder(int r[], int w[], int len) {
    int i, d, x, y, m, n, ret;
    ret = 0;
    n = 1;
    for (int i = 0; i < len; i++) {
        n *= w[i];
    }
    for (int i = 0; i < len; i++) {
        m = n / w[i];
        d = extend_gcd(w[i], m, x, y);
        ret = (ret + y * m * r[i]) % n;
    }
    return (n + ret % n) % n;
}

//非互质的中国剩余定理
//有解返回解，无解返回-1  x%(w[i])=r[i]  n表示又n个方程 0～n-1
ll CRT2(ll r[], ll w[], int n) {
    if (n == 1) {
        if (w[0] > r[0])
            return r[0];
        else
            return -1;
    }
    ll x, y, d;
    for (int i = 1; i < n; i++) {
        if (w[i] <= r[i]) return -1;
        d = extend_gcd(w[0], w[i], x, y);
        if ((r[i] - r[0]) % d != 0) return -1;
        ll t = w[i] / d;
        x = ((r[i] - r[0]) / d * x % t + t) % t;
        r[0] = x * w[0] + r[0];
        w[0] = w[0] * w[i] / d;
        r[0] = (r[0] % w[0] + w[0]) % w[0];
    }
    return r[0];
}

// Lucas 定理  p为质数
// Lucas(n,m,p)=c(n%p,m%p)*Lucas(n/p,m/p,p) (其中n>m, p 为模数  )
ll fac[100005];
void get_fact(ll p) {
    fac[0] = 1;
    for (int i = 1; i <= p; i++)
        fac[i] = (fac[i - 1] * i) % p;
}
ll Lucas(ll n, ll m, ll p) {
    ll ret = 1;
    while (n & m) {
        ll a = n % p, b = m % p;
        if (a < b) return 0;
        ret = (ret * fac[a] * pow_mod(fac[b] * fac[a - b] % p, p - 2, p)) % p;
        n /= p;
        m /= p;
    }
    return ret;
}

//非质数的Lucas定理
/*
把p分解成p1*p2*p3*...*pn
再对每个因子分别用Lucas定义求解
最后将将所有的结果并列在一起进行中国剩余定理求解
即可得到结果
*/