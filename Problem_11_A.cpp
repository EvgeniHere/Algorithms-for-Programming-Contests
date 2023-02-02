#include <iostream>
#include <bits/stdc++.h>

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
    return vec2(a.y, -a.x);
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
    disk(vec2 c, lf r) : c(c), r(r) {}
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

int main() {
    lf a, b, c, R;
    cin >> a >> b >> c >> R;

    cout << setprecision(6);
    cout << fixed;

    if (b == 0) {
        cout << a << " " << b << " " << c + R * a << endl;
        cout << a << " " << b << " " << c - R * a << endl;
        return 0;
    }

    lf alpha = angle(perp(vec2(a, b)), vec2(1, 0));

    lf f = b * R / cos(alpha);

    cout << a << " " << b << " " << c + f << endl;

    cout << a << " " << b << " " << c - f << endl;
}
