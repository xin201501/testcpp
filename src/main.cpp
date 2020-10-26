#include<iostream>
#include"chapter2.h"
using namespace std;
int main(int argc, char const* argv[])
{
    vector v1{ 1,3,5,4,2 };
    cout << myAlgorithm::findMinPostiveInterger(v1);
    for (auto&& v : v1) {
        cout << v << ' ';
    }
    return 0;
}