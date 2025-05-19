#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <filesystem>

#include "..\tools\Logger.h"

#include <GLFW/glfw3.h>
#include <unordered_map>

struct RebindContext {
    bool awaitingKey = false;
    std::string actionName;
    int* targetKey = nullptr;
};

struct InputState {
    bool cameraUp = false;
    bool cameraDown = false;
    bool cameraLeft = false;
    bool cameraRight = false;
    bool cameraForward = false;
    bool cameraBackward = false;
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
    bool moveForward = false;
    bool moveBackward = false;
    bool pause = false;
    // Weitere Tastenaktionen je nach Spiel
};

struct KeyBindings {
    int cameraUp = GLFW_KEY_KP_9;
    int cameraDown = GLFW_KEY_KP_7;
    int cameraLeft = GLFW_KEY_KP_4;
    int cameraRight = GLFW_KEY_KP_6;
    int cameraForward = GLFW_KEY_KP_8;
    int cameraBackward = GLFW_KEY_KP_5;
    int up = GLFW_KEY_E;
    int down = GLFW_KEY_Q;
    int left = GLFW_KEY_A;
    int right = GLFW_KEY_D;
    int forward = GLFW_KEY_W;
    int backward = GLFW_KEY_S;
    int pause = GLFW_KEY_SPACE;
};

class Controls {
public:
    Controls();

    void keyCallback(int key, int action);
    const KeyBindings& getKeyBindings() const;
    void setKeyBindings(const KeyBindings& bindings);
    const InputState& getInputState();
    const char* getKeyDisplayName(int key);
    void update(GLFWwindow* window);

    void loadBindings();
    void saveBindings();

private:
    KeyBindings keyMap;
    InputState state;

    std::string filename;
};