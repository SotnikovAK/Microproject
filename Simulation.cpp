#include "Simulation.h"

Simulation::Simulation(int n)
{
    CreationElements(UpdateFrames,n);
}

void Simulation::WindowInteraction()
{
    sf::RenderWindow window(sf::VideoMode(WindowSize[0], WindowSize[1]), "Simulation");
    sf::Texture T;
    sf::Event event;
    T.create(window.getSize().x, window.getSize().y);

    long long int  t = 0;
    while (window.isOpen())
    {

        if (t % UpdateFrames == 0)
        {
            T.update(window);
        }
        ++t;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        for (auto element = ElementList.begin(); element != ElementList.end(); element++)
        {
            element->Starting_conditions_for_W();
        }
        for (auto element = ElementList.begin(); element != ElementList.end(); ++element)
        {
            for (auto force = std::next(element); force != ElementList.end(); force++)
            {
                element->GravitationalForce(&(*force));
            }
        }
        window.clear();

        for (auto element = ElementList.begin(); element != ElementList.end(); element++)
        {

            auto element_ = std::next(element);
            while (element_ != ElementList.end())
            {
                if (element->ClashReporter(*element_))
                {
                    element->InelasticClashForce(&(*element_));
                    element_ = ElementList.erase(element_);
                    element_--;
                }
                element_++;
            }
        }

        for (auto element = ElementList.begin(); element != ElementList.end(); element++)
        {
            element->Cout();
            element->Move();
            element->Draw(&window);
        }

        window.display();

       
    }
}

void Simulation::CreationElements(float UpdateFrames, int N)
{

    std::seed_seq seed_{ time(NULL) };
    std::mt19937 mt(seed_);
    std::uniform_real_distribution<> X(SpawnBorderEpsillon[0], WindowSize[0] - SpawnBorderEpsillon[0]);
    std::uniform_real_distribution<> Y(SpawnBorderEpsillon[1], WindowSize[1] - SpawnBorderEpsillon[1]);
    std::uniform_real_distribution<> Vx(0, 1);
    std::uniform_real_distribution<> Vy(0, 1);
    std::uniform_real_distribution<> M(10, 250);

    for (int i = 0; i < N; ++i) {
        ElementList.push_back(ElementarElement(X(mt), Y(mt), UpdateFrames));

    }
    for (auto element = ElementList.begin(); element != ElementList.end(); ++element) {

        element->SpawnPoint(X(mt), Y(mt));
        element->Starting_conditions_for_V(Vx(mt), Vy(mt));
        element->Starting_conditions_for_M(M(mt));

    }
}

