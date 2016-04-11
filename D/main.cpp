#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

const double PI = asin(0);

class Point
{
    public:
        double x;
        double y;
        Point(double X=0, double Y=0): x(X), y(Y) {}

        Point operator+(Point const&r) { return Point(x+r.x,y+r.y); }
        Point operator-(Point const&r) { return Point(x-r.x,y-r.y); }
        Point operator*(double r) { return Point(x*r,y*r); }
        Point operator/(double r) { return Point(x/r,y/r); }
        bool operator < (const Point &r)  const { return make_pair (x,y) < make_pair (r.x,r.y); }

        double sqlen() { return x*x+y*y; }
        double len() { return sqrt(sqlen()); }
};

double dot(Point a,Point b) { return a.x*b.x+a.y*b.y; }

double cross(Point a,Point b) { return a.x*b.y-a.y*b.x; }

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

class Segment
{
    public:
      double a,b,c;
      Segment (Point a1,Point b1)
      {
          a=b1.y-a1.y;
          b=a1.x-b1.x;
          c=a1.x*(a1.y-b1.y)+a1.y*(b1.x-a1.x);
      }
      Segment(){}
};

Point segment_segment (Segment o,Segment q)
{
    Point a;
    a.y=(q.c*o.a-o.c*q.a)/(o.b*q.a-q.b*o.a);
    if (q.a!=0)
        a.x=(-q.b*a.y-q.c)/q.a;
    else
        a.x=(-o.b*a.y-o.c)/o.a;
    return a;
}

double dist_point_point (Point a,Point b)
{
       return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

vector <Point> circ (Point a, Point b, double R, double bigR)
	{
		if ((b - a).sqlen() > (R + bigR) * (R + bigR) + 1e-8 || (b - a).sqlen() < (R - bigR) * (R - bigR) - 1e-8)
			return vector <Point> ();

			double alpha = (R * R + (b - a).sqlen() - bigR * bigR) / (2.0 * (b - a).len() * R);
			Point k;
			k.x = alpha * (b - a).x - sqrt(1 - alpha * alpha) * (b - a).y;
			k.y = sqrt(1 - alpha * alpha) * (b - a).x + alpha * (b - a).y;
			k = (k / (b - a).len()) * R + a;

			double alpha1 = (R * R + (b - a).sqlen() - bigR * bigR) / (2.0 * (b - a).len() * R);
			Point w;
			w.x = alpha1 * (b - a).x + sqrt(1 - alpha1 * alpha1) * (b - a).y;
			w.y = - sqrt(1 - alpha1 * alpha1) * (b - a).x + alpha1 * (b - a).y;
			w = (w / (b - a).len() * R) + a;
		vector <Point> res;
		if ((k - w).sqlen() < 1e-8)
			res.push_back(k);
		else
		{
			res.push_back(k);
			res.push_back(w);
		}
		return res;
	}
int main()
{
    ifstream in;
    ofstream out;

    in.open("intersec4.in");
    out.open("intersec4.out");

	Point a, b;
	double R1, R2;
	int n;
	in >> n;
	out.precision(10);
    out.setf(ios:: fixed);
	for (int i = 0; i < n; ++i) {
        in >>a >> R1 >> b >>R2;
        if ((b - a).sqlen() == 0 && R1 == R2)
        {
            out <<3 <<endl;
            continue;
        }
        vector <Point> ans = circ (a, b, R1, R2);
        out << ans.size() <<endl;
        if (ans.size() == 1) {
            out <<ans[0]<<endl;
        }
        if (ans.size() == 2) {
            Point h = segment_segment(Segment(a,b),Segment(ans[0],ans[1]));
            out << h << endl;
            out << dist_point_point(a,h) << " " << dist_point_point(ans[0],h) << endl;
            out <<ans[0]<<endl;
            out <<ans[1]<<endl;
        }

	}
	return 0;

}
