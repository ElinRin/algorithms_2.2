#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>


using namespace std;

class Point
{
    public:
        long long x;
        long long y;
        Point(long long X=0, long long Y=0): x(X), y(Y) {}

        Point operator+(Point const&r) { return Point(x+r.x,y+r.y); }
        Point operator-(Point const&r) { return Point(x-r.x,y-r.y); }
        Point operator*(long long r) { return Point(x*r,y*r); }
        Point operator/(long long r) { return Point(x/r,y/r); }
        bool operator < (const Point &r)  const { return make_pair (x,y) < make_pair (r.x,r.y); }
        bool operator > (const Point &r)  const { return make_pair (x,y) > make_pair (r.x,r.y); }

        long long sqlen() { return x*x+y*y; }
        long long len() { return sqrt(sqlen()); }
};
class Polygon
{
    public:
       vector<Point> points_polygon;
       Polygon() {}
       Polygon(vector<Point> a): points_polygon(a) {}
};

class Convex_polygon
{
public:
    Polygon convex_points;

	Convex_polygon() {}
	Convex_polygon(int size){
        for(int i = 0; i < size; ++i)
        {
            convex_points.points_polygon[i].y = rand() % size*2;
            convex_points.points_polygon[i].x = rand() % size*2;
        }
    }
	Convex_polygon(Polygon &data);
	void Print(Convex_polygon a);
	~Convex_polygon(){}

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
    for (int i=0;i<a.points_polygon.size();++i)
    {
        cout<<a.points_polygon[i]<<endl;
    }
    return cout;
}



bool compare (Point a, Point b)
{
	return (a.x < b.x) || (a.x == b.x && a.y < b.y);
}

long long rotate(Point &a, Point &b, Point &c) {
    return (a.y - b.y)*(c.x - b.x) - (a.x - b.x)*(c.y - b.y);
}

Convex_polygon::Convex_polygon(Polygon &hull)
{
	sort(hull.points_polygon.begin(), hull.points_polygon.end(), &compare);

	vector<Point> data;
    for (int i = 0; i < hull.points_polygon.size(); ++i)
    {
        while ((data.size() > 1) && (rotate(data[data.size() - 2], data[data.size() - 1], hull.points_polygon[i]) <= 0))
        {
            data.pop_back();
        }
        data.push_back(hull.points_polygon[i]);
    }

    int flag = 1;
    for (int i = hull.points_polygon.size() - 2; i >= 0; --i)
    {
        while ((flag > 1) && (rotate(data[data.size() - 2], data[data.size() - 1], hull.points_polygon[i]) <= 0))
        {
            data.pop_back();
            --flag;;
        }
        data.push_back(hull.points_polygon[i]);
        ++flag;
    }

    while ((data.size() > 2) && ((rotate(data[data.size() - 1], data[0], data[1]) <= 0) ||
                           (rotate(data[data.size() - 2], data[data.size() - 1], data[0]) <= 0)))
    {
        data.pop_back();
    }

    convex_points = Polygon(data);
}

int main() {

    ifstream in;
    ofstream out;

    in.open("hull.in");
    out.open("hull.out");

    Polygon points;
    in >> points;
    Convex_polygon a(points);
    out << a.convex_points.points_polygon.size() << endl;
    for(int i = 0; i < a.convex_points.points_polygon.size(); ++i)
	{
		out << a.convex_points.points_polygon[i].x << " " << a.convex_points.points_polygon[i].y << endl;
	}

    return 0;
}
