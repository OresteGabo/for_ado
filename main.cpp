#include <iostream>
using namespace std;

template <typename T>
class Gene{
private:
    T* tableau;
    int taille;
public:
    explicit Gene(unsigned int taille);
    ~Gene();
    void tri();
    Gene<T> slice(int,int);
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Gene<U>&);

    void swap(T &pT, T &pT1);
};


class Rique{
private:
    int n;
public:
    Rique(int _n):n{_n}{}
    Rique():n(rand()%100){}
    ~Rique(){}
    int get_n()const{return n;}
    Rique& operator=(int);
    friend std::ostream& operator<<(std::ostream&, const Rique&);
    bool operator<(const Rique& )const;
    bool operator>(const Rique& )const;
    bool operator==(const Rique& )const;
};
bool Rique::operator<(const Rique& r)const{
    if(this==&r)return false;
    return r.get_n()<n;
}
bool Rique::operator>(const Rique& r)const{
    if(this==&r)return false;
    return r.get_n()>n;
}
bool Rique::operator==(const Rique& r)const{
    if(this==&r)return true;
    return r.get_n()==n;
}
std::ostream& operator<<(std::ostream& os, const Rique& r){
    os<<r.get_n();
    return os;
}
Rique& Rique::operator=(int val){
    this->n=val;
    return *this;
}
template <typename T>
Gene<T>::Gene(unsigned int _taille){
    taille=_taille;
    tableau=new T[_taille];
    srand(time(NULL));
    for(int x=0;x<taille;x++){
        tableau[x]=rand()%100;
    }
}
template<typename T> Gene<T>::~Gene(){
    delete[] tableau;
}

/**
 * La fonction marche quand le T est de type nombre(comme int, long, double,..), ou quand il y a la surcharges des operateurs de comparaisons
 * @tparam T
 */
template<typename T> void Gene<T>::tri(){
    int i, j;
    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            if (tableau[j] > tableau[j + 1]) {
                auto inter = tableau[j];
                tableau[j] = tableau[j + 1];
                tableau[j + 1] = inter;
            }
        }
    }
}

template<typename T> Gene<T> Gene<T>::slice(int debut,int fin){
    Gene<T> gene=Gene(fin-debut);
    unsigned int compteur=0;
    for(int x=debut;x<fin;++x){
        gene.tableau[compteur++]=this->tableau[x];
    }
    return gene;
}
template<typename U>
 std::ostream& operator<<(std::ostream& os, const Gene<U>&g){
     for(int i=0;i<g.taille;++i){
         os<<g.tableau[i]<<' ';
     }
     os<<std::endl;
    return os;
 }


int main() {
    Gene<int> g2(4);
    //cout<<g2;
    g2.tri();
    cout<<g2;
    Gene<Rique> g(5);
    //cout<<g;
    g.tri();
    cout<<g;
    return 0;
}