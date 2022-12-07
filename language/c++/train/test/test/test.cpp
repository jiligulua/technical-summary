#include <stdio.h>
#include "Container.h"
#include "BaseFeature.h"
// #include "Point3d.h"
#include "Point.h"

int main()
{
    printf("Hello World!");
    // system("pause");
    Container c;
    c.testVector();

    pt::Vertex3d v3d;
    pt::Point3d *p = &v3d;
    p->print();

    {
        pt2::Point3d p3d;

        cout << "pt2 Point3d object address : " << &p3d << endl;
        cout << "pt2 Point3d object x memeber offset: " << &p3d.x << endl;
        cout << "pt2 Point3d object y memeber offset: " << &p3d.y << endl;
        cout << "pt2 Point3d object z memeber offset: " << &p3d.z << endl;

        cout << "pt2 Point3d x memeber offset: " << &pt2::Point3d::x << endl;
        cout << "pt2 Point3d y memeber offset: " << &pt2::Point3d::y << endl;
        cout << "pt2 Point3d z memeber offset: " << &pt2::Point3d::z << endl;

        printf("&Point3d::x = %p\n", &pt2::Point3d::x);
        printf("&Point3d::y = %p\n", &pt2::Point3d::y);
        printf("&Point3d::z = %p\n", &pt2::Point3d::z);

        float pt2::Point3d::*p1 = &pt2::Point3d::x;
        float pt2::Point3d::*p2 = &pt2::Point3d::y;
        if (p1 == p2)
        {
            cout << "p1 & p2 same\n";
        }
        else
        {
            cout << "p1 & p2 is note same\n";
        }
        printf("x and y address are: %p and %p\n", p1, p2);

        float *px = &p3d.x;

        printf("sizeof pt2::Point3d is: %ld\n", sizeof(pt2::Point3d));

        printf("sizeof float is: %ld\n", sizeof(float));
        printf("alignof pt2::Point3d: %ld\n", alignof(pt2::Point3d));
    }

    {
        pt::printOffset(); 
        pt::Point3d p3d;
        p3d.normalize();
        pt::Point3d *pp3d = &p3d;
    }

    A a;
    a.testForeach();
    a.testUniquePtr();
    a.testSharePtr();
    a.testWeakPtr();
    a.testLoopReference();
    a.testLambda();
    a.testC99();
    a.testPrintf();
    a.testMacro();
    a.testUnicodeLib();
    a.testUnicodeLib2();

    // Point3d p3d;
    // Point3d::length mu = p3d.mumble();

    return 0;
}