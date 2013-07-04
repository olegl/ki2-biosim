#include "flock.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
namespace biosim
{

// fix the dumb MS C++ without round()
#ifndef round
	inline int round(double x)
	{
		return floor(x+0.5);
	}
#endif

emuflock::emuflock()
{
    //ctor
}

void emuflock::vote()
{
    int preferences[] = {0,0,0,0,0,0,0,0,0};
    int result[] = {0,0,0,0,0,0,0,0,0};

    for (auto iter = creatures.begin(); iter != creatures.end(); iter++)
    {
        (*iter)->getPreferences(preferences);
        for (int i = 0; i < 9; i++)
        {
//            std::cout << preferences[i] << std::endl;
            result[preferences[i]] += (9 - i);
        }
    }

    std::cout << "Ergebnis der Abstimmung: " << std::endl;
    for (int i = 0; i < 9; i++)
    {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    // Gewinner finden
    int maximum = 0;
    int index = 0;
    for (int i = 0; i < 9; i++)
    {
        if (result[i] > maximum)
        {
            index = i;
            maximum = result[i];
        }
    }

    std::cout << "Gewinner ist " << index << " mit " << result[index] << " Stimmen." << std::endl;

    for (auto iter = creatures.begin(); iter != creatures.end(); iter++)
    {
        (*iter)->move_queue.clear();

        (*iter)->preferedDirection = index;
    }

    std::cout << "nach abstimmung" << std::endl;
}

void emuflock::addCreature(std::shared_ptr<creature> new_creature)
{
    if (!new_creature->inFlock)
    {
        new_creature->inFlock = true;
        creatures.push_back(new_creature);
    }
}

void emuflock::removeCreature(std::shared_ptr<creature> c)
{
    auto removeit = std::find(creatures.begin(), creatures.end(), c);

    if (removeit != creatures.end())
    {
        creatures.erase(removeit);
    }
}

void emuflock::calcCenter(int & x, int & y)
{
    x = 0;
    y = 0;
    for (auto iter = creatures.begin(); iter != creatures.end(); iter++)
    {
        x += (*iter)->x();
        y += (*iter)->y();
    }

    x = round((double)x / (double)creatures.size());
    y = round((double)y / (double)creatures.size());
}

}
