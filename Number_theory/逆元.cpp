//求逆元的几种方法
// 1.扩展欧几里得O(logn)
int inverse(int a, int m) {
    int d, x, y;
    d = extend_gcd(a, m, x, y);
    return d == 1 ? (x + m) % m : -1;
}
//给定模数m，求a的逆相当于求解ax=1(mod m)
//这个方程可以转化为ax-my=1
//要求 a 和 m 互素

// 2.费马小定理||欧拉函数
//在模为素数p的情况下，有费马小定理 a^(p-1)=1（mod p）
//那么a^(p-2)=a^-1(mod p) 也就是说a的逆元为a^(p-2)
//而在模不为素数p的情况下，有欧拉定理
// a^phi(m)=1(mod m) (a,m)=1
//同理a^-1=a^(phi(m)-1)
//因此逆元x便可以套用快速幂求得了x=a^(phi(m)-1)
pow_mod(a, phi(m) - 1, m); //调用
//要求 a 和 m 互素

// 3.逆元打表O(n)
//在模质数p下，求1~n逆元 n<p（这里为奇质数）递推式:
// inv[i]=(p-p/i)*inv[p%i]%p
void inverse(int n, int p) {
    inv[1] = 1;
    for (int i = 2; i <= n; i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
}
//要求 p 为素数