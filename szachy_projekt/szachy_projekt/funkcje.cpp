//
//  funkcje.cpp
//  szachy_projekt
//
//  Created by Stanislaw Czembor on 10/12/2018.
//  Copyright © 2018 Stanislaw Czembor. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include "funkcje.hpp"
#include "struktury.hpp"



void wyswietl_szachownice(char tab[][8],const int ROZMIAR)
{
    int indeks_literowy = 8;
    std::cout<<"        A      B      C      D      E      F      G      H   "<<std::endl;
    
    for(int i =0;i<8;i++)
    {
        std::cout<<"     #########################################################"<<std::endl;
        std::cout<<"     #      #      #      #      #      #      #      #      #"<<std::endl;
        std::cout<<"  "<<indeks_literowy<<"  ";
        indeks_literowy--;
        for(int j =0;j<8;j++)
        {
            std::cout<<"#  "<<tab[i][j]<<"   ";
            
        }
        
        std::cout<<"#"<<std::endl;
        std::cout<<"     #      #      #      #      #      #      #      #      #"<<std::endl;
        
    }
    std::cout<<"     #########################################################"<<std::endl<<std::endl<<std::endl;
    
    
}


void reset_szachownicy(char tab[][8],const int ROZMIAR)
{
   //gracz 2
    tab[0][0] = tab[0][7] = 'W'; //wieża
    tab[0][1] = tab[0][6] = 'S'; //skoczek
    tab[0][2] = tab[0][5] = 'G'; //goniec
    tab[0][3] = 'H'; //hetman
    tab[0][4] = 'K'; //krol
    for(int i = 0; i < 8; i++)
        tab[1][i] = 'P'; //pionki
    
    //gracz 1
    tab[7][0] = tab[7][7] = 'w';
    tab[7][1] = tab[7][6] = 's';
    tab[7][2] = tab[7][5] = 'g';
    tab[7][3] = 'h';
    tab[7][4] = 'k';
    for(int i = 0; i < 8; i++)
        tab[6][i] = 'p';
    
    //puste pola
    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j++)
            tab[i][j] = ' ';
}
void gra(struct ruch * &pHead, struct ruch *&pTail,int kolor,char tab[][8])
{
    std::string skad;
    std::string dokad;
    int poprawny;
    if(!kolor)
        std::cout<<"------------------Ruch bialych------------------"<<std::endl;
    else
        std::cout<<"------------------Ruch czarnych------------------"<<std::endl;
    
    std::cout<<"wprowadz polozenie pionka, ktory chcesz ruszyc(np.a4): ";
    std::cin>>skad;
    std::cout<<std::endl;
    poprawny=czy_poprawny_pionek(skad,kolor,tab);
    while(!poprawny)
    {
        std::cout<<"niepoprawna figura, sprobuj ponownie : ";
        std::cin>>skad;
        poprawny=czy_poprawny_pionek(skad,kolor,tab);
    }
    
    if(poprawny)
    {
        std::cout<<"wprowadz docelowe polozenie pionka(np.a4): ";
        dokad=ruchy(skad,dokad,kolor,tab);
        
    }
    dodaj_na_koniec(pHead, pTail, skad, dokad);

}

