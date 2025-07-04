#include "inputHandler.h"
#include <iostream>

InputHandler::InputHandler()
{
}

InputHandler::~InputHandler()
{
}

void InputHandler::handleEvents(SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
        handleQuit();
        break;
    case SDL_KEYDOWN:
        handleKeyDown(event.key.keysym.sym);
        break;
    case SDL_KEYUP:
        handleKeyUp(event.key.keysym.sym);
        break;
    case SDL_MOUSEBUTTONDOWN:
        handleMouseDown(event.button.button, event.button.x, event.button.y);
        break;
    case SDL_MOUSEBUTTONUP:
        handleMouseUp(event.button.button, event.button.x, event.button.y);
        break;
    }
}

void InputHandler::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        handleEvents(event);
    }
}

void InputHandler::onKeyDown(SDL_Keycode key, KeyCallback callback)
{
    m_keyDownCallbacks[key].push_back(callback);
}

void InputHandler::onKeyUp(SDL_Keycode key, KeyCallback callback)
{
    m_keyUpCallbacks[key].push_back(callback);
}

void InputHandler::onEscapeDown(KeyCallback callback)
{
    onKeyDown(SDLK_ESCAPE, callback);
}

void InputHandler::onSpaceDown(KeyCallback callback)
{
    onKeyDown(SDLK_SPACE, callback);
}

void InputHandler::onMouseClick(int button, MouseCallback callback)
{
    m_mouseCallbacks[button].push_back(callback);
}

void InputHandler::onLeftClick(MouseCallback callback)
{
    onMouseClick(SDL_BUTTON_LEFT, callback);
}

void InputHandler::onRightClick(MouseCallback callback)
{
    onMouseClick(SDL_BUTTON_RIGHT, callback);
}

void InputHandler::onQuit(KeyCallback callback)
{
    m_quitCallbacks.push_back(callback);
}

void InputHandler::removeKeyCallback(SDL_Keycode key, bool isKeyDown)
{
    if (isKeyDown)
    {
        m_keyDownCallbacks.erase(key);
    }
    else
    {
        m_keyUpCallbacks.erase(key);
    }
}

void InputHandler::removeMouseCallback(int button)
{
    m_mouseCallbacks.erase(button);
}

void InputHandler::removeQuitCallback()
{
    m_quitCallbacks.clear();
}

bool InputHandler::isKeyPressed(SDL_Keycode key) const
{
    auto it = m_keyStates.find(key);
    return (it != m_keyStates.end()) ? it->second : false;
}

bool InputHandler::isMouseButtonPressed(int button) const
{
    auto it = m_mouseButtonStates.find(button);
    return (it != m_mouseButtonStates.end()) ? it->second : false;
}

void InputHandler::handleKeyDown(SDL_Keycode key)
{
    m_keyStates[key] = true;

    auto it = m_keyDownCallbacks.find(key);
    if (it != m_keyDownCallbacks.end())
    {
        for (auto &callback : it->second)
        {
            callback();
        }
    }
}

void InputHandler::handleKeyUp(SDL_Keycode key)
{
    m_keyStates[key] = false;

    auto it = m_keyUpCallbacks.find(key);
    if (it != m_keyUpCallbacks.end())
    {
        for (auto &callback : it->second)
        {
            callback();
        }
    }
}

void InputHandler::handleMouseDown(int button, int x, int y)
{
    m_mouseButtonStates[button] = true;

    auto it = m_mouseCallbacks.find(button);
    if (it != m_mouseCallbacks.end())
    {
        for (auto &callback : it->second)
        {
            callback(x, y);
        }
    }
}

void InputHandler::handleMouseUp(int button, int x, int y)
{
    (void)x;
    (void)y;
    m_mouseButtonStates[button] = false;
}

void InputHandler::handleQuit()
{
    for (auto &callback : m_quitCallbacks)
    {
        callback();
    }
}