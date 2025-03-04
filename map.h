#pragma once

#include <vector>
#include <raylib.h>

class Map {
public:
    Map();
    static constexpr int numRows = 20;  // Nombre de lignes de la grille
    static constexpr int numCols = 10;  // Nombre de colonnes de la grille
    static constexpr int cellSize = 30; // Taille d'une cellule (modifiable selon l'affichage) en pixel
    int map[numRows][numCols]; // Matrice représentant la carte
     

    void initializeMap();
    void Draw(); // Affiche la carte

    bool CheckCellOutside(int row, int column) const {
        return row < 0 || row >= numRows || column < 0 || column >= numCols;
    }

    bool IsCellEmpty(int row, int column) const {
        return map[row][column] == 0;
    }

    int EliminateAllLines(); // Supprime toutes les lignes complètes et retourne le nombre supprimé

private:
    std::vector<Color> colors; // Couleurs des blocs

    bool isRowComplete(int row) const; // Vérifie si une ligne est complète
    void EliminateLine(int row); // Supprime une ligne spécifique
    void MoveLinesDown(int row, int numLines); // Décale les lignes vers le bas après suppression
};
