#include "setprotect.h"

std::pair<int, int> SetProtect::createProtect(name_equipment N, type_equipment T){
    int mn, mx;
    if (T == type_equipment::helmet){
        mn = 1;
        mx = 3;
    } else if (T == type_equipment::bib){
        mn = 5;
        mx = 6;
    } else if (T == type_equipment::leggings){
        mn = 4;
        mx = 6;
    } else if (T == type_equipment::boots){
        mn = 2;
        mx = 4;
    } else{
        throw std::invalid_argument("Its not equipment");
    }
    if (N == name_equipment::leather){
        mn *= 1;
        mx *= 1;
    } else if (N == name_equipment::iron){
        mn *= 1.2;
        mx *= 1.2;
    } else if (N == name_equipment::gold){
        mn *= 1.6;
        mx *= 1.6;
    } else if (N == name_equipment::diamond){
        mn *= 2;
        mx *= 2;
    } else{
        throw std::invalid_argument("Its not equipment");
    }
    return std::make_pair(mn, mx);
}

int SetProtect::setBonus_Protect(type_artifact T){
    if (T == type_artifact::casual){
        return 5;
    } else if (T == type_artifact::rare){
        return 7;
    } else if (T == type_artifact::mythical){
        return 10;
    } else if (T == type_artifact::legendary){
        return 15;
    } else{
        throw std::invalid_argument("Its not artifact");
    }
}
