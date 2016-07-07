#ifndef GS_TEST_TIC_TAC_GAME_STATE
#define GS_TEST_TIC_TAC_GAME_STATE

#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "GameSolver/GameState.hpp"

class Vec2 {
public:
	Vec2(int p_x,
	     int p_y)
		: x(p_x),
		  y(p_y)
	{
	}

	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
        
	int x;
	int y;
};

inline
bool operator==(const Vec2& lhs,
		       const Vec2& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline
Vec2 operator+(Vec2 lhs,
	       const Vec2& rhs) {
	return lhs += rhs;
}

inline
Vec2 operator-(Vec2 lhs,
	       const Vec2& rhs) {
	return lhs -= rhs;
}

/**
 * A very simple tic-tac-toe like class used for testing the game solver.
 *
 * There are two players: 1 and 2, while empty cells have the value 0.
 */
class TicTacGameState : public gs::GameState {

public:
	/**
	 * Creates a new \c TicTacGameState object.
	 *
	 * \param p_cols The number of columns on the board.
	 * \param p_rows The number of rows on the board.
	 */
	TicTacGameState(int p_cols,
			int p_rows,
			int p_num_to_win)
		: cols(p_cols),
		  rows(p_rows),
		  num_to_win(p_num_to_win),
		  m_steps_taken(0),
		  m_winner(0),
		  m_first_player(true),
		  m_table(std::vector< std::vector<int> >(
				  cols,
				  std::vector<int>(rows, 0)))
	{
	}

	TicTacGameState(const TicTacGameState& other)
		: cols(other.cols),
		  rows(other.rows),
		  num_to_win(other.num_to_win),
		  m_steps_taken(other.m_steps_taken),
		  m_winner(other.m_winner),
		  m_first_player(other.m_first_player),
		  m_table(other.m_table)
	{
	}

	/**
	 * Returns the value of a cell.
	 *
	 * \param x The x (horizontal) coordinate of the cell.
	 * \param y The y (vertical) coordinate of the cell.
	 *
	 * \return The value of the given cell.
	 *         Possible values:
	 *         1 - first player;
	 *         2 - second player;
	 *         0 - empty;
	 *         -1 - invalid cell.
	 */
	int get(int x,
		int y) const {
		if (x < 0 || x >= cols || y < 0 || y >= rows)
			return -1;
		else
			return m_table.at(x).at(y);
	}

	/**
	 * Sets the value of a cell.
	 *
	 * \param x The x (horizontal) coordinate of the cell.
	 * \param y The y (vertical) coordinate of the cell.
	 * \param value The value to set - can be 0, 1 or 2.
	 *
	 * \return \c true if the given cell was set;
	 *         \c false if the given cell or the given value is invalid.
	 */
	bool set(int x,
		 int y,
		 int value) {
		if (get(x, y) == -1)
			return false;
		if (value < 0 || value > 2)
			return false;

		m_table.at(x).at(y) = value;
		++m_steps_taken;

		int winner = winner_at(x, y);
		if (m_winner == 0 && winner != 0)
			m_winner = winner;
		return true;
	}

	/**
	 * Takes a move with the current player.
	 *
	 * \param x The x (horizontal) coordinate of the cell.
	 * \param y The y (vertical) coordinate of the cell.
	 *
	 * \return whether the move was successful.
	 */
	bool move(int x, int y) {
		int value = m_first_player ? 1 : 2;
		bool res = set(x, y, value);

		if (res)
			m_first_player = !m_first_player;

		return res;
	}

	int get_steps_taken() const {
		return m_steps_taken;
	}

	/**
	 * Dumps the state of the board to the given stream.
	 *
	 * \param out The stream to dump the data to.
	 */
	void dump(std::ostream& out = std::cout) const {
		using namespace std;
		string sep = " ";
		for (int i = 0; i < cols; ++i) {
			for (int j = 0; j < rows; ++j) {
				out << get(i, j) << sep;
			}

			out << std::endl;
		}
	}

	virtual Result get_winner() const override {
	        if (m_winner == 1)
			return Result::MAXIMIZING;
		if (m_winner == 2)
			return Result::MINIMIZING;
		if (m_steps_taken >= cols * rows)
			return Result::DRAW;

		return Result::NONE;
	}

	virtual std::vector< std::shared_ptr<GameState> >
	generate_next_states() const override {
		std::vector< std::shared_ptr<GameState> > res;
		for (int i = 0; i < cols; ++i) {
			for (int j = 0; j < rows; ++j) {
				int value = get(i, j);
				if (value == 0) {
					auto copy = new TicTacGameState(*this);
					copy->move(i, j);
					std::shared_ptr<GameState> smart(copy);
					res.emplace_back(smart);
				}
			}
		}
		
		return res;
	}

	virtual std::shared_ptr<GameState> shallow_copy() const override {
		return deep_copy();
	}

	virtual std::shared_ptr<GameState> deep_copy() const override {
		return std::make_shared<TicTacGameState>(*this);
	}
	
	const int cols;
	const int rows;
	const int num_to_win;
private:
	int winner_at(int x, int y) const {
		int value = get(x, y);
		if (value != 1 && value != 2)
			return 0;

	        if(winner_at_in_dir(x, y, 1, 0)
			|| winner_at_in_dir(x, y, 0, 1)
			|| winner_at_in_dir(x, y, 1, 1)
			|| winner_at_in_dir(x, y, -1, 1))
			return value;
	        return 0;		
	}

	int winner_at_in_dir(const int x,
			     const int y,
			     const int x_dir,
			     const int y_dir) const {
	        int value = get(x, y);
		if (value != 1 && value != 2)
			return 0;

		int current_x = x + x_dir;
		int current_y = y + y_dir;
		int counter = 1;

		// Forward
	        while(value == get(current_x, current_y)) {
			++counter;
			current_x += x_dir;
			current_y += y_dir;
		}

		// Backward
		current_x = x - x_dir;
		current_y = y - y_dir;
		while(value == get(current_x, current_y)) {
			++counter;
			current_x -= x_dir;
			current_y -= y_dir;
		}

		if (counter >= num_to_win)
			return value;
		else
			return 0;
	}

	int m_steps_taken;
	int m_winner;
	bool m_first_player;
	std::vector< std::vector<int> > m_table;
};

// Free functions
gs::eval_type evaluate(TicTacGameState *state) {
	using namespace gs;
	
	if (!state)
		return 0;
	
	GameState::Result winner = state->get_winner();
	if (winner == GameState::MAXIMIZING)
		return std::numeric_limits<gs::eval_type>::max();
	if (winner == GameState::MINIMIZING)
		return std::numeric_limits<gs::eval_type>::lowest();
	if (winner == GameState::DRAW)
		return 0;

	// TODO - heuristic value if the game is not over.
	return 0;
}

#endif // GS_TEST_TIC_TAC_GAME_STATE
