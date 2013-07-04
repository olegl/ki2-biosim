// partially (c) Daniel Kober
// partially (c) Simon Pirkelmann

/**
 *************************************************************************
 *
 * @file model.cpp
 *
 * Contains the high-level application data model, implementation.
 *
 ************************************************************************/


#include "model.hpp"


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>


#include "exception.hpp"
// #include <Windows.h>
#include <queue>

#define TEST


namespace biosim
{


//////////////////////////////////////////////////////////////////////////
//
// model
//
//////////////////////////////////////////////////////////////////////////


model::model()
    :
    prototypes_(creature_prototype::load(default_prototype_list_)),
    map_(default_world_size_x_, default_world_size_y_),
    map_smell(default_world_size_x_, default_world_size_y_),
    cursor_x_(0),
    cursor_y_(0)
{
    srand( static_cast<unsigned int>(time(NULL) ));


#ifdef TEST
    for (auto iter = prototypes_.begin(); iter != prototypes_.end(); iter++)
    {
//        if ((*iter).name() == "Kaktus")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Sonnenblume")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Eiche")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Obstbaum")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Tannenbaum")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Gebüsch")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }

        if ((*iter).name() == "Gras")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,5) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Emu")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,10) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

//        if ((*iter).name() == "Wolf")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                    // Gras zufällig platzieren
//                    if (randomNumberMinMax(1,200) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }

//        if ((*iter).name() == "Schaf")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//
//        if ((*iter).name() == "Kuh")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Pferd")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
//
//        if ((*iter).name() == "Emu")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                     Gras zufällig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
    }
#endif

//    int number_of_flocks = (int)((double)(default_world_size_x_ * default_world_size_y_) / 625.0);
//
//    emu_flocks.resize(number_of_flocks);

    std::vector<std::shared_ptr<creature>> emus;

    // Neue Gerüche hinzufügen
    for(auto it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        if (prototype.name() == "Emu")
            emus.push_back(*it);
    }

    std::cout << "Anzahl Emus: " << emus.size() << std::endl;

    bool cont = true;

    if (emus.size()>0)
    while (cont)
    {
        // Zufälligen Emu auswählen
        int random_number = randomNumberMinMax(0,emus.size()-1);

        std::shared_ptr<creature> random_emu = emus[random_number];

        std::cout << "Zufaelliger Emu: " << random_number << std::endl;

//        std::vector<creature> new_flock;
        emuflock new_flock;

        // Alle Emus im Umkreis des zufälligen Emus suchen
        for (auto it = emus.begin(); it != emus.end(); it++)
        {
            // Falls der Abstand zum zufälligen Emu kleiner als 20 ist, kommen die Emus zusammen in eine Herde
            if ( abs( (*it)->x() - random_emu->x() ) + abs( (*it)->y() - random_emu->y() ) <= 25)
            {
                new_flock.addCreature(*it);
            }
        }

        std::cout << "Groesse der neuen Herde: " << new_flock.size() << std::endl;

        if (new_flock.size() != 0)
        {
            emu_flocks.push_back(new_flock);
        }

        cont = false;
        // Überprüfen, ob es noch Emus ohne Herde gibt
        for (auto it = emus.begin(); it != emus.end(); it++)
        {
            // Wenn ein Emu noch keine Herde hat, wird weitergemacht
            if (!(*it)->inFlock)
                cont = true;
        }
    }

    std::cout << emu_flocks.size() << " Erstellte Herden: " << std::endl;
    int i = 0;
    for (auto iter = emu_flocks.begin(); iter != emu_flocks.end(); iter++, i++)
    {
        int x,y;
        iter->calcCenter(x,y);
        std::cout << "Herde " << i+1 << " hat " << iter->size() << " Emus, Zentrum ist : (" << x << "," << y << ")" << std::endl;
    }
}


void model::set_cursor(int x, int y)
{
    if (x < 0 || x >= map_.size_x() ||
            y < 0 || y >= map_.size_y()) return;

    cursor_x_ = x;
    cursor_y_ = y;
}


void model::create_creature_at_cursor
(const creature_prototype& prototype)
{
    create_creature(prototype, cursor_x_, cursor_y_);
}


