#define double long double
typedef double T;
typedef complex<T> pt;
#define x real()
#define y imag()

int quadRoots(double a, double b, double c, pair<double,double> &out) {
    assert(a != 0);
    double disc = b*b - 4*a*c;
    if (disc < 0) return 0;
    double sum = (b >= 0) ? -b-sqrt(disc) : -b+sqrt(disc);
    out = {sum/(2*a), sum == 0 ? 0 : (2*c)/sum};
    return 1 + (disc > 0);
}

pt scale(pt c, double factor, pt p) { return c + (p - c) * factor; }
pt rot(pt p, double a) { return p * polar(1.0l, a); }
pt perp(pt p) { return rot(p, acos(-1) / 2.0); }
pt LT(pt p, pt q, pt r, pt fp, pt fq) { return fp + (r - p) * (fq - fp) / (q - p); }
T cross(pt v, pt w) { return v.x * w.y - v.y * w.x; }
T dot(pt v, pt w) { return v.x * w.x + v.y * w.y; }
double angle(pt v, pt w) { return acosl(clamp(dot(v, w) / (abs(v) * abs(w)), -1.0l, 1.0l)); }
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool inAngle(pt a, pt b, pt c, pt p) {
    //not collinear
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

bool isConvex(vector<pt> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > 0) hasPos = true;
        if (o < 0) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

bool half(pt p) {
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSortAround(pt o, vector<pt> &vec) {
    sort(vec.begin(), vec.end(), [o](pt v, pt w) {
        return make_tuple(half(v - o), 0) <
               make_tuple(half(w - o), cross(v - o, w - o));
    });
}

struct line {
    pt v;
    T c;
    // From direction vector v and offset c
    line(pt v, T c) : v(v), c(c) {
    }

    // From equation ax+by=c
    line(T a, T b, T c) : v({b, -a}), c(c) {
    }

    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {
    }

    // Will be defined later:
    // - these work with T = int
    T side(pt p) { return cross(v, p) - c; }
    double dist(pt p) { return abs(side(p)) / abs(v); }
    line perpThrough(pt p) { return {p, p + perp(v)}; }
    bool cmpProj(pt p, pt q) { return dot(v, p) < dot(v, q); }
    line translate(pt t) { return {v, c + cross(v, t)}; }
    // - these require T = double
    line shiftLeft(double dist) { return {v, c + dist * abs(v)}; }

    pt proj(pt p) { return p - perp(v) * side(p) / norm(v); }
    pt refl(pt p) { return p - perp(v) * 2.0l * side(p) / norm(v); }
};

bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (d == 0) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}

line bisector(line l1, line l2, bool interior) {
    //must not be parallel
    double sign = interior ? 1 : -1;
    return {
        l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign,
        l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign
    };
}

bool inDisk(pt a, pt b, pt p) { return dot(a - p, b - p) <= 0; }

bool onSegment(pt a, pt b, pt p) {
    return orient(a, b, p) == 0 && inDisk(a, b, p);
}

bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    double oa = orient(c, d, a),
            ob = orient(c, d, b),
            oc = orient(a, b, c),
            od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

struct cmpX {
    bool operator()(pt a, pt b) const {
        return make_pair(a.x, a.y) < make_pair(b.x, b.y);
    }
};

set<pt, cmpX> inters(pt a, pt b, pt c, pt d) {
    //size: 0-> no intersection, 1-> intersection at a point, 2-> infinite intersections
    pt out;
    if (properInter(a, b, c, d, out)) return {out};
    set<pt, cmpX> s;
    if (onSegment(c, d, a)) s.insert(a);
    if (onSegment(c, d, b)) s.insert(b);
    if (onSegment(a, b, c)) s.insert(c);
    if (onSegment(a, b, d)) s.insert(d);
    return s;
}

double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p - a), abs(p - b)); // otherwise distance to A or B
}

double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({
        segPoint(a, b, c), segPoint(a, b, d),
        segPoint(c, d, a), segPoint(c, d, b)
    });
}

pt circumCenter(pt a, pt b, pt c) {
    b = b-a, c = c-a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b*norm(c) - c*norm(b))/cross(b,c)/2.0l;
}
int circleLine(pt o, double r, line l, pair<pt,pt> &out) {
    double h2 = r*r - l.dist(o)*l.dist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v*sqrt(h2)/abs(l.v); // vector parallel to l, of length h
        out = {p-h, p+h};
    }
    if(h2>0) return 2;
    if(!h2) return 1;
    return 0;
}

