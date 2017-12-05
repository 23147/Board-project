//快速幂下x^n
ll quick_pow(ll x, ll n) {
    ll ans = 1;
    while (n) {
        if (n & 1) ans *= x;
        x *= x;
        n >>= 1;
    }
    return ans;
}

//快速幂取模x^n (mod m)
ll pow_mod(ll x, ll n, ll m) {
    ll ans = 1;
    x %= m;
    //预处理防止数据过大；
    while (n) {
        if (n & 1) ans = ans * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return ans;
}

//欧几里得gcd也可以用__gcd(a,b)
int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

//扩展欧几里得在已知a,b的情况下求一组x,y使得ax+by=gcd(a,b)=d
int extend_gcd(int a, int b, int &x, int &y) {
    int d;
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    } else {
        d = extend_gcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }
}
//递归公式ax1+by1=ay2+b(x2-[a/b]*y2)
// x1=y2;y1=x2-[a/b]*y2;
//通过x=1 y=0往上递归

//扩展欧几里得算法解不定方程ax+by=c
bool linear_equation(int a, int b, int c, int &x, int &y) {
    int d = extend_gcd(a, b, x, y);
    if (c % d) return false;
    int k = c / d;
    x *= k;
    y *= k;
    return true;
}