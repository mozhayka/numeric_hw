#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <sstream>
#include <cassert>

using namespace std;

struct point
{
    float x, y;
};

string print_point(point a)
{
    stringstream ss;
    ss << "(" << a.x << ", " << a.y << ")";
    return ss.str();
}

bool operator==(point p1, point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

point operator-(point p1, point p2)
{
    return {p1.x - p2.x, p1.y - p2.y};
}

float vector_product(point a, point b)
{
    return a.x * b.y - a.y * b.x;
}

float edge_order(point a, point b, point p)
{
    return vector_product((a - p), (b - p));
}

bool is_on_segment(float left, float right, float mid)
{
    if (left > right)
    {
        swap(left, right);
    }
    return left <= mid && mid <= right;
}

bool is_inside_rectangle(point a, point b, point p)
{
    return is_on_segment(a.x, b.x, p.x) && is_on_segment(a.y, b.y, p.y);
}

int point_order(vector<point> polygon, point p)
{
    int order = 0;
    for (int i = 0; i < polygon.size(); i++)
    {
        point a = polygon[i];
        point b = polygon[(i + 1) % polygon.size()];

        double t = edge_order(a, b, p);
        if (a.y <= p.y && p.y < b.y && t > 0)
        {
            order++;
        }
        if (b.y <= p.y && p.y < a.y && t < 0)
        {
            order--;
        }
        if (t == 0 && is_inside_rectangle(a, b, p)) 
        { // без этого в случае с точкой на границе может вернуться 0
            return -1;
        }
    }
    return order;
}

/// Triangulation

struct triangle
{
    point a, b, c;
};

string print_triangle(triangle t)
{
    stringstream ss;
    ss << "[" << print_point(t.a) << ", " << print_point(t.b) << ", " << print_point(t.c) << "]";
    return ss.str();
}

int point_order(triangle t, point p)
{
    vector<point> polygon {t.a, t.b, t.c};
    return point_order(polygon, p);
}

bool is_inside(triangle t, point p)
{
    return point_order(t, p) != 0;
}

bool is_ear(triangle ear, vector<point> polygon)
{
    for (auto vertex: polygon)
    {
        if (vertex == ear.a || vertex == ear.b || vertex == ear.c)
        {
            continue;
        }

        if (is_inside(ear, vertex))
        {
            return false;
        }
    }
    return true;
}

bool is_convex(point prev, point cur, point next)
{
    return vector_product(cur - prev, cur - next) > 0;
}

vector<triangle> triangulation(vector<point> polygon)
{
    int triangles_cnt = polygon.size();
    vector<triangle> triangles;
    for (int i = 0; i < triangles_cnt - 2; i++)
    {
        int n = polygon.size();
        for (int i = 0; i < n; i++)
        {
            point prev = polygon[(i + n - 1) % n];
            point cur = polygon[i];
            point next = polygon[(i + 1) % n];

            if (is_convex(prev, cur, next))
            {
                triangle ear = {prev, cur, next};
                if (is_ear(ear, polygon))
                {
                    triangles.push_back(ear);
                    polygon.erase(polygon.begin() + i);
                    break;
                }
            }
        }
    }
    return triangles;
}

void test1()
{
    cout << "test 1" << endl;
    vector<point> polygon = 
    {
        {0, 0},
        {0, 1.5},
        {1.5, 1.5},
        {1, 1},
        {1.5, 0}
    };

    vector<triangle> ans = triangulation(polygon);
    for (auto triangle: ans)
    {
        cout << print_triangle(triangle) << endl;
    }
}

void test2()
{
    cout << "test 2" << endl;
    vector<point> polygon = 
    {
        {0, 0},
        {0, 1.5},
        {1.5, 1.5},
        {0.75, 0.75},
        {1.5, 0}
    };

    vector<triangle> ans = triangulation(polygon);
    for (auto triangle: ans)
    {
        cout << print_triangle(triangle) << endl;
    }
}

int main()
{
    test1();
    test2();
}