/*
 * Die Methode, welche nach jedem Schritt aufgerufen wird.
 *
 */
void model::perform_step()
{
    turn++;

//    std::cout << "-------------------------------" << std::endl;
//    std::cout << "#     Runde " << std::setw(3) << turn << "               #" << std::endl;
//    std::cout << "-------------------------------" << std::endl;
    int i = 0;
    for (auto iter = emu_flocks.begin(); iter != emu_flocks.end(); iter++, i++)
    {
        int x,y;
        iter->calcCenter(x,y);
        std::cout << "Herde " << i+1 << " hat " << iter->size() << " Emus, Zentrum ist : (" << x << "," << y << ")" << std::endl;

        if (turn % 3 == 0)
        {
            std::cout << "Herde " << i+1 << " stimmt ab" << std::endl;
            iter->vote();
        }
    }



    // Iterator für das Durchlaufen der Creature-Liste:
    std::list<std::shared_ptr<creature>>::iterator it;

    // Update der Map mit den Geruchsinformationen
    map_smell.update();

    // Neue Gerüche hinzufügen
    for(it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        if (prototype.sustentation() == creature_prototype::herbivore && prototype.habitat() == creature_prototype::habitat_land)
        {
            map_smell.addSmell(creaturePointer->x(),creaturePointer->y());
        }
    }
//      Testausgabe
//    map_smell.print();

    // Queue für die Kreaturen, die entfernt werden müssen (löschen beim Iterieren der Liste endet sonst böse):
    std::queue<std::shared_ptr<creature>> creaturesToRemove;


    // Alle Kreaturen durchlaufen:
    for(it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        /*
         * Zustandsautomat:
         */
        makeAction(sharedPointer, creaturePointer->state);


        // In jeder Runde erhöht sich das Alter der Kreatur
        creaturePointer->lifetime-= 1;

        //
//        creaturePointer->lifepoints-= 1;

    }

    // Schleife zum Entfernen der Kreaturen
    for(it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        // Position der Kreatur:
        int x = creaturePointer->x();
        int y = creaturePointer->y();

        // Feld und Feldtyp:
        world_tile& tile = map_.at(x,y);
        world_tile::climate_type climate = tile.climate();

        // Lebensraum der Kreatur:
        creature_prototype::habitat_type habitat = prototype.habitat();

        // Kreatur bereits tot?
        if(creaturePointer->dead == true)
        {
            int temp = creaturePointer->numOfDeadRounds;
            temp++;
            creaturePointer->numOfDeadRounds = temp;

            // Nach 3 Runden tote Kreatur speichern, um sie anschließend zu löschen...
            if(creaturePointer->numOfDeadRounds == 3)
            {
                creaturesToRemove.push(*sharedPointer);
            }
        }
        else   // Kreatur lebt noch
        {
            // Wenn die Kreatur normalerweise im Wasser lebt ...
            if (habitat == creature_prototype::habitat_water)
            {
                // ... dann prüfe, ob sie gerade NICHT auf einem Wasserfeld ist:
                if(!((climate == world_tile::deep_water) || (climate == world_tile::shallow_water)))
                {
                    // Lebenspunkte um 50 erniedrigen und zuweisen:
                    int life = creaturePointer->lifepoints;
                    life = life - 50;
                    creaturePointer->lifepoints = life;
                }
                else
                {
                    // die Kreatur ist auf einem Wasserfeld, alles in Ordnung
                }
            }
            else   // Landbewohner
            {
                // Wenn die Kreatur im Wasser ist ...
                if((climate == world_tile::deep_water) || (climate == world_tile::shallow_water))
                {
                    // Lebenspunkte um 50 erniedrigen und zuweisen:
                    int life = creaturePointer->lifepoints;
                    life = life - 50;
                    creaturePointer->lifepoints = life;
                }
                else
                {
                    // alles in Ordnung
                }
            }

            // Ist Kreatur jetzt tot?
            if(creaturePointer->lifepoints <= 0 || creaturePointer->lifetime <= 0)
            {
                creaturePointer->dead = true;

                // Pflanzen werden sofort entfernt
                if(prototype.sustentation() == creature_prototype::plant)
                {
                    creaturesToRemove.push(*sharedPointer);
                }
            }
        }
    }
    // Zum Schluss noch Kreaturen löschen, die seit 3 Runden tot sind:
    while (!creaturesToRemove.empty())
    {
        std::shared_ptr<creature> temp = creaturesToRemove.front();
        creaturesToRemove.pop();
        destroy_creature(temp);
    }

    // Leere Herden löschen
    for (auto iter = emu_flocks.begin(); iter != emu_flocks.end(); iter++)
    {
        if (iter->size() == 0)
        {
            iter = emu_flocks.erase(iter);
        }
    }

    /**
        Statistiken ausgeben
        */

    int kuehe = 0, pferde = 0, schafe = 0, emus = 0;
    for(it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        if (prototype.name() == "Kuh")
        {
            kuehe++;
        }
        else  if (prototype.name() == "Pferd")
        {
            pferde++;
        }
        else  if (prototype.name() == "Schaf")
        {
            schafe++;
        }
        else  if (prototype.name() == "Emu")
        {
            emus++;
        }

    }

//    std::cout << "\r";
//    std::cout << " Runde " << std::setw(5) << ++turn << " | ";
//    std::cout << " Kuehe: " << std::setw(3) << kuehe << " | ";
//    std::cout << " Pferde: " << std::setw(3) << pferde << " | ";
//    std::cout << " Schafe: " << std::setw(3) << schafe << " | ";
//    std::cout << " Emus: " << std::setw(3) << emus << " | ";
//    std::cout.flush();
}

