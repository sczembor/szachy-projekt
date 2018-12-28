//
//  struktury.hpp
//  szachy_projekt
//
//  Created by Stanislaw Czembor on 19/12/2018.
//  Copyright © 2018 Stanislaw Czembor. All rights reserved.
//

#ifndef struktury_hpp
#define struktury_hpp
#include <string>
#include <stdio.h>
struct ruch
{
    std::string skad;
    std::string dokad;
    ruch* nastepny;
    ruch* poprzedni;
};

#endif /* struktury_hpp */
