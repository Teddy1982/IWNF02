#include "Controls.h"

Controls::Controls() {
    filename = "data/Controls.txt";
    if (!std::filesystem::exists(filename)) {
        if (!std::filesystem::exists("data")) {
            std::filesystem::create_directory("data");
        }
        std::ofstream ofs(filename);
        if (!ofs) {
            Logger::log(2, "error while creating '%s'\n", filename.c_str());
        }

        saveBindings();
    }
}

const KeyBindings& Controls::getKeyBindings() const {
    return keyMap;
}

void Controls::setKeyBindings(const KeyBindings& bindings) {
    keyMap = bindings;
}

void Controls::keyCallback(int key, int action) {
    bool pressed = (action == GLFW_PRESS);

    if (key == keyMap.cameraUp)                  state.cameraUp = pressed;
    else if (key == keyMap.cameraDown)           state.cameraDown = pressed;
    else if (key == keyMap.cameraLeft)           state.cameraLeft = pressed;
    else if (key == keyMap.cameraRight)          state.cameraRight = pressed;
    else if (key == keyMap.cameraForward)        state.cameraForward = pressed;
    else if (key == keyMap.cameraBackward)       state.cameraBackward = pressed;
    else if (key == keyMap.up)                   state.moveUp = pressed;
    else if (key == keyMap.down)                 state.moveDown = pressed;
    else if (key == keyMap.left)                 state.moveLeft = pressed;
    else if (key == keyMap.right)                state.moveRight = pressed;
    else if (key == keyMap.forward)              state.moveForward = pressed;
    else if (key == keyMap.backward)             state.moveBackward = pressed;
    else if (key == keyMap.pause)                state.pause = pressed;
}

const InputState& Controls::getInputState() {
    return state;
}

const char* Controls::getKeyDisplayName(int key) {
    const char* name = glfwGetKeyName(key, 0);
    if (name) return name;

    switch (key) {
    case GLFW_KEY_UP: return "<ARROW_UP>";
    case GLFW_KEY_DOWN: return "<ARROW_DOWN>";
    case GLFW_KEY_LEFT: return "<ARROW_LEFT>";
    case GLFW_KEY_RIGHT: return "<ARROW_RIGHT>";
    case GLFW_KEY_SPACE: return "<SPACE>";
    case GLFW_KEY_ENTER: return "<ENTER>";
    case GLFW_KEY_ESCAPE: return "<ESC>";
    default: return "???";
    }
}

void Controls::update(GLFWwindow* window) {
    state.cameraUp = glfwGetKey(window, keyMap.cameraUp) == GLFW_PRESS;
    state.cameraDown = glfwGetKey(window, keyMap.cameraDown) == GLFW_PRESS;
    state.cameraLeft = glfwGetKey(window, keyMap.cameraLeft) == GLFW_PRESS;
    state.cameraRight = glfwGetKey(window, keyMap.cameraRight) == GLFW_PRESS;
    state.cameraForward = glfwGetKey(window, keyMap.cameraForward) == GLFW_PRESS;
    state.cameraBackward = glfwGetKey(window, keyMap.cameraBackward) == GLFW_PRESS;
    state.moveUp = glfwGetKey(window, keyMap.up) == GLFW_PRESS;
    state.moveDown = glfwGetKey(window, keyMap.down) == GLFW_PRESS;
    state.moveLeft = glfwGetKey(window, keyMap.left) == GLFW_PRESS;
    state.moveRight = glfwGetKey(window, keyMap.right) == GLFW_PRESS;
    state.moveForward = glfwGetKey(window, keyMap.forward) == GLFW_PRESS;
    state.moveBackward = glfwGetKey(window, keyMap.backward) == GLFW_PRESS;
    state.pause = glfwGetKey(window, keyMap.pause) == GLFW_PRESS;
}

void Controls::loadBindings() {
    std::vector<int> entries;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int entry;
        entry = std::stoi(line);
        entries.push_back(entry);
    }

    KeyBindings bindings;
    bindings.cameraUp = entries[0];
    bindings.cameraDown = entries[1];
    bindings.cameraLeft = entries[2];
    bindings.cameraRight = entries[3];
    bindings.cameraForward = entries[4];
    bindings.cameraBackward = entries[5];
    bindings.up = entries[6];
    bindings.down = entries[7];
    bindings.left = entries[8];
    bindings.right = entries[9];
    bindings.forward = entries[10];
    bindings.backward = entries[11];
    bindings.pause = entries[12];

    setKeyBindings(bindings);
}

void Controls::saveBindings() {
    std::ofstream file(filename, std::ios::trunc);
    file << keyMap.cameraUp << "\n";
    file << keyMap.cameraDown << "\n";
    file << keyMap.cameraLeft << "\n";
    file << keyMap.cameraRight << "\n";
    file << keyMap.cameraForward << "\n";
    file << keyMap.cameraBackward << "\n";
    file << keyMap.up << "\n";
    file << keyMap.down << "\n";
    file << keyMap.left << "\n";
    file << keyMap.right << "\n";
    file << keyMap.forward << "\n";
    file << keyMap.backward << "\n";
    file << keyMap.pause << "\n";

    file.close();
}
