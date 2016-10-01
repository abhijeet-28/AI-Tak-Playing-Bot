#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include <chrono>

using namespace std;

void execute_move(string );


struct Player {
	int flats;
	int caps;
};

struct Game {
	int total_squares;
	bool turn;
	int max_flats;
	int max_capstones;
};

vector<vector<int>> board;
int n;


int main() {
	
	std::ios::sync_with_stdio(false);
	
	int player_num, time;
	string move;
	
	cin>>player_num>>n>>time;
	
	Game game = {n*n,0,0,0};
	
	board.resize(n);
	for(int i=0; i<n; i++) {
		board[i].resize(n);
	}
	
	if(n == 5) {
		game.max_flats = 21;
		game.max_capstones = 1;
	}
	else if(n == 6){
		game.max_flats = 30;
		game.max_capstones = 1;
	}
	else if(n == 7){
		game.max_flats = 40;
		game.max_capstones = 1;
	}
	
	if(player_num == 1) {
		getline(cin,move);
		getline(cin,move);
		execute_move(move);
	}
}

int square_to_num(string square_str) {
	int row = (int)square_str[0] - 96;
	int col = square_str[1]-'0';
	if(row < 1 or row > n or col < 1 or col > n)
		return -1;
	return n * (col - 1) + (row - 1)
}

void execute_move(string move_string) {
	
	if(isalpha(move_string[0])) {
		int square = square_to_num(move_string.substr(1));
		cout<<square;
		// if move_string[0] == 'F' or move_string[0] == 'S':
			// self.board[square].append((current_piece, move_string[0]))
			// self.players[current_piece].flats -= 1
		// elif move_string[0] == 'C':
			// self.board[square].append((current_piece, move_string[0]))
			// self.players[current_piece].capstones -= 1
	}
}
