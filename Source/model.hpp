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

                // Kreaturen in Umgebung zur�ckgeben
		std::list<std::shared_ptr<creature>> locator(std::shared_ptr<creature>* c, int distance);

        bool isPossibleLandType(int x, int y); // Kann Landbewohner an diese Stelle gehen?
		bool isPossibleWaterType(int x, int y);// Kann Wasserbewohner an diese Stelle gehen?
		bool isEmpty(int x, int y);     // Ist das Feld (x,y) leer?
		bool findValidNeighbor(std::shared_ptr<creature>* c, int & x, int & y);

		int randomNumber();

		int randomNumberMinMax(int min, int max);


	private:

        int turn;

		std::weak_ptr<creature> create_creature
			(const creature_prototype& prototype, int x, int y, double smell_awareness = 0);
		void destroy_creature
			(const std::weak_ptr<creature>& c) NOTHROW;

		void move_creature
			(const std::weak_ptr<creature>& c, int x, int y);

		void actionPlant    (std::shared_ptr<creature>* c, int currentState);
		int  actionHerbivore(std::shared_ptr<creature>* c, int currentState);
		int  actionCarnivore(std::shared_ptr<creature>* c, int currentState);


		std::list<creature_prototype> prototypes_;
		std::list<std::shared_ptr<creature>> creatures_;
		world_map map_;

		std::vector<std::vector<double> > smell_map;

		int cursor_x_;
		int cursor_y_;


		static const char *default_prototype_list_;

		static const int default_world_size_x_;
		static const int default_world_size_y_;
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_MODEL_HPP) */
