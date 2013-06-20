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
    cursor_x_(0),
    cursor_y_(0)
{
    srand( static_cast<unsigned int>(time(NULL) ));


    for (auto iter = prototypes_.begin(); iter != prototypes_.end(); iter++)
    {
        if ((*iter).name() == "Kaktus")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Sonnenblume")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Eiche")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Obstbaum")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Tannenbaum")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Gebüsch")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Gras")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Schaf")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }


        if ((*iter).name() == "Kuh")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Pferd")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gras zufällig platzieren
                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
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
                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }
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

//    std::cout << "-------------------------------" << std::endl;
//    std::cout << "#     Runde " << std::setw(3) << ++turn << "               #" << std::endl;
//    std::cout << "-------------------------------" << std::endl;

    // Queue für die Kreaturen, die entfernt werden müssen (löschen beim Iterieren der Liste endet sonst böse):
    std::queue<std::shared_ptr<creature>> creaturesToRemove;

    // Iterator für das Durchlaufen der Creature-Liste:
    std::list<std::shared_ptr<creature>>::iterator it;

    int i = 0;
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

        // Position der Kreatur:
        int x = creaturePointer->x();
        int y = creaturePointer->y();

        // Feld und Feldtyp:
        world_tile& tile = map_.at(x,y);
        world_tile::climate_type climate = tile.climate();

        // Lebensraum der Kreatur:
        creature_prototype::habitat_type habitat = prototype.habitat();


        // In jeder Runde erhöht sich das Alter der Kreatur
        creaturePointer->lifetime-= 1;

        // In jeder Runde reduzieren sich die Lebenspunkte jeder Kreatur um 1
        creaturePointer->lifepoints--;

        // Kreatur bereits tot?
        if(creaturePointer->dead == true)
        {
//            std::cout << "dead" << std::endl;
            int temp = creaturePointer->numOfDeadRounds;
            temp++;
            creaturePointer->numOfDeadRounds = temp;

            // Nach 3 Runden tote Kreatur speichern, um sie anschließend zu löschen:
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

    std::cout << "\r";
    std::cout << " Runde " << std::setw(5) << ++turn << " | ";
    std::cout << " Kuehe: " << std::setw(3) << kuehe << " | ";
    std::cout << " Pferde: " << std::setw(3) << pferde << " | ";
    std::cout << " Schafe: " << std::setw(3) << schafe << " | ";
    std::cout << " Emus: " << std::setw(3) << emus << " | ";
    std::cout.flush();
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

    int x = c->get()->x();
    int y = c->get()->y();

    // Zunächst Pflanzen betrachten
    if (c->get()->prototype.sustentation() == creature_prototype::plant)
    {
        // Alter bestimmen (= Differenz aus aktueller und maximaler Lebensdauer
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
    }
    // Pflanzenfresser betrachten
    else if(c->get()->prototype.sustentation() == creature_prototype::herbivore)
    {

        // Ein Pflanzenfresser gilt als satt, wenn der Sättigung >= 80
        if (c->get()->hunger >= 80)
        {
            // Dann Counter erhöhen, der angibt seit wie vielen Runden der Pflanzenfresser satt ist
            c->get()->full_count++;
        }
        else
        {
            // Sonst Counter zurücksetzen
            c->get()->full_count = 0;
        }

        // Falls die Kreatur mind. so oft kontinuierlich satt war, wie die Frequenz angibt, gehe direkt in den REPRODUCE-Zustand
        if (c->get()->full_count >= c->get()->prototype.repFreq())
        {
            currentState = creature::REPRODUCE;
        }

        std::list<std::shared_ptr<creature>> env;
        std::list<std::shared_ptr<creature>>::iterator iter;

        switch(currentState)
        {
        case creature::INITIAL_STATE:
            // Im Initial State erst einmal Umgebung erkunden:
            currentState = creature::DISCOVER;
            break;

        case creature::EAT:
            /* Hier sollte man essen bzw. wenn das Essen verbraucht ist, nach neuem suchen bzw. Feinden ausweichen. */

            env = locator(c,0);

            // Schauen ob noch essen da ist
            for (iter = env.begin(); iter != env.end(); iter++)
            {
                const creature_prototype& prototype = (*iter)->prototype;

                // Essen gibt es noch, falls noch eine Pflanze da ist, die auch noch lebt
                if (prototype.sustentation() == creature_prototype::plant && !(*iter)->dead)
                {
                    break;
                }
            }

            // Falls kein Futter mehr da ist -> Erkunde die Umgebung
            if (iter == env.end())
            {
                currentState = creature::DISCOVER;
            }

            // Sonst essen
            // Dadurch erhöht sich die Sättigkeit um 5
            c->get()->hunger += 5;

            // Maximale Sättigkeit ist 100
            if (c->get()->hunger > 100)
            {
                c->get()->hunger = 100;
            }

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
            break;

        case creature::DISCOVER:
            /* Hier sollte man prüfen, ob Feinde in der Nähe sind oder ob es etwas zu essen gibt. Je nachdem wird dann der Zustand gesetzt. */

            // Betrachte Umgebung von 5 Feldern
            env = locator(c, 5);

            // Sind Feinde da?
            for (iter = env.begin(); iter != env.end(); iter++)
            {
                const creature_prototype& prototype = (*iter)->prototype;

                // Man muss sich nur Sorgen machen um Feinde, die den gleichen Lebensraum haben (Haie fressen keine Kühe)
                if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::carnivore)
                {
                    // Wenn Feinde da sind -> Wechsle in RUN-Zustand
                    currentState = creature::RUN;
                    break;
                }
            }

            // Falls man einen Feind gefunden hat -> Ändere den Zustand
            if (iter != env.end())
            {
                break;
            }


            // Nur eigenes Feld betrachten
            env = locator(c,0);

            // Ist Futter da?
            for (iter = env.begin(); iter != env.end(); iter++)
            {
                const creature_prototype& prototype = (*iter)->prototype;

                if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::plant && !(*iter)->dead)
                {
                    // Wenn Futter da ist -> Wechsel in EAT-Zustand
                    currentState = creature::EAT;
                    break;
                }
            }

            // Falls man Futter gefunden hat -> Ändere den Zustand
            if (iter != env.end())
            {
                break;
            }

            // Falls keine Feinde da sind und auch kein Futter -> Weiter Erkunden
            if (findValidNeighbor(c,x,y))
                move_creature(*c,x,y);

            break;

        case creature::RUN:

            env = locator(c, 5);

            // Schauen, ob Feind noch in der Nähe ist
            for (iter = env.begin(); iter != env.end(); iter++)
            {
                const creature_prototype& prototype = (*iter)->prototype;

                // Man muss sich nur Sorgen machen um Feinde, die den gleichen Lebensraum haben (Haie fressen keine Kühe)
                if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::carnivore)
                {
                    // Wenn Feind noch nah ist -> laufe weiterhin weg
                    break;
                }
            }


            // Falls kein Feind mehr in der Nähe -> Ändere den Zustand
            if (iter == env.end())
            {
                // Gehe wieder in Initialzustand
                currentState = creature::INITIAL_STATE;
                break;
            }

            // Falls der Feind noch da ist -> Laufe in zufällige Richtung
            if (findValidNeighbor(c,x,y))
                move_creature(*c,x,y);

            break;

        case creature::REPRODUCE:

            // Neue Kreatur auf eigenem Feld platzieren
            create_creature(c->get()->prototype,x, y);

            // Vermehren macht hungrig -> Hunger zurücksetzen
            c->get()->hunger = 0;

            // Neuer Zustand nach Reproduce
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

    }
    // Fleischfresser betrachten
    else if (c->get()->prototype.sustentation() == creature_prototype::carnivore)
    {

        switch(currentState)
        {
        case creature::REPRODUCE:
            // Neue Kreatur erstellen auf eigenem Feld erstellen
            create_creature(c->get()->prototype,x,y);

            // Hunger-Memory löschen (damit nicht gleich noch mehr Kreaturen entstehen)
            c->get()->hunger_memory.clear();

            // Neuer Zustand nach Fortpflanzung
            currentState = creature::INITIAL_STATE;
            break;

        default:

            // Die Jagd wird durch Würfelwurf simuliert
            int rnd = randomNumberMinMax(1,6);

            if (rnd == 6)
            {
                // Bei einer 6 ist die Kreatur in der aktuellen Runde satt
                c->get()->hunger_memory.push_back(true);
            }
            else
            {
                // Sonst ist sie hungrig
                c->get()->hunger_memory.push_back(false);
            }

            // Nur die letzten 10 Runden merken
            if (c->get()->hunger_memory.size() > 10)
            {
                c->get()->hunger_memory.pop_front();
            }

            // Betrachte die letzten 10 Runden
            if (c->get()->hunger_memory.size() == 10)
            {
                int counter = 0;
//                for (bool nothungry : c->get()->hunger_memory)
                for (auto iter = c->get()->hunger_memory.begin(); iter != c->get()->hunger_memory.end(); iter++)
                {
                    if (*iter)
                        counter++;
                }

                // Falls die Kreatur in den letzten 10 Runden mind. repFreq mal satt war
                if (counter >= c->get()->prototype.repFreq())
                {
                    // In Reproduce-Zustand wechseln
                    currentState = creature::REPRODUCE;
                }
            }

            // Die Kreatur bewegt sich in ein angrenzendes Feld (falls es eines gibt)
            if (findValidNeighbor(c,x,y))
                move_creature(*c,x,y);

            break;
        }

    }

    // Neuen Zustand übernehmen
    (*c)->state = currentState;

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

const int model::default_world_size_x_ = 100;
const int model::default_world_size_y_ = 100;




} /* namespace biosim */
