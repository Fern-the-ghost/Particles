#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
  create(m_Window);
  VideoMode::getDesktopMode();
}

void Engine::run()
{
  Clock clock;
  Time time1 = clock.getElapsedTime();
  
  cout << "Starting Particle unit tests..." << endl;
  Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
  p.unitTests();
  cout << "Unit tests complete.  Starting engine..." << endl;

  while(m_Window.isOpen)
    {
      Time time2 = clock.restart();
      input();
      update(time1);
      draw();
    }
}

void Engine::input()
{
  Event event;
  
  while(window.pollEvent(event))
  {
      if(event.type == Event::Closed)
      {
          window.close();
      }
  }
  if(event.type == Event::MouseButtonPressed)
  {
    if(event.mouseButton.button == Mouse::Left)
    {
      for(int i = 0; i < 5; i++)
        {
          Particle particle;
          particle.position = sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
        }
    }
  }
}

void Engine::update(float dtAsSeconds)
{
  for(int i = 0; i < m_particles)
    {
      if(getTTL() > 0.0)
      {
        particles.update(dt);
        i++;
      }
      else
      {
        particles.erase(i);
        //erase needs to return an iterator
        //do not increment
      }
    }
}

void Endgine::draw()
{
  window.clear();
  for(int i = 0; i < m_Particles; i++)
    {
      m_Window.draw(m_Particles(i));
      //should it be Particle::draw();?
    }
  window.display();
}
