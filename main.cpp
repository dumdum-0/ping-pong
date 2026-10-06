#include "raylib.h"

class Ball
{
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw()
    {
        DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
    }

    void Update()
    {
        x += speed_x;
        y += speed_y;

        if (x + radius > GetScreenWidth())
        {
            speed_x *= -1;
        }
        if (y + radius > GetScreenHeight())
        {
            speed_y *= -1;
        }
        if (x - radius <= 0)
        {
            speed_x *= -1;
        }
        if (y - radius <= 0)
        {
            speed_y *= -1;
        }
    }
};

class Paddle
{
public:
    float x, y;
    float width, height;
    int speed;

    void Draw()
    {
        DrawRectangle(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height), WHITE);
    }

    void Update()
    {
        
    }
};

int main()
{
    int screenWidth = 800;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "PONG PONG");
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(60);

    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    Ball ball = {screenWidth / 2.0f, screenHeight / 2.0f, 5, 5, 10};
    Paddle paddle = {20, screenHeight / 2.0f - 50.0f, 15, 100, 6};

    while (!WindowShouldClose())
    {
        paddle.Update();
        ball.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        paddle.Draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}