/*
 * Übung 2 Aufgabe 1
 * Methode, welche eine Aktion mit Hilfe des Zustandes einer Kreatur berechnet. Die Kreatur macht dabei eine Aktion.
 *
 */
void model::makeAction(std::shared_ptr<creature>* c, int currentState)
{
    // Tote Kreaturen können keine Aktionen machen
    if (c->get()->dead == true)
        return;

    // Pflanzen betrachten
    if (c->get()->prototype.sustentation() == creature_prototype::plant)
    {
        (*c)->state = makeActionPlant(c);
    }
    // Pflanzenfresser betrachten
    else if(c->get()->prototype.sustentation() == creature_prototype::herbivore)
    {
        (*c)->state = makeActionHerbivore(c);
    }
    // Fleischfresser betrachten
    else if (c->get()->prototype.sustentation() == creature_prototype::carnivore)
    {
        (*c)->state = makeActionCarnivore(c);
    }

}

int model::makeActionPlant(std::shared_ptr<creature>* c)
{
    int x = c->get()->x();
    int y = c->get()->y();

    int currentState = (*c)->state;

    // Alter bestimmen (= Differenz aus aktueller und maximaler Lebensdauer)
    int age = c->get()->prototype.lifetime() - c->get()->lifetime;

    // Frequenz mit der sich die Pflanze vermehrt (neue Spalte in der CreatureTable.txt)
    int repFreq = c->get()->prototype.repFreq();

    if( (age >= repFreq) && age%repFreq == 0)  // Nur Fortpflanzen, wenn mind. so alt wie die Frequenz und dann nur alle reqFreq Runden
    {

        // Finde benachbarte Kreaturen der selben Gattung
        int same_species = 0;

        std::list<std::shared_ptr<creature>> nearby_creatures = locator(c,1);

        for (auto iter = nearby_creatures.begin(); iter != nearby_creatures.end(); iter++)
        {
            if ((*iter)->prototype.name() == c->get()->prototype.name() && !((*iter)->dead))
            {
                same_species++;
            }
        }

        // Falls mind. 2 gleiche Pflanzen in angrenzenden Feldern sind
        if (same_species >= 2)
        {
            // Finde passendes Feld, das auch noch leer sein muss
            if (findValidNeighbor(c,x,y) && isEmpty(x,y))
            {
                // Neue Pflanze auf dem Feld erstellen
                create_creature(c->get()->prototype,x, y);
            }
        }
    }

    return currentState;
}

