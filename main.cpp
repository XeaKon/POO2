#include <iostream>
#include <cstring>
using namespace std;


class DenumireEgz
{
    public:
    static int nr;
    char nume[40];
};

class RezultatEgz
{
    DenumireEgz *p;
    int ntscris;
    int data[8];
    public:

    RezultatEgz & operator=(RezultatEgz e)
    {
        int i;
        p=new DenumireEgz;


       *p=*e.p;
       ntscris=e.ntscris;
       for(i=0;i<8;i++)
       {
           data[i]=e.data[i];
       }

    };


    void senumeste()
    {
      cout<<"Examenul se numeste "<<p->nume<<endl;
    };


    virtual void afisare()
    {
        cout<<ntscris<<endl;
    };
};

class Partial:public RezultatEgz
{
    int ntoral;
    public:
    void afisare()
    {
        cout<<ntoral<<endl;
    };


};

class EgzFinal:public Partial
{
    int ntproiect;
    float ntgrila;     //daca nota la grila este mai mare de 5,0 , se adauga un punct
    void afisare()
    {
        cout<<ntproiect<<" "<<ntgrila;
    };

};



template <class T> class CatalogIndividual
{
    static double nr_matricol;
    int nr_examene;
    RezultatEgz **v;

    CatalogIndividual()
    {
      nr_matricol++;

      nr_examene=0;
    };


    friend istream & operator>>(istream &i,CatalogIndividual &e);


     CatalogIndividual <T> & operator+=(RezultatEgz b)
     {
         RezultatEgz **a;
         int i;

         a=new RezultatEgz *[nr_examene+1];  // mai lucrez aici
         a[nr_examene]=new RezultatEgz;
         *(a[nr_examene])=b;
         for(i=0;i<nr_examene;i++)
         {
             a[i]=v[i];
         }

         nr_examene++;
         v=a;
         delete a;

     };

};

int DenumireEgz::nr=0;
template <class T> double CatalogIndividual<T>::nr_matricol=0;

istream & operator>>(istream &i,CatalogIndividual &e)
    {

    cin>>e.nr_examene;

        return i;
    }


int main()
{

int nrex,i;
    cin>>nrex;
     DenumireEgz *v;
     v=new DenumireEgz [nrex];


     for(i=0;i<nrex;i++)
     {
         cin.get(v[i].nume,40,'\n');
         cin.get();

     }
  int y,nex;    //nex=nr de examene ce trebuiesc inserate la fiecare student

    cin>>y;
   CatalogIndividual <int> **a;

   a=new CatalogIndividual <int> *[y];

   for(i=0;i<y;i++)
   {
       cin>>nex;



   }

    return 0;
}
