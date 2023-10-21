#ifndef DUNGEON_H
#define DUNGEON_H
#include <vector>
#include<fstream>
#include "matrix.h"
#include "cell.h"
class Dungeon{

private:
    Matrix<Cell>* levels;
public:
    Dungeon();
    /*~Dungeon() {delete [] levels; }*/
    Matrix<Cell>* getLevels() {return levels;}
};

#endif // DUNGEON_H
