// partially (c) Daniel Kober
// partially (c) Simon Pirkelmann
// partially (c) Christian Wolf

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


    // initialize smell_map; same size as world map and no smell at the beginning
    for (int y=0; y<default_world_size_y_ ; y++){
    	smell_map.push_back(std::vector<double>());
    	for (int x=0; x<default_world_size_x_ ; x++){
    		smell_map.at(y).push_back(0);
    	}
    }


    for (auto iter = prototypes_.begin(); iter != prototypes_.end(); iter++)
    {
        if ((*iter).name() == "Kaktus")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Kakteen zuf�llig platzieren
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
                    // Sonnenblumen zuf�llig platzieren
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
                    // Eichen zuf�llig platzieren
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
                    // Obstbäume zuf�llig platzieren
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
                    // Tannenbäume zuf�llig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

        if ((*iter).name() == "Geb�sch")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Gebüsch zuf�llig platzieren
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
                    // Gras zuf�llig platzieren
                    if (randomNumberMinMax(1,6) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

//        if ((*iter).name() == "Schaf")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                    // Schaf zuf�llig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }


        if ((*iter).name() == "Kuh")
        {
            for (int i = 0; i < map_.size_x(); i++)
            {
                for (int j = 0; j < map_.size_y(); j++)
                {
                    // Kuh zuf�llig platzieren
                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
                        create_creature(*iter,i,j);
                }
            }
        }

//        if ((*iter).name() == "Pferd")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                    // Pferd zuf�llig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }

//        if ((*iter).name() == "Emu")
//        {
//            for (int i = 0; i < map_.size_x(); i++)
//            {
//                for (int j = 0; j < map_.size_y(); j++)
//                {
//                    // Emu zuf�llig platzieren
//                    if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
//                        create_creature(*iter,i,j);
//                }
//            }
//        }
        if ((*iter).name() == "Tiger")
            {
                for (int i = 0; i < map_.size_x(); i++)
                {
                    for (int j = 0; j < map_.size_y(); j++)
                    {
                        // Tiger zuf�llig platzieren
                        if (randomNumberMinMax(1,500) == 1 && isPossibleLandType(i,j))
                            create_creature(*iter,i,j,((double)randomNumberMinMax(1,50))/10);
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

//	std::cout<<std::endl;
//			for(int y=0; y<10; ++y) {
//				for(int x=0; x<10; ++x)
//					std::printf("%7.3f ", smell_map.at(y).at(x));
//				std::cout<<std::endl;
//			}

//    std::cout << "-------------------------------" << std::endl;
//    std::cout << "#     Runde " << std::setw(3) << ++turn << "               #" << std::endl;
//    std::cout << "-------------------------------" << std::endl;

    // Queue f�r die Kreaturen, die entfernt werden m�ssen (l�schen beim Iterieren der Liste endet sonst b�se):
    std::queue<std::shared_ptr<creature>> creaturesToRemove;

    // Iterator f�r das Durchlaufen der Creature-Liste:
    std::list<std::shared_ptr<creature>>::iterator it;


    //create new smell map to update smell

    std::vector<std::vector< double> > new_smell_map;

    for (int y=0; y<default_world_size_y_ ; y++){
    	for (int x=0; x<default_world_size_x_ ; x++){
    		smell_map.at(y).at(x) *= 0.5;
    	}
    }

    new_smell_map = smell_map;


    for (int y=0; y<default_world_size_y_ ; y++){
    	for (int x=0; x<default_world_size_x_ ; x++){

    		// expand smell
    		for (int d_y=-1; d_y<=1; d_y++){
    			for (int d_x=-1; d_x<=1; d_x++){
    				if (y+d_y>=0 && y+d_y < default_world_size_y_){
    					if (x+d_x>=0 && x+d_x < default_world_size_x_){
    						if (smell_map.at(y+d_y).at(x+d_x) > 0.01 && smell_map.at(y+d_y).at(x+d_x)*0.2 > smell_map.at(y).at(x))
    							new_smell_map.at(y).at(x) = smell_map.at(y+d_y).at(x+d_x)*0.2;
    					}
    				}
    			}
    		}
    	}
    }

    smell_map = new_smell_map;


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


        // In jeder Runde erh�ht sich das Alter der Kreatur
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

            // Nach 3 Runden tote Kreatur speichern, um sie anschlie�end zu l�schen:
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
                // ... dann pr�fe, ob sie gerade NICHT auf einem Wasserfeld ist:
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

                	// ist die Kreatur eine Kuh, stinkt sie
                	if (creaturePointer->prototype.name() == "Kuh"){
                		if (smell_map.at(y).at(x) +100 > 500)
                			smell_map.at(y).at(x) =500;
                		else smell_map.at(y).at(x) += 100;
                	}
                }
            }

            // Ist Kreatur jetzt tot?
            if(creaturePointer->lifepoints <= 0 || creaturePointer->lifetime <= 0)
            {
                creaturePointer->dead = true;
            }
        }
    }

    // Zum Schluss noch Kreaturen l�schen, die seit 3 Runden tot sind:
    while (!creaturesToRemove.empty())
    {
        std::shared_ptr<creature> temp = creaturesToRemove.front();
        creaturesToRemove.pop();
        destroy_creature(temp);
    }

    /**
        Statistiken ausgeben
        */

    int kuehe = 0, pferde = 0, schafe = 0, emus = 0, tiger = 0;
    for(it = creatures_.begin(); it != creatures_.end(); ++it)
    {
        creature *creaturePointer;
        std::shared_ptr<creature> *sharedPointer = &*it; // Pointer zu shared pointer
        creaturePointer = sharedPointer->get(); // Pointer zum "richtigen" Creature-Objekt

        const creature_prototype& prototype = creaturePointer->prototype;  // Referenz zum Prototyp

        if (prototype.name() == "Tiger")
        {
            tiger++;
        }

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

/**
 * Actionen pro Gattung. (c) Christian Wolf, mit geringfügigen Änderungen
 *
 */
void model::actionPlant(std::shared_ptr<creature>* c, int currentState)
{

	int x = c->get()->x();
	int y = c->get()->y();

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
int model::actionHerbivore(std::shared_ptr<creature>* c, int currentState)
{

	int x = c->get()->x();
	int y = c->get()->y();

	// Ein Pflanzenfresser gilt als satt, wenn der S�ttigung >= 80
	if (c->get()->hunger >= 80)
	{
		// Dann Counter erh�hen, der angibt seit wie vielen Runden der Pflanzenfresser satt ist
		c->get()->full_count++;
	}
	else
	{
		// Sonst Counter zur�cksetzen
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
		// Dadurch erh�ht sich die S�ttigkeit um 5
		c->get()->hunger += 5;

		// Maximale S�ttigkeit ist 100
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
		/* Hier sollte man pr�fen, ob Feinde in der N�he sind oder ob es etwas zu essen gibt. Je nachdem wird dann der Zustand gesetzt. */

		// Betrachte Umgebung von 5 Feldern
		env = locator(c, 5);

		// Sind Feinde da?
		for (iter = env.begin(); iter != env.end(); iter++)
		{
			const creature_prototype& prototype = (*iter)->prototype;

			// Man muss sich nur Sorgen machen um Feinde, die den gleichen Lebensraum haben (Haie fressen keine K�he)
			if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::carnivore)
			{
				// Wenn Feinde da sind -> Wechsle in RUN-Zustand
				currentState = creature::RUN;
				break;
			}
		}

		// Falls man einen Feind gefunden hat -> �ndere den Zustand
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

		// Falls man Futter gefunden hat -> �ndere den Zustand
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

		// Schauen, ob Feind noch in der N�he ist
		for (iter = env.begin(); iter != env.end(); iter++)
		{
			const creature_prototype& prototype = (*iter)->prototype;

			// Man muss sich nur Sorgen machen um Feinde, die den gleichen Lebensraum haben (Haie fressen keine K�he)
			if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::carnivore)
			{
				// Wenn Feind noch nah ist -> laufe weiterhin weg
				break;
			}
		}


		// Falls kein Feind mehr in der N�he -> �ndere den Zustand
		if (iter == env.end())
		{
			// Gehe wieder in Initialzustand
			currentState = creature::INITIAL_STATE;
			break;
		}

		// Falls der Feind noch da ist -> Laufe in zuf�llige Richtung
		if (findValidNeighbor(c,x,y))
			move_creature(*c,x,y);

		break;

	case creature::REPRODUCE:

		// Neue Kreatur auf eigenem Feld platzieren
		create_creature(c->get()->prototype,x, y);

		// Vermehren macht hungrig -> Hunger zur�cksetzen
		c->get()->hunger = 0;

		// Neuer Zustand nach Reproduce
		currentState = creature::INITIAL_STATE;
		break;

	case creature::DO_NOTHING:
		// Wird im Moment nie erreicht
		/* Hier sollte man auch pr�fen, ob Feinde in der N�he sind bzw. Nahrung. */
		// nicht tun
		break;
	}

	// Wenn die Kreatur gerade nicht isst -> S�ttigkeit reduzieren
	if (currentState != creature::EAT)
		c->get()->hunger -= 5;

	// Nicht unter 0
	if (c->get()->hunger < 0)
		c->get()->hunger = 0;

	return currentState;
}
int model::actionCarnivore(std::shared_ptr<creature>* c, int currentState)
{

	int x = c->get()->x();
	int y = c->get()->y();

	switch(currentState)
	{
	case creature::REPRODUCE:
		// Neue Kreatur erstellen auf eigenem Feld erstellen
		create_creature(c->get()->prototype,x,y,c->get()->getSmellAwareness());

		// Hunger-Memory l�schen (damit nicht gleich noch mehr Kreaturen entstehen)
		c->get()->hunger_memory.clear();

		// Neuer Zustand nach Fortpflanzung
		currentState = creature::INITIAL_STATE;
		break;

	default:


		bool victim = false;

		std::list<std::shared_ptr<creature>> env;
		std::list<std::shared_ptr<creature>>::iterator iter;

		env = locator(c,0);

		// Schauen, ob Beute im eigenen Feld ist
		for (iter = env.begin(); iter != env.end(); iter++)
		{
			const creature_prototype& prototype = (*iter)->prototype;

			// Man muss sich nur Sorgen machen um Beute, die den gleichen Lebensraum haben
			if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::herbivore)
			{
				// Wenn Beute da ist greife an
				victim = true;
				break;
			}
		}

		std::pair<int,int> next_move(y,x);

		for (int d_y=-1; d_y<=1; d_y++){
			for (int d_x=-1;d_x<=1; d_x++){
				if (y+d_y >= 0 && y+d_y < default_world_size_y_){
					if (x+d_x >=0 && x+d_x < default_world_size_x_){
						if (smell_map.at(y+d_y).at(x+d_x) > smell_map.at(y).at(x)){
							next_move = std::make_pair(y+d_y, x+d_x);
						}
					}
				}
			}
		}

		// Falls es keinen geruch zum verfolgen gibt --> zufällige Bewegung
		if ((next_move.first == y) && (next_move.second == x)){
			if(findValidNeighbor(c,x,y)){
				move_creature(*c,x,y);
			}
		}

		// ansonsten Bewegung entlang der stärksten Geruchsspur
		else {
			move_creature(*c, next_move.second,next_move.first);
		}

		env = locator(c,0); //Befindet sich Beute im aktuellen Feld;

		// Schauen, ob nach der Bewegung Beute im eigenen Feld ist
		for (iter = env.begin(); iter != env.end(); iter++)
		{
			const creature_prototype& prototype = (*iter)->prototype;

			// Man muss sich nur Sorgen machen um Beute, die den gleichen Lebensraum haben
			if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::herbivore)
			{
				// Wenn Beute da ist greife an
				victim = true;
				break;
			}
		}


		// Der Angriff auf ein Beutetier wird durch W�rfelwurf simuliert
		int rnd = randomNumberMinMax(1,20);

		if (rnd != 1 && victim == true)
		{
			// Bei einer 2-20 ist die Kreatur in der aktuellen Runde satt und die Beute tot
			c->get()->hunger_memory.push_back(true);

			for (iter = env.begin(); iter != env.end(); iter++)
			{
				const creature_prototype& prototype = (*iter)->prototype;

				if (prototype.habitat() == c->get()->prototype.habitat() && prototype.sustentation() == creature_prototype::herbivore)
				{
					//Beute ist tot
					(*iter)->dead= true;
					break;
				}
			}


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

	return currentState;
}

/*
* �bung 2 Aufgabe 1
* Methode, welche eine Aktion mit Hilfe des Zustandes einer Kreatur berechnet. Die Kreatur macht dabei eine Aktion.
*
*/

void model::makeAction(std::shared_ptr<creature>* c, int currentState)
{
	// Tote Kreaturen k�nnen keine Aktionen machen
	if (c->get()->dead == true)
		return;

	// Zun�chst Pflanzen betrachten
	if (c->get()->prototype.sustentation() == creature_prototype::plant)
		actionPlant(c, currentState);
	// Pflanzenfresser betrachten
	else if(c->get()->prototype.sustentation() == creature_prototype::herbivore)
		currentState = actionHerbivore(c, currentState);
	// Fleischfresser betrachten
	else if (c->get()->prototype.sustentation() == creature_prototype::carnivore)
		currentState = actionCarnivore(c, currentState);

	// Neuen Zustand �bernehmen
	(*c)->state = currentState;

}

/*
 * �bung 2 Aufgabe 2
 * Methode, welche die Kreaturen im Umkreis der �bergebenen Kreatur zur�ckgibt.
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
 * Gibt zur�ck, ob Landlebewesen an diese Stelle gehen kann (z.B. Wasser usw.).
 */
bool model::isPossibleLandType(int x, int y)
{
    // R�nder pr�fen:
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
 * Gibt zur�ck, ob Wasserlebewesen an diese Stelle gehen kann (z.B. Land usw.).
 */
bool model::isPossibleWaterType(int x, int y)
{
    // R�nder pr�fen:
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
    Gibt zur�ck, ob das Feld (x,y) leer ist
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
 *  Findet ein zuf�lliges passendes Nachbarfeld, f�r die Kreatur
 *  Die �bergebenen Variablen x, y enthalten danach die Koordinaten eines passenden Felds
 *  Wenn es keins gibt, wird das Feld der Kreatur zur�ckgegeben und false
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
 * Gibt eine zuf�llige Zahl zwischen 0 und 1 zur�ck.
 */
int model::randomNumber()
{
    int randNum = rand() % 2;

    return randNum;
}

/*
 * Gibt eine zuf�llige Zahl zwischen min und max zur�ck.
 */
int model::randomNumberMinMax(int min, int max)
{

    int randNum = min + rand() % (max - min + 1);

    return randNum;
}


std::weak_ptr<creature> model::create_creature
(const creature_prototype& prototype, int x, int y, double smell_awareness)
{
    std::shared_ptr<creature> c(new creature(prototype, x, y, smell_awareness));

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
