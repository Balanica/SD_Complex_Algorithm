#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("abce.in");
ofstream fout("abce.out");

struct Treap{
    int key, priority;
    Treap *left, *right;
};

Treap *Creation(int key){
    Treap *nod = new Treap;
    nod->key = key;
    nod->priority = rand() % 1000;
    nod->left = nullptr;
    nod->right = nullptr;
    return nod;
}

Treap *left_rotation(Treap *old_root){
    Treap *new_root;
    new_root = old_root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    return new_root;
};

Treap *right_rotation(Treap *old_root){
    Treap *new_root;
    new_root = old_root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    return new_root;
};

Treap *Insertion(Treap *treap, int key){
    if(treap == nullptr){
        return Creation(key);
    }
    else{
        if(treap->key > key){
            treap->left = Insertion(treap->left, key);
            if(treap->priority < treap->left->priority)
                treap = right_rotation(treap);
        }
        else{
            treap->right = Insertion(treap->right, key);
            if(treap->priority < treap->right->priority)
                treap = left_rotation(treap);
        }
    }
    return treap;
}

Treap *Deletion(Treap *treap, int key){
    //cout<<"d";
    //cout<<treap->key<<treap->left->key;
    if(treap == nullptr){
        //cout<<"i";
        return treap;
    }
    else{
        //cout<<"w";
        if(key < treap->key){
            //cout<<"w";
            treap->left = Deletion(treap->left, key);
            }
        else{
            //cout<<"v";
            if(key > treap->key)
                treap->right = Deletion(treap->right, key);
            else{
                //cout<<"b";
                if(treap->left == nullptr){
                    //cout<<"l";
                    Treap *aux = treap->right;
                    delete(treap);
                    treap = aux;
                }
                else if(treap->right == nullptr){
                    //cout<<"k";
                    Treap *aux = treap->left;
                    delete(treap);
                    treap = aux;
                }
                else{
                    if(treap->left->priority > treap->right->priority){
                        //cout<<"y";
                        treap = right_rotation(treap);
                        treap->right = Deletion(treap->right, key);
                    }
                    else{
                        //cout<<"e";
                        treap = left_rotation(treap);
                        treap->left = Deletion(treap->left, key);
                    }
                }
            }
        }
    }
    return treap;
}
int Search(Treap* treap, int key){
    if(treap == nullptr)
        return 0;
    if(treap->key > key)
        return Search(treap->left, key);
    else if(treap->key < key)
        return Search(treap->right, key);
    else
        return 1;
}

//void Search4(Treap* treap,Treap *, int key){
//    cout<<"9";
//    if(treap->key > key)
//        Search4(treap->left, key);
//    else if(treap->key < key){
//
//        return Search4(treap->right, key);
//    }
//    else if (treap->left != nullptr){
//        Treap *aux;
//        aux = treap->left;
//        while(treap->right !=nullptr)
//            aux = treap->right;
//        return aux->key;
//    }
//}
//int Search5(Treap* treap, int key){
//    if(treap->key > key)
//        return Search(treap->left, key);
//    else if(treap->key < key)
//        return Search(treap->right, key);
//    else{
//        treap->right->key;
//    }
//}

int Search4(Treap *treap, int key){
    Treap *t = nullptr;
    while(treap){
        if(treap->key > key)
            treap = treap->left;
        else if(treap->key < key){
            t = treap;
            treap = treap->right;
        }
        else{
            return treap->key;
        }
    }
    return t->key;
}

int Search5(Treap *treap, int key){
    Treap *t = nullptr;
    while(treap){
        if(treap->key < key)
            treap = treap->right;
        else if(treap->key > key){
            t = treap;
            treap = treap->left;
        }
        else{
            return treap->key;
        }
    }
    return t->key;
}

void print(Treap *treap, int left, int right){
    if(!treap)
        return;
    if(left < treap->key)
        print(treap->left, left, right);
    if(right>=treap->key && left<=treap->key)
        fout<<treap->key<<" ";
    if(right > treap->key)
        print(treap->right, left, right);
}

int main()
{
    int x, op, var, a, b;
    Treap *treap = nullptr;
    fin>>x;
    for(int i = 0; i< x; i++){
        fin>>op;
        //cout<<op;
        if(op == 1){
            fin>>var;
            treap = Insertion(treap, var);
        }
        if(op == 2){
            fin>>var;
            treap = Deletion(treap, var);
        }
        if(op == 3){
            fin>>var;
            fout<<Search(treap, var)<<"\n";
        }
        if(op == 4){
            fin>>var;
            fout<<Search4(treap, var)<<"\n";
        }
        if(op == 5){
            fin>>var;
            fout<<Search5(treap, var)<<"\n";
        }
        if(op == 6){
            fin>>a>>b;
            print(treap, a, b);
            fout<<"\n";
        }
    }
}
