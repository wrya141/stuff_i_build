
#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define MAX_POINTS 2000
#define STEPS 100

typedef struct {
    float x, y;
} Point;

Point path[MAX_POINTS];
int count = 0;
int digit9_start;

// Add a point to the path
void addPoint(float x, float y) {
    if (count < MAX_POINTS) {
        path[count++] = (Point){x, y};
    }
}

// Generate a cubic Bezier curve
void bezier(Point p0, Point p1, Point p2, Point p3) {
    for (int i = 1; i <= STEPS; i++) {
        float t = (float)i / STEPS;
        float u = 1.0f - t;

        float x =
            u*u*u*p0.x +
            3*u*u*t*p1.x +
            3*u*t*t*p2.x +
            t*t*t*p3.x;

        float y =
            u*u*u*p0.y +
            3*u*u*t*p1.y +
            3*u*t*t*p2.y +
            t*t*t*p3.y;

        addPoint(x, y);
    }
}

int main(void) {
    InitWindow(800, 600, "The Legendary 69");
    SetTargetFPS(60);

    Texture2D turtle = LoadTexture("turtle.png");

    // -------------------------
    // DRAW THE NUMBER 6
    // -------------------------

    Point p = {380, 145};

    bezier(p, (Point){300, 145},
              (Point){230, 210},
              (Point){230, 300});

    p = (Point){230, 300};

    bezier(p, (Point){230, 380},
              (Point){300, 420},
              (Point){360, 380});

    p = (Point){360, 380};

    bezier(p, (Point){420, 340},
              (Point){380, 260},
              (Point){310, 270});

    p = (Point){310, 270};

    bezier(p, (Point){250, 275},
              (Point){245, 350},
              (Point){300, 365});

    // Remember where 9 begins
    digit9_start = count;

    // -------------------------
    // DRAW THE NUMBER 9
    // -------------------------

    p = (Point){520, 250};

    bezier(p, (Point){445, 250},
              (Point){445, 140},
              (Point){520, 140});

    p = (Point){520, 140};

    bezier(p, (Point){600, 140},
              (Point){600, 250},
              (Point){520, 250});

   p = (Point){520, 250};

bezier(p, (Point){575, 265},
          (Point){585, 325},
          (Point){550, 365});

p = (Point){550, 365};

bezier(p, (Point){530, 390},
          (Point){500, 410},
          (Point){475, 430});    // -------------------------
    // ANIMATION
    // -------------------------

    int progress = 1;
    bool finished = false;

    while (!WindowShouldClose()) {

        if (!finished) {
            progress += 2;

            if (progress >= count) {
                progress = count;
                finished = true;
            }
        }

        BeginDrawing();

        ClearBackground((Color){18, 18, 18, 255});

        // Draw the 6
        int end6 = progress < digit9_start
                 ? progress : digit9_start;

        for (int i = 1; i < end6; i++) {
            DrawLineEx(
                (Vector2){path[i-1].x, path[i-1].y},
                (Vector2){path[i].x, path[i].y},
                3, GREEN
            );
        }

        // Draw the 9
        for (int i = digit9_start + 1; i < progress; i++) {
            DrawLineEx(
                (Vector2){path[i-1].x, path[i-1].y},
                (Vector2){path[i].x, path[i].y},
                3, SKYBLUE
            );
        }

        // Draw turtle at current position
        if (progress < count && turtle.id>0) {

            Point current = path[progress];
            Point previous = path[progress - 1];

            float angle = atan2f(
                current.y - previous.y,
                current.x - previous.x
            ) * RAD2DEG;

            float scale = 0.1f;

            Rectangle source = {
                0, 0,
                (float)turtle.width,
                (float)turtle.height
            };

            Rectangle destination = {
                current.x,
                current.y,
                turtle.width * scale,
                turtle.height * scale
            };

            Vector2 origin = {
                destination.width / 2,
                destination.height / 2
            };

            DrawTexturePro(
                turtle,
                source,
                destination,
                origin,
                angle,
                WHITE
            );
        }

        if (finished) {
            DrawText("MISSION ACCOMPLISHED",
                     260, 520, 20, GREEN);
        }

        EndDrawing();
    }

    UnloadTexture(turtle);
    CloseWindow();

    return 0;
}
