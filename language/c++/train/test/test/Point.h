#pragma once
#include <iostream>

using namespace std;

namespace pt
{
    class Point2d
    {
    public:
        virtual void print() { cout << "Point2d print\n"; }
    };

    class Point3d : public virtual Point2d
    {
    public:
        virtual void print() { cout << "Point3d print\n"; }
        static float normalize() {
            cout << "normalize return 1.0\n"; 
            return 1.0; 
            }
    };

    class Vertex : public virtual Point2d
    {
    public:
        virtual void print() { cout << "Vertex print\n"; }
    };

    class Vertex3d : public Point3d, public Vertex
    {
    public:
        virtual void print() { cout << "Vertex3d print\n"; }
    };

    class Base1
    {
        public:
        int val1;
    };

    class Base2
    {
        public:
        int val2;
    };

    class Derived : public Base1, public Base2
    {
        public:
        int val3;
    };

    void func1(int Derived::*dmp, Derived *pd);
    void func2(Derived *pd);
    void printOffset();

}

namespace pt2
{
    class Point1d
    {
    public:
        virtual void print() { cout << "Point1d print\n"; }

    public:
        float x;
    };

    class Point2d
    {
    public:
        virtual void print() { cout << "Point2d print\n"; }

    public:
        float y;
    };

    class Point3d
    {
    public:
        virtual void print() { cout << "Point3d print\n"; }

    public:
        // static Point2d p2d;
        float x, y, z;
    };

}
