//
//  funkcje.hpp
//  szachy_projekt
//
//  Created by Stanislaw Czembor on 10/12/2018.
//  Copyright © 2018 Stanislaw Czembor. All rights reserved.
//

#ifndef funkcje_hpp
#define funkcje_hpp

#include <string>
void wyswietl_szachownice(char tab[][8],const int ROZMIAR);
void reset_szachownicy(char tab[][8],const int ROZMIAR);//funkcja ustawia pionki na szachownicy w pozycji poczatkowej
void gra(struct ruch * & pHead, struct ruch * & pTail,int kolor,char tab[][8]);
int czy_poprawny_pionek(std::string skad,int kolor,char tab[][8]);
void ruch_pionek_bialy(int kolor,std::string skad,std::string dokad, char tab[][8]);//funkcja wykonujaca ruch pionka bialego
void ruch_pionek_czarny(int kolor,std::string skad,std::string dokad, char tab[][8]);//funkcja wykonujaca ruch pionka czarnego
void ruch_wieza(std::string skad,std::string dokad,int kolor, char tab[][8]);//funkcja ruszajaca wierza
void ruch_skoczek(std::string skad,std::string dokad,int kolor, char tab[][8]);
void ruch_goniec(std::string skad,std::string dokad,int kolor, char tab[][8]);
void ruch_hetman(std::string skad,std::string dokad,int kolor, char tab[][8]);
void ruch_krol(std::string skad,std::string dokad,int kolor, char tab[][8]);
std::string ruchy(std::string skad,std::string dokad,int kolor, char tab[][8]);
void czyszczenie_ekranu();
int szachowanie();//jezeli funkcja zwraca jeden to pozwala na wykonanie ruchu co oznacza ze po wykonaniu tego ruchu twoj krol nie znajdzie sie w pozycji szach, w przeciwnym przypadku zwraca zero;
int zakonczenie_gry(int kolor,char tab[][8]);//funckja sprawdzajaca czy w poprzednim ruchu nie zsotal zbity krol;
void dodaj_na_koniec(struct ruch *  &pHead, struct ruch * & pTail, std::string skad, std::string dokad);
void wypisz_od_poczatku(struct ruch *pHead, std::ostream & ss);
void usun_liste(struct ruch *&pHead);
#endif /* funkcje_hpp */