int model::makeActionHerbivore(std::shared_ptr<creature>* c)
{
//    std::cout << "makeActionHerbivore: Lifepoints: " << c->get()->lifepoints << std::endl;

    int x = c->get()->x();
    int y = c->get()->y();

    int currentState = (*c)->state;

    // Ein Pflanzenfresser gilt als satt, wenn der Sättigung >= 80
    if (c->get()->hunger >= 90)
    {
        // Dann Counter erhöhen, der angibt seit wie vielen Runden der Pflanzenfresser satt ist
        c->get()->full_count++;
    }
    else
    {
        // Sonst Counter zurücksetzen
        c->get()->full_count = 0;
    }

    // Falls die Kreatur zu hungrig ist verliert sie Lebenspunkte
//    if (c->get()->hunger < 10)
//    {
//        c->get()->lifepoints -= 1;
//    }

    // Falls die Kreatur mind. so oft kontinuierlich satt war, wie die Frequenz angibt, gehe direkt in den REPRODUCE-Zustand
    if (c->get()->isFull())
    {
        currentState = creature::REPRODUCE;
    }

    switch(currentState)
    {
    case creature::INITIAL_STATE:
        // Im Initial State erst einmal Umgebung erkunden:
        currentState = creature::DISCOVER;

        break;

    case creature::EAT:

        if (enemyNearby(c))
        {
            currentState = creature::RUN;
            break;
        }

        // Schaue, ob noch Futter da ist
        if (!foodAvailable(c))
        {
            // Wenn nicht, gehe in Discover
            currentState = creature::DISCOVER;
        }
        else
        {
            // Sonst essen
            // Dadurch erhöht sich die Sättigkeit um 5
            c->get()->hunger += 5;

            // Maximale Sättigkeit ist 100
            if (c->get()->hunger > 100)
            {
                c->get()->hunger = 100;
            }

            // Reduziere Lebenspunkte aller Pflanzen in der Zelle der Kreatur
            reducePlantHP(c);

            // Die Kreatur bleibt nach dem Essen im aktuellen Feld stehen
            c->get()->move_queue.clear();
            c->get()->moveNot();
        }
        break;

    case creature::DISCOVER:

        // Schaue ob Feinde in der Nähe sind
        if (enemyNearby(c))
        {
            // Wenn ja, wechsle in Run-Zustand
            currentState = creature::RUN;
        }
        // Schaue, ob Futter da ist
        else if (foodAvailable(c))
        {
            // Wenn ja, gehe in Eat-Zustand
            currentState = creature::EAT;

            // Dann soll sich die Kreatur nicht weiter bewegen
            c->get()->move_queue.clear();
            c->get()->moveNot();
        }
        else
        {
            // Die Kreatur läuft in die Richtung, die von der Gruppe bestimmt wurde
        }

        break;

    case creature::RUN:

        // Schaue ob noch Feinde da sind
        if (!enemyNearby(c))
        {
            // Falls kein Feind mehr in der Nähe -> Gehe wieder in Initialzustand
            currentState = creature::INITIAL_STATE;

            c->get()->move_queue.clear();
        }
        else
        {
            // Die Kreatur wählt zufällige Richtung
            c->get()->moveRandom();
        }

        break;

    case creature::REPRODUCE:
    {

        // Neue Kreatur auf eigenem Feld platzieren
        auto child = create_creature(c->get()->prototype,x, y);

        // Neue Kreatur einer Herde zuweisen (der Herde, deren Mittelpunkt am nächsten liegt)
        addToFlock(child.lock());

        // Vermehren macht hungrig -> Hunger zurücksetzen
        c->get()->hunger = 25;

        // Neuer Zustand nach Reproduce
        currentState = creature::INITIAL_STATE;
        }
        break;

    case creature::VOTED:

        std::cout << "in VOTED" << std::endl;
        std::cout << "move_queue.size(): " << c->get()->move_queue.size() << std::endl;
        if (c->get()->move_queue.size() == 0)
            currentState = creature::INITIAL_STATE;
        break;


    case creature::DO_NOTHING:
        // Wird im Moment nie erreicht
        /* Hier sollte man auch prüfen, ob Feinde in der Nähe sind bzw. Nahrung. */
        // nicht tun
        break;
    }

    // Wenn die Kreatur gerade nicht isst -> Sättigkeit reduzieren
    if (currentState != creature::EAT)
        c->get()->hunger -= 5;

    // Nicht unter 0
    if (c->get()->hunger < 0)
        c->get()->hunger = 0;

    // Am Ende die Bewegung durchführen
    // Neue Bewegung in Schlange aufnehmen, entsprechend der bevorzugten Richtung der Kreatur
    c->get()->addMove();

    int new_x, new_y;
    // Die Kreatur wird "gefragt" wohin sie will
    c->get()->getMove(new_x, new_y);
    // Falls das ein gültiges Feld ist, wird die Bewegung ausgeführt
    if (c->get()->prototype.habitat() == creature_prototype::habitat_land)
    {
        if (isPossibleLandType(new_x,new_y))
        {
            move_creature(*c,new_x, new_y);
        }
    }
    else
    {
        if (isPossibleWaterType(new_x,new_y))
        {
            move_creature(*c,new_x, new_y);
        }
    }



    return currentState;
}

