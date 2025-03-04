#include "game.h"
#include <cstdlib>  // Utilisation de rand()
#include "block.h"

Game::Game() {
    map = Map();
    blocks = getBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    EndGame = false;
}

Block Game::getRandomBlock() {
    return blocks[rand() % blocks.size()];
}

std::vector<Block> Game::getBlocks() {
    return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::draw() {
    // DrawRectangle(5, 5, 400 + 10, 600 + 10, BROWN);  // Cadre en bois
     //DrawRectangleLines(5, 5, 400 + 10, 600 + 10, DARKBROWN); // Contour plus foncé

    map.Draw();
    currentBlock.Draw();

    // Afficher le prochain bloc
    nextBlock.DrawNext(550, 270); // Affiche le prochain bloc dans la zone de prévisualisation
}

void Game::PressKey() {
    int Keypressed = GetKeyPressed();

    if (EndGame) {
        if (Keypressed != 0) {
            EndGame = false;
            restart();
        }
        return;
    }

    if (Keypressed == KEY_DOWN) {
        currentBlock.move(1, 0);
        if (IsBlockOutside() || !CanBlockSit()) {
            currentBlock.move(-1, 0);
        }
    }
    else if (Keypressed == KEY_LEFT) {
        currentBlock.move(0, -1);
        if (IsBlockOutside() || !CanBlockSit()) {
            currentBlock.move(0, 1);
        }
    }
    else if (Keypressed == KEY_RIGHT) {
        currentBlock.move(0, 1);
        if (IsBlockOutside() || !CanBlockSit()) {
            currentBlock.move(0, -1);
        }
    }
    else if (Keypressed == KEY_UP) {
        rotateBlock();
        if (IsBlockOutside() || !CanBlockSit()) {
            rotateBlock();
            rotateBlock();
            rotateBlock();
        }
    }
}

bool Game::IsBlockOutside() {
    for (const Position& ceil : currentBlock.getCeilPositions()) {
        if (map.CheckCellOutside(ceil.row, ceil.column)) {
            return true;
        }
    }
    return false;
}

void Game::rotateBlock() {
    currentBlock.rotate();
}

bool Game::CanBlockSit() {
    for (const Position& ceil : currentBlock.getCeilPositions()) {
        if (!map.IsCellEmpty(ceil.row, ceil.column)) {
            return false;
        }
    }
    return true;
}

void Game::restart() {
    map.initializeMap();
    blocks = getBlocks();
    currentBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    score = 0;  // Reset score, but NOT bestScore
    EndGame = false;
}

void Game::moveBlockDown() {
    if (EndGame) return;

    currentBlock.move(1, 0);
    if (IsBlockOutside() || !CanBlockSit()) {
        currentBlock.move(-1, 0);
        lockMoving();
    }
}

void Game::lockMoving() {
    for (const Position& ceil : currentBlock.getCeilPositions()) {
        map.map[ceil.row][ceil.column] = currentBlock.id;
    }

    currentBlock = nextBlock;
    nextBlock = getRandomBlock();

    if (!CanBlockSit()) {
        EndGame = true;
        score = 0;
    }
    else {
        int linesCleared = map.EliminateAllLines();
        updateScore(linesCleared);
    }
}

int Game::updateScore(int lines) {
    if (lines == 1) score += 40;
    else if (lines == 2) score += 100;
    else if (lines == 3) score += 300;
    else if (lines == 4) score += 1200;
    if (score > bestScore) {  // Update best score
        bestScore = score;
    }
    return score;
}
int Game::getBestScore() const { return bestScore; }

