#include <iostream>
#include <bits/stdc++.h>

# define M_PI           3.14159265358979323846

using namespace std;

typedef double lf;

const lf EPSI = 1e-10, INF = numeric_limits<lf>::infinity();
bool equal(lf x, lf y) { return abs(x - y) < EPSI; }


//---------------------------VECTOR-STUFF---------------------------------
struct vec2 {
    lf x, y;
    vec2() : x(0), y(0) {}
    vec2(lf x, lf y) : x(x), y(y) {}
    vec2& operator+=(const vec2& o) { x += o.x; y += o.y; return *this; }
    vec2& operator-=(const vec2& o) { x -= o.x; y -= o.y; return *this; }
    vec2& operator*=(const lf& o) { x *= o; y *= o; return *this; }
    vec2& operator/=(const lf& o) { x /= o; y /= o; return *this; }
    friend vec2 operator+(vec2 a, const vec2& b) { return a += b; }
    friend vec2 operator-(vec2 a, const vec2& b) { return a -= b; }
    friend vec2 operator*(vec2 a, const lf& b) { return a *= b; }
    friend vec2 operator*(const lf& b, vec2 a) { return a *= b; }
    friend vec2 operator/(vec2 a, const lf& b) { return a /= b; }
    friend bool operator==(const vec2& a, const vec2& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const vec2& a, const vec2& b) { return !(a == b); }
    friend ostream& operator<<(ostream& out, const vec2 v) {
        return out << "(" << v.x << "," << v.y << ")";
    }
};

template<typename T>
lf dist(vec2 a, T l);

// error value for vec2
const vec2 novec2 = vec2(INF, INF);
// dot product
lf dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}
// cross product
lf cross(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}
// get a vector perpendicular to a (rotated by 90deg)
vec2 perp(vec2 a) {
    return vec2(-a.y, a.x);
}
// squared length
lf norm_sqr(vec2 a) {
    return dot(a, a);
}
// actual length
lf norm(vec2 a) {
    return sqrt(norm_sqr(a));
}
// squared distance
lf dist_sqr(vec2 a, vec2 b) {
    return norm_sqr(a - b);
}
// actual distance
lf dist(vec2 a, vec2 b) {
    return norm(a - b);
}
// smallest angle between vectors a, b
lf angle(vec2 a, vec2 b) {
    return acos(dot(a, b) / (norm(a) * norm(b)));
}
// counter-clockwise angle between vectors a, b
lf full_angle(vec2 a, vec2 b) {
    return atan2(cross(a, b), dot(a, b));
}
// check whether angle between vectors a, b is acute
bool angle_acute(vec2 a, vec2 b) {
    return dot(a, b) > 0;
}
// check whether angle between vectors a, b is obtuse
bool angle_obtuse(vec2 a, vec2 b) {
    return dot(a, b) < 0;
}
// check whether a, b, c lie counter-clockwise
bool cw(vec2 a, vec2 b, vec2 c) {
    return cross(a - b, c - b) >= EPSI;
}
// check whether a, b, c lie clockwise
bool ccw(vec2 a, vec2 b, vec2 c) {
    return cross(a - b, c - b) <= -EPSI;
}
// get signed angle between a and b
lf signed_angle(vec2 a, vec2 b) {
    return atan2(cross(a, b), dot(a, b));
}
// check if a, b, c lie on the same line
bool colinear(vec2 a, vec2 b, vec2 c) {
    return abs(cross(a - b, c - b)) < EPSI;
}

//----------------------------LINE-STUFF----------------------------------

struct line {
    vec2 n;
    lf c;
    line(vec2 n, lf c) : n(n), c(c) {}
    // construct line through a and b
    line(vec2 a, vec2 b) {
        n = perp(a - b);
        c = dot(a, n);
    }
    lf operator()(vec2 a) {
        return dot(a, n) - c;
    }
};

vec2 project(vec2 a, line l) {
    return a - (dot(l.n, a) - l.c) / norm_sqr(l.n) * l.n;
}
line normalize(line l) {
    lf len = norm(l.n);
    return line(l.n / len, l.c / len);
}
lf dist(line l, vec2 a) {
    return abs(normalize(l)(a));
}
bool parallel(line l, line s) {
    return abs(cross(l.n, s.n)) < EPSI;
}
bool equivalent(line l, line s) {
    return parallel(l, s) && norm(l.n * s.c - s.n * l.c) < EPSI;
}
vec2 intersect(line l, line s) {
    if (parallel(l, s))
        return equivalent(l, s) ? project(vec2(0, 0), l) : novec2;
    return (s.c * perp(l.n) - l.c * perp(s.n)) / cross(l.n, s.n);
}

//-----------------------------RAY-STUFF----------------------------------
struct ray {
    vec2 a, b;
    ray(vec2 a, vec2 b) : a(a), b(b) {}
};

