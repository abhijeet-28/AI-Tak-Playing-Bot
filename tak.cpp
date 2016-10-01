#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include <chrono>

using namespace std;

void execute_move(string );
void play();

struct Player {
	int flats;
	int caps;
}players[2];

bool turn = 0;
int max_flats;
int max_capstones;

vector<vector<pair<int,string>>> board;
int n;
int moves=0;
int player_num, time_limit;


int main() {
	
	std::ios::sync_with_stdio(false);
	
	cin>>player_num>>n>>time_limit;
	cin.ignore();
	player_num-=1;
	
	board.resize(n+1);
	for(int i=0; i<n+1; i++) {
		board[i].resize(n+1);
	}
	
	if(n == 5) {
		max_flats = 21;
		max_capstones = 1;
	}
	else if(n == 6){
		max_flats = 30;
		max_capstones = 1;
	}
	else if(n == 7){
		max_flats = 40;
		max_capstones = 1;
	}
	
	players[1].flats = max_flats;
	players[2].flats = max_flats;
	players[1].caps = max_capstones;
	players[2].caps = max_capstones;
	
	play();
}

void execute_move(string move_string) {
	
	int row, col, count, change, next_count;
	bool current_piece;
	
	if(turn == 0)
		moves += 1;
	if(moves != 1)
		current_piece = turn;
	else
		current_piece = 1 - turn;
	
	if(isalpha(move_string[0])) {
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		
		// cout<<row<<"   "<<col;
		if(move_string[0] == 'F' or move_string[0] == 'S') {
			board[row][col] = make_pair(current_piece, move_string[0]);
			players[current_piece].flats -= 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col] = make_pair(current_piece, 'C');
			players[current_piece].caps -= 1;
		}
	}
	else if(isdigit(move_string[0])) {
		count = move_string[0]-'0';
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		char direction = move_string[3];
		int prev_row = row;
		int prev_col = col;
		if(direction == '+') {
			for(int i=4; i<move_string.length(); i++) {
				next_count = move_string[i]-'0';
				int next_row = prev_row - next_count;
				
			}
		}
		else if(direction == '-')
			change = -n;
		else if(direction == '>')
			change = 1;
		elif(direction == '<')
			change = -1;
		
		count = int(move_string[0]);
		// self.board[square] = self.board[square][:-count]
	}
	turn = 1 - turn;
}

void play() {
	string move;
	
	if(player_num == 1) {
		getline(cin,move);
		execute_move(move);
	}
	while(1) {
		cout<<
	}
}
