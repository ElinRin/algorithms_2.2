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

class Polygon
{
     public:
       vector<Point> points_polygon;
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


istream &operator >> (istream &cin, Polygon &a)
{
   int n;
   cin>>n;
   a.points_polygon.resize(n);
   int i;
   for (i=0;i<n;++i)
       cin>>a.points_polygon[i];
   return cin;
}
ostream &operator << (ostream &cout, Polygon &a)
{
    cout<<a.points_polygon.size()<<endl;
    int i;
    for (i=0;i<a.points_polygon.size();++i)
    {
        cout<<a.points_polygon[i]<<endl;
    }
    return cout;
}

double vc (Point a,Point b)//[a,b]=|a||b|sinA
{
       return a.x*b.y-a.y*b.x;
}

double area_triangle (Point a,Point b,Point c)
{
      return (vc(a-b,a-c))/2;
}
double area (Polygon &a)
{
     int i;
     double s = 0;
     for (i=1;i<a.points_polygon.size()-1;++i)
     {
         s = s + area_triangle(a.points_polygon[i],a.points_polygon[i+1],a.points_polygon[0]);
     }
     return s;
}

int main()
{
    ifstream in;
    ofstream out;

    in.open("area.in");
    out.open("area.out");

   Polygon a;
   in >> a;
   out << abs(area(a)) << endl;
   return 0;
}
