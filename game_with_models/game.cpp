#include "raylib.h"
#include "raymath.h"
#include "iostream"
#include "string"
using namespace std;

// states for the player
enum State {
    IDLE,
    WALK,
    ATTACK,
    HURT,
    DEATH
};

struct Animation {
    Texture2D texture;
    int frameWidth = 100; // 100 x 100 frames
    int frameHeight = 100;
    int maxFrames = 6; // 6 frames per sprite
    float frameDuration = 0.10f; // how long the frame will last
};

struct Player {
    Vector2 pos; // x and y position
    float speed; // movement speed
    int health; // health lol
    State state; // determine which Texture to use
    int currentFrame; // which frame in the sprite are we at
    float frameTimer; // the duration of that frame
};

int main()
{
    int window_width = 800;
    int window_height = 600;

    // initialize player postion, state, etc
    Player player;
    player.speed = 200.0f;
    player.pos = {window_width / 2.0f, window_height / 2.0f};
    player.state = IDLE;
    player.health = 100; // TODO: gotta work on health logic, health bar, etc.
    player.currentFrame = 0;
    player.frameTimer = 0.0f;

    InitWindow(window_width,window_height,"Soldier Window");

    // load player models to use in Animation struct
    Texture2D soldier = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Idle.png");

    Texture2D soldierIdle = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Idle.png");
    Texture2D soldierWalking = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Walk.png");
    Texture2D soldierAttacking = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Attack01.png");
    Texture2D soldierHurt = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Hurt.png");
    Texture2D soldierDead = LoadTexture("Tiny RPG Character Asset Pack v1.03b -Free Soldier&Orc/Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc/Characters(100x100)/Soldier/Soldier/Soldier-Death.png");
    
    SetTextureFilter(soldier, TEXTURE_FILTER_POINT);
    Animation anims[5]; // List of animations. An animation for each State. index with State

    // have an animation for each state
    anims[IDLE] = {soldierIdle};
    anims[WALK] = {soldierWalking};
    anims[ATTACK] = {soldierAttacking};
    anims[HURT] = {soldierHurt};
    anims[DEATH] = {soldierDead};

    // pick the animation based on the players current state
    
    // upscaling the soldier, its pretty small. using drawWidth and drawHeight for bounding its position to the screen 
    float soldierScale = 2.5f;
    float soldierDrawWidth = 100.0f * soldierScale;
    float soldierDrawHeight = 100.0f * soldierScale;

    // define a frame rectangle. the texture contains multiple soldiers in a sprite   
    int frameWidth = 100;
    int frameHeight = 100;
    Rectangle TextureSingleFrame = {0, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight)}; // rectangle wants floats for the height and width of the rectangle

    // animation constants
    int currentFrame = 0;
    float frameTime = 0.0f;
    int maxFrames = 6;

    SetTargetFPS(120);

    // RENDER LOOP
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime(); // for 120 fps. 1/120.
        // speed is 200, 200*.0083 = 3.33. makes the movement independent of the fps.

        // movement keys. TODO: no up or down , just left and right
        if (IsKeyDown(KEY_S)) {player.pos.y += player.speed * delta;} // since 0,0 is at the top left, y increases downward
        if (IsKeyDown(KEY_W)) {player.pos.y -= player.speed * delta;} 
        if (IsKeyDown(KEY_A)) {player.pos.x -= player.speed * delta;} 
        if (IsKeyDown(KEY_D)) {player.pos.x += player.speed * delta;}

        Animation &currentAnim = anims[player.state];
        if (player.state != ATTACK && player.state != HURT && player.state != DEATH)
        {
            bool moving = IsKeyDown(KEY_A) || IsKeyDown(KEY_D);
            player.state = moving ? WALK : IDLE; // if player is moving, state = WALK, else IDLE
        }
        // if (IsKeyDown(KEY_S)) player1.pos.y += 2.0f;

        // need to clamp each render loop
        player.pos.x = Clamp(player.pos.x, 0.0f, (float)window_width-soldierDrawWidth);
        player.pos.y = Clamp(player.pos.y, 0.0f, (float)window_height-soldierDrawHeight);

        BeginDrawing();
        ClearBackground(SKYBLUE);

        // need to loop through the soldiers in the idle file
        int row = 0; 
        TextureSingleFrame.x = row * 100;
        player.frameTimer += delta;
        frameTime += delta;
        if (player.frameTimer > currentAnim.frameDuration) // meaning each frame in the sprite will last .1 seconds. 100 ms
        {
            player.frameTimer = 0.0f; // go to next frame.
            player.currentFrame++;
            if (player.currentFrame >= currentAnim.maxFrames)
            {
                player.currentFrame = 0;
            }
        }

        if (currentFrame >= maxFrames) currentFrame = 0; // back to first frame
        TextureSingleFrame.x = currentFrame * 100; // next frame in the sprite

        // source rec says what part of texture to read from sprite sheet. destination rec is where it will be drawn and what size.
        Rectangle sourceRec = {
            (float)(player.currentFrame * currentAnim.frameWidth), // frameWidth is 100
            0.0f,
            (float)currentAnim.frameWidth,
            (float)currentAnim.frameHeight
            };
        Rectangle destRec = {
            player.pos.x,
            player.pos.y,
            currentAnim.frameWidth * soldierScale,
            currentAnim.frameHeight * soldierScale
        };
        Vector2 origin = {0.0f, 0.0f};

        DrawTexturePro(currentAnim.texture, sourceRec, destRec, origin, 0.0f, WHITE);
                
        // DrawTextureRec(soldier, TextureSingleFrame, player1.pos, WHITE);
        
        DrawFPS(10,10);
        DrawText("Block moving window", 10,30,20,BLACK);
        cout << player.state;
        EndDrawing();
    }
    // UnloadTexture(p.texture);
    CloseWindow();
    return 0;
}