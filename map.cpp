#include "map.h"
#include <iostream>
#include "colors.h" 
using namespace std;  

// Constructeur de la classe Map
Map::Map() {
    initializeMap(); // Initialisation de la carte (remplissage avec des zéros)
    colors = Getceilcolor(); // Récupération des couleurs des blocs
}

// Initialisation de la grille : Remplit la matrice avec des zéros (cellules vides)
void Map::initializeMap() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            map[i][j] = 0; // 0 représente une cellule vide
        }
    }
}

// Affichage graphique de la carte en utilisant Raylib
void Map::Draw() {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            // Dessine un rectangle coloré correspondant à l'état de la cellule
            DrawRectangle(j * cellSize + 1, i * cellSize + 1, cellSize - 1, cellSize - 1, colors[map[i][j]]);
            
            // DrawRectangleLines(j * cellSize + 1, i * cellSize + 1, cellSize - 1, cellSize - 1, BLACK);
        }
    }
}

// Vérifie et élimine les lignes complètes, puis les décale vers le bas
int Map::EliminateAllLines() {
    int lines = 0; // Compteur du nombre de lignes supprimées

    for (int i = 0; i < numRows; i++) {
        if (isRowComplete(i)) { // Vérifie si la ligne est complète
            EliminateLine(i);   // Supprime la ligne
            MoveLinesDown(i, 1); // Décale les lignes supérieures vers le bas
            lines++; // Incrémente le nombre de lignes supprimées
        }
    }
    return lines; // Retourne le nombre total de lignes supprimées
}

// Vérifie si une ligne est complète (aucune cellule vide)
bool Map::isRowComplete(int row) const {
    for (int j = 0; j < numCols; j++) {
        if (map[row][j] == 0) { // Si une cellule est vide, la ligne n'est pas complète
            return false;
        }
    }
    return true; // La ligne est complète si toutes les cellules sont occupées
}

// Supprime une ligne en mettant toutes ses cellules à zéro
void Map::EliminateLine(int row) {
    for (int j = 0; j < numCols; j++) {
        map[row][j] = 0; // Remplace toutes les cellules de la ligne par 0
    } 
}

// Déplace toutes les lignes supérieures vers le bas après suppression d'une ligne
void Map::MoveLinesDown(int row, int numLines) {
    for (int i = row; i >= numLines; i--) { // Parcours des lignes à partir de la ligne supprimée
        for (int j = 0; j < numCols; j++) {
            map[i][j] = map[i - numLines][j]; // Déplace la ligne du dessus vers celle du dessous
            map[i - numLines][j] = 0; // Remplace l'ancienne ligne par des cellules vides
        }
    }
}
