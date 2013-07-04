/**
 *************************************************************************
 *
 * @file model.hpp
 *
 * Contains the high-level application data model.
 *
 ************************************************************************/


#if !defined(INCLUDED_MODEL_HPP)
#define INCLUDED_MODEL_HPP


#include "build_config.hpp"


#include <memory>
#include <vector>


#include "creature.hpp"
#include "world_map.hpp"
#include "smell_map.hpp"
#include "flock.hpp"


namespace biosim
{


/**
 *************************************************************************
 *
 * @class model
 *
 * The high-level application data model, which contains all creatures,
 * creature prototypes, and the world map.
 *
 ************************************************************************/
class model
{

	public:

		model();

		const std::list<creature_prototype>& prototypes() const NOTHROW
			{ return prototypes_; }
		const world_map& map() const NOTHROW
			{ return map_; }

		void set_cursor(int x, int y);

		int cursor_x() const NOTHROW { return cursor_x_; }
		int cursor_y() const NOTHROW { return cursor_y_; }

		void create_creature_at_cursor
			(const creature_prototype& prototype);

		void perform_step();

		void makeAction(std::shared_ptr<creature>* c, int currentState); // Zustandsautomat
		int makeActionPlant(std::shared_ptr<creature>* c);
		int makeActionHerbivore(std::shared_ptr<creature>* c);
		int makeActionCarnivore(std::shared_ptr<creature>* c);

                // Kreaturen in Umgebung zurückgeben
		std::list<std::shared_ptr<creature>> locator(std::shared_ptr<creature>* c, int distance);

        bool isPossible(int x, int y);      // Ist das Feld innerhalb der Karte?
        bool isPossibleLandType(int x, int y); // Kann Landbewohner an diese Stelle gehen?
		bool isPossibleWaterType(int x, int y);// Kann Wasserbewohner an diese Stelle gehen?
		bool isEmpty(int x, int y);     // Ist das Feld (x,y) leer?
		bool findValidNeighbor(std::shared_ptr<creature>* c, int & x, int & y);

        bool foodAvailable(std::shared_ptr<creature>*c);    // Methode, die überprüft, ob es Futter in der Zelle der Kreatur gibt
		bool enemyNearby(std::shared_ptr<creature>*c);      // Methode, die überprüft, ob Feinde in einer Umgebung der Kreatur sind

		void reducePlantHP(std::shared_ptr<creature>*c);    // Methode, die allen Pflanzen in der Zelle der Kreatur 5 HP abzieht
		void killPrey(std::shared_ptr<creature>*c);         // Tötet einen Pflanzenfresser auf dem Feld der Kreatur

		int randomNumber();

		int randomNumberMinMax(int min, int max);

		void addToFlock(std::shared_ptr<creature>c);




	private:

        int turn;

		std::weak_ptr<creature> create_creature
			(const creature_prototype& prototype, int x, int y);

        std::weak_ptr<creature> create_creature
            (const creature_prototype& prototype, int x, int y, double threshold);

		void destroy_creature
			(const std::weak_ptr<creature>& c) NOTHROW;

		void move_creature
			(const std::weak_ptr<creature>& c, int x, int y);

        std::list<emuflock> emu_flocks;


		std::list<creature_prototype> prototypes_;
		std::list<std::shared_ptr<creature>> creatures_;

		world_map map_;
		smell_map map_smell;    // Karte mit Geruchsinformationen für die Fleischfresser

		int cursor_x_;
		int cursor_y_;


		static const char *default_prototype_list_;

		static const int default_world_size_x_;
		static const int default_world_size_y_;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_MODEL_HPP) */
