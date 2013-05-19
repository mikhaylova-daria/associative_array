#ifndef RBTREE_H
#define RBTREE_H
#include <algorithm>
using namespace std;
template <typename T, typename U, typename Compare = std::less<T> >
class RBtree
{
    Compare comp;
    struct Node;
    Node NIL;
    Node * root;
    struct Node
    {
        bool colour; //true - черный, false - красный
        T key;
        U value;
        Node * left;
        Node * right;
        Node * parent;
        Node(){;}
        Node (T _key, U _value): key(_key), value(_value) {;}
        Node (Node * _root): colour(true),left(_root), right(_root) {;}     //для NIL
        ~Node(){;}

        bool is_NIL(RBtree * tree){
            if ((this->left == tree->root) && (this->right == tree->root)) {
                return true;
            } else {
                return false;
            }
        }
    };
private:
    void LEFT_ROTATE (Node *);
    void RIGHT_ROTATE (Node *);
    void RB_INSERT (Node *);
    void RB_INSERT_FIXUP (Node *);
    void * RB_DELETE (Node *);
    void RB_DELETE_FIXUP (Node *);
    void TreeWalk(Node*);
    typename RBtree<T, U, Compare>::Node * TreeSuccessor(Node *);
    typename RBtree<T, U, Compare>::Node * TreePredecessor(Node *);
    typename RBtree<T, U, Compare>::Node * TreeMinimum (Node * x);
    typename RBtree<T, U, Compare>::Node * TreeMaximum (Node *x);
    typename RBtree<T, U, Compare>::Node * TreeSearch (Node * x , T key);
    std::pair <RBtree<T, U, Compare>::Node*, bool> has_key (T key);
public:
    class iterator;
    class const_iterator;
    RBtree() {
        NIL.left = &NIL;
        NIL.right = &NIL;
        NIL.colour = true;
        root = &NIL;
    }
    ~RBtree() {
        Node *min;
        Node *max;
        while (!(root->is_NIL(this))) {
            min = (Node*)(this->TreeMinimum(root));
            max = (Node*)(this->TreeMaximum(root));
            delete((Node*)(this->RB_DELETE(max)));
            if (min != max){
                delete((Node*)(this->RB_DELETE(min)));
            }
        }
      }

    pair<typename RBtree<T, U, Compare>::iterator, bool> insert(std::pair<T, U> _pair);
    void insert (RBtree<T, U, Compare>::iterator first, RBtree<T, U, Compare>::iterator last);
    void erase (T key);
    RBtree <T, U, Compare >::iterator begin();
    RBtree <T, U, Compare>::iterator end();
    RBtree <T, U, Compare >::const_iterator cbegin();
    RBtree <T, U, Compare>::const_iterator cend() ;
    RBtree <T, U, Compare>::iterator find(const T & _key);
    void erase (iterator itr);

};

// INSERT 1
template <typename T, typename U, typename Compare>
  void RBtree<T, U, Compare>::insert (RBtree<T, U, Compare>::iterator first, RBtree<T, U, Compare>::iterator last){
      for (;first != last; ++first){
          insert((*first));
      }
      return;
  }

//INSERT 2
template <typename T, typename U, typename Compare>
     pair<typename RBtree<T, U, Compare>::iterator, bool>  RBtree<T, U, Compare>::insert(std::pair<T, U> _pair){
        Node * node = new Node(_pair.first, _pair.second);
        Node * key = (this->TreeSearch(root, _pair.first));
        if (key ->is_NIL(this)) {
            this->RB_INSERT(node);
            iterator itr(node, this);
            std::pair<typename RBtree<T, U, Compare>::iterator, bool>  answer(itr, true);
            return answer;
        } else {
            iterator itr(key, this);
            std::pair<typename RBtree<T, U, Compare>::iterator, bool>  answer(itr, false);
            return answer;
        }
    }

//FIND
template <typename T, typename U, typename Compare>
     typename RBtree<T, U, Compare>::iterator RBtree<T, U, Compare>::find(const T & _key){
          Node * key =  (this->TreeSearch(root, _key));
          iterator itr(key, this);
          return itr;
     }


