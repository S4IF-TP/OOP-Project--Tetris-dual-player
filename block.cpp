#include "block.h"

/**
 * @brief Constructeur de la classe Block.
 * Initialise la taille d'une cellule, l'état de rotation, les couleurs et les offsets de position.
 */
Block::Block() {
    rotateState = 0; // Initialisation de l'état de rotation à 0
    rowOffset = 0;   // Décalage initial en ligne
    columnOffset = 0; // Décalage initial en colonne
    colors = Getceilcolor(); // Récupération des couleurs définies

    // Vérification que la taille du vecteur colors est suffisante pour éviter les erreurs d'accès
    if (colors.empty()) {
        colors.push_back(WHITE); // Ajout d'une couleur par défaut si la liste est vide
    }
}

/**
 * @brief Dessine le bloc sur la grille de jeu.
 * Chaque cellule du bloc est dessinée selon sa position actuelle et sa couleur.
 */
void Block::Draw() {
    std::vector<Position> currentCells = getCeilPositions();

    // Vérification que l'ID est valide pour éviter une erreur d'accès dans colors
    if (id < 0 || id >= static_cast<int>(colors.size())) {
        return; // Ne rien dessiner si l'ID est hors limites
    }

    for (const auto& cell : currentCells) {
        DrawRectangle(
            cell.column * ceilSize + 1,
            cell.row * ceilSize + 1,
            ceilSize - 1,
            ceilSize - 1,
            colors[id]
        );
    }
}

/**
 * @brief Dessine le bloc dans la zone de prévisualisation du prochain bloc.
 * Cette fonction est utilisée pour afficher le prochain bloc en attente.
 */
void Block::DrawNext(int X , int Y) {
    std::vector<Position> p = getCeilPositions(); 
    for (Position c : p) {
        DrawRectangle(c.column * ceilSize + X, c.row * ceilSize + Y, ceilSize - 1, ceilSize - 1, colors[id]); 
    }
}

/**
 * @brief Déplace le bloc d'un certain nombre de lignes et colonnes.
 * @param rows Nombre de lignes de déplacement (positif vers le bas, négatif vers le haut).
 * @param columns Nombre de colonnes de déplacement (positif vers la droite, négatif vers la gauche).
 */
void Block::move(int rows, int columns) {
    rowOffset += rows;
    columnOffset += columns;
}

/**
 * @brief Retourne les positions absolues des cellules du bloc sur la grille.
 * @return Un vecteur contenant les positions des cellules du bloc.
 */
std::vector<Position> Block::getCeilPositions() const {
    std::vector<Position> positions;

    // Vérification que l'état de rotation est bien défini dans `cells`
    auto it = cells.find(rotateState);
    if (it == cells.end()) {
        return positions; // Retourne un vecteur vide si la rotation n'est pas définie
    }

    for (const auto& cell : it->second) {
        positions.emplace_back(cell.row+rowOffset , cell.column+columnOffset );
    }

    return positions;
}

/**
 * @brief Fait pivoter le bloc dans le sens horaire.
 * La rotation alterne entre 4 états (0, 1, 2, 3).
 */
void Block::rotate() {
    rotateState = (rotateState + 1) % 4;
}

// void Block::setPosition(int row, int col) {
//     if (cells.empty()) return;  // Safety check

//     // Get the first available key in the map
//     auto firstKey = cells.begin()->first;
//     auto& firstVec = cells[firstKey];

//     if (firstVec.empty()) return;  // Safety check

//     int rowOffset = row - firstVec[0].row;
//     int colOffset = col - firstVec[0].column;

//     // Update all positions in the map
//     for (auto& [key, vec] : cells) {
//         for (auto& cell : vec) {
//             cell.row += rowOffset;
//             cell.column += colOffset;
//         }
//     }
// }