int model::makeActionCarnivore(std::shared_ptr<creature>* c)
{
//    std::cout << "makeActionCarnivore: Lifepoints: " << c->get()->lifepoints << std::endl;
    int x = c->get()->x();
    int y = c->get()->y();

    int currentState = (*c)->state;

    // Falls die Kreatur in 10 Runden niemals satt war werden die Lebenspunkte reduziert
//    if (c->get()->hunger_memory.size() == 10 && c->get()->getFullRounds() == 0)
//    {
//        c->get()->lifepoints -= 1;
//    }


    switch(currentState)
    {
    case creature::INITIAL_STATE:

        // Fleischfresser geht direkt auf die Jagd
        currentState = creature::HUNT;
        break;

    case creature::REPRODUCE:

        // Neue Kreatur erstellen auf eigenem Feld erstellen, Geruchsschwelle wird übernommen
        create_creature(c->get()->prototype,x,y,c->get()->smell_threshold);

        // Hunger-Memory löschen (damit nicht gleich noch mehr Kreaturen entstehen)
        c->get()->hunger_memory.clear();

        // Neuer Zustand nach Fortpflanzung
        currentState = creature::INITIAL_STATE;
        break;

    case creature::HUNT:

    {
        // Wenn die Kreatur schon satt ist, gehe in Reproduce
        if (c->get()->isFull())
        {
            currentState = creature::REPRODUCE;
        }
        // Sonst gehe auf die Jagd
        else
        {
            bool hunt_success = false;

            // Schaue ob Beute auf dem Feld ist
            if (foodAvailable(c))
            {
                // Zufallszahl bestimmen
                int rnd = randomNumberMinMax(1,20);

                // Falls != 1 ist die Jagd erfolgreich
                if (rnd != 1)
                {
                    hunt_success = true;

                    // Töte Pflanzenfresser auf eigenem Feld
                    killPrey(c);
                }
                // Sonst ist die Jagd fehlgeschlagen
                else
                {
                    hunt_success = false;
                }
            }
            // Falls auf dem eigenen Feld keine Beute ist, ins Nachbarfeld bewegen
            else
            {

                int x_old = x, y_old = y;

                // Die Kreatur bewegt sich in das angrenzende Feld, in dem es am stärksten nach Beute riecht
                if (map_smell.strongestSmell(x,y,c->get()->smell_threshold) && isPossibleLandType(x,y))
                {
                    move_creature(*c,x,y);
                }
                else
                {
                    x = x_old;
                    y = y_old;

                    if (findValidNeighbor(c,x,y))  // Wenn es nirgends riecht, oder überall gleich, dann zufällig bewegen
                    {
                        move_creature(*c,x,y);
                    }
                }

                // Dort nochmal jagen
                if (foodAvailable(c))
                {

                    // Zufallszahl bestimmen
                    int rnd = randomNumberMinMax(1,20);

                    // Falls != 1 ist die Jagd erfolgreich
                    if (rnd != 1)
                    {
                        hunt_success = true;

                        killPrey(c);
                    }
                    // Sonst ist die Jagd fehlgeschlagen
                    else
                    {
                        hunt_success = false;
                    }
                }
            }

            // Ergebnis der Jagd speichern
            c->get()->hunger_memory.push_back(hunt_success);
            // Nur die letzten 10 Runden merken
            if (c->get()->hunger_memory.size() > 10)
            {
                c->get()->hunger_memory.pop_front();
            }
        }

        break;
    }

    }

    return currentState;
}

