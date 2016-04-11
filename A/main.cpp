#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
class Point
{
    public:
       double x,y;
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

double dist_point_point (Point a,Point b)
{
       return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
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

Segment perpendicular (Segment a,Point b)
{
     Segment q;
     q.a=-a.b;
     q.b=a.a;
     q.c=-(q.a*b.x+q.b*b.y);
     return q;
}


double dist_point_segment(Point a,Point b,Point c)
{
   Segment s,p;
   s = Segment(b,c);
   p = perpendicular(s,a);
   Point t = segment_segment(s,p);
   if ( ((t.y <= max(c.y,b.y)) && (t.y >= min(c.y,b.y))) && ((t.x <= max(c.x,b.x)) && (t.x >= min(c.x,b.x))) )
        return dist_point_point(t,a);
   else
       return min(dist_point_point(a,b),dist_point_point(a,c));
}

bool inSegment(Point t, Point a1, Point a2)
{
    if ( ((t.y <= max(a1.y,a2.y)) && (t.y >= min(a1.y,a2.y))) && ((t.x <= max(a1.x,a2.x)) && (t.x >= min(a1.x,a2.x))) )
        return true;
    else
        return false;

}

int main()
{

    ifstream in;
    ofstream out;

    in.open("intersec2.in");
    out.open("intersec2.out");

    /*Point a,b,c;
    in >> a >> b >> c;
    out.precision(10);
    out.setf(ios:: fixed);
    out << dist_point_segment(a,b,c) << endl;*/

    /*Segment a,b;
    in >> a >> b;
    out.precision(10);
    out.setf(ios:: fixed);
    Point c = segment_segment(a,b);
    out << c << endl;*/
    Point a1,a2,b1,b2;
    in >> a1 >> a2 >> b1 >> b2;
    Segment a(a1,a2),b(b1,b2);
    /*cout.precision(20);
    cout.setf(ios:: fixed);*/
    if ((a.b*b.a-b.b*a.a) != 0)
    {
        Point t = segment_segment(a,b);
        if ( inSegment(t,a1,a2) && inSegment(t,b1,b2) )
            out << "YES" << endl;
        else
            out << "NO" << endl;
    }
    else
    {
        if ( inSegment(a1,b1,b2) || inSegment(a1,b1,b2) || inSegment(b1,a1,a2) || inSegment(b2,a1,a2) )
            out << "YES" << endl;
        else
            out << "NO" << endl;
    }


    return 0;
}

