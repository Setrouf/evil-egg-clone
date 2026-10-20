#include <assert.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
// #include "reasings.h"

#define P_SPEED 60.0f
#define UP KEY_W
#define DOWN KEY_S
#define LEFT KEY_A
#define RIGHT KEY_D

#define GAME_WIDTH 240.0f
#define GAME_HEIGHT 150.0f
#define GAME_RATIO (GAME_WIDTH / GAME_HEIGHT)
#define INV_GAME_RATIO (1 / GAME_RATIO)

Vector2 Vec2Scale(Vector2 v, float l) {
  v.x *= l;
  v.y *= l;
  return v;
}
Vector2 Vec2Add(Vector2 v1, Vector2 v2) {
  v1.x += v2.x;
  v1.y += v2.y;
  return v1;
}

typedef struct {
  Vector2 position;
  Vector2 shootingVec;
} Player;

Player InitPlayer(int x, int y) {
  Vector2 position = {x, y};
  Vector2 shootingVec = {0,0};
  Player p = {position};
  return p;
}

void DrawPlayer(Player *p) {
  Vector2 linestart = p->position;
  linestart.x += 5;
    linestart.y += 5;
  DrawLineV(linestart, Vec2Add(linestart, Vec2Scale(p->shootingVec, 10)),  RED);
  DrawRectangleV(p->position, (Vector2){10, 10}, BLUE);
}

void resize(Rectangle *drec) {
  float nw = GetScreenWidth();
  float nh = GetScreenHeight();
  if (nw / nh <= GAME_RATIO) {
    drec->width = nw;
    drec->height = INV_GAME_RATIO * nw;
    drec->x = 0;
    drec->y = (int)((nh - drec->height) / 2);
  } else if (nw / nh > GAME_RATIO) {
    drec->height = nh;
    drec->width = GAME_RATIO * nh;
    drec->y = 0;
    drec->x = (int)((nw - drec->width) / 2);
  }
}

int main() {

  // Initialization
  InitWindow(GAME_WIDTH * 4, GAME_HEIGHT * 4, "Fighting");
  RenderTexture2D gameScreen = LoadRenderTexture(GAME_WIDTH, GAME_HEIGHT);
  Texture2D backgroundTexture = LoadTexture("./resources/BG.png");

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  Rectangle srec = {0, 0, GAME_WIDTH, -GAME_HEIGHT};
  Rectangle drec = {0, 0, width, height};

  Player p = InitPlayer((GAME_WIDTH / 2) - 10, (GAME_HEIGHT / 2) - 10);

  SetWindowState(FLAG_WINDOW_RESIZABLE);

  while (!WindowShouldClose()) {

    if (IsWindowResized())
      resize(&drec);

    if (IsKeyPressed(KEY_F11))
      ToggleFullscreen();

  //Update Player
  float delta = GetFrameTime();
  if (IsKeyDown(KEY_W)) p.position.y -= P_SPEED*delta;
  if (IsKeyDown(KEY_A)) p.position.x -= P_SPEED*delta;
  if (IsKeyDown(KEY_S)) p.position.y += P_SPEED*delta;
  if (IsKeyDown(KEY_D)) p.position.x += P_SPEED*delta;
  p.shootingVec = (Vector2){0, 0};
  if (IsKeyDown(KEY_I)) p.shootingVec.y -= 1;
  if (IsKeyDown(KEY_L)) p.shootingVec.x += 1;
  if (IsKeyDown(KEY_K)) p.shootingVec.y += 1;
  if (IsKeyDown(KEY_J)) p.shootingVec.x -= 1;

    // Drawing
    BeginTextureMode(gameScreen);
    {
      ClearBackground(BLACK);
      DrawPlayer(&p);
    }
    EndTextureMode();

    BeginDrawing();
    {
      ClearBackground(BLACK);
      DrawTexturePro(gameScreen.texture, srec, drec, (Vector2){0, 0}, 0, WHITE);
      // DrawText(TextFormat("W: %i\nH: %i", GetScreenWidth(),
      // GetScreenHeight()), 0, 0, 24, DARKGREEN); DrawText( TextFormat("drec.x:
      // %f\ndrec.y: %f\ndrec.width: %f\ndrec.height: %f", drec.x, drec.y,
      // drec.width, drec.height), 0, 60, 24, DARKPURPLE);
    }
    EndDrawing();
  }
  CloseWindow();
}
