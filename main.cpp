//
// Created by Anton on 03/12/2023.
//

#include "raylib.h"
#include "raymath.h"
#include "src/World.h"

using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


int main() {
    int rows = 20;
    int columns = 30;

    float time{};
    auto cellSize = 20;
    // Initialization

    //--------------------------------------------------------------------------------------
    const int screenWidth = cellSize * columns;
    const int screenHeight = cellSize * rows;
    vector<pair<int, int>> aliveCells{make_pair(10, 10), make_pair(11, 10), make_pair(9, 10)};
    World world{rows, columns, aliveCells};

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera mouse zoom");

    Camera2D camera = {0};
    camera.zoom = 1.0f;

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------


    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Translate based on mouse right click
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f / camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }


        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0) {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.925f;

            camera.zoom += (wheel * zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }

        //----------------------------------------------------------------------------------
        int slices = 100;
        int spacing = cellSize;
        time += GetFrameTime();
        if (time > 0.5) {
            world.update();
            time = 0;
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera);

        world.draw(cellSize);
        for (int i = 0; i < columns; ++i) {
            DrawLine(spacing * i, 0, spacing * i, screenHeight, BEIGE);
        }
        for (int i = 0; i < rows; ++i) {
            DrawLine(0, spacing * i, screenWidth, spacing * i, BEIGE);
        }

        EndMode2D();
        //        GuiButton((Rectangle){ 0, 0, 125, 30 }, GuiIconText(ICON_FILE_SAVE, "Save File"));

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}