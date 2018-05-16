#include <iostream>
#include <cstring>
using namespace std;


class DenumireEgz
{

    static int nr;
    char nume[40];
    public:

    static void init()
    {
      int  nr=0;
    }

    void numire(char c[40])
    {
        int i;
        for(i=0;i<40;i++)
        {
            nume[i]=c[i];
        }

    }
    char* getNume()
    {
        return nume;
    }

    void senumeste()
    {
      cout<<"Examenul se numeste "<<nume<<endl;
    };

};
int DenumireEgz::nr;
class RezultatEgz
{
    DenumireEgz *p;
    int ntscris;
    int data[8];
    public:

      virtual void citire(istream &i)
     {

         cout<<"Introduceti nota la scris"<<endl;
          cin>>ntscris;
          int j;

          cout<<"Data(cu spatii intre cifre)"<<endl;
          for(j=0;j<8;j++)
          {
              cin>>data[j];
          }

     };

     friend istream &operator>>(istream &i,RezultatEgz &e)
     {
         e.citire(i);
         return i;
     }

    RezultatEgz & operator=(RezultatEgz e)
    {
        int i;
        p=e.p;

       ntscris=e.ntscris;
       for(i=0;i<8;i++)
       {
           data[i]=e.data[i];
       }

    };
   void atNume(DenumireEgz *d)
   {
       p=d;//de lucrat
   }

    virtual void afisare()
    {
        cout<<ntscris<<endl;
        p->senumeste();

    };




};
class Partial:public RezultatEgz
{
    int ntoral;
    public:
    void afisare()
    {
        cout<<ntoral<<endl;
        RezultatEgz::afisare();
    };


    virtual void citire(istream &i)
     {
         cout<<"Introduceti nota la oral"<<endl;
          cin>>ntoral;
          RezultatEgz::citire(i);

     };



};

class EgzFinal:public Partial
{
    int ntproiect;
float ntgrila;
    public:     //daca nota la grila este mai mare de 0,5 , se adauga un punct
    void afisare()
    {
        cout<<ntproiect<<" "<<ntgrila;
        Partial::afisare();
    };

virtual void citire(istream &i)
     {
         cout<<"Introduceti nota la proiect si nota la grila(daca nu s-a dat introduceti 0)"<<endl;
          cin>>ntproiect;
          cin>>ntgrila;
          Partial::citire(i);

     };

};




template <class T> class CatalogIndividual
   { static double nr_matricol;
    int nr_examene;
    RezultatEgz **v;
    public:

    CatalogIndividual()
    {
      nr_matricol++;

      nr_examene=0;
    };

    static void initC()
    {
       double nr_matricol=0;
    }

    int getnr_examene()
    {
        return nr_examene;
    }

    RezultatEgz * getex(int i)
    {
        return v[i];
    }


    void afisare(int i)
    {
        cout<<"Nr. matricol: "<<nr_matricol<<endl;
        cout<<"Nr. de examene: "<<nr_examene<<endl;


        (v[i])->afisare();
    }



     friend istream & operator>>(istream &i,CatalogIndividual &e)
     {
          cin>>e.nr_examene;

        return i;
     };


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
template <class T> double CatalogIndividual<T>::nr_matricol;



int main()
{

     DenumireEgz::init();
 CatalogIndividual<double>::initC();

int nrex,i;

char b[40];


cout<<"Cate tipuri de examene sunt ?"<<endl;
    cin>>nrex;
     DenumireEgz *v;
     v=new DenumireEgz [nrex];


     for(i=0;i<nrex;i++)
     {
         cin>>b;

         v[i].numire(b);

     }
  int y,j;    //nex=nr de examene ce trebuiesc inserate la fiecare student


  cout<<"Introduceti nr. de studenti"<<endl;
    cin>>y;
   CatalogIndividual <int> **a;

   a=new CatalogIndividual <int> *[y];

   RezultatEgz  *r;
   int nrExSt;
   int z;

   for(i=0;i<y;i++)
   {   a[i]=new CatalogIndividual <int>;


       cout<<"Intriduceti nr. de examene al studentului"<<endl;

       cin>>(*a[i]);
       nrExSt=(a[i]->getnr_examene());
      while(nrExSt!=0)
      {


   cout<<"Introduceti numele examenului "<<endl;
       cin>>b;
       j=0;
       while(b!=v[j].getNume())
       {
           j++;
       }

       cout<<"Tipul examenului:"<<endl<<"1.Partial"<<endl<<"2.Final"<<endl;
       cin>>z;
       if(z==1)
       {
           r=new Partial;
       }
       else
       {
           r=new EgzFinal;
       }
       cin>>*r;


       r->atNume(&v[j]);

       (*a[i])+=(*r);


       nrExSt--;
      }






   }

   z=1;


  while(z==1)
  {




      cout<<"Se afiseaza catalogul elevului:"<<endl;
      cin>>i;
      cout<<"Nr. examenului:"<<endl;
      cin>>j;
      a[i]->afisare(j);


      cout<<"Iesiti din program ?"<<endl<<"1.Nu"<<endl<<"2.Da"<<endl;
      cin>>z;

  }

    return 0;
}
