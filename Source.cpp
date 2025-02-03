// A Computer Science Quote
// KISS
// (Keep It Simple Stupid)
#include<raylib.h>
#include<iostream>
const int screenHeight = 800;
const int screenWidth = 1200;
const int speed = 5;
struct Background {
    Texture2D texture;
    Vector2 position;
    Image img;
  
};
struct Fruit {
    Vector2 position;
    Texture2D texture;
    Image img;
    int height = 30;
    int width = 30;
};
struct Basket {
    Vector2 position;
    Texture2D texture;
    Image img;
    int height=200;
    int width=200;
    
};

void appearFruit(Fruit& apple) {
    apple.position.x = rand() % screenWidth + 1;
    apple.position.y = 0;
}


int main() {
    srand(time(0));
    Background B1, B2;
    Fruit apple;
    Basket basket;
   
    int score = 0;
    InitWindow(screenWidth, screenHeight, "HEHE BOI");

    B1.img = LoadImage("D:\\source\\repos\\Raylib egg\\x64\\Debug\\b1.png");
    ImageResize(&B1.img,screenWidth,screenHeight);
    B1.texture = LoadTextureFromImage(B1.img);
    B1.position = { 0,0 };

    B2.img = LoadImage("D:\\source\\repos\\Raylib egg\\x64\\Debug\\b2.png");
    ImageResize(&B2.img, screenWidth, screenHeight);
    B2.texture = LoadTextureFromImage(B2.img);
    B2.position = { screenWidth,0 };

    apple.img = LoadImage("D:\\source\\repos\\Raylib egg\\x64\\Debug\\apple.png");
    ImageResize(&apple.img, apple.width,apple.height);
    apple.texture = LoadTextureFromImage(apple.img);
    apple.position = {0,0};

    basket.img = LoadImage("D:\\source\\repos\\Raylib egg\\x64\\Debug\\basket.png");
    ImageResize(&basket.img, basket.width, basket.height);
    basket.texture = LoadTextureFromImage(basket.img);
    basket.position = { screenWidth/2, (float)screenHeight - basket.height };

    Rectangle basketCollider = { basket.position.x , basket.position.y , basket.width , basket.height };
    Rectangle appleCollider = { apple.position.x , apple.position.y , apple.width , apple.height };


    SetTargetFPS(60); 
    appearFruit(apple);
    appleCollider.x = apple.position.x;
    while (!WindowShouldClose()) {

        B1.position.x -= speed;
        B2.position.x -= speed;

        if (B1.position.x == -screenWidth)
            B1.position.x *= -1;
        if (B2.position.x == -screenWidth)
            B2.position.x *= -1;


        apple.position.y += speed;
        appleCollider.y = apple.position.y;

        if (apple.position.y >= screenHeight) {
            apple.position.y = 0;
            appleCollider.y = apple.position.y;
            appearFruit(apple);
            appleCollider.x = apple.position.x;
        }
        if (IsKeyDown(KEY_A)) {
            basket.position.x -= 2* speed;
            basketCollider.x = basket.position.x;
        }
        if (IsKeyDown(KEY_D)) {
            basket.position.x += 2*speed;
            basketCollider.x = basket.position.x;
        }

        if (basket.position.x < 0) basket.position.x = screenWidth - basket.width;
        if (basket.position.x > screenWidth) basket.position.x = 0;

        basketCollider.x = basket.position.x;
       

        bool collision = CheckCollisionRecs(basketCollider, appleCollider);

        if (collision) {
            score++;
            apple.position.y = 0;
            appleCollider.y = apple.position.y;
            appearFruit(apple);
            appleCollider.x = apple.position.x;
        }

        BeginDrawing();
        ClearBackground(WHITE);
        DrawTexture(B1.texture, B1.position.x, B1.position.y, WHITE);
        DrawTexture(B2.texture, B2.position.x, B2.position.y, WHITE);
        DrawTexture(basket.texture, basket.position.x, basket.position.y, WHITE);
        DrawTexture(apple.texture, apple.position.x, apple.position.y, WHITE);
        DrawText(TextFormat("Score: %d", score) , 0, 0 ,24, BLACK);
        EndDrawing();
    }

    UnloadTexture(B1.texture); 
    UnloadTexture(B2.texture); 
    CloseWindow();
	return 0;
}
