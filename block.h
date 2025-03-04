#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"
#include <raylib.h>

class Block {
public:
    Block(); // Constructeur par défaut

    /**
     * @brief Dessine le bloc actuel sur la grille de jeu.
     */
    void Draw();

    /**
     * @brief Dessine le bloc dans la zone de prévisualisation du prochain bloc.
     */
    void DrawNext(int x , int  y );

   
    void move(int rows, int columns);

    /**
     * @brief Retourne les positions des cellules occupées par le bloc dans la grille.
     * @return Un vecteur contenant les positions des cellules.
     */
    std::vector<Position> getCeilPositions() const;

    /**
     * @brief Fait pivoter le bloc dans le sens horaire.
     */
    void rotate();

    void setPosition(int row, int col);

    int id; // Identifiant du type de bloc (T, L, Z, etc.)
    /**
     * @brief Contient toutes les configurations des blocs pour chaque rotation.
     * La clé est l'état de rotation, et la valeur est une liste de positions relatives.
     */
    std::map<int, std::vector<Position>> cells;
private:
    

    static constexpr int ceilSize = 30; // Taille d'une cellule du bloc
    int rotateState; // État actuel de la rotation (0 à 3)
    
    std::vector<Color> colors; // Liste des couleurs associées aux blocs

    int rowOffset; // Décalage de ligne (position du bloc dans la grille)
    int columnOffset; // Décalage de colonne

    /**
     * @brief Déplace le bloc d'une ligne vers le bas (utilisé pour la gravité).
     */
    void moveBlockDown();

    
};
