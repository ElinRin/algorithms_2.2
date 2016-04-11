#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const double PI = 3.14159265358979323846;

class Point
{
    public:
        double x;
        double y;
        Point(double X, double Y): x(X), y(Y) {}
        Point() {}
};

istream &operator >> (istream &cin, Point &a)
{
   cin>>a.x>>a.y;
   return cin;
}
ostream &operator << (ostream &cout, Point &a)
{
    cout<<a.x<<" "<<a.y<<" ";
    return cout;
}


class Point_on_circle {
public:
    Point p;
    double r;
    bool left;
    Point_on_circle() {}
    /*bool operator < (const Point_on_circle &a)  const {
            return (p.y < a.p.y) || (p.y == a.p.y && p.x < a.p.x)|| (p.y == a.p.y && p.x == a.p.x && r > a.r);
    }*/
};

struct setcomp{
    bool operator() (const Point_on_circle & a , const Point_on_circle & b) {
        if (a.p.y != b.p.y) return (a.p.y < b.p.y);
        if (a.p.x + a.r != b.p.x + b.r) return (a.p.x + a.r < b.p.x + b.r);
        return a.r < b.r;
    }
};

bool circle_circle(Point_on_circle &a, Point_on_circle &b) {
    if (a.r < b.r)
        return false;
    else
        if ( ( (a.p.x + a.r - b.p.x - b.r)*(a.p.x + a.r - b.p.x - b.r) + (a.p.y - b.p.y)*(a.p.y - b.p.y) ) < a.r*a.r)
            return true;
        else
            return false;
}
bool compare (Point_on_circle &a, Point_on_circle &b)
{
        if(a.p.x != b.p.x) return a.p.x < b.p.x;
        if(a.left != b.left) return a.left < b.left;
        if(a.r != b.r) return a.r > b.r;
        else return a.p.y < b.p.y;
}

double area (double &r) {
    return PI*r*r;
}

double true_area (vector<Point_on_circle> &circles) {

    set<Point_on_circle, setcomp> y;
    double ans = 0;
    sort(circles.begin(), circles.end(), &compare);

    for (int i = 0; i < circles.size(); i++) {

        if (circles[i].left) {
            if (y.find(circles[i]) == y.end()) {
                set<Point_on_circle, setcomp>::iterator it;
                y.insert(circles[i]);
                if (y.size() > 1) {
                    it = y.find(circles[i]);
                    it++;
                    if (it != y.end()) {
                        Point_on_circle a = *it;
                        if ( circle_circle(a, circles[i]) ) {;
                                y.erase(circles[i]);
                                continue;
                        }
                    }
                    it = y.find(circles[i]);
                    if ( (it != y.begin()) && (it != y.end()) ) {
                        it--;
                        Point_on_circle a = *it;
                        if ( circle_circle(a, circles[i]) ) {
                                y.erase(circles[i]);
                                continue;
                        }
                    }
                }


            }
        }
        else
        {
            Point_on_circle p = circles[i];
            p.p.x = p.p.x - 2*p.r;
            p.left = true;
            if (y.find(p) != y.end() ) {
                  ans+=area(circles[i].r);
                  y.erase(p);
            }
        }
    }
  /* cout << y.size() << "size"<< endl;
    for (set<Point_on_circle, setcomp>::iterator it = y.begin(); it != y.end(); ++it) {
        cout << (*it).p.x << " " << (*it).p.y << endl;
        cout << (*it).r << endl;
        cout << (*it).circle << endl;
        cout << (*it).left << endl;
    }*/
    return ans;
}
int main()
{
    ifstream in;
    ofstream out;

    in.open("circles.in");
    out.open("circles.out");

    int n;
    int j = 0;
    Point center;
    double r;
    vector<Point_on_circle> circles;
    in >> n;
    circles.resize(2*n);
    for (int i = 0; i < n; ++i)
    {
        in >> center >> r;

        circles[j].p = Point(center.x - r, center.y);
        circles[j].r = r;
        circles[j].left = true;

        circles[j + 1].p = Point(center.x + r, center.y);
        circles[j + 1].r = r;
        circles[j + 1].left = false;

        j+=2;

    }

    out.precision(20);
    out.setf(ios:: fixed);
    out << true_area(circles) << endl;

    return 0;
}
