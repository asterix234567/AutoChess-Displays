#pragma once

#include <array>
#include <chrono>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

//control parameters
static constexpr int max_ply             = 20;
static constexpr float max_time_per_move = 10.0f;
static constexpr int max_chess_moves     = 218 / 2;
static constexpr int max_score_entries   = 100000;

//piece values, in centipawns
static constexpr int king_value   = 20000;
static constexpr int queen_value  = 900;
static constexpr int rook_value   = 500;
static constexpr int bishop_value = 330;
static constexpr int knight_value = 320;
static constexpr int pawn_value   = 100;
static constexpr int mate_value   = king_value * 10;
static constexpr int timeout_value = mate_value * 2;

//board square/piece types
static constexpr int white = 1;
static constexpr int empty = 0;
static constexpr int black = -1;

//piece capture actions, per vector
static constexpr int no_capture   = 0;
static constexpr int may_capture  = 1;
static constexpr int must_capture = 2;

//board is string of 64 chars
typedef std::string board;
typedef std::vector<board> boards;

//evaluation score and board combination
struct score_board
{
	int score;
	int bias;
	board brd;
};
typedef std::vector<score_board> score_boards;

//description of a pieces movement and capture action
struct move
{
	int dx;
	int dy;
	int length;
	int flag;
};
typedef const std::vector<move> moves;

//description of a pieces check influence
struct vector
{
	int dx;
	int dy;
	int length;
};
typedef const std::vector<vector> vectors;

//check test, array of pieces that must not be on this vectors from the king
struct test
{
	std::string pieces;
	vectors *vectors;
};
typedef const std::vector<test> tests;

//map board square contents to piece type/colour
static auto piece_type = std::map<char, const int>{
	{'p', black}, {'r', black}, {'n', black}, {'b', black}, {'k', black}, {'q', black},
	{'P', white}, {'R', white}, {'N', white}, {'B', white}, {'K', white}, {'Q', white},
	{' ', empty}};

static auto unicode_pieces = std::map<char, const std::string>{
	{'p', "♟"}, {'r', "♜"}, {'n', "♞"}, {'b', "♝"}, {'k', "♚"}, {'q', "♛"},
	{'P', "♙"}, {'R', "♖"}, {'N', "♘"}, {'B', "♗"}, {'K', "♔"}, {'Q', "♕"},
	{' ', " "}};

//piece move vectors and capture actions
static auto black_pawn_moves = moves{
	{0, 1, 0, no_capture}, {-1, 1, 1, must_capture}, {1, 1, 1, must_capture}};
static auto white_pawn_moves = moves{
	{0, -1, 0, no_capture}, {-1, -1, 1, must_capture}, {1, -1, 1, must_capture}};
static auto rook_moves = moves{
	{0, -1, 7, may_capture}, {-1, 0, 7, may_capture}, {0, 1, 7, may_capture}, {1, 0, 7, may_capture}};
static auto bishop_moves = moves{
	{-1, -1, 7, may_capture}, {1, 1, 7, may_capture}, {-1, 1, 7, may_capture}, {1, -1, 7, may_capture}};
static auto knight_moves = moves{
	{-2, 1, 1, may_capture}, {2, -1, 1, may_capture}, {2, 1, 1, may_capture}, {-2, -1, 1, may_capture},
	{-1, -2, 1, may_capture}, {-1, 2, 1, may_capture}, {1, -2, 1, may_capture}, {1, 2, 1, may_capture}};
static auto queen_moves = moves{
	{0, -1, 7, may_capture}, {-1, 0, 7, may_capture}, {0, 1, 7, may_capture}, {1, 0, 7, may_capture},
	{-1, -1, 7, may_capture}, {1, 1, 7, may_capture}, {-1, 1, 7, may_capture}, {1, -1, 7, may_capture}};
static auto king_moves = moves{
	{0, -1, 1, may_capture}, {-1, 0, 1, may_capture}, {0, 1, 1, may_capture}, {1, 0, 1, may_capture},
	{-1, -1, 1, may_capture}, {1, 1, 1, may_capture}, {-1, 1, 1, may_capture}, {1, -1, 1, may_capture}};

//map piece to its movement possibilities
static auto moves_map = std::map<char, moves*>{
	{'p', &black_pawn_moves}, {'P', &white_pawn_moves},
	{'R', &rook_moves}, {'r', &rook_moves},
	{'B', &bishop_moves}, {'b', &bishop_moves},
	{'N', &knight_moves}, {'n', &knight_moves},
	{'Q', &queen_moves}, {'q', &queen_moves},
	{'K', &king_moves}, {'k', &king_moves}};

