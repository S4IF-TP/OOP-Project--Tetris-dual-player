#pragma once 

#include "map.h"    
#include "blocks.cpp"

class Game {
public:
    Game(); // Constructeur de la classe Game

    Map map; // Objet représentant la carte de jeu

    Block getRandomBlock(); // Génère un bloc aléatoire

    std::vector<Block> getBlocks(); // Retourne la liste des blocs actifs dans le jeu

    void draw(); // Affiche l'état actuel du jeu

    void PressKey(); // Gère les entrées utilisateur pour déplacer ou faire tourner le bloc

    void moveBlock(int rowOffset, int colOffset);

    int score; // Score du joueur

    void moveBlockDown(); // Fait descendre le bloc en cours

    void lockMoving(); // Verrouille le bloc lorsqu'il atteint sa position finale

    int updateScore(int lines); // Met à jour le score en fonction du nombre de lignes complétées

    int getBestScore() const;

    void drawNextBlock();

    bool EndGame; // Indique si la partie est terminée
        
    int bestScore = 0;  // Best score storage

    void restart(); // Réinitialise la partie pour recommencer

    

    


private:
    std::vector<Block> blocks; // Liste des blocs utilisés dans le jeu
    Block currentBlock; // Bloc actuellement en jeu
    Block nextBlock; // Bloc suivant qui apparaîtra

    bool IsBlockOutside(); // Vérifie si le bloc est en dehors des limites du plateau

    void rotateBlock(); // Gère la rotation du bloc actuel

    bool CanBlockSit(); // Vérifie si le bloc peut se poser à sa position actuelle
};