vec2 project(vec2 a, ray r) {
    lf d = max(0., dot(r.b - r.a, a - r.a) / norm_sqr(r.b - r.a));
    return r.a + d * (r.b - r.a);
}

//-----------------------------SEG-STUFF----------------------------------
struct seg {
    vec2 a, b;
    seg(vec2 a, vec2 b) : a(a), b(b) {}
};

vec2 project(vec2 a, seg s) {
    if (dist(s.a, s.b) < EPSI)
        return s.a;
    lf d = min(max(0., dot(s.b - s.a, a - s.a) / norm_sqr(s.b - s.a)), 1.);
    return s.a + d * (s.b - s.a);
}
vec2 intersect(line l, seg s) {
    if (abs(dot(l.n, s.b - s.a)) >= EPSI) {
        vec2 a = intersect(l, line(s.a, s.b));
        if (a != novec2 && dist(a, s) < EPSI)
            return a;
    }
    else if (dist(s.a, l) < EPSI) {
        return s.a;
    }
    return novec2;
}

//----------------------------DISK-STUFF----------------------------------
struct disk {
    vec2 c;
    lf r;
    int index;
    bool accessable;
    disk(vec2 c, lf r) : c(c), r(r), index(0), accessable(false) {}
    disk(vec2 c, lf r, int index, bool accessable) : c(c), r(r), index(index), accessable(accessable) {}
};

seg project(disk d, line l) {
    vec2 a = project(d.c, l);
    vec2 r = perp(l.n) / norm(l.n) * d.r;
    return seg(a + r, a - r);
}
seg intersect(disk d, line l) {
    vec2 a = project(d.c, l);
    lf rr = d.r * d.r - dist_sqr(d.c, a);
    if (rr < 0)
        return seg(novec2, novec2);
    vec2 r = sqrt(rr) * perp(l.n) / norm(l.n);
    return seg(a + r, a - r);
}

//----------------------------GENERAL----------------------------------
template<typename T>
lf dist(vec2 a, T l) {
    return dist(a, project(a, l));
}

bool onSegment(vec2 p, vec2 q, vec2 r) {
    return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
}

int orientation(vec2 p, vec2 q, vec2 r) {
    lf val = (q.y - p.y) * (r.x - q.x) -
        (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;

    return (val > 0) ? 1 : 2;
}

bool doIntersect(vec2 p1, vec2 q1, vec2 p2, vec2 q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

int n, d;
vector<disk> lilies;

struct edge {
    int u, cost;
};

vector<edge> edges[1000];

int used[1000];
vector<int> dd(1000);

void dijkstra_set(int s, int n) {
    fill(dd.begin(), dd.end(), 1e9);
    dd[s] = 0;
    set <pair <int, int > > dst;
    dst.insert({ dd[s], s });
    while (!dst.empty()) {
        int v = dst.begin()->second;
        dst.erase(dst.begin());
        for (auto e : edges[v])
            if (dd[v] + e.cost < dd[e.u]) {
                dst.erase({ dd[e.u], e.u });
                dd[e.u] = dd[v] + e.cost;
                dst.insert({ dd[e.u], e.u });
            }
    }
}

int main() {
    //cout << setprecision(6);
    //cout << fixed;

    int pond_x, pond_y;

    cin >> pond_x >> pond_y >> n;

    for (int i = 0; i < n; i++) {
        lf x, y, r;
        cin >> x >> y >> r;

        disk lilie = disk(vec2(x, y), r);

        lilie.index = i;

        lilies.push_back(lilie);
    }

    cin >> d;

    int minJumps = 1e9;

    for (int i = 0; i < (int)lilies.size(); i++) {
        for (int j = i + 1; j < (int)lilies.size(); j++) {
            if (i == j)
                continue;

            lf jmp_dist = dist(lilies[i].c, lilies[j].c) - (lilies[i].r + lilies[j].r);

            if (jmp_dist > d)
                continue;

            edges[i].push_back({ j, jmp_dist > 0 });
            edges[j].push_back({ i, jmp_dist > 0 });
        }
    }

    for (int i = 0; i < (int)lilies.size(); i++) {
        disk lilie = lilies[i];

        lf bottom_dist = lilie.c.y;
        lf left_dist = lilie.c.x;
        lf right_dist = pond_x - lilie.c.x;
        lf top_dist = pond_y - lilie.c.y;

        lf pond_jmp_dist = min(bottom_dist, min(left_dist, min(right_dist, top_dist))) - lilie.r;

        if (pond_jmp_dist > d)
            continue;

        dijkstra_set(i, n - 1);

        int traversed_minJumps = dd[n - 1];

        minJumps = min(minJumps, pond_jmp_dist > 0 ? traversed_minJumps + 1 : traversed_minJumps);
    }

    if (minJumps == 1e9)
        cout << ":(" << endl;
    else
        cout << minJumps << endl;

    return 0;
}
