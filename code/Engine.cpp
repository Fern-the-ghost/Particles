#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "particle.cpp"
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
  create(m_Window);
  VideoMode::getDesktopMode(1980,1080);
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
      clock.restart();
      float sec = time1.asSeconds();
      p.input();
      p.update(sec);
      p.draw();
    }
}

void Engine::input()
{
  Event event;
  
  while(m_window.pollEvent(event))
  {
      if(event.type == Event::Closed)
      {
          m_window.close();
      }
  
      if(event.type == Event::MouseButtonPressed)
      {
          if(event.mouseButton.button == Mouse::Left)
          {
              for(int i = 0; i < 5; i++)
              {
                m_numPoints = rand() % 5;
                //Particle particle; 
                m_particles.position = sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
              }
          }
      }
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
          m_window.close();
      }
  
  } 
}

void Engine::update(float dtAsSeconds)
{
  for(int i = 0; i < m_particles)
    {
      if(m_particles[i].getTTL() > 0.0)
      {
        m_particles[i].update(dt);
        i++;
      }
      else
      {
        m_particles.erase(i);
        return i++; //don't know if this would work
        //DO NOT increment
      }
    }
}

void Endgine::draw()
{
  m_window.clear();
  for(int i = 0; i < m_particles; i++)
    {
      m_Window.draw(m_particles(i));
      //should it be Particle::draw();?
      //mentions using polymorphism
    }
  m_window.display();
}