void model::addToFlock(std::shared_ptr<creature>c)
{
    int min_distance = default_world_size_x_ + default_world_size_y_;

    int flock_x, flock_y, creature_x, creature_y;
    creature_x = c->x();
    creature_y = c->y();

    auto min_iter = emu_flocks.end();

    for (auto iter = emu_flocks.begin(); iter != emu_flocks.end(); iter++)
    {
        iter->calcCenter(flock_x, flock_y);

        if (abs(flock_x - creature_x) + abs(flock_y - creature_y) < min_distance)
        {
            min_distance = abs(flock_x - creature_x) + abs(flock_y - creature_y);
            min_iter = iter;
        }
    }

    if (min_iter != emu_flocks.end())
        min_iter->addCreature(c);
}

/*
    Methode, die überprüft, ob ein Feind in der Nähe ist
    */
bool model::enemyNearby(std::shared_ptr<creature>*c)
{
    // Betrachte Umgebung von 2 Feldern
    std::list<std::shared_ptr<creature>> env = locator(c, 2);
    std::list<std::shared_ptr<creature>>::iterator iter;

    // Schauen, ob Feind noch in der Nähe ist
    for (iter = env.begin(); iter != env.end(); iter++)
    {
        const creature_prototype& prototype = (*iter)->prototype;

        // Man muss sich nur Sorgen machen um Feinde, die den gleichen Lebensraum haben (Haie fressen keine Kühe)
        if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::carnivore)
        {
            break;
        }
    }

    return (iter != env.end());
}

/*
    Methode, die überprüft, ob Futter auf dem eigenen Feld ist
    */
bool model::foodAvailable(std::shared_ptr<creature>*c)
{
    // Nur eigenes Feld betrachten
    std::list<std::shared_ptr<creature>> env = locator(c, 0);
    std::list<std::shared_ptr<creature>>::iterator iter;

    // Ist Futter da?

    // Pflanzenfresser
    if (c->get()->prototype.sustentation() == creature_prototype::herbivore)
    {
        for (iter = env.begin(); iter != env.end(); iter++)
        {
            const creature_prototype& prototype = (*iter)->prototype;

            if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::plant && !(*iter)->dead)
            {
                break;
            }
        }
    }
    // Fleischfresser
    else if (c->get()->prototype.sustentation() == creature_prototype::carnivore)
    {
        for (iter = env.begin(); iter != env.end(); iter++)
        {
            const creature_prototype& prototype = (*iter)->prototype;

            if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::herbivore && !(*iter)->dead)
            {
                break;
            }
        }
    }

    // Falls man Futter gefunden hat -> Ändere den Zustand
    return (iter != env.end());
}

/*
    Methode, die die Lebenspunkte aller Pflanzen im Feld der übergebenen Kreatur reduziert
    */
void model::reducePlantHP(std::shared_ptr<creature>*c)
{
    std::list<std::shared_ptr<creature>> env = locator(c, 0);
    std::list<std::shared_ptr<creature>>::iterator iter;

    // Alle Pflanzen in der Zelle verlieren 5 Lebenspunkte
    for (iter = env.begin(); iter != env.end(); iter++)
    {
        const creature_prototype& prototype = (*iter)->prototype;

        if (prototype.sustentation() == creature_prototype::plant)
        {
            (*iter)->lifepoints -= 5;

            // Dadurch stirbt die Pflanze eventuell
            if((*iter)->lifepoints <= 0)
            {
                (*iter)->dead = true;
            }
        }
    }
}

/*
    Tötet einen Pflanzenfresser auf dem Feld der übergebenen Kreatur
    */
