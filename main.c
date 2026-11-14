#include "include/raylib.h"

Vector2 centerPoint;
centerPoint = (Vector2){300.0f,300.0f};
const int raio = 250;
const float velocidade = 60.0f;

int main(void)
{
    float proa = 0.0f;
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Busula");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            float dt = GetFPS();
        if(GetKeyPressed())

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}