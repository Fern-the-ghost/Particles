#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "particle.cpp"
using namespace sf;
using namespace std;

translate(double xShift, double yShift) {
    TranslationMatrix T;
    T += m_A;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}

void rotate(double theta) {
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    RotationMatrix R(theta);
    m_A = R * m_A;                  
    translate(temp.x, temp.y);
}

void scale(double c) {
    m_centerCoordinate = Vector2f temp;     
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y); 
    ScalingMatrix S(c);   
    m_A = S * m_A;           
    translate(temp.x, temp.y);
}
