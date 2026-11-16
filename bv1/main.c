#include "include/raylib.h"
#include <math.h>

// utilitários
float normalizar360(float angulo){
    angulo = fmodf(angulo, 360.0f);
    if(angulo < 0){
        angulo = angulo + 360.0f;
    }
    return angulo;
}

float aleatorio(float min, float max){
    return min + ((float)GetRandomValue(0, 10000) / 10000.0f) * (max - min);
}

const char *rotulo(int marca){
    if(marca == 0)   return "N";
    if(marca == 90)  return "L";
    if(marca == 180) return "S";
    if(marca == 270) return "O";
    return TextFormat("%d", marca / 10);
}

// simulação do mundo
float atualizarProaReal(float proaV, float dt, float v){
    if(IsKeyDown(KEY_D)){
        proaV = proaV + v * dt;
    }else if(IsKeyDown(KEY_A)){
        proaV = proaV - v * dt;
    }
    return normalizar360(proaV);
}

// sensor
Vector2 lerMagnetico(float rumoV, float campo, float ruido){
    float rad = rumoV * DEG2RAD;
    float mx = campo * cosf(rad) + ruido * aleatorio(-1.0f, 1.0f);
    float my = campo * sinf(rad) + ruido * aleatorio(-1.0f, 1.0f);
    return (Vector2){ mx, my };
}

// instrumento
float calcularProa(Vector2 leitura){
    float proa = atan2f(leitura.y, leitura.x) * RAD2DEG;
    return normalizar360(proa);
}

// desenho
void desenhar_cartao(Vector2 centerPoint, float raio, float proa){
    DrawCircleV(centerPoint, raio, BLACK);

    for(int i = 0; i < 360; i = i + 10){
        float rad = (i - proa) * DEG2RAD;
        Vector2 dir = { sinf(rad), -cosf(rad) };

        int tam = (i % 30 == 0) ? 25 : 12;

        Vector2 inicio = { centerPoint.x + dir.x * (raio - tam),
                           centerPoint.y + dir.y * (raio - tam) };
        Vector2 fim    = { centerPoint.x + dir.x * raio,
                           centerPoint.y + dir.y * raio };

        DrawLineV(inicio, fim, WHITE);

        if(i % 30 == 0){
            const char *txt = rotulo(i);
            int fonte = 20;
            int larg = MeasureText(txt, fonte);

            int x = (int)(centerPoint.x + (raio - 50) * dir.x);
            int y = (int)(centerPoint.y + (raio - 50) * dir.y);

            DrawText(txt, x - larg / 2, y - fonte / 2, fonte, WHITE);
        }
    }
}

void desenharRf(Vector2 centerPoint, float raio){
    Vector2 p1 = { centerPoint.x - 10, centerPoint.y - raio - 15 };   // canto esquerdo da base
    Vector2 p2 = { centerPoint.x,      centerPoint.y - raio + 10 };   // ponta, apontando para o centro
    Vector2 p3 = { centerPoint.x + 10, centerPoint.y - raio - 15 };   // canto direito da base

    DrawTriangle(p1, p2, p3, WHITE);
};

void desenharTc(Vector2 centerPoint, float proa){
    int proaExib = (int)roundf(proa) % 360;
    const char *textoExib = TextFormat("%d°",proaExib);
    int largura = MeasureText(textoExib,30);
    DrawText(textoExib, (int)(centerPoint.x - largura), 30, 30,WHITE);
}

int main(void)
{
    Vector2 centerPoint;
    centerPoint = (Vector2){300.0f,310.0f};
    const int raio = 250;
    const float velocidade = 60.0f;\
    const int screenWidth = 600;
    const int screenHeight = 600;
    const float campo = 1.0f;
    const float ruido = 0.2f;
    float proaV = 0.0f;

    InitWindow(screenWidth, screenHeight, "Busula");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        float dt = GetFrameTime();
        proaV = atualizarProaReal(proaV,dt, velocidade);
        Vector2 leitura = lerMagnetico(proaV, campo, ruido);
        float proaM = calcularProa(leitura);

        BeginDrawing();
            ClearBackground(DARKGRAY);
            desenhar_cartao(centerPoint, raio, proaM);
            desenharRf(centerPoint,raio);

            desenharTc(centerPoint, proaM);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}