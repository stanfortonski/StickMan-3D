/* Copyright (c) 2020, Stan Fortoński. All rights reserved.*/

#include "Game.hpp"

Game::Game(Window & win): window(win), perspectiveCamera(win), camera(&perspectiveCamera),
worldModel("objects/world/world.obj"), bloomEffect(win), post(win), postHDR(win, 2),
pointLight(glm::vec3(0.0f, 9.0f, 0.0f), glm::vec3(1.3f), glm::vec3(1.3f), glm::vec3(1.3f), 1.0f, 0.0003f, 0.018f)
{
  initShadersManager();
  initOnlyMap();
  gui = new GUI(window, manager);
  input = new GameInput(*this);
}

void Game::initOnlyMap()
{
  scene = new Scene(window, camera, manager);

  skybox.getTexture().load({"textures/cubemap/px.jpg", "textures/cubemap/nx.jpg", "textures/cubemap/py.jpg", "textures/cubemap/ny.jpg", "textures/cubemap/pz.jpg", "textures/cubemap/nz.jpg"});
  scene->addSkybox(skybox);
  scene->addLight(pointLight);

  worldModel.scale(glm::vec3(3.0f, 1.0f, 3.0f));
  worldModel.setPosition(glm::vec3(0.0f, -0.37f, 0.0f));
  scene->addObject(worldModel);

  rain = new RainEffect(camera, manager.getParticleProgram());
  rain->generate(18000);
}

void Game::clearForFight()
{
  scene->getAnimations().clear();

  if (fight != nullptr)
    delete fight;

  if (player1 != nullptr)
    delete player1;

  if (player2 != nullptr)
    delete player2;
}

void Game::initFight()
{
  player1 = new Player;
  if (fightMode == PVP_MODE)
    player2 = new Player;
  else if (fightMode == PVN_MODE)
    player2 = new NPC;
  else throw std::runtime_error("Undefined Fight Mode");

  fight = new Fight(perspectiveCamera, *player1, *player2);
  scene->addAnimation(*player1);
  scene->addAnimation(*player2);
}

void Game::initShadersManager()
{
  Shader fragment = Shader::createFragmentShader("shaders/depth/depth.fs");
  Shader geometry = Shader::createGeometryShader("shaders/depth/depth.gs");

  Program depthProgram;
  depthProgram.create();
  depthProgram.attachShader(Shader::createVertexShader("shaders/depth/depth.vs"));
  depthProgram.attachShader(geometry);
  depthProgram.attachShader(fragment);
  depthProgram.link();

  Program depthAnimProgram;
  depthAnimProgram.create();
  depthAnimProgram.attachShader(Shader::createVertexShader("shaders/depth/anim_depth.vs"));
  depthAnimProgram.attachShader(geometry);
  depthAnimProgram.attachShader(fragment);
  depthAnimProgram.link();

  manager.setObjectProgram(Program("shaders/object.vs", "shaders/object.fs"));
  manager.setAnimProgram(Program("shaders/anim.vs", "shaders/object.fs"));
  manager.setSkyboxProgram(Program("shaders/skybox.vs", "shaders/skybox.fs"));
  manager.setHDRProgram(Program("shaders/effect/hdr.vs", "shaders/effect/hdr.fs"));
  manager.setBlurProgram(Program("shaders/effect/blur.vs", "shaders/effect/blur.fs"));
  manager.setParticleProgram(Program("shaders/rain.vs", "shaders/rain.fs"));
  manager.setFontProgram(Program("shaders/font/font.vs", "shaders/font/font.fs"));
  manager.setPostProcessProgram(Program("shaders/effect/postprocessing.vs", "shaders/effect/postprocessing.fs"));
  manager.setDepthProgram(depthProgram);
  manager.setAnimDepthProgram(depthAnimProgram);

  interfaceProgram = new Program("shaders/interface.vs", "shaders/interface.fs");
  interfaceProgram->use();
  interfaceProgram->setFloat("width", window.getWidth());

  manager.getPostProcessProgram().use();
  manager.getPostProcessProgram().setFloat("slowMotion", 1);
}

Game::~Game()
{
  delete scene;
  delete rain;
  delete input;
  delete interfaceProgram;
  delete gui;

  clearForFight();
}

void Game::render()
{
  Engine::Engine::get().initDeltaTime();

  if (appMode == MENU_MODE || appMode == CREDITS_MODE)
    perspectiveCamera.setMapView();

  if (fight != nullptr && appMode == FIGHT_MODE)
  {
    fight->fight();
    if (fight->getState() == Fight::ENDED)
    {
      appMode = PAUSE_MODE;
      gui->initPauseMenu();
    }
  }

  glm::vec3 camPos = camera->getPosition();
  rain->setPosition(glm::vec3(camPos.x, 0.0f, camPos.z));
  rain->translate(glm::vec3(2.0f, 0.0f, 2.0f));

  scene->renderShadows();

  postHDR.startProcessing();
  glDisable(GL_BLEND);
  scene->render();
  glEnable(GL_BLEND);
  rain->update();
  rain->render();
  postHDR.endProcessing();
  bloomEffect.blurTexture(manager.getBlurProgram(), postHDR.getResultTextures()[1]);

  std::vector<Texture> result;
  result.push_back(postHDR.getResultTextures()[0]);
  result.push_back(bloomEffect.getResultTexture());

  post.startProcessing();
  PostProcessing::renderToQuad(manager.getHDRProgram(), result);

  if (appMode == PAUSE_MODE || appMode == MENU_MODE)
    PostProcessing::renderToQuad(*interfaceProgram, post.getResultTextures());

  if (appMode == MENU_MODE)
    gui->renderMainMenu();
  else if (appMode == FIGHT_MODE)
    gui->renderFightInterface(*fight);
  else if (appMode == CREDITS_MODE)
    gui->renderAuthorCredits();
  else if (appMode == PAUSE_MODE)
    gui->renderPauseMenu();

  post.endProcessing();

  PostProcessing::renderToQuad(manager.getPostProcessProgram(), post.getResultTextures());

  Engine::Engine::get().limitFPS(64);
}

void Game::mouseMove(const double & posX, const double & posY)
{
  if (input != nullptr)
    input->mouseMove(posX, posY);
}

void Game::processInput()
{
  if (input != nullptr)
    input->processInput();
}

void Game::keyPress(int key, int scancode, int action, int mods)
{
  if (input != nullptr)
    input->keyPress(key, scancode, action, mods);
}
