#include<iostream>
#include<conio.h>
#include "../Files/Headers/vector2D.h"
using namespace std;
int main()
{
    Vint2 v1, v2;
    while(true)
    {
        cout<<" 1. ";
        cin >> v1;
        cout<<" 2. ";
        cin >> v2;
        cout<<angler(v1, v2);
        cout<<endl;
    }
}
