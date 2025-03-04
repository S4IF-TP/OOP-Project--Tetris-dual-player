**Important : Il faut telecharger les bibliotheques RayLib et SFML sur Linux.

*commandes pour compiler et executer les fichiers TETRISserver.cpp et TETRISclient.cpp
g++ TETRISserver.cpp game.cpp position.cpp map.cpp colors.cpp blocks.cpp block.cpp -o tetris1 -lraylib -lm -lpthread -ldl -lrt -lX11 -lsfml-network -lsfml-system

g++ TETRISclient.cpp game.cpp position.cpp map.cpp colors.cpp blocks.cpp block.cpp -o tetris2 -lraylib -lm -lpthread -ldl -lrt -lX11 -lsfml-network -lsfml-system

(il faut executer dans deux terminaux differents)

terminal 1 : ./tetris1

terminal 2 : ./tetris2

*Comment jouer : il faut cliquer sur START pour les deux joueurs pour commencer le jeu.