void model::killPrey(std::shared_ptr<creature>*c)
{
    std::list<std::shared_ptr<creature>> env = locator(c, 0);
    std::list<std::shared_ptr<creature>>::iterator iter;

    for (iter = env.begin(); iter != env.end(); iter++)
    {
        const creature_prototype& prototype = (*iter)->prototype;

        if (prototype.sustentation() == creature_prototype::herbivore && !(*iter)->dead)
        {
            (*iter)->lifepoints = 0;
            (*iter)->dead = true;

            // Nur einen Pflanzenfresser töten
            break;
        }
    }
}

/*
 * Übung 2 Aufgabe 2
 * Methode, welche die Kreaturen im Umkreis der übergebenen Kreatur zurückgibt.
 *
 * (c) Simon Pirkelmann, with minor changes
 */

std::list<std::shared_ptr<creature>> model::locator(std::shared_ptr<creature>* c, int distance)
{
    std::list<std::shared_ptr<creature>> nearby_creatures;
    int mypos_x = c->get()->x();
    int mypos_y = c->get()->y();

    for (int i = (std::max)(mypos_x - distance, 0);
            i <= (std::min)(map_.size_x()-1, mypos_x + distance);
            i++)
    {
        for (int j = (std::max)(mypos_y - distance, 0);
                j <= (std::min)(map_.size_y()-1, mypos_y + distance);
                j++)
        {
            if (abs(mypos_x - i) + abs(mypos_y - j) <= distance)
            {
                world_tile currenttile = map_.at(i,j);
                world_tile::creature_iterator ci = currenttile.begin();
                while (ci != currenttile.end())
                {
                    // don't include myself
                    if(ci->get() != c->get())
                        nearby_creatures.push_back(*ci);
                    ci++;
                }
            }
        }
    }

    return nearby_creatures;

}

bool model::isPossible(int x, int y)
{
    // Ränder prüfen:
    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        return false;
    }

    return true;
}


/*
 * Gibt zurück, ob Landlebewesen an diese Stelle gehen kann (z.B. Wasser usw.).
 */
bool model::isPossibleLandType(int x, int y)
{
    // Ränder prüfen:
    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        return false;
    }
    world_tile& tile = map_.at(x,y);
    world_tile::climate_type climate = tile.climate();

    // Kachel darf kein Wasser sein:
    if((climate == world_tile::deep_water) || (climate == world_tile::shallow_water))
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*
 * Gibt zurück, ob Wasserlebewesen an diese Stelle gehen kann (z.B. Land usw.).
 */
bool model::isPossibleWaterType(int x, int y)
{
    // Ränder prüfen:
    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        return false;
    }
    world_tile& tile = map_.at(x,y);
    world_tile::climate_type climate = tile.climate();

    // Kachel darf kein Wasser sein:
    if((climate == world_tile::deep_water) || (climate == world_tile::shallow_water))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
    Gibt zurück, ob das Feld (x,y) leer ist
    */
bool model::isEmpty(int x, int y)
{
    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        return false;
    }

    std::list<std::shared_ptr<creature>> local_creatures;

    world_tile currenttile = map_.at(x,y);
    world_tile::creature_iterator ci = currenttile.begin();

    while (ci != currenttile.end())
    {
        local_creatures.push_back(*ci);
        ci++;
    }

    return (local_creatures.size() == 0);
}

/*
 *  Findet ein zufälliges passendes Nachbarfeld, für die Kreatur
 *  Die Übergebenen Variablen x, y enthalten danach die Koordinaten eines passenden Felds
 *  Wenn es keins gibt, wird das Feld der Kreatur zurückgegeben und false
 */