//piece check vectors, king is tested for being on these vectors for check tests
static auto black_pawn_vectors = vectors{{-1, 1, 1}, {1, 1, 1}};
static auto white_pawn_vectors = vectors{{-1, -1, 1}, {1, -1, 1}};
static auto bishop_vectors = vectors{{-1, -1, 7}, {1, 1, 7}, {-1, 1, 7}, {1, -1, 7}};
static auto rook_vectors = vectors{{0, -1, 7}, {-1, 0, 7}, {0, 1, 7}, {1, 0, 7}};
static auto knight_vectors = vectors{{-1, -2, 1}, {-1, 2, 1}, {-2, -1, 1}, {-2, 1, 1}, {1, -2, 1}, {1, 2, 1}, {2, -1, 1}, {2, 1, 1}};
static auto queen_vectors = vectors{{-1, -1, 7}, {1, 1, 7}, {-1, 1, 7}, {1, -1, 7}, {0, -1, 7}, {-1, 0, 7}, {0, 1, 7}, {1, 0, 7}};
static auto king_vectors = vectors{{-1, -1, 1}, {1, 1, 1}, {-1, 1, 1}, {1, -1, 1}, {0, -1, 1}, {-1, 0, 1}, {0, 1, 1}, {1, 0, 1}};

//check tests, piece types given can not be on the vectors given
static auto white_tests = tests{{"qb", &bishop_vectors}, {"qr", &rook_vectors}, {"n", &knight_vectors}, {"k", &king_vectors}, {"p", &white_pawn_vectors}};
static auto black_tests = tests{{"QB", &bishop_vectors}, {"QR", &rook_vectors}, {"N", &knight_vectors}, {"K", &king_vectors}, {"P", &black_pawn_vectors}};

//map piece to black/white scores for board evaluation
static auto piece_values = std::map<char, const std::pair<int, int>>{
	{'k', {king_value, 0}}, {'K', {0, king_value}}, {'q', {queen_value, 0}}, {'Q', {0, queen_value}},
	{'r', {rook_value, 0}}, {'R', {0, rook_value}}, {'b', {bishop_value, 0}}, {'B', {0, bishop_value}},
	{'n', {knight_value, 0}}, {'N', {0, knight_value}}, {'p', {pawn_value, 0}}, {'P', {0, pawn_value}}};

//pawn values for position in board evaluation
static const auto pawn_position_values = std::array<int, 64>{{
	0, 0, 0, 0, 0, 0, 0, 0,
	50, 50, 50, 50, 50, 50, 50, 50,
	10, 10, 20, 30, 30, 20, 10, 10,
	5, 5, 10, 25, 25, 10, 5, 5,
	0, 0, 0, 20, 20, 0, 0, 0,
	5, -5, -10, 0, 0, -10, -5, 5,
	5, 10, 10, -20, -20, 10, 10, 5,
	0, 0, 0, 0, 0, 0, 0, 0}};

static const auto knight_position_values = std::array<int, 64>{{
	-50, -40, -30, -30, -30, -30, -40, -50,
	-40, -20, 0, 0, 0, 0, -20, -40,
	-30, 0, 10, 15, 15, 10, 0, -30,
	-30, 5, 15, 20, 20, 15, 5, -30,
	-30, 0, 15, 20, 20, 15, 0, -30,
	-30, 5, 10, 15, 15, 10, 5, -30,
	-40, -20, 0, 5, 5, 0, -20, -40,
	-50, -40, -30, -30, -30, -30, -40, -50}};

static const auto bishop_position_values = std::array<int, 64>{{
	-20, -10, -10, -10, -10, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 10, 10, 5, 0, -10,
	-10, 5, 5, 10, 10, 5, 5, -10,
	-10, 0, 10, 10, 10, 10, 0, -10,
	-10, 10, 10, 10, 10, 10, 10, -10,
	-10, 5, 0, 0, 0, 0, 5, -10,
	-20, -10, -10, -10, -10, -10, -10, -20}};

static const auto rook_position_values = std::array<int, 64>{{
	0, 0, 0, 0, 0, 0, 0, 0,
	5, 10, 10, 10, 10, 10, 10, 5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	0, 0, 0, 5, 5, 0, 0, 0}};

static const auto queen_position_values = std::array<int, 64>{{
	-20, -10, -10, -5, -5, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 5, 5, 5, 0, -10,
	-5, 0, 5, 5, 5, 5, 0, -5,
	0, 0, 5, 5, 5, 5, 0, -5,
	-10, 5, 5, 5, 5, 5, 0, -10,
	-10, 0, 5, 0, 0, 0, 0, -10,
	-20, -10, -10, -5, -5, -10, -10, -20}};

static const auto king_position_values = std::array<int, 64>{{
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-20, -30, -30, -40, -40, -30, -30, -20,
	-10, -20, -20, -20, -20, -20, -20, -10,
	20, 20, 0, 0, 0, 0, 20, 20,
	20, 30, 10, 0, 0, 10, 30, 20}};

//map piece to position value table
static auto piece_positions = std::map<char, const std::array<int, 64>*>{
	{'k', &king_position_values}, {'K', &king_position_values},
	{'q', &queen_position_values}, {'Q', &queen_position_values},
	{'r', &rook_position_values}, {'R', &rook_position_values},
	{'b', &bishop_position_values}, {'B', &bishop_position_values},
	{'n', &knight_position_values}, {'N', &knight_position_values},
	{'p', &pawn_position_values}, {'P', &pawn_position_values}};

//=== public API ===

//best move for given board position for given colour
board best_move(const board &brd, int colour, const boards &history);

//optional helpers (useful for debugging)
bool in_check(const board &brd, int colour, std::size_t &king_index);
int evaluate(const board &brd, int colour);
void display_board(const board &brd);

