#include <cmath>
#include <iostream>
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
    // return format("({}, {})", a.x, a.y);
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

void test1()
{
    vector<point> polygon =
    {
        {0, 0},
        {0, 1.5},
        {1.5, 1.5},
        {1, 1},
        {1.5, 0}
    };
    point inner_point = {0.5, 0.5};
    point outer_point = {2, 2};
    point edge_point = {0, 1};

    cout << "Point order for inner point " << print_point(inner_point) << " is " << point_order(polygon, inner_point) << endl;
    cout << "Point order for outer point " << print_point(outer_point) << " is " << point_order(polygon, outer_point) << endl;
    cout << "Point order for edge point " << print_point(edge_point) << " is " << point_order(polygon, edge_point) << endl;

}

void test2()
{
    vector<point> polygon =
    {
        {0, 0},
        {0, 2},
        {2, 0}
    };
    point edge_point = {1, 1};
    assert(point_order(polygon, edge_point) != 0);
}

int main()
{
    test1();
    test2();
}