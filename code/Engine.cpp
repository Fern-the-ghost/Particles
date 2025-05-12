#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle-2.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Particle.cpp"
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
  m_Window.create(VideoMode::getDesktopMode(1980,1080), "Particle Program");
}

void Engine::run()
{
  Clock clock;
  
  cout << "Starting Particle unit tests..." << endl;
  Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
  p.unitTests();
  cout << "Unit tests complete.  Starting engine..." << endl;

  while(m_Window.isOpen)
    {
      Time time1 = clock.restart();
      float sec = time1.asSeconds();
      input();
      update(sec);
      draw();
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
                m_numPoints = rand() % 26 + 25;
                Particle particle; 
                particle.position = sf::Vector2f(event.mouseButton.x,event.mouseButton.y);
                m_particle.push_back(particle);
                
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
  int num = 0;
  
  while(num < m_particles.end())
    {
      if(m_particles[num].getTTL() > 0.0)
      {
        m_particles[num].update(dtAsSeconds);
        ++i;
      }
      else
      {
        num = m_particles.erase();
        //don't know if this would work
        //DO NOT increment
      }
    }
}

void Endgine::draw()
{
  m_window.clear();
  //using this for loop would keep the vector the same and not change any of the info in the vector
  for(const auto& Particle : m_particles)
    {
      //Will go through each particle in the vector and put it in m_window.draw where it will call the Particle draw function
      m_Window.draw(Particles);
    }
  m_window.display();
}
