#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Particle.cpp"
using namespace sf;
using namespace std;
//Done by Anna

Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) {
    m_ttl = TTL;
    m_numPoints = numPoints;
    float randomNumber = static_cast<float>(rand())/(RAND_MAX) /
    m_radiansPerSec = randomNumber * PI;

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, -1.0 * target.getSize().y);
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane); 
    m_vx = rand() % 401 + 100; //Can be between whatever number (100-500)
    m_vy = rand() % 401 + 100; 
    m_color1 = Color::White;
    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256);

    theta = rand() % PI / 2;
    dTheta = 2 * PI / (numPoints - 1);
    float r, dx, dy;
    for (int j = 0; j < numPoints; j++) {
        r = rand() % 21 + 20; //20-40
        dx = r * cos(theta);
        dy = r * sin(theta);
        m_A(0, j) = m_centerCoordinate.x + dx;
        m_A(1, j) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}

/*
draw(RenderTarget& target, RenderStates states) const
This function overrides the virtual function from sf::Drawable to allow our draw function to polymorph
To draw, we will convert our Cartesian matrix coordinates from m_A to pixel coordinates in a VertexArray of primitive type TriangleFan
    Take a look at the SFML tutorial regarding the TriangleFanLinks to an external site. and refer to the picture below:
    Triangle fan diagram

Construct a VertexArray named lines
    Its arguments are TriangleFan, and the number of points numPoints + 1
    The + 1 is to account for the center as shown above
Declare a local Vector2f named center
    This will be used to store the location on the monitor of the center of our particle
    Assign it with the mapping of m_centerCoordinate from Cartesian to pixel / monitor coordinates
    using target.mapCoordsToPixelLinks to an external site.
        Don't forget to pass m_cartesianPlane in as an argument!
Assign lines[0].position with center
Assign lines[0].color with m_color
      This will assign m_color to the center of our particle.  
      If the outer colors are different, the engine will automatically
      create a cool looking smooth color gradient between the two colors
Loop j from 1 up to and including m_numPoints
    Note that the index in lines is 1-off from the index in m_A because
    lines must contain the pixel coordinate for the center as its first element
    Assign lines[j].position with the coordinate from column j - 1 in m_A, mapped from Cartesian to
    pixel coordinates using target.mapCoordsToPixelLinks to an external site.
        Don't forget to pass m_cartesianPlane in as an argument!
    Assign lines[j].color with m_Color2
When the loop is finished, draw the VertexArray:
    target.draw(lines)
*/

void draw(RenderTarget& target, RenderStates states) const {   
    VertexArray lines(TriangleFan, numPoints + 1); 
    Vector2f center = target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane); 

    lines[0].position = center;
    lines[0].color = m_color;

    for (int j = 1; j <= m_numPoints; j++) {
        lines[j].position = target.mapCoordsToPixel(Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane);
        lines[j].color = m_Color2;
    }
    target.draw(lines, states); 
}

/*
update(float dt)
Subtract dt from m_ttl
Note:  the functions rotate, scale, and translate will be defined later
Call rotate with an angle of dt * m_radiansPerSec
Call scale using the global constant SCALE from Particle.h
    SCALE will effectively act as the percentage to scale per frame
    0.999 experimentally seemed to shrink the particle at a nice speed that wasn't too fast or too slow (you can change this)
Next we will calculate how far to shift / translate our particle, using distance (dx,dy)
    Declare local float variables dx and dy
    Assign m_vx * dt to dx
    The vertical velocity should change by some gravitational constant G, also experimentally determined and defined in Particle.h
        This will allow the particle to travel up then fall down as if having an 
        initial upward velocity and then getting pulled down by gravity
    Subtract G * dt from m_vy
    Assign m_vy * dt to dy
    Call translate using dx,dy as arguments
*/

void update(float dt) { 
    m_ttl -= dt; 
    rotate(dt * m_radiansPerSec);
    scale(SCALE);   

    float dx, dy;
    dx = m_vx * dt;
    m_vy -= G * dt; 
    dy = m_vy * dt;

    translate(dx, dy);
}
  
/*
translate(double xShift, double yShift)
Construct a TranslationMatrix T with the specified shift values xShift and yShift
Add it to m_A as m_A = T + m_A
Update the particle's center coordinate:
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
 */

translate(double xShift, double yShift) {
    TranslationMatrix T(xShift, yShift);
    T += m_A;
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
}
    
/*
rotate(double theta)
Since the rotation matrix we will use is algebraically derived to rotate coordinates about the origin,
we will temporarily shift our particle to the origin before rotating it
    Store the value of m_centerCoordinate in a Vector2f temp
    Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        This will shift our particle's center, wherever it is, back to the origin
Construct a RotationMatrix R with the specified angle of rotation theta
Multiply it by m_A as m_A = R * m_A
      Note: make sure to left-multiply R, as matrix multiplication is not commutative due to the fact that
      it multiplies the lvalue's rows into the rvalue's columns.
Shift our particle back to its original center:
    translate(temp.x, temp.y);
*/

void rotate(double theta) {
    Vector2f temp = m_centerCoordinate;
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
    RotationMatrix R(theta);
    m_A = R * m_A;                  
    translate(temp.x, temp.y);
}

/*
scale(double c)
Scaling is also derived to scale coordinates relative to their distance from the origin.  
So we will also have to temporarily shift back to the origin here before scaling:
    Store the value of m_centerCoordinate in a Vector2f temp
    Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        This will shift our particle's center, wherever it is, back to the origin
Construct a ScalingMatrix S with the specified scaling multiplier c
Multiply it by m_A as m_A = S * m_A
Shift our particle back to its original center:
    translate(temp.x, temp.y);
    

*/

void scale(double c) {
    m_centerCoordinate = Vector2f temp;     
    translate(-m_centerCoordinate.x, -m_centerCoordinate.y); 
    ScalingMatrix S(c);   
    m_A = S * m_A;           
    translate(temp.x, temp.y);
}

/*
almostEqual and unitTests
Copy these from the starter code given above. 
Make sure to call unitTests from Engine::run as you go so you can check your progress

Matrix Transformations
Each Matrix transformation class is a specific type of matrix that will apply the given transformation to another matrix.
RotationMatrix inherits from Matrix.  Its constructor will create the following 2x2 matrix: (photo)

ScalingMatrix inherits from Matrix.  Its constructor will create the following 2x2 matrix: (photo)

TranslationMatrix inherits from Matrix.  Its constructor will create the following 2xn matrix, where n is the total number of stored points: (photo)

*/
