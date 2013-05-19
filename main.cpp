#include <iostream>
#include "RBTree.h"
#include <list>
using namespace std;

int main()
{
    RBtree< int, int, greater<int> > A, B;
    B.insert(std::pair<int, int>(213 ,7));
    B.insert(std::pair<int, int>(11 ,7));
    A.insert(std::pair<int, int>(1 ,7));
    A.insert(std::pair<int, int>(1 ,5));
    A.insert(std::pair<int, int>(1 ,9));
    A.insert(std::pair<int, int>(3 ,8));
    A.insert(std::pair<int, int>(3 ,2));
    A.insert(std::pair<int, int>(123 ,2));
    A.insert(std::pair<int, int>(45 ,2));
    A.insert(std::pair<int, int>(334 ,2));
    A.insert(std::pair<int, int>(12 ,2));
    if (A.insert(std::pair<int, int>(12 ,2)).second == false) {cout << "повтор\n";}
    A.insert(std::pair<int, int>(44 ,2));
    A.insert(std::pair<int, int>(31 ,2));
    A.insert(B.begin(), B.end());
   // A.print();
    RBtree<int, int, greater<int> >::iterator itr;
    itr = A.begin();
    for (; itr!= A.end(); ++itr) {
        cout<<(*itr).first<<" "<<(*itr).second<<'\n';
    }
    //A.erase(1);
   // A.print();
    //int c;
  //  cin>>c;
    return 0;
}

