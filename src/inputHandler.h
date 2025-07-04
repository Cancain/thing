#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SDL2/SDL.h>
#include <functional>
#include <map>
#include <vector>

class InputHandler
{
public:
    using KeyCallback = std::function<void()>;
    using MouseCallback = std::function<void(int x, int y)>;
    using EventCallback = std::function<void(SDL_Event &)>;

    InputHandler();
    ~InputHandler();

    void handleEvents(SDL_Event &event);
    void pollEvents();

    void onKeyDown(SDL_Keycode key, KeyCallback callback);
    void onKeyUp(SDL_Keycode key, KeyCallback callback);
    void onEscapeDown(KeyCallback callback);
    void onSpaceDown(KeyCallback callback);

    void onMouseClick(int button, MouseCallback callback);
    void onLeftClick(MouseCallback callback);
    void onRightClick(MouseCallback callback);

    void onQuit(KeyCallback callback);

    void removeKeyCallback(SDL_Keycode key, bool isKeyDown = true);
    void removeMouseCallback(int button);
    void removeQuitCallback();

    bool isKeyPressed(SDL_Keycode key) const;
    bool isMouseButtonPressed(int button) const;

private:
    std::map<SDL_Keycode, bool> m_keyStates;
    std::map<int, bool> m_mouseButtonStates;

    std::map<SDL_Keycode, std::vector<KeyCallback>> m_keyDownCallbacks;
    std::map<SDL_Keycode, std::vector<KeyCallback>> m_keyUpCallbacks;
    std::map<int, std::vector<MouseCallback>> m_mouseCallbacks;
    std::vector<KeyCallback> m_quitCallbacks;

    void handleKeyDown(SDL_Keycode key);
    void handleKeyUp(SDL_Keycode key);
    void handleMouseDown(int button, int x, int y);
    void handleMouseUp(int button, int x, int y);
    void handleQuit();
};

#endif