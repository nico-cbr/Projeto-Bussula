#include "include/raylib.h"
#include <math.h>



int main(void)
{
    Vector2 centerPoint;
    centerPoint = (Vector2){300.0f,300.0f};
    const int raio = 250;
    const float velocidade = 60.0f;
    float proa = 0.0f;
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Busula");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        float dt = GetFPS();
        if(IsKeyDown(KEY_D)){
            proa = proa + velocidade * dt;
        }else if (IsKeyDown(KEY_A))
        {
            proa = proa - velocidade * dt;
        };

        proa = fmodf(proa, 360.0f);
        if(proa < 0){
            proa = proa + 360.0;
        };
        BeginDrawing();
            ClearBackground(DARKGRAY);
            DrawCircleV(centerPoint, raio, BLACK);

            for(int i = 0; i < 360; i = i + 10){
                float angulo = i - proa;
                float rad = angulo * DEG2RAD;
                Vector2 dir = {sinf(rad), -cosf(rad)};

                int tam;
                if(i % 30 == 0){
                    tam = 25;
                } else{
                    tam = 12;
                };
                Vector2 inicio = { centerPoint.x + dir.x * (raio - tam),
                   centerPoint.y + dir.y * (raio - tam) };
                Vector2 fim    = { centerPoint.x + dir.x * raio,
                   centerPoint.y + dir.y * raio };

                DrawLineV(inicio, fim, WHITE);
DrawLineV(inicio, fim, RED);
            };

        EndDrawing();
    }

    CloseWindow();

    return 0;
}