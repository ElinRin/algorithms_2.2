#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>

 using namespace std;

struct Point {

    Point(long double x_, long double y_) {
        x = x_;
        y = y_;
    }
    Point(){};

    long double x;
    long double y;
    int i;
};

long double operator *(const Point & a, const Point & b) {
    return a.x * b.x + a.y * b.y;
}
Point operator -(const Point & a, const Point & b) {
    return Point(a.x - b.x, a.y - b.y);
}
Point operator +(const Point & a, const Point & b) {
    return Point(a.x + b.x, a.y + b.y);
}
void operator /= (Point & a, const long double x) {
    assert(x != 0);
    a.x /= x;
    a.y /= x;
}

long double dist(const Point & a, const Point & b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}
long double dist(const Point & a) {
    return sqrt(a.x * a.x + a.y * a.y);
}
long double gdet(long double a, long double b, long double c, long double d) {
    return a*d - b*c;
}

long double mult(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

/*******************************/

long double get_dist(const Point &  p,const Point & p1, const Point & p2) {
    Point v1,v2,v;
    v1 = p1 - p;
    v2 = p2 - p;
    v = p2 - p1;

    if((v1 * v) * (v2 * v) < 0) { // inside
        long double A,B,C;
        A = p1.y - p2.y;
        B = p2.x - p1.x;
        C = p1.x * p2.y - p1.y * p2.x;
        long double d = sqrt(A*A + B*B);
        A/= d; B/= d; C /= d;
        return abs(A * p.x + B * p.y + C);
    } else {
        return min(dist(p1,p),dist(p2,p));
    }
}

/**************/

#define pi (long double)3.141592653589793238

long double get_fi(const Point & _v) {
    Point v = _v;
    long double r = dist(v);
    v.x /= r;
    v.y /= r;
    if(v.x >= 0 && v.y >= 0) {
        return asin(v.y);
    }

    if(v.x >= 0 && v.y <= 0) {
        return 2*pi + asin(v.y);
    }

    if(v.x <= 0 && v.y >= 0) {
        return acos(v.x);
    }

    if(v.x <= 0 && v.y <= 0) {
        return pi + acos(-v.x);
    }
    return 0;
}

bool cmake_pair(const Point & a, const Point & b) {
    // cout << get_fi(a) << " " << get_fi(b) << endl;
    return get_fi(a) < get_fi(b);
}

/********************** ********************/

void merge(const vector <Point> & m1, const vector <Point> & m2 , vector <Point> & ans) {
    int i = 0 ,j = 0;
    while(i < m1.size() & j < m2.size()) {
        if(cmake_pair(m1[i],m2[j])) {
            ans.push_back(m1[i]);
            ++i;
        } else {
            ans.push_back(m2[j]);
            ++j;
        }
    }

    while(i < m1.size()) {
        ans.push_back(m1[i]);
        ++i;
    }

    while(j < m2.size()) {
        ans.push_back(m2[j]);
        ++j;
    }
}

void solve() {

    int N1,N2;
    cin >> N1;
    vector <Point> m1(N1),l1(N1);
    long long x,y;
    for(int i = 0; i < N1 ; ++i) {
        cin >> x >> y;
        m1[i].x = x;
        m1[i].y = y;
    }

    cin >> N2;
    vector <Point> m2(N2), l2(N2);
    for(int i = 0; i < N2 ; ++i)  {
        cin >> x >> y;
        m2[i].x = -x;
        m2[i].y = -y;
    }

    Point c1(0,0),c2(0,0),cs(0,0);
    for(int i = 0; i < N1 ; ++i)  {
        c1 = c1 + m1[i];
    }
    c1 /= N1;

    for(int i = 0; i < N2 ; ++i)  {
        c2 = c2 + m2[i];
    }

    c2 /= N2;

    for(int i = 0; i < N1 - 1 ; ++i)  {
        l1[i] = m1[i+1] - m1[i];
        // l1[i].i = i;
    }
    l1[N1 - 1] = m1[0] - m1[N1-1];
    // l1[N1 - 1].i = N1 - 1;

    for(int i = 0; i < N2 - 1 ; ++i)  {
        l2[i] = m2[i+1] - m2[i];
        // l2[i].i = i;
    }
    l2[N2 - 1] = m2[0] - m2[N2-1];
    // l2[N2 - 1].i = N2 - 1;

    sort(l1.begin(),l1.end(),cmake_pair);
    sort(l2.begin(),l2.end(),cmake_pair);

    // loop(i,N2) {
    //     cout << l2[i].x << " " << l2[i].y << endl;
    // }
    // loop(i,N2) {
    //     cout << l2[i].i << " ";
    // }

    vector <Point> merged(N1 + N2);
    // merge(l1,l2,merged);
    merge(l1.begin(), l1.begin() + N1, l2.begin(), l2.begin() + N2, merged.begin(), cmake_pair);

    // loop(i,N1 + N2) {
    //     cout << merged[i].x << " " << merged[i].y << endl;
    // }

    vector <Point> sum;
    sum.reserve(N1 + N2);
    Point cur(0,0);
    sum.push_back(cur);
    for(int i = 0; i < merged.size() ; ++i)  {
        cur = cur + merged[i];
        sum.push_back(cur);
    }
    sum.pop_back();

    // loop(i,sum.size()) {
    //     cout << sum[i].x << " " << sum[i].y << endl;
    // }

    for(int i = 0; i < N1 + N2 ; ++i) {
        cs = cs + sum[i];
    }
    cs.x /= (N1 + N2);
    cs.y /= (N1 + N2);

    Point delta =  Point(0,0)  - c1 - c2 - cs;
    // cout << delta.x << " " << delta.y << endl;
    for(int i = 0; i < sum.size() ; ++i) {
        sum[i] = sum[i] + delta;
        // cout << sum[i].x << " " << sum[i].y << " ";
    }

    // cout << endl;

    /************/

    Point v;
    long double mmin = 1e12;
    long long ind;
    for(int i = 0; i < sum.size(); ++i) {
        long double cur = get_dist(Point(0,0), sum[(i+1) % (sum.size())], sum[i]);
        if(cur < mmin) {
            mmin = cur;
            ind = i;
        }
    }

    long double A = sum[ind].y - sum[(ind+1) % sum.size()].y;
    long double B = sum[(ind+1) % sum.size()].x - sum[ind].x;
    v = Point(mmin * A / sqrt(A*A + B*B) , mmin * B / sqrt(A*A + B*B));
    v /= 2;
    // cout << v.x << " " << v.y << endl;

    for(int i = 0; i < N2 ; ++i) {
        m2[i] = Point(0,0) - m2[i];
    }

    vector<pair<long double,int> > dists1(N1);
    vector<pair<long double,int> > dists2(N2);

    for(int i = 0; i < N1; ++i) dists1[i] = make_pair(abs(m1[i] * v),i);
     for(int i = 0; i < N2 ; ++i) dists2[i] = make_pair(abs(m2[i] * v),i);

    sort(dists1.begin(), dists1.end());
    sort(dists2.begin(), dists2.end());

    long double A2 = A / sqrt(A*A + B*B);
    long double B2 = B / sqrt(A*A + B*B);

    // cout << A2 << " " << B2 << endl;
    Point c[8] = {
        m1[dists1[0].second] + v ,
        m1[dists1[0].second] - v ,
        m1[dists1[dists1.size() - 1].second] + v ,
        m1[dists1[dists1.size() - 1].second] - v ,

        m2[dists2[0].second] + v ,
        m2[dists2[0].second] - v ,
        m2[dists2[dists2.size() - 1].second] + v ,
        m2[dists2[dists2.size() - 1].second] - v
    };

    long double C[8];
    bool check;
    int id = -1;
    for(int i = 0; i < 8; ++i){
        check = true;
        C[i] = -A2 * c[i].x - B2 * c[i].y;
        // cout <<"ci" <<  C[i] <<endl;
        if(abs(A2 * m1[0].x + B2 * m1[0].y + C[i]) < 1e-12) {
            check = false;
            continue;
        }

        long double sign = (A2 * m1[0].x + B2 * m1[0].y + C[i]) / abs(A2 * m1[0].x + B2 * m1[0].y + C[i]);
        // cout <<"sign:" <<sign << endl;

         for(int j = 0; j < N1 ; ++j){
            // cout << A2 << " " << m1[j].x << " " << B2 << " " << m1[j].y << " " << C[i] << endl;
            long double cur1 = A2 * m1[j].x;
            long double cur2 =  B2 * m1[j].y;
            long double cur = cur1 + cur2 + C[i];
            // cout << "cur " << cur1 << " " <<cur2 << " " << C[i] << " "<<cur << endl;
            if(abs(cur) < 1e-12 || cur * sign < 0) {
                check = false;
                break;
            }
        }

        if(!check) continue;
        if(abs(A2 * m2[0].x + B2 * m2[0].y + C[i]) < 1e-12) {
            check = false;
            continue;
        }

        long double sign2 = sign;
        sign = (A2 * m2[0].x + B2 * m2[0].y + C[i]) / abs(A2 * m2[0].x + B2 * m2[0].y + C[i]);
        if(abs(sign - sign2) < 1e-12 ){
            check = false;
            continue;
        }

        for(int j = 0; j < N2 ; ++j){
            long double cur = A2 * m2[j].x + B2 * m2[j].y + C[i];
            if(abs(cur) < 1e-12 || cur * sign < 0) {
                check = false;
                break;
            }
        }
        if(check) {
            id = i;
            break;
        }
    }

    // cout << id << endl;
    // cout << m1[id].x << " " << m2[id].y << endl;
    // assert(check);
    cout << A2 << " " << B2 << " " << C[id];
}

int main()


{
    // freopen("in.txt","r", stdin);
    freopen("rest.in","r", stdin);
    freopen("rest.out","w", stdout);

    cout << fixed;
    cout.precision(15);
    ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
