#ifndef CELL_H
#define CELL_H

enum class type_cell{
    floor,
    open_door,
    close_door,
    up_lader,
    down_lader,
    wall,
    hero,
};
class Character;

class Cell{
    private:
        type_cell type;
        int i;
        int j;
        /*Item
         * chest*/
    public:
        Cell();
        Cell(type_cell t, int h, int w): type(t), i(h), j(w){}
        type_cell getType() {return type; }
        Cell& setType(type_cell t) { type = t; return *this;}
        Cell operator=(const Cell &c);
        int getI() { return i; }
        int getJ() { return j; }
};

#endif // CELL_H
