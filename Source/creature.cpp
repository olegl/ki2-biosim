/**
 *************************************************************************
 *
 * @file creature.cpp
 *
 * Creatures, creature prototypes, and creature management.
 *
 ************************************************************************/


#include "creature.hpp"


#include <iostream>
#include <fstream>
#include <stdlib.h>


#include "exception.hpp"


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// creature_prototype
//
//////////////////////////////////////////////////////////////////////////


std::list<creature_prototype>
creature_prototype::load(const std::string& path)
{
    std::list<creature_prototype> result;

    std::ifstream inputtext;
    inputtext.open(path);

    if (!inputtext)
    {
        std::cerr << "Creature list: " << path << " was not found." << std::endl;
        throw file_operation_failed();
    }

    while (!inputtext.eof() && !!inputtext)
    {
        std::string line;
        std::getline(inputtext, line);

        std::vector<std::string> split_line;
        size_t nextstop = 0;
        while (true)
        {
            nextstop = line.find_first_of(',');
            split_line.push_back(line.substr(0, nextstop));

            if (nextstop == std::string::npos || nextstop > 1000)
                break;

            line = line.substr(nextstop + 1);
        }

        if (split_line.size() != 7)
        {
            std::cerr << "Line in creature list has too few or too many entries. Nextstop = " << nextstop << ", split_line size is " << split_line.size() << std::endl;
            continue;
        }

        try
        {
            std::string name(split_line[0]);
            int strength = atoi(split_line[1].c_str());
            int speed = atoi(split_line[2].c_str());
            int lifetime = atoi(split_line[3].c_str());
            std::string properties(split_line[4]);
            creature_prototype::habitat_type habitat = string_to_habitat(split_line[4]);
            creature_prototype::sustentation_type sustentation = string_to_sustentation(split_line[4]);
            std::unique_ptr<image> graphics(image::load(split_line[5]));
            int reproduction = atoi(split_line[6].c_str());

            result.push_back
            (creature_prototype(name, strength, speed, lifetime,
                                properties, habitat, sustentation, *graphics, reproduction));
        }
        catch (const std::exception&)
        {
            std::cerr << "Line in creature list contains corrupt data." << std::endl;
            continue;
        }
    }

    return result;
}


creature_prototype::habitat_type
creature_prototype::string_to_habitat(const std::string& s)
{
    if (s.find("Wasserbewohner") != std::string::npos)
        return creature_prototype::habitat_water;
    else if (s.find("Landbewohner") != std::string::npos)
        return creature_prototype::habitat_land;
    else
    {
        std::cerr << "Creature habitat was not specified." << std::endl;
        throw corrupt_data();
    }
    std::cerr << "Never reached!" << std::endl;
}


creature_prototype::sustentation_type
creature_prototype::string_to_sustentation(const std::string& s)
{
    if (s.find("Pflanzenfresser") != std::string::npos)
        return creature_prototype::herbivore;
    else if (s.find("Pflanze") != std::string::npos)
        return creature_prototype::plant;
    else if (s.find("Fleischfresser") != std::string::npos)
        return creature_prototype::carnivore;
    else
    {
        std::cerr << "Creature habitat was not specified." << std::endl;
        throw corrupt_data();
    }
    std::cerr << "Never reached!" << std::endl;
}

int creature::getFullRounds()
{
    int counter = 0;

    // Zähle, wie oft die Kreatur in den letzten 10 Runden satt war
    for (auto iter = hunger_memory.begin(); iter != hunger_memory.end(); iter++)
    {
        if (*iter)
            counter++;
    }

    return counter;
}

bool creature::isFull()
{
    if (prototype.sustentation() == creature_prototype::herbivore)
    {
        if (full_count >= prototype.repFreq())
            return true;
    }
    else if (prototype.sustentation() == creature_prototype::carnivore)
    {
        if (hunger_memory.size() == 10)
        {
            // Falls die Kreatur in den letzten 10 Runden mind. repFreq mal satt war
            if (getFullRounds() >= prototype.repFreq())
            {
                return true;
            }
        }
    }

    return false;
}

void creature::getPreferences(int pref[9])
{
    std::vector<int> numbers;
    for (int i = 0; i < 9; i++)
    {
        numbers.push_back(i);
    }

    int j = 0;
    while (numbers.size() > 0)
    {
        int random = rand() % numbers.size();
        pref[j] = numbers[random];
        numbers.erase(numbers.begin()+random);
        j++;
    }
}

void creature::addMove()
{
    if (move_queue.size() == 0)
    {
        switch(preferedDirection)
        {
        case 0:
            move_queue.push_back(0);
            break;
        case 1:
            move_queue.push_back(1);
            break;
        case 2:
            move_queue.push_back(1);
            move_queue.push_back(2);
            break;
        case 3:
            move_queue.push_back(2);
            break;
        case 4:
            move_queue.push_back(3);
            move_queue.push_back(2);
            break;
        case 5:
            move_queue.push_back(3);
            break;
        case 6:
            move_queue.push_back(3);
            move_queue.push_back(4);
            break;
        case 7:
            move_queue.push_back(4);
            break;
        case 8:
            move_queue.push_back(1);
            move_queue.push_back(4);
            break;
        default:
            move_queue.push_back(rand()%4 + 1);
            break;
        }
    }
}

void creature::moveNot()
{
    preferedDirection = 0;
}

void creature::moveUp()
{
    preferedDirection = 1;
}
void creature::moveRight()
{
    preferedDirection = 3;
}
void creature::moveDown()
{
    preferedDirection = 5;
}
void creature::moveLeft()
{
    preferedDirection = 7;
}
void creature::moveUpRight()
{
    preferedDirection = 2;
}
void creature::moveUpLeft()
{
    preferedDirection = 8;
}
void creature::moveDownRight()
{
    preferedDirection = 4;
}
void creature::moveDownLeft()
{
    preferedDirection = 6;
}
void creature::moveRandom()
{
    preferedDirection = 9;
}

void creature::getMove(int & x, int & y)
{
    if (!move_queue.empty())
    {
        // Richtung ermitteln
        int direction = move_queue.front();
        move_queue.pop_front();

        switch(direction)
        {
        case 0: // Stehen bleiben
            x = x_;
            y = y_;
            break;
        case 1: // Nach oben
            x = x_;
            y = y_ - 1;
            break;
        case 2: // Nach rechts
            x = x_ + 1;
            y = y_;
            break;
        case 3: // Nach unten
            x = x_;
            y = y_ + 1;
            break;
        case 4: // Nach links
            x = x_ - 1;
            y = y_;
            break;
        }
    }
    // Wenn keine Bewegung gespeichert ist -> stehen bleiben
    else
    {
        x = x_;
        y = y_;
    }
}

} /* namespace biosim */
