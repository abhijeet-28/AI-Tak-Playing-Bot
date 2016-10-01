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

// vector<vector<int>> partition(n){
	// vector<vector<int>> part_list;
	// part_list.push_back(vector<int>(1,n));
	// for(int i=1; i<n; i++) {
		// for(auto const& y: partition(n - i) {
			// vector<int> temp;
			// temp.push_back(i);
			// temp.insert( temp.end(), y.begin(), y.end() );
			// part_list.push_back(temp);
		// }
	// }
	// return part_list;
// }

// def check_valid(self, square, direction, partition):
	// '''For given movement (partition), check if stack on
	// square can be moved in direction. Assumes active player
	// is topmost color
	// '''
	// if direction == '+':
		// change = self.n
	// elif direction == '-':
		// change = -self.n
	// elif direction == '>':
		// change = 1
	// elif direction == '<':
		// change = -1
	// for i in xrange(len(partition)):
		// next_square = square + change * (i + 1)
		// if len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'C':
			// return False
		// if len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and i != len(partition) - 1:
			// return False
		// if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and partition[i] > 1:
			// return False
		// if i == len(partition) - 1 and len(self.board[next_square]) > 0 and self.board[next_square][-1][1] == 'S' and self.board[square][-1][1] != 'C':
			// return False
	// return True

// vector<string> generate_stack_moves(vector<string> all_moves, int row, int col) {
	// int size = board[row][col].size();
	// char dirs[] = {'+', '-', '<', '>'};
	// int up = n - row;
	// int down = row - 1;
	// int right = n - col;
	// int left = col - 1;
	// int rem_squares = {up, down, left, right};
	// size = min(size, n);
	// for(int i=0; i<size; i++) {
		// vector<vector<int>> part_list = partition(i + 1);
		// for(int j=0; j<4; j++) {
			// part_dir = [part for part in part_list if len(part) <= rem_squares[di]]
			// for part in part_dir:
				// if self.check_valid(square, dirs[di], part):
					// part_string = ''.join([str(i) for i in part])
					// all_moves.append(str(sum(part)) + self.all_squares[square] + dirs[di] + part_string)
		// }
	// }
	// return all_moves
	
// }

vector<string> generate_all_moves(int player) {
	
	vector<string> all_moves;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(board[i][j].empty()) {
				if(players[player].flats > 0) {
					string move="F";
					move+=(char)(j+96);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
				if(moves != player && players[player].flats > 0) {
					string move="S";
					move+=(char)(j+48);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
				if(moves != player && players[player].caps > 0) {
					string move="C";
					move+=(char)(j+48);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
			}
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if((!board[i][j].empty()) && (board[i][j].top().first == player) && (moves != player))
				all_moves += self.generate_stack_moves(all_moves, i, j);
	}
	return all_moves;
}

void play() {
	string move;
	
	if(player_num == 1) {
		getline(cin,move);
		execute_move(move);
	}
	
	while(true) {
		
		vector<string> all_moves = generate_all_moves(player_num);
		cout<<"\n";
		for(int i=0;i<all_moves.size();i++) {
			cout<<all_moves[i]<<"   ";
		}
		cout<<"\n\n";
		//print the board
		vector<vector<stack<pair<int,int>>>> temp(board);
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
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
