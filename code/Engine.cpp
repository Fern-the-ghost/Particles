#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
  create(m_Window);
  VideoMode::getDesktopMode();
}

void input()
{
}

void update(float dtAsSeconds)
{
}

void draw()
{
}

void run()
{
}
