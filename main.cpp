#include <iostream>
#include "RBTree.h"
using namespace std;

int main()
{
    RBtree< int, int, greater<int> > A;
    A.insert(std::pair<int, int>(1 ,2));
    A.insert(std::pair<int, int>(4 ,2));
    A.insert(std::pair<int, int>(3 ,2));
    A.insert(std::pair<int, int>(123 ,2));
    A.insert(std::pair<int, int>(45 ,2));
    A.insert(std::pair<int, int>(334 ,2));
    A.insert(std::pair<int, int>(12 ,2));
    A.insert(std::pair<int, int>(44 ,2));
    A.insert(std::pair<int, int>(31 ,2));
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

