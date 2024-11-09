#include <raylib.h>
#include <iostream>
using namespace std;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int player2_score = 0;
int cpu_score = 0;
int win_count = 0;
int win_target = 5;
int choice = 0;

class Ball
{
public:
    float x, y;
    int speedX, speedY;
    int radius;

    void draw()
    {
        DrawCircle(x, y, radius, Yellow);
    }

    void update()
    {
        x += speedX;
        y += speedY;

        if ((y + radius) >= GetScreenHeight() || (y - radius) <= 0)
        {
            speedY *= -1;
        }
        if ((x + radius) >= GetScreenWidth())
        {
            cpu_score++;
            // speedX *= -1;
            reset_ball();
        }
        if ((x - radius) <= 0)
        {
            player_score++;
            // speedX *= -1;
            reset_ball();
        }
    }
    void update2()
    {
        x += speedX;
        y += speedY;

        if ((y + radius) >= GetScreenHeight() || (y - radius) <= 0)
        {
            speedY *= -1;
        }
        if ((x + radius) >= GetScreenWidth())
        {
            player2_score++;
            // speedX *= -1;
            reset_ball();
        }
        if ((x - radius) <= 0)
        {
            player_score++;
            // speedX *= -1;
            reset_ball();
        }
    }

    void reset_ball()
    {

        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speedX *= speed_choices[GetRandomValue(0, 1)];
        speedY *= speed_choices[GetRandomValue(0, 1)];
    }
};

class Paddle
{
protected:
    void LimitMovement()
    {
        if (y <= 0)
        {
            y = 0;
        }
        else if ((y + height) >= GetScreenHeight())
        {
            y = GetScreenHeight() - height;
        }
    }

public:
    float x, y;
    float width, height;
    float speed;

    void draw()
    {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void update()
    {
        if (IsKeyDown(KEY_UP))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN))
        {
            y += speed;
        }
        LimitMovement();
    }
};

class Player2Paddle : public Paddle
{
public:
    void update()
    {
        if (IsKeyDown(KEY_W))
        {
            y -= speed;
        }
        else if (IsKeyDown(KEY_S))
        {
            y += speed;
        }
        LimitMovement();
    }
};

class CpuPaddle : public Paddle
{
public:
    void update(int ball_Y)
    {
        if (y + height / 2 > ball_Y)
        {
            y = y - speed;
        }
        else if (y + height / 2 <= ball_Y)
        {
            y = y + speed;
        }
        LimitMovement();
    }
};

void check_winner()
{
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        if (win_count == 1)
        {
            ClearBackground(BLACK);
            DrawText("CPU WINS!", GetScreenWidth() / 2 - 300, GetScreenHeight() / 4, 90, WHITE);
            DrawText("press 'enter' key to restart!", GetScreenWidth() / 2 - 200, GetScreenHeight() - GetScreenHeight() / 4, 30, WHITE);
            DrawText("press 'enter' then 'escape' key to exit.", GetScreenWidth()/2-200, (GetScreenHeight()-GetScreenHeight()/4) + 30, 30, WHITE);
        }
        else if (win_count == 2)
        {
            ClearBackground(BLACK);
            DrawText("PLAYER WINS!", GetScreenWidth() / 2 - 300, GetScreenHeight() / 4, 90, WHITE);
            DrawText("press 'enter' key to restart!", GetScreenWidth() / 2 - 200, GetScreenHeight() - GetScreenHeight() / 4, 30, WHITE);
            DrawText("press 'enter' then 'escape' key to exit.", GetScreenWidth()/2-200, (GetScreenHeight()-GetScreenHeight()/4) + 30, 30, WHITE);
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            cpu_score = 0;
            player_score = 0;
            break;
        }
        EndDrawing();
    }
}