//ERASE(KEY)
template <typename T, typename U, typename Compare>
    void RBtree<T, U, Compare>::erase (T _key){
        Node * key =  this->TreeSearch(root, _key);
        if (key ->is_NIL(this)) return;
        this->RB_DELETE(key);
        delete (key);
        return;
    }

//ERASE(ITERATOR)
    template <typename T, typename U, typename Compare>
        void RBtree<T, U, Compare>::erase (iterator itr){
            if (itr.current->is_NIL(this)) return;
            this->RB_DELETE(itr.current);
            delete (itr.current);
            return;
        }


template <typename T, typename U, typename Compare>
    pair <typename RBtree<T, U, Compare>::Node*, bool> RBtree<T, U, Compare>::has_key (T _key){
        Node * key = (this->TreeSearch(root, _key));
        return pair<Node*, bool> (key,!(key->is_NIL(this)));
    }


template <typename T, typename U , typename Compare>
    void RBtree<T, U, Compare>::LEFT_ROTATE (RBtree<T, U, Compare>::Node * x) {
       Node* y = x->right;
       x->right = y->left;
       if(!y->left->is_NIL(this)) {
           y->left->parent = x;
       }
       y->parent = x->parent;

       if (x->parent->is_NIL(this)) {
           root = y;
           Node newNil(root);
           NIL = newNil;
       } else {
           if (x == x->parent->left) {
               x->parent->left = y;
           } else {
               x->parent->right = y;
           }
       }
       y->left = x;
       x->parent = y;
       return;
    }

template <typename T, typename U , typename Compare>
    void RBtree<T,U, Compare>::RIGHT_ROTATE (RBtree<T, U, Compare>::Node * x) {
       Node* y = x->left;
       x->left = y->right;

       if(!y->right->is_NIL(this)) {
           y->right->parent = x;
       }
       y->parent = x->parent;
       if (x->parent->is_NIL(this)) {
           root = y;
           Node newNil(root);
           NIL = newNil;
       } else {
           if (x == x->parent->right) {
               x->parent->right = y;
           } else {
               x->parent->left = y;
           }
       }
       y->right = x;
       x->parent = y;
       return;
    }

template <typename T , typename U, typename Compare>
    void RBtree<T, U, Compare>::RB_INSERT(RBtree<T, U, Compare>::Node * z) {
        Node* y = &NIL;
        Node* x  = root;
        while (! x->is_NIL(this)){
            y = x;
            if (comp(z->key, x->key)) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;

        if (y->is_NIL(this)) {
            root = z;
            Node newNil(root);
            NIL = newNil;
        } else {
            if (comp(z->key, y->key)) {
                y->left = z;
            } else {
                y->right = z;
            }
        }
        z->left = &NIL;
        z->right = &NIL;
        z->colour = false;
        RB_INSERT_FIXUP(z);
        return;
    }


template <typename T, typename U, typename Compare >
    void RBtree<T, U, Compare>::RB_INSERT_FIXUP (RBtree<T, U, Compare>::Node * z) {
        Node* y;
        while (((z->parent) -> colour) == false) {
            if (z->parent == (((z->parent)->parent) ->left)) {
                y = ((z->parent)->parent) -> right;
                if (y->colour == false){
                    z->parent->colour = true;
                    y->colour  = true;
                    z->parent->parent->colour = false;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent -> right) {
                       z = z->parent;
                       LEFT_ROTATE(z);
                    }
                    z -> parent -> colour = true;
                    z->parent->parent->colour = false;
                    RIGHT_ROTATE(z->parent->parent);
                }
            } else {
                if (z->parent == (((z->parent)->parent) ->right)) {
                    y = ((z->parent)->parent) -> left;
                    if (y->colour == false){
                        z->parent->colour = true;
                        y->colour = true;
                        z->parent->parent->colour = false;
                        z = z->parent->parent;
                    } else {
                        if (z == z->parent -> left) {
                           z = z->parent;
                           RIGHT_ROTATE(z);
                        }
                        z -> parent->colour = true;
                        z->parent->parent->colour = false;
                        LEFT_ROTATE(z->parent->parent);
                    }
                }
            }
         }
        root->colour = true;
        return;
    }