int czy_poprawny_pionek(std::string skad,int kolor,char tab[][8])
{
    if(kolor==1)
        if(65<(tab[7-(skad[1]-49)][skad[0]-97]) and (tab[7-(skad[1]-49)][skad[0]-97])<90)
            return 1;
        else
            return 0;
    if(kolor==0)
        if(96<(tab[7-(skad[1]-49)][skad[0]-97]) and (tab[7-(skad[1]-49)][skad[0]-97])<122)
            return 1;
        else
            return 0;
    
    return 0;
}
void ruch_pionek_bialy(int kolor,std::string skad,std::string dokad, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny=false;
    char nowy_pionek;
    
            if (poczatkowy_wiersz-docelowy_wiersz>0 and poczatkowy_wiersz-docelowy_wiersz<3)
            {
                
                    if(docelowy_wiersz ==poczatkowy_wiersz-1 and((tab[docelowy_wiersz][docelowy_kolumna]==' ' and poczatkowy_kolumna==docelowy_kolumna) or (abs(docelowy_kolumna-poczatkowy_kolumna)==1 and isupper(tab[7-(docelowy_wiersz)][docelowy_kolumna]))))
                       {
                           poprawny =true;
                       }
                    else if (poczatkowy_wiersz== 6 and docelowy_wiersz ==poczatkowy_wiersz-2 and (tab[docelowy_wiersz+1][docelowy_kolumna] ==' ' and (tab[docelowy_wiersz][docelowy_kolumna]==' ')))
                    {
                        poprawny = true;
                    }
                
            
            }
    if(poprawny)
    {
        if(docelowy_wiersz==0)
        {
            std::cout<<"wprowadz figure, ktora wybierzasz(np. h) : ";
            std::cin>>nowy_pionek;
            tab[poczatkowy_wiersz][poczatkowy_kolumna] = ' ';
            tab[docelowy_wiersz][docelowy_kolumna]=nowy_pionek;
        }
        else
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
    }
    else
    {
        std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
        ruchy(skad, dokad,kolor,tab);
    }
    
    
}
void ruch_pionek_czarny(int kolor,std::string skad,std::string dokad, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny=false;
    char nowy_pionek;
    
            if (docelowy_wiersz-poczatkowy_wiersz>0 and docelowy_wiersz-poczatkowy_wiersz<3)
            {
               
                    if(docelowy_wiersz ==poczatkowy_wiersz+1 and((tab[docelowy_wiersz][docelowy_kolumna]==' ' and poczatkowy_kolumna==docelowy_kolumna) or (abs(docelowy_kolumna-poczatkowy_kolumna)==1 and islower(tab[docelowy_wiersz][docelowy_kolumna]))))
                    {
                        poprawny=true;
                    }
                    else if (poczatkowy_kolumna==docelowy_kolumna and poczatkowy_wiersz== 1 and docelowy_wiersz ==poczatkowy_wiersz+2 and (tab[docelowy_wiersz-1][docelowy_kolumna] ==' ' and (tab[docelowy_wiersz][docelowy_kolumna]==' ')))
                    {
                        poprawny = true;
                    }
                
            }
    if(poprawny)
    {
        if(docelowy_wiersz==7)
        {
            std::cout<<"wprowadz figure, ktora wybierzasz(np. H) : ";
            std::cin>>nowy_pionek;
            tab[poczatkowy_wiersz][poczatkowy_kolumna] = ' ';
            tab[docelowy_wiersz][docelowy_kolumna]=nowy_pionek;
        }
        else
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
    }
    else
    {
        std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
        ruchy(skad, dokad,kolor,tab);
    }

}
void ruch_wieza(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =true;
        if(poczatkowy_kolumna==docelowy_kolumna)
        {
            if(poczatkowy_wiersz>docelowy_wiersz)
            {
                for(int i = 1 ;i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
                {
                    if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna]!=' ')
                        poprawny=false;
                        if(!poprawny)
                            break;
                }
            }
            else if (poczatkowy_wiersz<docelowy_wiersz)
            {
                for(int i = 1 ;i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
                {
                    if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna]!=' ')
                        poprawny=false;
                        if(!poprawny)
                            break;
                }
            }
        }
        else if (poczatkowy_wiersz==docelowy_wiersz)
        {
            if(poczatkowy_kolumna>docelowy_kolumna)
            {
                for(int i = 1 ;i<abs(docelowy_kolumna-poczatkowy_kolumna);i++)
                {
                    if(tab[poczatkowy_wiersz][poczatkowy_kolumna-i]!=' ')
                        poprawny=false;
                        if(!poprawny)
                            break;
                }
            }
            else if (poczatkowy_kolumna<docelowy_kolumna)
            {
                for(int i = 1 ;i<abs(docelowy_kolumna-poczatkowy_kolumna);i++)
                {
                    if(tab[poczatkowy_wiersz][poczatkowy_kolumna+i]!=' ')
                        poprawny=false;
                        if(!poprawny)
                            break;
                }
            
            }
    
        
        }
    if(kolor)
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or islower(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
        
    }
    else
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or isupper(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
    }
}
void ruch_skoczek(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =false;
    
        if(poczatkowy_wiersz+2==docelowy_wiersz or poczatkowy_wiersz-2==docelowy_wiersz)
        {
            if(poczatkowy_kolumna+1==docelowy_kolumna or poczatkowy_kolumna-1==docelowy_kolumna)
            {
                poprawny=true;
            }
        }
        else if (poczatkowy_kolumna+2==docelowy_kolumna or poczatkowy_kolumna-2==docelowy_kolumna)
        {
            if(poczatkowy_wiersz+1==docelowy_wiersz or poczatkowy_wiersz-1==docelowy_wiersz)
            {
                poprawny=true;
            }
        }
    if(kolor)
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or islower(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
           std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
        
    }
    else
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or isupper(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
    }
             
}
void ruch_goniec(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =true;
        if(docelowy_kolumna>poczatkowy_kolumna and docelowy_wiersz>poczatkowy_wiersz)
        {
            for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna+i]!=' ')
                    poprawny=false;
                    if(!poprawny)
                        break;
            }
        }
        if(docelowy_kolumna<poczatkowy_kolumna and docelowy_wiersz>poczatkowy_wiersz)
        {
            for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz+i][poczatkowy_kolumna-i]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
        if(docelowy_kolumna<poczatkowy_kolumna and docelowy_wiersz<poczatkowy_wiersz)
        {
            for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna-i]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
        if(docelowy_kolumna>poczatkowy_kolumna and docelowy_wiersz<poczatkowy_wiersz)
        {
            for(int i = 1; i<abs(docelowy_wiersz-poczatkowy_wiersz);i++)
            {
                if(tab[poczatkowy_wiersz-i][poczatkowy_kolumna+i]!=' ')
                    poprawny=false;
                if(!poprawny)
                    break;
            }
        }
    if(kolor)
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or islower(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
           std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
        
    }
    else
    {
        if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or isupper(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
    }
}
void ruch_hetman(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    if(poczatkowy_kolumna==docelowy_kolumna)
        ruch_wieza(skad, dokad, kolor, tab);
    else
        ruch_goniec(skad, dokad, kolor,tab);
}
void ruch_krol(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    int poczatkowy_wiersz = 7-(skad[1]-49);
    int docelowy_wiersz = 7-(dokad[1]-49);
    int poczatkowy_kolumna = skad[0]-97;
    int docelowy_kolumna = dokad[0]-97;
    bool poprawny =false;
    
            if(poczatkowy_wiersz+1==docelowy_wiersz or poczatkowy_wiersz-1==docelowy_wiersz or poczatkowy_wiersz==docelowy_wiersz)
            {
                if(poczatkowy_kolumna==docelowy_kolumna or poczatkowy_kolumna+1==docelowy_kolumna or poczatkowy_kolumna-1 ==docelowy_kolumna)
                {
                    poprawny=true;
                }
            }
    if(!kolor)
    {
        if(poczatkowy_kolumna+2 == docelowy_kolumna and poczatkowy_wiersz == docelowy_wiersz and poczatkowy_wiersz ==7 and poczatkowy_kolumna ==4 and tab[7][5]==' ' and tab[7][6]==' ' and tab[7][7]=='w')
        {
            tab[7][4]=' ';
            tab[7][7]=' ';
            tab[7][5]='w';
            tab[7][6]='k';
        }
        else if(poczatkowy_kolumna-2 == docelowy_kolumna and poczatkowy_wiersz == docelowy_wiersz and poczatkowy_wiersz ==7 and poczatkowy_kolumna ==4 and tab[7][3]==' ' and tab[7][2]==' ' and tab[7][1]==' ' and tab[7][0]=='w')
        {
            tab[7][0]=' ';
            tab[7][1]=' ';
            tab[7][4]=' ';
            tab[7][3]='w';
            tab[7][2]='k';
        }
        else if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or isupper(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
    }
    else
    {
        if(poczatkowy_kolumna+2 == docelowy_kolumna and poczatkowy_wiersz == docelowy_wiersz and poczatkowy_wiersz ==0 and poczatkowy_kolumna ==4 and tab[0][5]==' ' and tab[0][6]==' ' and tab[0 ][7]=='W')
        {
            tab[0][4]=' ';
            tab[0][7]=' ';
            tab[0][5]='W';
            tab[0][6]='K';
        }
        else if(poczatkowy_kolumna-2 == docelowy_kolumna and poczatkowy_wiersz == docelowy_wiersz and poczatkowy_wiersz ==0 and poczatkowy_kolumna ==4 and tab[0][3]==' ' and tab[0][0]==' ' and tab[0][1]==' ' and tab[0][0]=='W')
        {
            tab[0][0]=' ';
            tab[0][1]=' ';
            tab[0][4]=' ';
            tab[0][3]='W';
            tab[0][2]='K';
        }
        else if(poprawny and (tab[docelowy_wiersz][docelowy_kolumna]==' ' or islower(tab[docelowy_wiersz][docelowy_kolumna])))
        {
            tab[docelowy_wiersz][docelowy_kolumna]=tab[poczatkowy_wiersz][poczatkowy_kolumna];
            tab[poczatkowy_wiersz][poczatkowy_kolumna]=' ';
        }
        else
        {
            std::cout<<"niedozwolony ruch, sprobuj ponownie: ";
            ruchy(skad, dokad,kolor,tab);
        }
    }
    
}

std::string ruchy(std::string skad,std::string dokad,int kolor, char tab[][8])
{
    std::cin>>dokad;
    switch (tab[7-(skad[1]-49)][skad[0]-97])
    {
        case 'p':
            ruch_pionek_bialy(kolor,skad,dokad,tab);
            break;
        case 'P':
            ruch_pionek_czarny(kolor,skad,dokad,tab);
            break;
        case 'W':
            ruch_wieza(skad, dokad,kolor,tab);
            break;
        case 'w':
            ruch_wieza(skad, dokad,kolor,tab);
            break;
        case 'S':
            ruch_skoczek(skad, dokad, kolor, tab);
            break;
        case 's':
            ruch_skoczek(skad, dokad, kolor, tab);
            break;
        case 'G':
            ruch_goniec(skad, dokad, kolor, tab);
            break;
        case 'g':
            ruch_goniec(skad, dokad, kolor, tab);
            break;
        case 'H':
            ruch_hetman(skad, dokad, kolor, tab);
            break;
        case 'h':
            ruch_hetman(skad, dokad, kolor, tab);
            break;
        case 'K':
            ruch_krol(skad, dokad,kolor,tab);
            break;
        case 'k':
            ruch_krol(skad, dokad,kolor,tab);
            break;
        default:
            break;
    }
    return dokad;

}
void czyszczenie_ekranu()
{
    for(int i = 0 ;i<100;i++)
        std::cout<<std::endl;
}
int zakonczenie_gry(int kolor, char tab[][8])
{
        if(!kolor)
        {
            for(int i = 0; i<8;i++)
            {
                for(int j = 0; j<8;j++)
                {
                    if(tab[i][j] =='K')
                        return 1;
                }
            }
        }
        else
        {
            for(int i = 0; i<8;i++)
            {
                for(int j = 0; j<8;j++)
                {
                    if(tab[i][j] =='k')
                        return 1;
                }
            }
        }
    return 0;
}

void dodaj_na_koniec(struct ruch * & pHead, struct ruch * & pTail, std::string skad, std::string dokad)
{
    if(pHead==nullptr)
    {
        ruch *pNowy = new ruch {skad,dokad,nullptr,nullptr};
        pTail = pNowy;
        pHead = pNowy;
    }
    else
    {
        ruch *pNowy = new ruch{skad,dokad,nullptr,pTail};
        pTail->nastepny=pNowy;
        pTail=pNowy;
    }
}
void wypisz_od_poczatku(struct ruch *pHead, std::ostream & ss)
{
    if(pHead)
    {
        ss<<pHead->skad<<"-";
        ss<<pHead->dokad<<std::endl;
        wypisz_od_poczatku(pHead->nastepny,ss);
    }
}
void usun_liste(struct ruch *& pHead)
{
    while(pHead)
    {
        ruch * pNastepnik = pHead->nastepny;
        delete pHead;
        pHead = pNastepnik;
    }
}
