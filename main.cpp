#include <iostream>
#include "RBTree.h"
#include <list>
#include<typeinfo>
#include<iterator>
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
    RBtree<int, int, greater<int> >::iterator itr;
    itr = A.begin();
    for (; itr!= A.end(); ++itr) {
        cout<<(*itr).first<<" "<<(*itr).second<<'\n';

    }
    cout <<"\n";
    A.erase(A.begin());



    itr = A.begin();
    (*itr).second = 6;// изменит значение

    for (itr = A.begin(); itr!= A.end(); ++itr) {
        cout<<(*itr).first<<" "<<(*itr).second<<'\n';
    }

    RBtree<int, int, greater<int> >::const_iterator itr1;
    itr1 = A.cbegin();
    for (; itr1!= A.cend(); ++itr1) {
        cout<<(*itr1).first<<" "<<(*itr1).second<<'\n';

    }
    cout <<"\n";

    cout<<'\n';

    itr1 = A.cbegin();
   // (*itr1).second = 6; //даст ошибку компиляции, как и положено

    for (itr1 = A.cbegin(); itr1 != A.cend(); ++itr1) {
        cout<<itr1->first<<" "<<(*itr1).second<<'\n';
    }
    cout<<A[5].second<<"\n";
    A[5].second =7;
    cout<<(*A.find(12)).first<<" "<<(*A.find(12)).second<<'\n';
    //A.erase(1);
   // A.print();
    //int c;
  //  cin>>c;
    //swap();


    return 0;
}

