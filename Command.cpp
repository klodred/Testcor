#include "Command.h"

void Command::process_command(Environment& environment, int i, int j) {
	Matrix<Entity*> matr = environment.get_matrix();
	Bot* bot = (Bot*)matr(i, j);
	//int index_move = bot->
    //int index_move = ((Bot*)environment.get_matrix())(i, j).get_index_move();
	//int current_move = ((Bot*)matrix(i, j))->get_genome()(index_move);
	int index = bot->get_index_move();
	//int index_move = ((Bot*)matr(i, j))->
}