void check_winner2()
{
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        if (win_count == 1)
        {
            ClearBackground(BLACK);
            DrawText("PLAYER2 WINS!", GetScreenWidth() / 2 - 300, GetScreenHeight() / 4, 90, WHITE);
            DrawText("press 'enter' key to restart!", GetScreenWidth() / 2 - 200, GetScreenHeight() - GetScreenHeight() / 4, 30, WHITE);
            // DrawText("press 'escape' key to exit.", GetScreenWidth()/2-200, (GetScreenHeight()-GetScreenHeight()/4) + 30, 30, WHITE);
        }
        else if (win_count == 2)
        {
            ClearBackground(BLACK);
            DrawText("PLAYER1 WINS!", GetScreenWidth() / 2 - 300, GetScreenHeight() / 4, 90, WHITE);
            DrawText("press 'enter' key to restart!", GetScreenWidth() / 2 - 200, GetScreenHeight() - GetScreenHeight() / 4, 30, WHITE);
            // DrawText("press 'escape' key to exit.", GetScreenWidth()/2-200, (GetScreenHeight()-GetScreenHeight()/4) + 30, 30, WHITE);
        }

        if (IsKeyDown(KEY_ENTER))
        {
            player2_score = 0;
            player_score = 0;
            break;
        }
        EndDrawing();
    }
}

void first_screen(){
    while (true)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("P  O  N  G  !", GetScreenWidth() / 2 - 300, GetScreenHeight() / 4, 120, WHITE);
        DrawText("PRESS 1 FOR SINGLE PLAYER", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 20, WHITE);
        DrawText("PRESS 2 FOR MULTI PLAYER", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 100, 20, WHITE);

        if (IsKeyDown(KEY_ONE))
        {
            choice = 1;
            break;
        }
        else if (IsKeyDown(KEY_TWO))
        {
            choice = 2;
            break;
        }
        EndDrawing();
    }
}

Ball ball;
Paddle player;
Player2Paddle player2;
CpuPaddle cpu;

int main()
{
    cout << "starting the game!" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "P O N G !");
    SetTargetFPS(60);

    first_screen();

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speedX = 7;
    ball.speedY = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 7;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height / 2 - cpu.height / 2;
    cpu.speed = 7;

    player2.width = 25;
    player2.height = 120;
    player2.x = 10;
    player2.y = screen_height / 2 - player.height / 2;
    player2.speed = 7;

    if (choice == 1)
    {
        while (WindowShouldClose() == false)
        {
            BeginDrawing();

            // Updating

            ball.update();
            player.update();
            cpu.update(ball.y);

            // CHECKING FOR COLLISIONS

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.speedX *= -1;
            }

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height}))
            {
                ball.speedX *= -1;
            }
            // DRAWING

            ClearBackground(Dark_Green);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            ball.draw();
            // left-paddle
            cpu.draw();
            // right-paddle
            player.draw();
            // dividing the screen
            DrawLine((screen_width / 2), 0, (screen_width / 2), screen_height, WHITE);
            DrawText(TextFormat("%i", cpu_score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), (screen_width - screen_width / 4) + 20, 20, 80, WHITE);
            
            // CHECKING FOR WINNNER
            if (cpu_score == win_target)
            {
                win_count = 1;
                check_winner();
            }
            else if (player_score == win_target)
            {
                win_count = 2;
                check_winner();
            }

            EndDrawing();
        }

        CloseWindow();
    }
    else if (choice == 2)
    {
        while (WindowShouldClose() == false)
        {
            BeginDrawing();

            // Updating

            ball.update2();
            player.update();
            player2.update();

            // CHECKING FOR COLLISIONS

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height}))
            {
                ball.speedX *= -1;
            }

            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height}))
            {
                ball.speedX *= -1;
            }
            // DRAWING

            ClearBackground(Dark_Green);
            DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green);
            DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
            ball.draw();
            // left-paddle
            player2.draw();
            // right-paddle
            player.draw();
            // dividing the screen
            DrawLine((screen_width / 2), 0, (screen_width / 2), screen_height, WHITE);
            DrawText(TextFormat("%i", player2_score), screen_width / 4 - 20, 20, 80, WHITE);
            DrawText(TextFormat("%i", player_score), (screen_width - screen_width / 4) + 20, 20, 80, WHITE);
            
            // CHECKING FOR WINNNER
            if (player2_score == win_target)
            {
                win_count = 1;
                check_winner2();

            }
            else if (player_score == win_target)
            {
                win_count = 2;
                check_winner2();
            }
            EndDrawing();
        }
        CloseWindow();
    }
    else
    {
        cout << "INVLAID INPUT!" << endl;
        CloseWindow();
    }
    return 0;
}