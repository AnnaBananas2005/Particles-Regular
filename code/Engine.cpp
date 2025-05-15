#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
using namespace sf;
using namespace std;
//Done by Fernanda :D

RenderWindow m_Window;
vector<Particle> m_particles;

Engine::Engine()
{
    //Anna's part
    unsigned int screenWidth = VideoMode::getDesktopMode().width / 2;
    unsigned int screenHeight = VideoMode::getDesktopMode().height / 2;

    VertexArray vertices(Points);

    m_Window.create(VideoMode(screenWidth, screenHeight), "P A R T I C L E S"); 
    //End of Anna's Contribution

}

void Engine::run()
{
    Clock clock;

    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    while (m_Window.isOpen())
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

    while (m_Window.pollEvent(event)) 
    {
        if (event.type == Event::Closed)
        {
            m_Window.close();
        }

        if (event.type == Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == Mouse::Left)
            {
                for (int i = 0; i < 5; i++)
                {
                    int m_numPoints = rand() % 26 + 25;
                    Particle particle(m_Window, m_numPoints, { event.mouseButton.x, event.mouseButton.y });

                    m_particles.push_back(particle); 

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
    for (size_t i = 0; i < m_particles.size();) 
    {
        if (m_particles[i].getTTL() > 0.0f)
        {
            m_particles[i].update(dtAsSeconds);
            i++;
        }
        else
        {
            m_particles.erase(m_particles.begin() + i);
        }
    }
}

void Engine::draw() 
{
    m_Window.clear();
    for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }
    m_Window.display();
}
