#include<bits/stdc++.h>
using namespace std;
struct point{
    double x,y;
}p;
struct line{
  point l,r;
}l;
point findIntersection(line l1,line l2){
       
}
vector<point> findBruteForce(vector<line>& lines){
    vector<point> ans;
    for(int i=0;i<lines.size();i++){
        for(int j=i+1;j<lines.size();i++){
            auto curr=findIntersection(lines[i],lines[j]);
            ans.push_back(curr);
        }
    }
}
int main(){
 //given a set of n line segments 
 //we need to find the intersection points of all the lines with each other
 vector<line> lines;//set of all lines
 vector<point> pnts;//set of all end points
  int n;
  double x1,y1,x2,y2;
 cin>>n;
 for(int i=0;i<n;i++){
     cin>>x1>>y1>>x2>>y2;
     line line1;
     point p1;
     p1.x=x1;
     p1.y=y1;
     point p2;
     p2.x=x2;
     p2.y=y2;
     line1.l=p1;
     line1.r=p2;
     pnts.push_back(p1);
     pnts.push_back(p2);
     lines.push_back(line1);
 }
 findBruteForce(lines);
 
 
}