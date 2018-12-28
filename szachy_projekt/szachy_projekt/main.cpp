//
//  main.cpp
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


int kolor = 0; //biale pionki sa male
//czarne pionki to duze litery
int koniec =1;
const int N = 8;
char szachownica[N][N];
int main()
{
    struct ruch *pHead = nullptr;
    struct ruch *pTail = nullptr;
    reset_szachownicy(szachownica, N);
    while(koniec)
    {
        wyswietl_szachownice(szachownica,N);
        gra(pHead,pTail,kolor,szachownica);
        koniec =zakonczenie_gry(kolor, szachownica);
        if(kolor==0)
            kolor =1;
        else
            kolor =0;
        czyszczenie_ekranu();
        
        //funkcja czyszcząca ekran
    }
    if(kolor)
        std::cout<<"wygraly biale!"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    
    else
        std::cout<<"wygraly czarne!"<<std::endl<<std::endl<<std::endl<<std::endl<<std::endl;
    wypisz_od_poczatku(pHead,std::cout);
    usun_liste(pHead);
    return 0;
}
