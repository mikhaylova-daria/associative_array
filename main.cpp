#include <iostream>
#include "RBTree.h"
using namespace std;

int main()
{
    RBtree< int, int > A;
    A.insert(std::pair<int, int>(1 ,2));
   // A.insert(std::pair<int, int>(2 ,2));
    //A.insert(std::pair<int, int>(3 ,2));
    cout << "Hello World!" << endl;
    A.print();
   // A.erase(1);
    A.print();
    int c;
  //  cin>>c;
    return 0;
}