template <typename T, typename U, typename Compare>
        void * RBtree<T, U, Compare>::RB_DELETE (RBtree<T, U, Compare>::Node * z) {
        Node * y;
        Node * x;
        if (z->left->is_NIL(this) || z->right->is_NIL(this)) {
            y = z;
        } else {
            y = (Node*)TreeSuccessor(z);
        }
        if (!(y->left->is_NIL(this))) {
            x = y->left;
        } else {
            x = y->right;
        }
        x->parent = y->parent;
        if (y->parent->is_NIL(this)) {
            root = x;
            Node newNil(root);
            NIL = newNil;
        } else {

            if (y == (y ->parent->left)) {
                y->parent->left = x;
            } else {
                y->parent->right = x;
            }
        }
        if (y != z) {
            z->key = y->key;
        }
        if (y->colour == true) {
            RB_DELETE_FIXUP(x);
        }
        return y;
    }


template <typename T , typename U, typename Compare>
    void RBtree<T, U, Compare>::RB_DELETE_FIXUP (RBtree<T, U, Compare>::Node * x) {
        Node * w;
        while ((x != root) && (x->colour == true)){
        if (x == x->parent->left) {
            w = x->parent ->right;
            if (w->colour == false) {
                w->colour = true;
                x->parent -> colour= false;
                LEFT_ROTATE(x->parent);
                w = x->parent->right;
            }
            if ((w->left->colour == true) && (w->right->colour == true)) {
                w->colour = false;
                x = x->parent;
            } else {
                if (w->right->colour == true) {
                    w->left->colour = true;
                    w->colour = false;
                    RIGHT_ROTATE(w);
                    w = x->parent->right;
                }
                w->colour = x->parent->colour;
                x->parent->colour = true;
                w->right->colour = true;
                LEFT_ROTATE(x->parent);
                x = root;
           }
        } else {
            w = x->parent ->left;
            if (w->colour == false) {
                w->colour = true;
                x->parent->colour = false;
                RIGHT_ROTATE(x->parent);
                w = x->parent->left;
            }
            if ((w->right->colour == true) && (w->left->colour == true)) {
                w->colour = false;
                x = x->parent;
            } else {
                if (w->left->colour == true) {
                    w->right->colour = true;
                    w->colour = false;
                    LEFT_ROTATE(w);
                    w = x->parent->left;
                }
                w->colour = x->parent->colour;
                x->parent->colour = true;
                w->left->colour = true;
                RIGHT_ROTATE(x->parent);
                x = root;
            }
        }
        }
        x->colour = true;
    }


template <typename T , typename U, typename Compare>
     typename RBtree<T, U, Compare>::Node* RBtree<T, U, Compare>::TreeSuccessor(Node * x) {
        if (!(x->right->is_NIL(this))) {
            return TreeMinimum(x->right);
        }
        Node * y = x->parent;
        while (!(y->is_NIL(this)) && x == y->right) {
            x = y;
            y = y->parent;
        }
        return y;
    }

template <typename T , typename U, typename Compare>
   typename RBtree<T, U, Compare>::Node * RBtree<T, U, Compare>::TreePredecessor(RBtree<T, U, Compare>::Node * x) {
        if (!(x->left->is_NIL(this))) {
            return TreeMaximum(x->left);
        }
        Node * y = x->parent;
        while (!(y->is_NIL(this)) && x == y->left) {
            x = y;
            y = y->parent;
        }
        return y;
    }

template <typename T, typename U , typename Compare>
    typename RBtree<T, U, Compare>::Node* RBtree<T, U, Compare>::TreeMinimum (RBtree<T, U, Compare>::Node * x) {
        while (!(x->left->is_NIL(this))) {
            x = x->left;
        }
        return x;
    }

