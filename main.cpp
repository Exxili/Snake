#include <iostream>
#include <vector>
#include <raylib.h>

using namespace std;

const int screenWidth = 800;
const int screenHeight = 600;
const int cellSize = 20;

struct SnakeSegment
{
    int x, y;
};

vector<SnakeSegment> snake;
int foodX, foodY;
int dirX = 1, dirY = 0; // Initial direction of the snake (right)

void ResetGame()
{
    snake.clear();
    // Snake starts in the middle of screen
    snake.push_back({screenWidth / 2, screenHeight / 2});

    // Reset food position
    foodX = (rand() % (screenWidth / cellSize)) * cellSize;
    foodY = (rand() % (screenHeight / cellSize)) * cellSize;
}

bool CheckCollision()
{
    for (size_t i = 1; i < snake.size(); i++)
    {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
        {
            return true;
        }
    }
    return snake[0].x < 0 || snake[0].x >= screenWidth || snake[0].y < 0 || snake[0].y >= screenHeight;
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(10); // Slower fps for a snake game - If this is too fast game is unplayable

    ResetGame();

    while (!WindowShouldClose())
    {

        // Key Controls
        if (IsKeyPressed(KEY_RIGHT) && dirX == 0)
        {
            dirX = 1;
            dirY = 0;
        }

        if (IsKeyPressed(KEY_LEFT) && dirX == 0)
        {
            dirX = -1;
            dirY = 0;
        }

        if (IsKeyPressed(KEY_UP) && dirY == 0)
        {
            dirX = 0;
            dirY = -1;
        }

        if (IsKeyPressed(KEY_DOWN) && dirY == 0)
        {
            dirX = 0;
            dirY = 1;
        }

        // Create the Snake
        SnakeSegment newHead = {snake[0].x + dirX * cellSize, snake[0].y + dirY * cellSize};
        snake.insert(snake.begin(), newHead);

        if (snake[0].x == foodX && snake[0].y == foodY)
        {
            foodX = (rand() % (screenWidth / cellSize)) * cellSize;
            foodY = (rand() % (screenHeight / cellSize)) * cellSize;
        }
        else
        {
            snake.pop_back();
        }

        if (CheckCollision())
        {
            ResetGame();
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (const SnakeSegment &segment : snake)
        {
            DrawRectangle(segment.x, segment.y, cellSize, cellSize, GREEN);
        }

        DrawRectangle(foodX, foodY, cellSize, cellSize, RED);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}