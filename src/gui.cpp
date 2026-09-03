#include <stdio.h>
#include "offsets.h"

extern bool espEnabled;

// ===== Unity OnGUI Toggle Button
void DrawToggleButton() {
    // This is Unity pseudo-code — actual implementation depends on Unity API
    // In a real hook, you'd call Unity's GUI.Button or use GL

    // Simple placeholder: just log the state
    // printf("[GUI] ESP: %s\n", espEnabled ? "ON" : "OFF");

    // Example of what the actual Unity code would look like:
    /*
    GUI.Box(Rect(10, 10, 180, 60), "MLBB ESP Control");
    if (GUI.Button(Rect(20, 35, 160, 30), 
                   espEnabled ? "ESP: ON" : "ESP: OFF")) {
        espEnabled = !espEnabled;
    }
    */
}