int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt,pt> &out) {
    pt d=o2-o1; double d2=norm(d);
    if (d2 == 0) {assert(r1 != r2); return 0;} // concentric circles
    double pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
    double h2 = r1*r1 - pd*pd/d2; // = hˆ2
    if (h2 >= 0) {
        pt p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    if(h2>0) return 2;
    if(!h2) return 1;
    return 0;
}

int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt,pt>> &out) {
    //to get tangents passing through a point, set r2 to 0 and o2 your point
    if (inner) r2 = -r2;
    pt d = o2-o1;
    double dr = r1-r2, d2 = norm(d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0) {assert(h2 != 0); return 0;}
    for (double sign : {-1,1}) {
        pt v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}

//
// double dist(pair<int, int> a, pair<int, int> b) {
//     return sqrt((double)((a.first - b.first)*(a.first -b.first) + (a.second - b.second)*(a.second-b.second)));
// }
// double side(pair<int,int> p, pair<int,int> v, int c) {
//     //Ax+By=c
//     auto [a,b] = p;
//     auto [x,y] = v;
//     return a*y-b*x-c;
// }
// bool in_rect(double x, double y, double l, double w) {
//     return x >= 0 && x <= l && y >= 0 && y <= w;
// }
//
// tuple<int,int,int> line(pair<int,int> p1, pair<int,int> p2) {
//     //y=mx+c m=y2-y1/x2-x1    x2-x1 y = y2-y1 x + c   (x2-x1) y - (y2-y1) x = c
//     // v=(x2-x1, y2-y1)  a=-dy, b=dx, c = dx*y1 - dy*x1
//     auto [x1,y1] = p1;
//     auto [x2,y2] = p2;
//     int dx = x2-x1;
//     int dy = y2-y1;
//     int g=__gcd(abs(dx), abs(dy));
//     dx/=g; dy/=g;
//     int a=-dy, b=dx, c=dx*y1-dy*x1;
//     // ax+by = c
//     if (a<0 || (a==0 && b<0)) a=-a, b=-b, c=-c;
//     return {a,b,c};
// }
// // tuple<double,double,double> line(pair<double,double> p1, pair<double,double> p2) {
// //     //y=mx+c m=y2-y1/x2-x1    x2-x1 y = y2-y1 x + c   (x2-x1) y - (y2-y1) x = c
// //     // v=(x2-x1, y2-y1)  a=-dy, b=dx, c = dx*y1 - dy*x1
// //     auto [x1,y1] = p1;
// //     auto [x2,y2] = p2;
// //     double dx = x2-x1;
// //     double dy = y2-y1;
// //     double a=-dy, b=dx, c=dx*y1-dy*x1;
// //     // ax+by = c
// //     if (a<0 || (a==0 && b<0)) a=-a, b=-b, c=-c;
// //     return {a,b,c};
// // }
// complex<double> perp(complex<double> p) {
//     return complex<double>(p.imag(), -p.real());
// }
// bool point_segment(int x1, int y1, int x2 , int y2, int x3, int y3) {
//     auto [a,b,c] = line({x2,y2}, {x3,y3});
//     return (a*x1+b*y1==c) && (x1-x2)*(x3-x2)+(y1-y2)*(y3-y2)>=0 && (x1-x3)*(x2-x3)+(y1-y3)*(y2-y3)>=0;
// }
// bool segments_intersect(int x11, int y11, int x12, int y12,
//                         int x21, int y21, int x22, int y22) {
//     int dx1 = x12 - x11;
//     int dy1 = y12 - y11;
//     int dx2 = x22 - x21;
//     int dy2 = y22 - y21;
//     int delta = dx2 * dy1 - dy2 * dx1;
//
//     if (delta == 0) {
//         auto [a,b,c] = line({x11,y11}, {x12,y12});
//         if (a*x21+b*y21==c) {
//             return point_segment(x11,y11,x21,y21,x22,y22)
//             || point_segment(x12,y12,x21,y21,x22,y22)
//             || point_segment(x21,y21,x11,y11,x12,y12)
//             || point_segment(x22,y22,x11,y11,x12,y12);
//         }
//         return false;
//     }
//
//     int s = dx1 * (y21 - y11) + dy1 * (x11 - x21);
//     int t = dx2 * (y11 - y21) + dy2 * (x21 - x11);
//
//     if (delta>0) return (0 <= s && s <= delta) && (0 >= t && t >= -delta);
//     return (0 >= s && s >= delta) && (0 <= t && t <= -delta);
// }
// double dist_to_seg(int x,int y,int x1,int y1,int x2,int y2) {
//     complex<double> start(x1,y1);
//     complex<double> end(x2,y2);
//     complex<double> p(x,y);
//     auto [a,b,c] = line({x1,y1},{x2,y2});
//     complex<double> v(b,-a);
//     double proj_dist = abs(side({x,y}, {b,-a}, -c)/abs(v));
//     double ends_dist = min(abs(p-start), abs(p-end));
//     complex<double> proj_point = p-perp(v)*side({x,y},{b,-a},-c)/norm(v);
//     if ((conj(proj_point-start)*v).real()<0 || (conj(end-proj_point)*v).real()<0)
//         return ends_dist;
//     return proj_dist;
// }
//
// pair<double, double> inter(int x11, int y11, int x12, int y12, int x21, int y21, int x22, int y22) {
//     auto [a1,b1,c1] = line({x11,y11},{x12,y12});
//     auto [a2,b2,c2] = line({x21,y21},{x22,y22});
//     complex<double> v1(b1,-a1),v2(b2,-a2);
//     complex<double> v3 = (double)c1*v2-(double)c2*v1;
//     v3/=(conj(v1)*v2).imag();
//     return {v3.real(), v3.imag()};
// }
//
