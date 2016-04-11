#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
struct point
{
       double x,y;
       friend point operator - (point a,point b)
       {
             a.x=a.x-b.x;
             a.y=a.y-b.y;
             return a;
       }
       friend point operator + (point a,point b)
       {
             a.x=a.x+b.x;
             a.y=a.y+b.y;
             return a;
       }
       bool operator == (point b)
    {
        if (x==b.x && y==b.y)
            return true;
        return false;
    }
};
struct line
{
      double a,b,c;
      line (point a1,point b1)
      {
          a=b1.y-a1.y;
          b=a1.x-b1.x;
          c=a1.x*(a1.y-b1.y)+a1.y*(b1.x-a1.x);
      }
      line(){}
};
struct triangle
{
       point a,b,c;
};
struct circle
{
       point a;
       double r;
};
istream &operator >> (istream &cin, point &a)
{
   cin>>a.x>>a.y;
   return cin;
}
ostream &operator << (ostream &cout, point &a)
{
    cout<<a.x<<" "<<a.y<<" ";
    return cout;
}
istream &operator >> (istream &cin, line &a)
{
   cin>>a.a>>a.b>>a.c;
   return cin;
}
ostream &operator << (ostream &cout, line &a)
{
    cout<<a.a<<" "<<a.b<<" "<<a.c<<" ";
    return cout;
}
istream &operator >> (istream &cin, triangle &a)
{
   cin>>a.a>>a.b>>a.c;
   return cin;
}
ostream &operator << (ostream &cout, triangle &a)
{
    cout<<a.a<<" "<<a.b<<" "<<a.c<<" ";
    return cout;
}
istream &operator >> (istream &cin, circle &a)
{
   cin>>a.a>>a.r;
   return cin;
}
ostream &operator << (ostream &cout, circle &a)
{
    cout<<a.a<<" "<<a.r;
    return cout;
}
point VECTOR (point a,point b)
{
      return a-b;
}
double RR (point a,point b)
{
       return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double ck (point a,point b)//(a,b)=|a||b|cosA
{
       return a.x*b.x+a.y*b.y;
}
double vc (point a,point b)//[a,b]=|a||b|sinA
{
       return a.x*b.y-a.y*b.x;
}
double _tg (point a,point b)
{
      return vc(a,b)/ck(a,b);
}
double S_triangle (point a,point b,point c)
{
      return (vc(a-b,a-c))/2;
}
double S (vector <point> &brr)
{
     int i;
     brr.push_back(brr[0]);
     point o;
     o.x=0;
     o.y=0;
     double S1;
     for (i=1;i<brr.size();++i)
     {
         S1=S1+S_triangle(brr[i-1],brr[i],o);
     }
     return S1;
}
point POINT_line (line a,double k)
{
      point o;
      if (a.b!=0)
      {
          o.x=k;
          o.y=(-a.c-o.x*a.a)/a.b;
      }
      else
      {
          o.y=k;
          o.x=(-a.c-o.y*a.b)/a.a;
      }
      return o;
}
point Line_Line (line o,line q)
{
    point a;
    if (o.b*q.a-q.b*o.a==0)
        a.y=0;
    else
        a.y=(q.c*o.a-o.c*q.a)/(o.b*q.a-q.b*o.a);
    if (q.a!=0)
        a.x=(-q.b*a.y-q.c)/q.a;
    else
        a.x=(-o.b*a.y-o.c)/o.a;
    return a;
}
bool Prinad_point_line (point a,line b)
{
    if (b.a*a.x+b.b*a.y+b.c==0)
        return true;
    return false;
}
bool Prinad_point_otr (point a,point b,point c)
{
    if (Prinad_point_line(a,line(b,c))==false)
        return false;
    if (a.x>=min(b.x,c.x) && a.x<=max(b.x,c.x) && a.y>=min(b.y,c.y) && a.y<=max(b.y,c.y))
        return true;
    return false;
}
double R_Line_Point (point a, line b)
{
    point q=POINT_line(b,-2231);
    point w=POINT_line(b,100222);
    return abs(vc(q-a,w-a))/sqrt(RR(q,w));
}
double Ugol (point a)
{
    double c=atan2(a.y,a.x);
    if (c<0)
        c=c+M_PI*2;
    return c;
}
int Vector_classif (point a,point b)
{
   if (vc(a,b)==0)
   {
      return 1;
   }
   if (ck(a,b)==0)
   {
      return 2;
   }
   return 0;
}
line point_vector (point a,point b)
{
     line q;
     q.a=b.x;
     q.b=b.y;
     q.c=-(q.a*a.x+q.b*a.y);
     return q;
}
double zn_line_point(line a,point b)
{
    return a.a*b.x+a.b*b.y+a.c;
}
bool  PR_point_luch(point c,point a,point b)
{
     point d=b-a,e=c-a;
     line q(a,b);
     if (Prinad_point_line(c,q)==true && ck(d,e)>=0)
        return true;
     return false;
}
bool  PR_point_otrezok(point c,point a,point b)
{
     if (PR_point_luch(c,a,b)==true && PR_point_luch(c,b,a)==true)
        return true;
     return false;
}
line line_na_R(line a,double r)
{
    point q,w,z;
    q=POINT_line(a,179);
    w=POINT_line(a,878);
    z.x=a.a;
    z.y=a.b;
    double d=sqrt(z.x*z.x+z.y*z.y);
    z.x=(z.x/d)*r;
    z.y=(z.y/d)*r;
    q=q-z;
    w=w-z;
    return line(q,w);
}
line perpendikular_line (line a,point b)
{
     line q;
     q.a=a.b;
     q.b=-a.a;
     q.c=-(q.a*b.x+q.b*b.y);
     return q;
}
bool otr_otr (point a,point b,point q,point w)
{
     line k=line(a,b);
     line l=line(q,w);
     if (zn_line_point(l,a)*zn_line_point(l,b)*zn_line_point(k,q)*zn_line_point(k,w)==0)
     {
         if (PR_point_otrezok(a,q,w)==true || PR_point_otrezok(b,q,w)==true || PR_point_otrezok(q,a,b)==true || PR_point_otrezok(w,a,b)==true)
            return true;
         return false;
     }
     if (zn_line_point(l,a)*zn_line_point(l,b)<0 && zn_line_point(k,q)*zn_line_point(k,w)<0)
        return true;
     return false;
}
line bissectr (point a,point b,point c)
{
     point q=b-a;
     point w=c-a;
     double r=sqrt(RR(c,a)),p=sqrt(RR(b,a));
     w.x=(w.x/r)*10;
     w.y=(w.y/r)*10;
     q.x=(q.x/p)*10;
     q.y=(q.y/p)*10;
     q=a+q;
     w=a+w;
     b.x=(q.x+w.x)/2;
     b.y=(q.y+w.y)/2;
     return line(a,b);
}
point triangle_bissectr(triangle a)
{
      line q=bissectr(a.a,a.b,a.c);
      line w=bissectr(a.b,a.a,a.c);
      return Line_Line(q,w);
}
line s_perpend(point a,point b)
{
     point m=a+b;
     m.x/=2;
     m.y/=2;
     return perpendikular_line(line(a,b),m);
}
point triangle_s_perpend(triangle a)
{
      line q=s_perpend(a.a,a.b);
      line w=s_perpend(a.c,a.b);
      return Line_Line(q,w);
}
bool polozhenie_point_line(line q,point a,point b)
{
     if (zn_line_point(q,a)*zn_line_point(q,b)>=0)
        return true;
     return false;
}
bool triangle_point (triangle a,point q)
{
    if (polozhenie_point_line(line(a.a,a.b),q,a.c) && polozhenie_point_line(line(a.a,a.c),q,a.b) && polozhenie_point_line(line(a.b,a.c),q,a.a))
       return true;
    return false;
}
double R_circle_line (circle c,line a)
{
       double r=R_Line_Point(c.a,a);
       if (r<=c.r-0.00001)
          return 0;
       return r-c.r;
}
double Ugol_circle (circle c,point a)
{
     return 2*asin(c.r/sqrt(RR(c.a,a)));
}
point povorot_vector(point a,double u)
{
      double R=sqrt(a.x*a.x+a.y*a.y);
      double q=Ugol(a);;
      q+=u;
      a.x=cos(q)*R;
      a.y=sin(q)*R;
      return a;
}
line povorot_line(line a,double u)
{
      point q=POINT_line(a,3),w=POINT_line(a,19);
      q=povorot_vector(q,u);
      w=povorot_vector(w,u);
      return line(q,w);
}
int pr_point_krug(circle c,point a)
{
     if (RR(a,c.a)==c.r*c.r)
        return 1;
     if (RR(a,c.a)<c.r*c.r+0.00000001)
        return 0;

     return 2;
}
vector<point> kasatelnaia (circle c,point a)
{
    vector<point> arr;
    if (pr_point_krug(c,a)==0)
       return arr;
    if  (pr_point_krug(c,a)==1)
    {
       arr.push_back(a);
       return arr;
    }
    double u=acos(c.r/sqrt(RR(a,c.a)));
    point z;
    z=povorot_vector(a-c.a,u);
    z.x=(z.x/sqrt(RR(a,c.a)))*c.r;
    z.y=(z.y/sqrt(RR(a,c.a)))*c.r;
    arr.push_back(c.a+z);
    z=povorot_vector(a-c.a,M_PI*2-u);
    z.x=(z.x/sqrt(RR(a,c.a)))*c.r;
    z.y=(z.y/sqrt(RR(a,c.a)))*c.r;
    arr.push_back(c.a+z);
    return arr;
}
int main()
{
   circle a;
   point b;
   cin>>a>>b;
   cout.precision(20);
   vector<point> brr=kasatelnaia(a,b);
   int i;
   cout<<brr.size()<<endl;
   for (i=0;i<brr.size();++i)
       cout<<brr[i]<<endl;
   //system ("pause");
   return 0;
}
