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
       cin >> a.points_polygon[i];
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

int sign (double a)
{
    if (a > 0.0000001)
       return 1;
    return -1;
}
bool convex (Polygon &a)
{
     int n = a.points_polygon.size();
     int z = sign(vc(a.points_polygon[0]-a.points_polygon[1],a.points_polygon[1]-a.points_polygon[2]));
     for (int i = 1;i < a.points_polygon.size(); ++i)
     {
         if (z != sign(vc(a.points_polygon[i]-a.points_polygon[(i+1)%n],a.points_polygon[(i+1)%n]-a.points_polygon[(i+2)%n])))
            return false;
     }
     return true;
}
int main()
{
    ifstream in;
    ofstream out;

    in.open("polygon.in");
    out.open("polygon.out");

    Polygon a;
    in >> a;
    if (convex(a) == true)
        out << "YES" << endl;
    else
        out<<"NO"<<endl;

   return 0;
}
