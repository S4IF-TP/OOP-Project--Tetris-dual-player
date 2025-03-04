#include <raylib.h>
#include "game.h"
#include <SFML/Network.hpp>
#include <iostream>
bool gameOverDisplayed = false;
 int clientScore = 0;
bool serverGameOver = false; // Track if the server has lost
bool clientGameOver = false; // Track if the client has lost

const int screenWidth = 800;
const int screenHeight = 600;
const Color bgcolor = {80, 80, 80, 255};

bool serverReady = false;
bool clientReady = false;
bool gameStarted = false;
Game game;
double startTime = 0.0;
double bestTime = 0.0;
double lastGameTime = 0.0;

void DrawUI() {
DrawText("Opponent's Score:", 550, 80, 20, WHITE);
    DrawText(TextFormat("%d", clientScore), 550, 110, 20, WHITE);

    // Score display
    DrawText("Score:", 550, 20, 20, WHITE);
    DrawText(TextFormat("%d", game.score), 550, 50, 20, WHITE);


 DrawText("PLAYER 1", 400, 20, 20, WHITE);
    DrawText(TextFormat("%d", game.score), 550, 50, 20, WHITE);
  

    // Timer display
    DrawText("Time:", 550, 140, 20, WHITE);
    if (game.EndGame) {
        DrawText(TextFormat("%.1f sec", lastGameTime), 550, 170, 20, WHITE);
    } else if (gameStarted) {
        double gameTime = GetTime() - startTime;
        DrawText(TextFormat("%.1f sec", gameTime), 550, 170, 20, WHITE);
    }

  

    // Start/Waiting button
    if (!gameStarted) {
        if (serverReady && !clientReady) {
            DrawRectangle(650, 500, 100, 40, GREEN);
            DrawText("Waiting", 670, 510, 20, WHITE);
        } else if (!serverReady) {
            DrawRectangle(650, 500, 100, 40, RED);
            DrawText("Start", 670, 510, 20, WHITE);
        }
    }

    // Game Over message
    if (game.EndGame) {
        DrawText("GAME OVER", 200, 250, 60, RED);
         
    }
    if (clientGameOver && serverGameOver) {
        if (clientScore > game.score) {
            DrawText("YOU LOST", 300, 320, 40, RED);
        } else if (clientScore < game.score){
            DrawText("YOU WON", 300, 320, 40, GREEN);
        }else{
        DrawText("DRAW", 300, 320, 40, WHITE);
        }
        gameOverDisplayed = true; // Indicate that the game over message is displayed
    }
}

int main() {
    sf::TcpListener listener;
    listener.listen(53000); // Listening on port 53000

    sf::TcpSocket client;
    listener.accept(client); // Wait for a client to connect
    std::cout << "Client connected!" << std::endl;

    InitWindow(screenWidth, screenHeight, "raylib Tetris");
    SetTargetFPS(10); // Set a higher target FPS

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(bgcolor);
        game.draw();  // Draw game grid
        DrawUI();     // Draw UI elements
        EndDrawing();

        // Handle Start/Waiting Button Click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            if (mouse.x >= 650 && mouse.x <= 750 && mouse.y >= 500 && mouse.y <= 540) {
                std::cout << "clicked" << std::endl;

                // Toggle server readiness
                if (!serverReady) {
                    serverReady = true;
                }

                // Update best time if the game ended
                if (gameStarted && game.EndGame) {
                    double gameTime = GetTime() - startTime;
                    lastGameTime = gameTime; // Store the last game's elapsed time
                    if (gameTime > bestTime) {
                        bestTime = gameTime;
                    }
                }

                // Send serverReady to client
                sf::Packet sendServerReadyPacket;
                sendServerReadyPacket << serverReady;
                if (client.send(sendServerReadyPacket) != sf::Socket::Done) {
                    std::cerr << "Failed to send serverReady to client." << std::endl;
                }

                // Receive clientReady
                sf::Packet receiveClientReadyPacket;
                if (client.receive(receiveClientReadyPacket) == sf::Socket::Done) {
                    if (receiveClientReadyPacket >> clientReady) {
                        std::cout << "ClientReady: " << clientReady << std::endl;
                    } else {
                        std::cerr << "Failed to extract clientReady from packet!" << std::endl;
                    }
                } else {
                    std::cerr << "Failed to receive clientReady!" << std::endl;
                }

                if (clientReady && serverReady && !gameStarted) {
                    // Reset the game
                    gameStarted = true;
                    startTime = GetTime();
                    game.restart();
                }
            }
        }

       if (gameStarted) {
    // Send server score and game-over status to client
    sf::Packet sendPacket;
    sendPacket << game.score << serverGameOver;
    if (client.send(sendPacket) != sf::Socket::Done) {
        std::cerr << "Failed to send score and game-over status to client." << std::endl;
    }

    // Receive client's score and game-over status
    sf::Packet receivePacket;
    if (client.receive(receivePacket) == sf::Socket::Done) {
        if (receivePacket >> clientScore >> clientGameOver) {
            std::cout << "Client's score: " << clientScore << std::endl;
            std::cout << "Client Game Over: " << clientGameOver << std::endl;
        } else {
            std::cerr << "Failed to extract data from client packet!" << std::endl;
        }
    }

    // Handle server's game logic
    if (!game.EndGame) {
        game.PressKey();
        game.moveBlockDown();
    } else {
        serverGameOver = true; // Mark the server as having lost
    }

    // Check if both players have lost
    if (serverGameOver && clientGameOver) {
    
     // Send server score and game-over status to client
    sf::Packet sendPacket;
    sendPacket << game.score << serverGameOver;
    if (client.send(sendPacket) != sf::Socket::Done) {
        std::cerr << "Failed to send score and game-over status to client." << std::endl;
    }

    // Receive client's score and game-over status
    sf::Packet receivePacket;
    if (client.receive(receivePacket) == sf::Socket::Done) {
        if (receivePacket >> clientScore >> clientGameOver) {
            std::cout << "Client's score: " << clientScore << std::endl;
            std::cout << "Client Game Over: " << clientGameOver << std::endl;
        } else {
            std::cerr << "Failed to extract data from client packet!" << std::endl;
        }
    }
    
    
        gameStarted = false; // Stop the game
        double gameTime = GetTime() - startTime;
        lastGameTime = gameTime; // Store the last game's elapsed time
        if (gameTime > bestTime) bestTime = gameTime;
        std::cout << "Both players lost. Game over." << std::endl;
       
    }
    if (serverGameOver && clientGameOver){
     BeginDrawing();
      if (clientScore > game.score) {
            DrawText("YOU LOST", 300, 320, 40, RED);
        } else if (clientScore < game.score){
            DrawText("YOU WON", 300, 320, 40, GREEN);
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

