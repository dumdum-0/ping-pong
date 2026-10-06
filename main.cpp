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

enum GameScreen { START , PLAYING , GAMEOVER};


int main()
{

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "PONG PONG");
    ToggleFullscreen();
    SetTargetFPS(60);

    InitAudioDevice();
    Sound bounce = LoadSound("bounce.wav");
    Sound game_end = LoadSound("gameover.mp3");
    

    int screenWidth ;
    int screenHeight ;
    screenWidth = GetScreenWidth();
    screenHeight = GetScreenHeight();

    Ball ball = {screenWidth / 2.0f, screenHeight / 2.0f, 5, 5, 25};
    Paddle paddle = {20, screenHeight / 2.0f - 50.0f, 15, 150, 10};

    int score = 0;
    GameScreen current = START ;

    while (!WindowShouldClose())
    {
        
        switch(current)
        {
            case START:
            
            if (IsKeyPressed(KEY_ENTER))
            {
                current = PLAYING;
            }
            break;
            
            case PLAYING:
                paddle.Update();
                ball.Update();
                if (CheckCollisionCircleRec(Vector2{ball.x , ball.y } , ball.radius , Rectangle{paddle.x , paddle.y , paddle.width, paddle.height}))
                {   
                    PlaySound(bounce);
                    ball.speed_x *= -1;
                    ball.speed_x += 1;
                    if (ball.speed_y > 0)
                    {
                        ball.speed_y += 1;
                    }
                    if (ball.speed_y < 0)
                    {
                        ball.speed_y -= 1;
                    }
                    
                    
                    score++;
                    
                }
                if (ball.x - ball.radius < 0)
                {
                    current = GAMEOVER;
                    PlaySound(game_end);
                }
                break;
                
                case GAMEOVER:
                if (IsKeyPressed(KEY_ENTER))
                {
                    ball.x = GetScreenWidth()/2;
                    ball.y = GetScreenHeight()/2;
                    ball.speed_x = -5 ;
                    ball.speed_y = 5;
                    paddle.y = GetScreenHeight()/2 - paddle.height/2;
                    score = 0;
                    
                    current = PLAYING;
                }
                break;
            }
            
            BeginDrawing();
            ClearBackground(BLACK);
            
            switch(current)
            {
                case START:
                DrawText("PONG PONG", screenWidth/2-MeasureText("PONG PONG",60)/2,screenHeight/2 - 100, 60 ,WHITE);
                DrawText("Press ENTER to Start", screenWidth/2 - MeasureText("Press ENTER to Start",20)/2,screenHeight/2 + 50 ,20 , LIGHTGRAY);
                break;
                
                case PLAYING:
                ball.Draw();
                paddle.Draw();
                DrawText(TextFormat("Score: %i",score), GetScreenWidth()-150,20,30,WHITE);
                break;

                case GAMEOVER:
                DrawText("GAME OVER", screenWidth/2 - MeasureText("GAME OVER",60)/2, screenHeight/2 - 100 , 60 , RED);
                DrawText(TextFormat("Final Score: %i",score), screenWidth/2 - MeasureText(TextFormat("Final Score: %i",score),30)/2 ,screenHeight/2 ,30 ,WHITE);
                DrawText("Press ENTER to Play Again" , screenWidth/2 - MeasureText("Press ENTER to Play Again",20)/2, screenHeight/2+75 , 20 ,LIGHTGRAY);
                break;
            }  
            
            EndDrawing();
    }

    CloseWindow();
    return 0;
}