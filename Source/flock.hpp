#ifndef FLOCK_H
#define FLOCK_H

#include <memory>
#include <vector>

#include "creature.hpp"

namespace biosim
{

class creature;

/**
    Klasse die eine Herde von Kreaturen modelliert
    */
class emuflock
{
    public:
        emuflock();

        void addCreature(std::shared_ptr<creature> new_creature);
        void removeCreature(std::shared_ptr<creature> c);

        int size() { return creatures.size(); }

        // Methode für die abstimmung in der Herde
        // Als Ergebnis wird eine Richtung zurückgeliefert
        void vote();

        void calcCenter(int & x, int & y);

    private:
        std::list<std::shared_ptr<creature>> creatures;
};

}

#endif // FLOCK_H
