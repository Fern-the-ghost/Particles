#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Particle.cpp"
using namespace sf;
using namespace std;

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
  m_Window.create(VideoMode(VideoMode::getDesktopMode()), "Particles Program");
}

void Engine::run()
{
  Clock clock;
  
  cout << "Starting Particle unit tests..." << endl;
  Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
  p.unitTests();
  cout << "Unit tests complete.  Starting engine..." << endl;

  while(m_Window.isOpen())
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
  
  while(m_Window.pollEvent(event))
  {
      if(event.type == Event::Closed)
      {
          m_Window.close();
      }
  
      if(event.type == Event::MouseButtonPressed)
      {
          if(event.mouseButton.button == Mouse::Left)
          {
            
            Vector2i mouse_Pos = Mouse::getPosition(event.mouseButton.x,event.mouseButton.y);
            
              for(int i = 0; i < 5; i++)
              {
                int numPoints = rand() % 26 + 25;
                
                Particle particle(m_Window, numPoints, mouse_Pos);
                
                m_particle.push_back(particle);
                
              }
          }
      }
      if (Keyboard::isKeyPressed(Keyboard::Escape))
      {
          m_Window.close();
      }
  
  } 
}

void Engine::update(float dtAsSeconds)
{
  auto num = m_particles.begin();
  
  while(num != m_particles.end())
    {
      if(num->getTTL() > 0.0f)
      {
        num->update(dtAsSeconds);
        ++num;
      }
      else
      {
        num = m_particles.erase(num);
        //DO NOT increment
      }
    }
}

void Engine::draw()
{
  m_Window.clear();
  //using this for loop would keep the vector the same and not change any of the info in the vector
  for(const auto& Particle : m_particles)
    {
      //Will go through each particle in the vector and put it in m_window.draw where it will call the Particle draw function
      m_Window.draw(Particle);
    }
  m_Window.display();
}
