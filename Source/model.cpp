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
	// Queue für die Kreaturen, die entfernt werden müssen (löschen beim Iterieren der Liste endet sonst böse):
	std::queue<std::shared_ptr<creature>> creaturesToRemove;

	// Iterator für das Durchlaufen der Creature-Liste:
	std::list<std::shared_ptr<creature>>::iterator it;

	// Alle Kreaturen durchlaufen:
	for(it = creatures_.begin(); it != creatures_.end();++it) {
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

		// Kreatur bereits tot?
		if(creaturePointer->dead == true) {
			int temp = creaturePointer->numOfDeadRounds;
			temp++;
			creaturePointer->numOfDeadRounds = temp;

			// Nach 3 Runden tote Kreatur speichern, um sie anschließend zu löschen:
			if(creaturePointer->numOfDeadRounds == 3) {
				creaturesToRemove.push(*sharedPointer);
			}
		}
		else { // Kreatur lebt noch
			// Wenn die Kreatur normalerweise im Wasser lebt ...
			if (habitat == creature_prototype::habitat_water) {
				// ... dann prüfe, ob sie gerade NICHT auf einem Wasserfeld ist:
			        if(!((climate == world_tile::deep_water) || (climate == world_tile::shallow_water))) {
					// Lebenspunkte um 50 erniedrigen und zuweisen:
					int life = creaturePointer->lifepoints;
					life = life - 50;
					creaturePointer->lifepoints = life;
				}
				else {
					// die Kreatur ist auf einem Wasserfeld, alles in Ordnung
				}
			}
			else { // Landbewohner
				// Wenn die Kreatur im Wasser ist ...
				if((climate == world_tile::deep_water) || (climate == world_tile::shallow_water)) {
					// Lebenspunkte um 50 erniedrigen und zuweisen:
					int life = creaturePointer->lifepoints;
					life = life - 50;
					creaturePointer->lifepoints = life;
				}
				else {
					// alles in Ordnung
				}
			}

			// Ist Kreatur jetzt tot?
			if(creaturePointer->lifepoints <= 0) {
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
}

/*
 * Übung 2 Aufgabe 1
 * Methode, welche eine Aktion mit Hilfe des Zustandes einer Kreatur berechnet. Die Kreatur macht dabei eine Aktion.
 * 
 */
void model::makeAction(std::shared_ptr<creature>* c, int currentState) {
	// Erst einmal nur Pflanzenfresser betrachten:
	if(c->get()->prototype.sustentation() == creature_prototype::herbivore) {
		currentState = creature::DISCOVER;
		int x;
		int y;
		bool found = false;
		std::list<std::shared_ptr<creature>> env;

		switch(currentState) {
		case creature::INITIAL_STATE:
			// Zu Beginn erst einmal Umgebung erkunden:
			currentState = creature::DISCOVER;
			break;
		case creature::EAT:
			/* Hier sollte man essen bzw. wenn das Essen verbraucht ist, nach neuem suchen bzw. Feinden ausweichen. */
			break;
		case creature::DISCOVER:
			/* Hier sollte man prüfen, ob Feinde in der Nähe sind oder ob es etwas zu essen gibt. Je nachdem wird dann der Zustand gesetzt. */
			env = locator(c, 5);

			// Position der Kreatur:
			x = c->get()->x();
			y = c->get()->y();
			x++;
			y++;

			move_creature(*c,x,y);

			break;
		case creature::RUN:
			// Zufällige Richtung wählen:
			x = c->get()->x();
			y = c->get()->y();

			while(found == false) {
				int random = randomNumberMinMax(1,4);

				switch(random) {
				case 1: 
					// nach oben?
					if(isPossible(x,y-1)) {
						found = true;
						move_creature(*c,x,y-1);
					}
					break;
				case 2:
					// nach rechts?
					if(isPossible(x+1,y)) {
						found = true;
						move_creature(*c,x+1,y);
					}
					break;
				case 3:
					// nach unten?
					if(isPossible(x,y+1)) {
						found = true;
						move_creature(*c,x,y+1);
					}
					break;
				case 4: // nach links?
					if(isPossible(x-1,y)) {
						found = true;
						move_creature(*c,x-1,y);
					}
					break;
				}
			}
			break;
		case creature::DO_NOTHING:
			/* Hier sollte man auch prüfen, ob Feinde in der Nähe sind bzw. Nahrung. */
			// nicht tun
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
		i <= (std::min)(map_.size_x(), mypos_x + distance);
		i++)
	{
		for (int j = (std::max)(mypos_y - distance, 0); 
			j <= (std::min)(map_.size_y(), mypos_y + distance); 
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
 * Gibt zurück, ob Pflanzenfresser an diese Stelle gehen kann (z.B. Wasser usw.).
 */
bool model::isPossible(int x, int y) {
	// Ränder prüfen:
	if (x < 0 || y < 0 || x >= map_.size_x() || y >= map_.size_y()) {
		return false;
	}
	world_tile& tile = map_.at(x,y);
	world_tile::climate_type climate = tile.climate();

	// Kachel darf kein Wasser sein:
	if((climate == world_tile::deep_water) || (climate == world_tile::shallow_water)) {
		return false;
	}
	else {
		return true;
	}
}

/*
 * Gibt eine zufällige Zahl zwischen 0 und 1 zurück.
 */
int model::randomNumber() {
	int randNum = rand() % 2;

	return randNum;
}

/*
 * Gibt eine zufällige Zahl zwischen min und max zurück.
 */
int model::randomNumberMinMax(int min, int max) {
	srand(static_cast<unsigned int>(time(NULL)));
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
		{ map_.add_creature_to_tile(c); }
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

	map_.move_creature(csp, x, y);
}


const char *model::default_prototype_list_ = "CreatureTable.txt";

const int model::default_world_size_x_ = 100;
const int model::default_world_size_y_ = 100;




} /* namespace biosim */