template <typename T , typename U, typename Compare>
    typename RBtree<T, U, Compare>::Node * RBtree<T, U, Compare>::TreeMaximum (RBtree<T, U, Compare>::Node *x) {
        while (!(x->right->is_NIL(this))) {
               x = x->right;
        }
        return x;
    }

template <typename T , typename U, typename Compare>
     typename RBtree<T, U, Compare>::Node * RBtree<T, U, Compare>::TreeSearch (RBtree<T, U, Compare>::Node * x, T key){
        while  (!(x->is_NIL(this)) && key != (x->key)) {
            if (comp(key ,x->key)) {
                   x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }


template <typename T , typename U, typename Compare>
     void RBtree<T, U, Compare>::TreeWalk(Node * x){
         if (!(x->is_NIL(this))) {
             TreeWalk(x->left);
             std::cout<<x->key<<' '<<x->value<<'\n';
             TreeWalk(x->right);
         }
     }

template <typename T , typename U, typename Compare>
     typename RBtree<T,U, Compare>::iterator RBtree<T,U, Compare>::begin()
     {
         RBtree<T, U, Compare>::Node * current = this->TreeMinimum(this->root);
         iterator it(current, this);
         return it;
     }


template <typename T , typename U, typename Compare>
    typename  RBtree<T,U, Compare>::iterator RBtree<T,U, Compare>::end()
     {

         iterator it(&(this->NIL) , this);
         return it;
     }

     template <typename T , typename U, typename Compare>
          typename RBtree<T,U, Compare>::const_iterator RBtree<T,U, Compare>::cbegin()
          {
              RBtree<T, U, Compare>::Node * current = this->TreeMinimum(this->root);
              const_iterator it(current, this);
              return it;
          }


     template <typename T , typename U, typename Compare>
         typename  RBtree<T,U, Compare>::const_iterator RBtree<T,U, Compare>::cend()
          {

              const_iterator it(&(this->NIL) , this);
              return it;
          }

template <typename T, typename U, typename Compare>
     class RBtree<T, U, Compare>::iterator{
         RBtree<T, U, Compare> *tree;
         RBtree<T, U, Compare>::Node * current;

     public:
         friend class RBtree<T, U, Compare>;
         iterator (RBtree<T, U, Compare>::Node *_current = 0, RBtree<T, U, Compare> *_tree  = 0):current(_current), tree(_tree){}
         bool operator !=(const iterator & other)
         {
             return (current != other.current || tree != other.tree);
         }
         bool operator ==(const iterator & other)
         {
             return (current == other.current && tree == other.tree);
         }
         iterator & operator++(){
         {
                current = tree->TreeSuccessor(current);
                if (current->is_NIL(tree)){
                    iterator itr(&(tree->NIL), tree);
                    return itr;
                } else {
                    iterator itr(current, tree);
                    return itr;
                }

          }
        }


         std::pair<const T, U&>  operator*(){
             std::pair<T, U&> answer(current->key, current->value);
             return answer;
         }


     };

     template <typename T, typename U, typename Compare>
          class RBtree<T, U, Compare>::const_iterator{
              RBtree<T, U, Compare> *tree;
              RBtree<T, U, Compare>::Node * current;

          public:
              friend class RBtree<T, U, Compare>;
              const_iterator (RBtree<T, U, Compare>::Node *_current = 0, RBtree<T, U, Compare> *_tree  = 0):current(_current), tree(_tree){}
              bool operator !=(const const_iterator & other)
              {
                  return (current != other.current || tree != other.tree);
              }
              bool operator ==(const const_iterator & other)
              {
                  return (current == other.current && tree == other.tree);
              }
              const_iterator & operator++(){
              {
                     current = tree->TreeSuccessor(current);
                     if (current->is_NIL(tree)){
                         const_iterator itr(&(tree->NIL), tree);
                         return itr;
                     } else {
                         const_iterator itr(current, tree);
                         return itr;
                     }

               }
             }

              const std::pair<const T, const U> operator*(){
                  std::pair<T, U> answer;
                  answer.first = current->key;
                  answer.second = current->value;
                  return answer;
              }
          };


#endif // RBTREE_H

