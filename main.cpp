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
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }

        if ( (y + height/2) > GetScreenHeight())
        {
            y = GetScreenHeight() - height/2;
        }
        if (y < 0)
        {
            y = 0;
        }
        
        
    }
};

int main()
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "PONG PONG");
    ToggleFullscreen();
    SetTargetFPS(60);

    int screenWidth ;
    int screenHeight ;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    Ball ball = {screenWidth / 2.0f, screenHeight / 2.0f, 5, 5, 25};
    Paddle paddle = {20, screenHeight / 2.0f - 50.0f, 15, 150, 6};


    while (!WindowShouldClose())
    {
        paddle.Update();
        ball.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        paddle.Draw();

        if (CheckCollisionCircleRec(Vector2{ball.x , ball.y } , ball.radius , Rectangle{paddle.x , paddle.y , paddle.width, paddle.height}))
        {
            ball.speed_x *= -1;
        }
        

        EndDrawing();
    }
    CloseWindow();
    return 0;
}