bool model::findValidNeighbor(std::shared_ptr<creature>* c, int & x, int & y)
{
    int random = randomNumberMinMax(0,3);

    if (c->get()->prototype.habitat() == creature_prototype::habitat_land)
    {
        for (int i = 0; i < 4; i++)
        {
            switch((random+i)%4)
            {
            case 0:
                // nach oben?
                if(isPossibleLandType(x,y-1))
                {
                    y = y-1;
                    return true;
                }
                break;
            case 1:
                // nach rechts?
                if(isPossibleLandType(x+1,y))
                {
                    x = x+1;
                    return true;
                }
                break;
            case 2:
                // nach unten?
                if(isPossibleLandType(x,y+1))
                {
                    y = y+1;
                    return true;
                }
                break;
            case 3: // nach links?
                if(isPossibleLandType(x-1,y))
                {
                    x = x-1;
                    return true;
                }
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            switch((random+i)%4)
            {
            case 0:
                // nach oben?
                if(isPossibleWaterType(x,y-1))
                {
                    y = y-1;
                    return true;
                }
                break;
            case 1:
                // nach rechts?
                if(isPossibleWaterType(x+1,y))
                {
                    x = x+1;
                    return true;
                }
                break;
            case 2:
                // nach unten?
                if(isPossibleWaterType(x,y+1))
                {
                    y = y+1;
                    return true;
                }
                break;
            case 3: // nach links?
                if(isPossibleWaterType(x-1,y))
                {
                    x = x-1;
                    return true;
                }
                break;
            }
        }
    }

    // Wenn kein passendes Feld gefunden wurde
    return false;
}

/*
 * Gibt eine zufällige Zahl zwischen 0 und 1 zurück.
 */
int model::randomNumber()
{
    int randNum = rand() % 2;

    return randNum;
}

/*
 * Gibt eine zufällige Zahl zwischen min und max zurück.
 */
int model::randomNumberMinMax(int min, int max)
{

    int randNum = min + rand() % (max - min + 1);

    return randNum;
}


std::weak_ptr<creature> model::create_creature
(const creature_prototype& prototype, int x, int y)
{
    std::shared_ptr<creature> c(new creature(prototype, x, y));

    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        std::cerr << "Invalid creature position." << std::endl;
        throw invalid_parameter();
    }

    creatures_.push_back(c);

    try
    {
        map_.add_creature_to_tile(c);
    }
    catch (...)
    {
        creatures_.pop_back();
        throw;
    }

    return c;
}

std::weak_ptr<creature> model::create_creature
(const creature_prototype& prototype, int x, int y, double threshold)
{
    std::shared_ptr<creature> c(new creature(prototype, x, y, threshold));

    if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y())
    {
        std::cerr << "Invalid creature position." << std::endl;
        throw invalid_parameter();
    }

    creatures_.push_back(c);

    try
    {
        map_.add_creature_to_tile(c);
    }
    catch (...)
    {
        creatures_.pop_back();
        throw;
    }

    return c;
}


void model::destroy_creature(const std::weak_ptr<creature>& c) NOTHROW
{
    std::shared_ptr<creature> csp(c.lock());

    if (!csp)
    {
        std::cerr << "Invalid creature for destruction." << std::endl;
        throw invalid_parameter();
    }

    std::list<std::shared_ptr<creature>>::iterator removeit
    (std::find(creatures_.begin(), creatures_.end(), csp));

    if (removeit != creatures_.end())
        creatures_.erase(removeit);
    else
        std::cerr << "Creature not found in global creature list." << std::endl;

    // Kreatur aus Herde entfernen
    for (auto iter = emu_flocks.begin(); iter != emu_flocks.end(); iter++)
    {
        (*iter).removeCreature(csp);
    }
//        std::list<std::shared_ptr<creature>>::iterator removeit(std::find(emuflock.begin(), creatures_.end(), csp));
//
//    if (removeit != creatures_.end())
//        creatures_.erase(removeit);
//    else
//        std::cerr << "Creature not found in global creature list." << std::endl;
//    }


    map_.remove_creature_from_tile(csp);
}


void model::move_creature
(const std::weak_ptr<creature>& c, int x, int y)
{
    std::shared_ptr<creature> csp(c.lock());

    if (!csp)
    {
        std::cerr << "Invalid creature for movement." << std::endl;
        throw invalid_parameter();
    }

    // Nur bewegen, wenn die Kreatur noch lebt
    if (csp->dead == false)
        map_.move_creature(csp, x, y);
}


const char *model::default_prototype_list_ = "CreatureTable.txt";

const int model::default_world_size_x_ = 50;
const int model::default_world_size_y_ = 50;




} /* namespace biosim */
