#include <raylib.h>
#include "game.h"
#include <SFML/Network.hpp>
#include <iostream>
bool gameOverDisplayed = false; 
    int serverScore=0;
bool clientGameOver = false; // Track if the client has lost
bool serverGameOver = false; // Track if the server has lost

const int screenWidth = 800;
const int screenHeight = 600;
const Color bgcolor = { 80, 80, 80, 255 };

bool serverReady = false;
bool clientReady = false;

bool gameStarted = false;
Game game;
double startTime = 0.0;
double bestTime = 0.0;
double lastGameTime = 0.0; // Stores the last game's elapsed time

void DrawUI() {

 DrawText("Opponent's Score:", 550, 80, 20, WHITE);
    DrawText(TextFormat("%d", serverScore), 550, 110, 20, WHITE);
    // Score display
    DrawText("Score:", 550, 20, 20, WHITE);
    DrawText(TextFormat("%d", game.score), 550, 50, 20, WHITE);

     DrawText("PLAYER 2", 400, 20, 20, WHITE);
    DrawText(TextFormat("%d", game.score), 550, 50, 20, WHITE);

    // Timer display
    DrawText("Time:", 550, 140, 20, WHITE);
    if (game.EndGame) {
        // Show the last game's time if the game is over
        DrawText(TextFormat("%.1f sec", lastGameTime), 550, 170, 20, WHITE);
    } else if (gameStarted) {
        // Show the current elapsed time
        double gameTime = GetTime() - startTime;
        DrawText(TextFormat("%.1f sec", gameTime), 550, 170, 20, WHITE);
    }

 

  if (!clientReady && !gameStarted) {
        // Show "Start" if the client has not clicked the button yet
        DrawRectangle(650, 500, 100, 40, RED);
        DrawText("Start", 670, 510, 20, WHITE);
    } else if (clientReady && !serverReady && !gameStarted) {
        // Show "Waiting" if the client is ready but the server isn't yet
        DrawRectangle(650, 500, 100, 40, GREEN);
        DrawText("Waiting", 660, 510, 20, WHITE);
    }

    // Game Over message
    if (game.EndGame) {
        DrawText("GAME OVER", 200, 250, 60, RED);
       }
       
 if (serverGameOver && clientGameOver) {
        if (game.score > serverScore) {
            DrawText("YOU WON", 300, 320, 40, GREEN);
        } else if (game.score < serverScore){
            DrawText("YOU LOST", 300, 320, 40, RED);
        }else{
        	DrawText("DRAW", 300, 320, 40, WHITE);
        }
        gameOverDisplayed = true; 
    }
}


int main() {
    sf::TcpSocket socket;
    if (socket.connect("192.168.100.235", 53000) != sf::Socket::Done) {
        std::cerr << "Failed to connect to server!" << std::endl;
        return -1;
    }
    std::cout << "Connected to server!" << std::endl;

    InitWindow(screenWidth, screenHeight, "raylib Tetris");
    SetTargetFPS(10);

    while (!WindowShouldClose()) {
        // Handle Start/Restart Button Click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    Vector2 mouse = GetMousePosition();
    if (mouse.x >= 650 && mouse.x <= 750 && mouse.y >= 500 && mouse.y <= 540) {
        std::cout << "Button clicked" << std::endl;

        if (!clientReady) {
            clientReady = true; // Set client ready

            // Send clientReady to server
            sf::Packet sendClientReadyPacket;
            sendClientReadyPacket << clientReady;
            if (socket.send(sendClientReadyPacket) != sf::Socket::Done) {
                std::cerr << "Failed to send clientReady to server." << std::endl;
            }
        }

        // Receive serverReady
        sf::Packet receiveServerReadyPacket;
        if (socket.receive(receiveServerReadyPacket) == sf::Socket::Done) {
            if (receiveServerReadyPacket >> serverReady) {
                std::cout << "ServerReady: " << serverReady << std::endl;
            } else {
                std::cerr << "Failed to extract serverReady from packet!" << std::endl;
            }
        } else {
            std::cerr << "Failed to receive serverReady!" << std::endl;
        }

        // Start the game if both are ready
        if (clientReady && serverReady && !gameStarted) {
            gameStarted = true;
            startTime = GetTime();
            game.restart();
        }
    }
}


      if (gameStarted) {
    // Send client's score and game-over status to server
    sf::Packet sendPacket;
    sendPacket << game.score << clientGameOver;
    if (socket.send(sendPacket) != sf::Socket::Done) {
        std::cerr << "Failed to send score and game-over status to server." << std::endl;
    }

    // Receive server's score and game-over status
    sf::Packet receivePacket;
    if (socket.receive(receivePacket) == sf::Socket::Done) {
        if (receivePacket >> serverScore >> serverGameOver) {
            std::cout << "Server's score: " << serverScore << std::endl;
            std::cout << "Server Game Over: " << serverGameOver << std::endl;
        } else {
            std::cerr << "Failed to extract data from server packet!" << std::endl;
        }
    }

    // Handle client's game logic
    if (!game.EndGame) {
        game.PressKey();
        game.moveBlockDown();
    } else {
        clientGameOver = true; // Mark the client as having lost
    }

    if (game.EndGame) {
        double gameTime = GetTime() - startTime;
        lastGameTime = gameTime; // Store the last game's elapsed time
        if (gameTime > bestTime) bestTime = gameTime;
    }

    // Check if both players have lost
    if (serverGameOver && clientGameOver) {
    
    
    // Send client's score and game-over status to server
    sf::Packet sendPacket;
    sendPacket << game.score << clientGameOver;
    if (socket.send(sendPacket) != sf::Socket::Done) {
        std::cerr << "Failed to send score and game-over status to server." << std::endl;
    }

    // Receive server's score and game-over status
    sf::Packet receivePacket;
    if (socket.receive(receivePacket) == sf::Socket::Done) {
        if (receivePacket >> serverScore >> serverGameOver) {
            std::cout << "Server's score: " << serverScore << std::endl;
            std::cout << "Server Game Over: " << serverGameOver << std::endl;
        } else {
            std::cerr << "Failed to extract data from server packet!" << std::endl;
        }
    }
    
    
    
        gameStarted = false; // Stop the game
        std::cout << "Both players lost. Game over." << std::endl;
        
    }
    if(serverGameOver && clientGameOver){
    BeginDrawing();
       if (game.score > serverScore) {
            DrawText("YOU WON", 300, 320, 40, GREEN);
        } else if (game.score < serverScore){
            DrawText("YOU LOST", 300, 320, 40, RED);
        }else{
        	DrawText("DRAW", 300, 320, 40, WHITE);
        }
        EndDrawing();
    
    }
}


        BeginDrawing();
        ClearBackground(bgcolor);
        game.draw();  // Draw game grid
        DrawUI();     // Draw UI elements
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

