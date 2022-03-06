#include<bits/stdc++.h>
using namespace std;
typedef struct{
    double x,y;
}point;
typedef struct{
  point l,r;
}line;
bool onSegment(point p, point q, point r){
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
    return false;
}
 
// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are collinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(point p, point q, point r){
    // See https://www.geeksforgeeks.org/orientation-3-ordered-points/
    // for details of below formula.
    double val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // collinear
    double epsilon = 0.0000001;
    // if(abs(val) < epsilon){
    //     return 0;
    // }
 
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
// The main function that returns true if line segment 'p1q1'
// and 'p2q2' intersect.
bool doIntersect(point p1, point q1, point p2, point q2){
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are collinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and q2 are collinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are collinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are collinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}
point lineLineIntersection(point A, point B, point C, point D){
    // Line AB represented as a1x + b1y = c1
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1*(A.x) + b1*(A.y);
  
    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2*(C.x)+ b2*(C.y);
  
    double determinant = a1*b2 - a2*b1;
    point ans;
    if (determinant == 0){
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        ans.x = FLT_MAX;
        ans.y = FLT_MAX;
    }
    else{

        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        ans.x = x;
        ans.y = y;
    }
    return ans;
}
point findIntersection(line l1,line l2){
    point ans;
    ans = lineLineIntersection(l1.l, l1.r, l2.l, l2.r);
    return ans;
}
vector<point> findBruteForce(vector<line>& lines){
    vector<point> ans;
    for(int i=0;i<lines.size();i++){
        for(int j=i+1;j<lines.size();j++){
            bool isint = doIntersect(lines[i].l, lines[i].r, lines[j].l, lines[j].r);
            cout<<isint<<"ADF"<<endl;
            if(isint == true){
                point curr;
                curr=findIntersection(lines[i],lines[j]);
                ans.push_back(curr);
            }
        }
    }
    return ans;
}
void printAns(vector<line>& lines){
    vector<point> ans = findBruteForce(lines);
    cout<<ans.size()<<endl;
    for(auto it: ans){
        cout<<"( "<<it.x<< " + "<<it.y <<" )"<<endl;
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
 //cout<<lines.size()<<" adsf"<<endl;
 //findBruteForce(lines);
 printAns(lines);
 
}