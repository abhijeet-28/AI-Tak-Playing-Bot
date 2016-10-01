#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
#include<stack>
#include<chrono>

using namespace std;

void execute_move(string );
void play();

struct Player {
	int flats;
	int caps;
}players[2];

short turn = 0;
int max_flats;
int max_capstones;


//'S' = 83,  'F' = 70,   'C' = 67
vector<vector<stack<pair<int,int>>>> board;
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
	
	players[0].flats = max_flats;
	players[1].flats = max_flats;
	players[0].caps = max_capstones;
	players[1].caps = max_capstones;
	
	play();
}

void execute_move(string move_string) {
	
	int row, col, count, change, next_count, prev_row, prev_col;
	pair<int, int> stones[5];
	short current_piece;
	char direction;
	
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
			board[row][col].push(make_pair(current_piece, move_string[0]));
			players[current_piece].flats -= 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col].push(make_pair(current_piece, 'C'));
			players[current_piece].caps -= 1;
		}
	}
	else if(isdigit(move_string[0])) {
		count = move_string.length()-4;
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		direction = move_string[3];
		prev_row = row;
		prev_col = col;
		if(direction == '+') {
			for(int i=move_string.length()-1; i>=4; i--) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col].top();
					board[row][col].pop();
				}
				if(!board[row-count][col].empty()) {
					if(board[row-count][col].top().second == 83)
						board[row-count][col].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row-count][col].push(stones[j]);
				}
				count--;
			}
		}
		else if(direction == '-') {
			for(int i=move_string.length()-1; i>=4; i--) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col].top();
					board[row][col].pop();
				}
				if(!board[row+count][col].empty()) {
					if(board[row+count][col].top().second == 83)
						board[row+count][col].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row+count][col].push(stones[j]);
				}
				count--;
			}
		}
		else if(direction == '>') {
			for(int i=move_string.length()-1; i>=4; i--) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col].top();
					board[row][col].pop();
				}
				if(!board[row][col+count].empty()) {
					if(board[row][col+count].top().second == 83)
						board[row][col+count].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col+count].push(stones[j]);
				}
				count--;
			}
		}
		else if(direction == '<') {
			for(int i=move_string.length()-1; i>=4; i--) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col].top();
					board[row][col].pop();
				}
				if(!board[row][col-count].empty()) {
					if(board[row][col-count].top().second == 83)
						board[row][col-count].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col-count].push(stones[j]);
				}
				count--;
			}
		}
	}
	turn = 1 - turn;
}

void play() {
	string move;
	
	if(player_num == 1) {
		getline(cin,move);
		execute_move(move);
	}
	
	while(true) {
		//print the board
		vector<vector<stack<pair<int,int>>>> temp(board);
		for(int i=1; i<temp.size(); i++) {
			for(int j=1; j<temp[0].size(); j++) {
				if(temp[i][j].empty())
					cout<<"-";
				while(!temp[i][j].empty()) {
					cout<<temp[i][j].top().first+1<<(char)temp[i][j].top().second<<" ";
					temp[i][j].pop();
				}
				cout<<"\t";
			}
			cout<<"\n";
		}
		cout<<"\n";
		
		getline(cin,move);
		execute_move(move);
	}
}
