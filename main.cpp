#include <iostream>
#include "RBTree.h"
using namespace std;

int main()
{
    RBtree< int, int > A;
    A.insert(std::pair<int, int>(1 ,2));
    A.insert(std::pair<int, int>(4 ,2));
    A.insert(std::pair<int, int>(3 ,2));
    cout << "Hello World!" << endl;
   // A.print();
    RBtree<int, int>::iterator itr;
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

