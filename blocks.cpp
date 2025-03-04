#include "position.h"
#include "block.h"

// Classe représentant le bloc en forme de "L"
class LBlock : public Block {
public:
    LBlock() {
        id = 1;
        // Définit les différentes rotations du bloc "L"
        cells[0] = {Position(0,2), Position(1,0), Position(1,1), Position(1,2)};
        cells[1] = {Position(0,1), Position(1,1), Position(2,1), Position(2,2)};
        cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,0)};
        cells[3] = {Position(0,0), Position(0,1), Position(1,1), Position(2,1)};
        move(0, 3); //
    }
    void rotate();
};

// Classe représentant le bloc en forme de "J"
class JBlock : public Block {
public:
    JBlock() {
        id = 2;
        // Définit les différentes rotations du bloc "J"
        cells[0] = {Position(0,0), Position(1,0), Position(1,1), Position(1,2)};
        cells[1] = {Position(0,1), Position(0,2), Position(1,1), Position(2,1)};
        cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,2)};
        cells[3] = {Position(0,1), Position(1,1), Position(2,0), Position(2,1)};
        move(0, 3);// Décalage initial
    }
    void rotate();
};

// Classe représentant le bloc en forme de "I"
class IBlock : public Block {
public:
    IBlock() {
        id = 3;
        // Définit les deux orientations du bloc "I" (horizontale et verticale)
        cells[0] = {Position(0,0), Position(1,0), Position(2,0), Position(3,0)};
        cells[1] = {Position(0,0), Position(0,1), Position(0,2), Position(0,3)};
        cells[2] = cells[0]; // Identique à la première orientation
        cells[3] = cells[1]; // Identique à la deuxième orientation
        move(0, 3);// Décalage initial
    }
    void rotate();
};

// Classe représentant le bloc en forme de "O" (ne tourne pas)
class OBlock : public Block {
public:
    OBlock() {
        id = 4;
        // Bloc carré qui reste identique dans toutes les rotations
        cells[0] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
        cells[1] = cells[0];
        cells[2] = cells[0];
        cells[3] = cells[0];
        move(0, 4);// Décalage initial
    }
    void rotate() {} // OBlock ne tourne pas
};

// Classe représentant le bloc en forme de "S"
class SBlock : public Block {
public:
    SBlock() {
        id = 5;
        // Définit les deux orientations du bloc "S"
        cells[0] = {Position(0,1), Position(0,2), Position(1,0), Position(1,1)};
        cells[1] = {Position(0,0), Position(1,0), Position(1,1), Position(2,1)};
        cells[2] = cells[0]; // Identique à la première orientation
        cells[3] = cells[1]; // Identique à la deuxième orientation
        move(0, 3);// Décalage initial
    }
    void rotate();
};

// Classe représentant le bloc en forme de "T"
class TBlock : public Block {
public:
    TBlock() {
        id = 6;
        // Définit les différentes rotations du bloc "T"
        cells[0] = {Position(0,1), Position(1,0), Position(1,1), Position(1,2)};
        cells[1] = {Position(0,1), Position(1,1), Position(1,2), Position(2,1)};
        cells[2] = {Position(1,0), Position(1,1), Position(1,2), Position(2,1)};
        cells[3] = {Position(0,1), Position(1,0), Position(1,1), Position(2,1)};
        move(0, 3);// Décalage initial
    }
    void rotate();
};

// Classe représentant le bloc en forme de "Z"
class ZBlock : public Block {
public:
    ZBlock() {
        id = 7;
        // Définit les deux orientations du bloc "Z"
        cells[0] = {Position(0,0), Position(0,1), Position(1,1), Position(1,2)};
        cells[1] = {Position(0,2), Position(1,1), Position(1,2), Position(2,1)};
        cells[2] = cells[0]; // Identique à la première orientation
        cells[3] = cells[1]; // Identique à la deuxième orientation
        move(0, 3);// Décalage initial
    }
    void rotate();
};
