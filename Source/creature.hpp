/**
 *************************************************************************
 *
 * @file creature.hpp
 *
 * Creatures, creature prototypes, and creature management.
 *
 ************************************************************************/


#if !defined(INCLUDED_CREATURE_HPP)
#define INCLUDED_CREATURE_HPP



#include "build_config.hpp"


#include <memory>
#include <string>
#include <vector>
#include <list>
#include <deque>
#include <iostream>

#include "flock.hpp"


#include "image.hpp"


namespace biosim
{


/**
 *************************************************************************
 *
 * @class creature_prototype
 *
 * Defines a type of creature and associated attributes.
 *
 * Usage notes:
 * - Read-only access.
 * - Accessed via a creature_prototype::load_list().
 *
 ************************************************************************/
class creature_prototype
{
	public:

		enum habitat_type { habitat_water, habitat_land };
		enum sustentation_type { plant, herbivore, carnivore };


		const std::string& name() const NOTHROW { return name_; }

		int strength() const NOTHROW { return strength_; }
		int speed() const NOTHROW { return speed_; }
		int lifetime() const NOTHROW { return lifetime_; }
		int repFreq() const NOTHROW { return reproduction_freq; }

		const std::string& properties() const NOTHROW { return properties_; }
		habitat_type habitat() const NOTHROW { return habitat_; }
		sustentation_type sustentation() const NOTHROW { return sustentation_; }

		const image& graphics() const NOTHROW { return graphics_; }

		/** Load creature prototypes from text file at given path. */
		static std::list<creature_prototype> load(const std::string& path);


	private:

		creature_prototype
			(const std::string& name, int strength, int speed, int lifetime,
			 const std::string& properties, habitat_type habitat, sustentation_type sustentation,
			 const image& graphics, int reproduction)
			:
			name_(name), strength_(strength), speed_(speed), lifetime_(lifetime),
			properties_(properties), habitat_(habitat), sustentation_(sustentation),
			graphics_(graphics), reproduction_freq(reproduction)
		{ }


		static habitat_type string_to_habitat(const std::string& s);
		static sustentation_type string_to_sustentation(const std::string& s);


		std::string name_;

		int strength_;
		int speed_;
		int lifetime_;
		int reproduction_freq;

		std::string properties_;
		habitat_type habitat_;
		sustentation_type sustentation_;

		image graphics_;
};



/**
 *************************************************************************
 *
 * @class creature
 *
 * An instance of a creature_prototype.
 *
 * Notes:
 * - Creature lifetime is managed via shared_ptr and weak_ptr.
 *		But a single, owning shared pointer persists for each creature.
 *		Other shared pointers are only locked from weak pointers during
 *		creature access.
 * - Creatures must be created, moved, and destroyed by respective
 *		functions within the model class. This ensures that management
 *		data structures are maintained.
 * - Other creature attributes (lifetime, ...) may be modified freely
 *		by application logics.
 *
 ************************************************************************/
class creature
{
	friend class world_map;

	public:

		// Zustände:
		static const int INITIAL_STATE = 1001; // Anfangszustand
		static const int EAT = 1002; // Gras essen
		static const int DISCOVER = 1003; // Umgebung erkunden
		static const int RUN = 1004; // Wegrennen
		static const int DO_NOTHING = 1005; // Nichts tun
		static const int REPRODUCE = 1006;  // Fortpflanzen
		static const int HUNT = 1007;  // Jagen (für Fleischfresser)
		static const int VOTED = 1008;  // Jagen (für Fleischfresser)

		creature(const creature_prototype& prototype, int x, int y)
			:
			prototype(prototype), lifetime(prototype.lifetime()),
			x_(x), y_(y), lifepoints(100), dead(false), numOfDeadRounds(0), hunger(25), state(INITIAL_STATE), full_count(0), inFlock(false), preferedDirection(0)
		{
            smell_threshold = 0.1 + (double)(rand()%500)/100.0;
		}

        creature(const creature_prototype& prototype, int x, int y, double threshold)
			:
			prototype(prototype), lifetime(prototype.lifetime()),
			x_(x), y_(y), lifepoints(100), dead(false), numOfDeadRounds(0), hunger(25), state(INITIAL_STATE), full_count(0), smell_threshold(threshold), inFlock(false), preferedDirection(9)
		{
		}


		int x() const NOTHROW { return x_; }
		int y() const NOTHROW { return y_; }

		const creature_prototype& prototype;

		int lifetime;   // Alter der Kreatur
		int lifepoints; // Lebenspunkte
		bool dead; // Tot oder nicht?
		int numOfDeadRounds; // Wie lange ist Kreatur schon tot?
		int hunger; // 0 = hungrig, 100 = satt
		int state; // In welchem Zustand ist die Kreatur?

        std::deque<bool> hunger_memory;  // Speichert für die letzten 10 Runden, ob die Kreatur satt war (für Fleischfresser)
        int full_count;     // Zählt seit wie vielen Runden die Kreatur kontinuierlich satt ist (für Pflanzenfresser)

        double smell_threshold; // Geruchsschwelle (für Fleischfresser)

        bool isFull();      // Methode, die zurückgibt, ob die Kreatur satt ist (unterschiedlich für Pflanzen und Fleischfresser)
        int getFullRounds();    // Liefert, wie oft ein Fleischfresser in den letzten 10 Runden satt war

        bool inFlock;       // Variable, die speichert, ob die Kreatur in einer Herde ist

        int preferences[9]; /* Array, das die Preferenzen für eine Kreatur speichert
                                Das erste Element des Arrays hat die höchste Priorität. Gespeichert wird jeweils ein int-Wert, der die Richtung angibt, in die die Kreatur sich bewegen will
                                Tabelle:      1
                                            4 0 2
                                              3
                                D.h. 0 bedeutet stehenbleiben, 1 heißt nach oben, 2 heißt nach rechts, usw.
                                */
        int preferedDirection;
        void getPreferences(int pref[9]);

        std::deque<int> move_queue; // Schlange, in der die Bewegungen der Kreatur eingetragen werden. Die Kreatur arbeitet diese bei einer Bewegung nacheinander ab



        // Ein paar Wrapper zur leichteren Verwendung
        void moveNot();
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void moveUpRight();
        void moveUpLeft();
        void moveDownRight();
        void moveDownLeft();
        void moveRandom();

        void addMove();   // Methode, die eine Bewegung in die Schlange aufnimmt
        void getMove(int & x, int & y);    // Methode, die die Kreatur entsprechend ihrer move_queue bewegt
                                        // Als Ergebnis werden die Koordinaten (x,y) zurückgeliefert, an die sich die Kreatur bewegen will
                                        // Die Bewegung muss vom aufrufenden Programm durchgeführt werden, ebenso eventuelle Checks


	private:

		creature(const creature& other); // Non-copyable
		creature& operator =(const creature& other); // Non-assignable

		int x_;
		int y_;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_CREATURE_HPP) */
