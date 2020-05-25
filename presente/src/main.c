
#include <raylib.h>
#include <math.h>

#include "level.h"
#include "draw.h"
#include "state.h"
#include "files.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    player_score = 0;
    hiscore = get_hiscore();

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    InitAudioDevice();

    Music music = LoadMusicStream("../music/Background.mp3");
    Sound shot = LoadSound("../music/Shot.mp3");
    PlayMusicStream(music);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);

    // Main loop
    while(!WindowShouldClose()){

        UpdateMusicStream(music);

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Update the state
        state_update(lvl,sta);

        // Drawing
        BeginDrawing();

            ClearBackground(RAYWHITE);

            draw_state(lvl, sta);

            DrawText("Presente profe!",190,200,20,LIGHTGRAY);
            DrawText(FormatText("Score = %d", player_score), 190, 220, 30, BLACK);
            DrawText(FormatText("Hi-score = %d", hiscore), 190, 250, 20, RED);

        EndDrawing();

    }
    hiscore_update(player_score);
    PlaySound(shot);
    while(IsSoundPlaying(shot));
    UnloadSound(shot);
    UnloadMusicStream(music);
    CloseAudioDevice();

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
