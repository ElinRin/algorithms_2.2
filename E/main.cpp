#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;
const double PI = asin(0);

class Point
{
     public:
       double x,y;
       friend Point operator - (Point a,Point b)
       {
             a.x=a.x-b.x;
             a.y=a.y-b.y;
             return a;
       }
       friend Point operator + (Point a,Point b)
       {
             a.x=a.x+b.x;
             a.y=a.y+b.y;
             return a;
       }
       bool operator == (Point b)
    {
        if (x==b.x && y==b.y)
            return true;
        return false;
    }
};
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

class Circle
{
    public:
       Point a;
       double r;
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
istream &operator >> (istream &cin, Segment &a)
{
   cin>>a.a>>a.b>>a.c;
   return cin;
}
ostream &operator << (ostream &cout, Segment &a)
{
    cout<<a.a<<" "<<a.b<<" "<<a.c<<" ";
    return cout;
}

istream &operator >> (istream &cin, Circle &a)
{
   cin>>a.a>>a.r;
   return cin;
}
ostream &operator << (ostream &cout, Circle &a)
{
    cout<<a.a<<" "<<a.r;
    return cout;
}

double sum_squares (Point a,Point b)
{
       return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}

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

double angle (Point a)
{
    double c=atan2(a.y,a.x);
    if (c<0)
        c=c+PI*2;
    return c;
}

double angle_circle (Circle c,Point a)
{
     return 2*asin(c.r/sqrt(sum_squares(c.a,a)));
}
Point rotation_vector(Point a,double u)
{
      double R=sqrt(a.x*a.x+a.y*a.y);
      double q=angle(a);;
      q+=u;
      a.x=cos(q)*R;
      a.y=sin(q)*R;
      return a;
}

int point_circle(Circle c,Point a)
{
     if (sum_squares(a,c.a)==c.r*c.r)
        return 1;
     if (sum_squares(a,c.a)<c.r*c.r+0.00000001)
        return 0;

     return 2;
}
vector<Point> tangent (Circle c,Point a)
{
    vector<Point> points;
    if (point_circle(c,a)==0)
       return points;
    if  (point_circle(c,a)==1)
    {
       points.push_back(a);
       return points;
    }
    double u=acos(c.r/sqrt(sum_squares(a,c.a)));
    Point z;
    z=rotation_vector(a-c.a,u);
    z.x=(z.x/sqrt(sum_squares(a,c.a)))*c.r;
    z.y=(z.y/sqrt(sum_squares(a,c.a)))*c.r;
    points.push_back(c.a+z);
    z=rotation_vector(a-c.a,PI*2-u);
    z.x=(z.x/sqrt(sum_squares(a,c.a)))*c.r;
    z.y=(z.y/sqrt(sum_squares(a,c.a)))*c.r;
    points.push_back(c.a+z);
    return points;
}
int main()
{
    ifstream in;
    ofstream out;

    in.open("tangent.in");
    out.open("tangent.out");

   Circle a;
   Point b;
   in >> a >> b;
   out.precision(10);
   out.setf(ios:: fixed);
   vector<Point> point_tangent = tangent(a,b);
   out << point_tangent.size() << endl;
    if (point_tangent.size() == 1) {
            out << point_tangent[0] << endl;
        }
    if (point_tangent.size() == 2) {
        Point h = segment_segment(Segment(a.a,b),Segment(point_tangent[0],point_tangent[1]));
        out << h << endl;
        out << sqrt(sum_squares(b,h)) << " " << sqrt(sum_squares(point_tangent[0],h)) << endl;
        out <<point_tangent[1]<<endl;
        out <<point_tangent[0]<<endl;
    }


   return 0;
}
