/// directly copied from You_Know_Who

#include<bits/stdc++.h>
using namespace std;

using T = __int128;
// ax + by = __gcd(a, b)
// returns __gcd(a, b)
T extended_euclid(T a, T b, T &x, T &y) {
  T xx = y = 0;
  T yy = x = 1;
  while (b) {
    T q = a / b;
    T t = b; b = a % b; a = t;
    t = xx; xx = x - q * xx; x = t;
    t = yy; yy = y - q * yy; y = t;
  }
  return a;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<T, T> CRT(T a1, T m1, T a2, T m2) {
  T p, q;
  T g = extended_euclid(m1, m2, p, q);
  if (a1 % g != a2 % g) return make_pair(0, -1);
  T m = m1 / g * m2;
  p = (p % m + m) % m;
  q = (q % m + m) % m;
  return make_pair((p * a2 % m * (m1 / g) % m + q * a1 % m * (m2 / g) % m) %  m, m);
}

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << (int)CRT(1, 31, 0, 7).first << '\n';
  return 0;
}

// directly copied from shefin vai 

// Source: https://forthright48.com/chinese-remainder-theorem-part-1-coprime-moduli/
// https://forthright48.com/chinese-remainder-theorem-part-2-non-coprime-moduli/
/**
    A CRT solver which works even when moduli are not pairwise coprime
    1. Add equations using addEquation() method
    2. Call solve() to get {x, N} pair, where x is the unique solution modulo N.
    Assumptions:
        1. LCM of all mods will fit into long long.
*/
class ChineseRemainderTheorem
{
    typedef long long vlong;
    typedef pair<vlong,vlong> pll;

    /** CRT Equations stored as pairs of vector. See addEqation()*/
    vector<pll> equations;

public:
    void clear()
    {
        equations.clear();
    }

    /** Add equation of the form x = r (mod m)*/
    void addEquation( vlong r, vlong m )
    {
        equations.push_back({r, m});
    }
    vlong ext_gcd(vlong a,vlong b,vlong &x,vlong &y)
    {
        if(b==0)
        {
            x=1;
            y=0;
            return a ;
        }
        /**
        gcd = x*b + y*(a%b) ;

        gcd = x*b + y*(a-(a/b)*b) ;

        gcd = x*b + y*a - y*(a/b)*b ;

        gcd = y*a + (x-(y*(a/b)))*b ;
        /**/

        vlong temp, g ;
        g=ext_gcd(b,a%b,x,y);
        temp=x-y*(a/b), x=y, y=temp ;
        return g ;
    }

    pll solve()
    {
        if (equations.size() == 0) return {-1,-1}; /// No equations to solve

        vlong a1 = equations[0].first;
        vlong m1 = equations[0].second;
        a1 %= m1;
        /** Initially x = a_0 (mod m_0)*/

        /** Merge the solution with remaining equations */
        for ( int i = 1; i < equations.size(); i++ )
        {
            vlong a2 = equations[i].first;
            vlong m2 = equations[i].second;

            vlong g = __gcd(m1, m2);
            if ( a1 % g != a2 % g ) return {-1,-1}; /// Conflict in equations

            /** Merge the two equations*/
            vlong p, q;

            ext_gcd(m1/g, m2/g, p, q);

            vlong mod = m1 / g * m2;
            vlong x = ( (__int128)a1 * (m2/g) % mod *q % mod + (__int128)a2 * (m1/g) % mod * p % mod ) % mod;

            /** Merged equation*/
            a1 = x;
            if ( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};
