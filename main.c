#include "raylib.h"
#include <stdio.h>
// main.c のどこかに追記しておく
void run_emulator(void) {}
void update_gps_from_js(void) {}
// --- 1. 構造体定義 ---
typedef struct {
    char name[32];
    float x, y, z;
    int hp, max_hp;
    int is_active;
} Monster;

typedef struct {
    float x, y, z;
    int is_active;
} Item;

// --- 2. グローバル変数 ---
Monster party[3];
Item droppedItems[10];
Camera camera = { { 10.0f, 10.0f, 10.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };

// --- 3. ロジック関数 ---
void missionLog(const char* type, const char* msg) {
    printf("[%s] %s\n", type, msg);
}

void spawnBerry(float x, float z) {
    for(int i = 0; i < 10; i++) {
        if (!droppedItems[i].is_active) {
            droppedItems[i].x = x;
            droppedItems[i].y = 0.5f;
            droppedItems[i].z = z;
            droppedItems[i].is_active = 1;
            missionLog("ITEM", "木の実が落ちた！");
            break;
        }
    }
}

void takeDamage(Monster* m, int damage) {
    if (!m->is_active) return;
    m->hp -= damage;
    missionLog("BATTLE", "ダメージを受けた！");
    if (m->hp <= 0) {
        m->hp = 0;
        m->is_active = 0;
        missionLog("BATTLE", "倒れました！");
        spawnBerry(m->x, m->z);
    }
}

void initStage(void) {
    for(int i = 0; i < 3; i++) {
        party[i].is_active = 1;
        party[i].hp = 100;
        party[i].max_hp = 100;
        party[i].x = (float)(i * 3 - 3);
        party[i].z = 5.0f;
    }
    for(int i = 0; i < 10; i++) droppedItems[i].is_active = 0;
    missionLog("STAGE", "ステージ初期化完了！");
}

// --- 4. 描画ループ ---
void UpdateDrawFrame(void) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    int uiHeight = screenHeight / 5;
    int btnY = screenHeight - uiHeight + 10;

    // 入力判定
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (party[0].is_active) {
            if (GetMousePosition().y > (screenHeight - uiHeight)) {
                missionLog("BATTLE", "SPECIAL 1 発動！");
                takeDamage(&party[0], 20);
            }
        }
    }

    // カメラ更新
    float avgX = (party[0].x + party[1].x + party[2].x) / 3.0f;
    camera.target = (Vector3){ avgX, 0.0f, 0.0f };
    camera.position = (Vector3){ avgX, 5.0f, 7.0f };

    BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
            DrawGrid(10, 1.0f);
            for(int i = 0; i < 3; i++) {
                if (party[i].is_active) DrawCube((Vector3){party[i].x, 0, party[i].z}, 2, 2, 2, BLUE);
            }
            for(int i = 0; i < 10; i++) {
                if (droppedItems[i].is_active) DrawSphere((Vector3){droppedItems[i].x, 0.5f, droppedItems[i].z}, 0.5f, MAROON);
            }
        EndMode3D();

        // UI描画
        DrawRectangle(0, screenHeight - uiHeight, screenWidth, uiHeight, LIGHTGRAY);
        DrawRectangle(50, btnY, 150, 50, BLUE);
        DrawText("SPECIAL", 60, btnY + 15, 20, WHITE);
    EndDrawing();
}

// --- 5. メイン ---
int main(void) {
    InitWindow(800, 450, "Pokemon Quest Web");
    initStage();
    while (!WindowShouldClose()) UpdateDrawFrame();
    CloseWindow();
    return 0;
}
