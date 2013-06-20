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
#include <list>
#include <deque>


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

		// Zust�nde:
		static const int INITIAL_STATE = 1001; // Anfangszustand
		static const int EAT = 1002; // Gras essen
		static const int DISCOVER = 1003; // Umgebung erkunden
		static const int RUN = 1004; // Wegrennen
		static const int DO_NOTHING = 1005; // Nichts tun
		static const int REPRODUCE = 1006;  // Fortpflanzen

		creature(const creature_prototype& prototype, int x, int y)
			:
			prototype(prototype), lifetime(prototype.lifetime()),
			x_(x), y_(y), lifepoints(100), dead(false), numOfDeadRounds(0), hunger(0), state(INITIAL_STATE), full_count(0)
		{ }


		int x() const NOTHROW { return x_; }
		int y() const NOTHROW { return y_; }

		const creature_prototype& prototype;

		int lifetime;   // Alter der Kreatur
		int lifepoints; // Lebenspunkte
		bool dead; // Tot oder nicht?
		int numOfDeadRounds; // Wie lange ist Kreatur schon tot?
		int hunger; // 0 = hungrig, 100 = satt
		int state; // In welchem Zustand ist die Kreatur?

        std::deque<bool> hunger_memory;  // Speichert f�r die letzten 10 Runden, ob die Kreatur satt war (f�r Fleischfresser)
        int full_count;     // Z�hlt seit wie vielen Runden die Kreatur kontinuierlich satt ist (f�r Pflanzenfresser)


	private:

		creature(const creature& other); // Non-copyable
		creature& operator =(const creature& other); // Non-assignable

		int x_;
		int y_;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_CREATURE_HPP) */
