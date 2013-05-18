#ifndef RBTREE_H
#define RBTREE_H

template <typename T, typename U >
class RBtree
{
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
    void * TreeSuccessor(Node *);
    void * TreePredecessor(Node *);
    void * TreeMinimum (Node * x);
    void * TreeMaximum (Node *x);
    void * TreeSearch (Node * x , T key);
public:
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

    void insert(std::pair<T, U> _pair);
    void erase (T key);
    bool has_key (T key);
    void print ();
    T min_key(){
        return ((Node*)(this->TreeMinimum(root)))->key;
    }
    T max_key(){
        return ((Node*)(this->TreeMaximum(root)))->key;
    }
};

template <typename T, typename U>
    void RBtree<T, U>::insert(std::pair<T, U> _pair){
        Node * node = new Node(_pair.first, _pair.second);
        this->RB_INSERT(node);
        return;
    }

template <typename T, typename U>
    void RBtree<T, U>::erase (T _key){
        Node * key = (Node*) (this->TreeSearch(root, _key));
        if (key ->is_NIL(this)) return;
        this->RB_DELETE(key);
        delete (key);
        return;
    }

template <typename T, typename U>
    bool RBtree<T, U>::has_key (T _key){
        Node * key = (Node*)(this->TreeSearch(root, _key));
        return (!(key->is_NIL()));
    }

template <typename T, typename U>
    void RBtree<T, U>::print() {
        TreeWalk(root);
        return;
    }

template <typename T, typename U >
    void RBtree<T, U>::LEFT_ROTATE (RBtree<T, U>::Node * x) {
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

template <typename T, typename U >
    void RBtree<T,U>::RIGHT_ROTATE (RBtree<T, U>::Node * x) {
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

template <typename T , typename U>
    void RBtree<T, U>::RB_INSERT(RBtree<T, U>::Node * z) {
        Node* y = &NIL;
        Node* x  = root;
        while (! x->is_NIL(this)){
            y = x;
            if (z->key < x->key) {
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
            if (z->key < y->key) {
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


template <typename T, typename U >
    void RBtree<T, U>::RB_INSERT_FIXUP (RBtree<T, U>::Node * z) {
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


template <typename T, typename U>
        void * RBtree<T, U>::RB_DELETE (RBtree<T, U>::Node * z) {
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
        return (void*)y;
    }


template <typename T , typename U>
    void RBtree<T, U>::RB_DELETE_FIXUP (RBtree<T, U>::Node * x) {
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


template <typename T , typename U>
    void* RBtree<T, U>::TreeSuccessor(Node * x) {
        if (!(x->right->is_NIL(this))) {
            return TreeMinimum(x->right);
        }
        Node * y = x->parent;
        while (!(y->is_NIL(this)) && x == y->right) {
            x = y;
            y = y->parent;
        }
        return (void*)y;
    }

template <typename T , typename U>
   void * RBtree<T, U>::TreePredecessor(RBtree<T, U>::Node * x) {
        if (!(x->left->is_NIL(this))) {
            return TreeMaximum(x->left);
        }
        Node * y = x->parent;
        while (!(y->is_NIL(this)) && x == y->left) {
            x = y;
            y = y->parent;
        }
        return (void*)y;
    }

template <typename T, typename U >
    void* RBtree<T, U>::TreeMinimum (RBtree<T, U>::Node * x) {
        while (!(x->left->is_NIL(this))) {
            x = x->left;
        }
        return (void *)x;
    }

template <typename T , typename U>
    void * RBtree<T, U>::TreeMaximum (RBtree<T, U>::Node *x) {
        while (!(x->right->is_NIL(this))) {
               x = x->right;
        }
        return (void *)x;
    }

template <typename T , typename U>
    void * RBtree<T, U>::TreeSearch (RBtree<T, U>::Node * x, T key){
        while  (!(x->is_NIL(this)) && key != (x->key)) {
            if (key < x->key) {
                   x = x->left;
            } else {
                x = x->right;
            }
        }
        return (void *)x;
    }


template <typename T , typename U>
     void RBtree<T, U>::TreeWalk(Node * x){
         if (!(x->is_NIL(this))) {
             TreeWalk(x->left);
             std::cout<<x->key<<' '<<x->value<<'\n';
             TreeWalk(x->right);
         }
     }






#endif // RBTREE_H

