template<class T> struct Point {
    T x;
    T y;

    explicit Point(T x_ = 0, T y_ = 0): x(x_), y(y_) {
    }

    template<class U> explicit operator Point<U>() {
        return Point<U>(U(x), U(y));
    }

    Point& operator+=(Point p)& {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(Point p)& {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point& operator*=(T v)& {
        x *= v;
        y *= v;
        return *this;
    }

    Point operator-() const {
        return Point(-x, -y);
    }

    friend Point operator+(Point a, Point b) {
        return a += b;
    }

    friend Point operator-(Point a, Point b) {
        return a -= b;
    }

    friend Point operator*(Point a, T b) {
        return a *= b;
    }

    friend Point operator*(T a, Point b) {
        return b *= a;
    }

    friend bool operator==(Point a, Point b) {
        return a.x == b.x && a.y == b.y;
    }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        return is >> p.x >> p.y;
    }

    friend std::ostream& operator<<(std::ostream& os, Point p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T> T dot(Point<T> a, Point<T> b) {
    return a.x * b.x + a.y * b.y;
}

template<class T> T cross(Point<T> a, Point<T> b) {
    return a.x * b.y - a.y * b.x;
}

template<class T> T square(Point<T> p) {
    return dot(p, p);
}

template<class T> double length(Point<T> p) {
    return std::sqrt(double(square(p)));
}

long double length(Point<long double> p) {
    return std::sqrt(square(p));
}

template<class T> struct Line {
    Point<T> a;
    Point<T> b;

    explicit Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()): a(a_), b(b_) {
    }
};

template<class T> Point<T> rotate(Point<T> a) {
    return Point(-a.y, a.x);
}

template<class T> int sgn(Point<T> a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T> bool pointOnLineLeft(Point<T> p, Line<T> l) {
    return cross(l.b - l.a, p - l.a) > 0;
}

template<class T> Point<T> lineIntersection(Line<T> l1, Line<T> l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}

template<class T> bool pointOnSegment(Point<T> p, Line<T> l) {
    return cross(p - l.a, l.b - l.a) == 0 && std::min(l.a.x, l.b.x) <= p.x && p.x <= std::max(l.a.x, l.b.x) && std::min(
            l.a.y, l.b.y) <= p.y && p.y <= std::max(l.a.y, l.b.y);
}

template<class T> bool pointInPolygon(Point<T> a, std::vector<Point<T>> p) {
    int n = p.size();
    for(int i = 0; i < n; i++) {
        if(pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }

    int t = 0;
    for(int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if(u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u))) {
            t ^= 1;
        }
        if(u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v))) {
            t ^= 1;
        }
    }

    return t == 1;
}