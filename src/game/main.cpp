/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include <cstdlib>
#include <ctime>
#include "Game.hpp"

#ifdef _WIN32
  #include <windows.h>
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Window * window = nullptr;
Game * game = nullptr;

void loop();
void processInput(GLFWwindow * win);
void resizeEvent(GLFWwindow * win, int w, int h);
void mouseEvent(GLFWwindow * win, double posX, double posY);
void keyPressEvent(GLFWwindow * win, int key, int scancode, int action, int mods);

int main()
{
  srand(time(0));

  try
  {
    #ifdef _WIN32
      FreeConsole();
    #endif

    window = new Window;
    window->create(true);
    window->setTitle("StickMan 3D: First Round");

    game = new Game(*window);
    window->setRenderMethod(loop);
    window->setEventInput(processInput);
    window->setEventMouseMove(mouseEvent);
    window->setEventKeyPress(keyPressEvent);
    window->startRender();
    delete game;
    delete window;
  }
  catch (std::runtime_error & e)
  {
    std::cerr<<e.what()<<std::endl;
    std::cin.get();
  }
  return 0;
}

void loop()
{
  game->render();
}

void mouseEvent(GLFWwindow * win, double posX, double posY)
{
  game->mouseMove(posX, posY);
}

void processInput(GLFWwindow * win)
{
  game->processInput();
}

void keyPressEvent(GLFWwindow * win, int key, int scancode, int action, int mods)
{
  game->keyPress(key, scancode, action, mods);
}
