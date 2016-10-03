#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<stack>
#include<chrono>
#include<stdlib.h>  //for srand
#include<time.h>   //for time(NULL) in srand

using namespace std;

void play();

struct Player {
	int flats;
	int caps;
}players[2];

int max_flats;
int max_capstones;

vector<vector<string>> possible = { {}, {"1"}, {"2","11"}, {"3","21","12","111"}, {"4","31","13","22","211","121","112","1111"},
                                    {"5","41","14","32","23","311","131","113","221","212","122","2111","1211","1121","1112","11111"},
									{"6","51","15","42","24","33","411","141","114","123","132","213","231","321","312","222","3111","1311","1131","1113","1212","2121","2211","1221","1122","2112","21111","12111","11112","11121","11211","111111"},
									{"7","61","16","52","25","43","34","511","151","115","124","142","214","241","421","412","331","313","133","223","232","322","4111","1411","1141","1114","1213","1231","1321","3211","2131","1132","3121","3112","2311","1123","2113","1312","2212","2122","1222","2221","31111","13111","11113","11131","11311","21112","12112","22111","11122","21121","11212","12121","12211","21211","11221","211111","111211","111112","112111","121111","111121","1111111"}};


//'S' = 83,  'F' = 70,   'C' = 67
vector<vector<stack<pair<int,int>>>> board;
int n;
int player_num, time_limit;


int main() {
	
	srand (time(NULL));
	
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

void execute_move(string move_string, short player) {
	
	int row, col, count;
	pair<int, int> stones[5];
	char direction;
	
	if(isalpha(move_string[0])) {
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		
		// cout<<row<<"   "<<col;
		if(move_string[0] == 'F' or move_string[0] == 'S') {
			board[row][col].push(make_pair(player, move_string[0]));
			players[player].flats -= 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col].push(make_pair(player, 'C'));
			players[player].caps -= 1;
		}
	}
	else if(isdigit(move_string[0])) {
		count = move_string.length()-4;
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		direction = move_string[3];
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
}

void reverse_execute_move(string move_string, short player) {
	
	int row, col, count;
	pair<int, int> stones[5];
	char direction;
	
	if(isalpha(move_string[0])) {
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		
		// cout<<row<<"   "<<col;
		if(move_string[0] == 'F' or move_string[0] == 'S') {
			board[row][col].pop();
			players[player].flats += 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col].pop();
			players[player].caps += 1;
		}
	}
	else if(isdigit(move_string[0])) {
		count = 1;
		row = n - move_string[2]+'0' + 1;
		col = (int)move_string[1] - 96;
		direction = move_string[3];
		if(direction == '+') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row-count][col].top();
					board[row-count][col].pop();
				}
				if(!board[row-count][col].empty()) {
					if(board[row-count][col].top().second == 83)
						board[row-count][col].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
		}
		else if(direction == '-') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row+count][col].top();
					board[row+count][col].pop();
				}
				if(!board[row+count][col].empty()) {
					if(board[row+count][col].top().second == 83)
						board[row+count][col].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
		}
		else if(direction == '>') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col+count].top();
					board[row][col+count].pop();
				}
				if(!board[row][col+count].empty()) {
					if(board[row][col+count].top().second == 83)
						board[row][col+count].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
		}
		else if(direction == '<') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col-count].top();
					board[row][col-count].pop();
				}
				if(!board[row][col-count].empty()) {
					if(board[row][col-count].top().second == 83)
						board[row][col-count].top().second = 'F';
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
		}
	}
}

vector<string> generate_stack_moves(vector<string> all_moves, int row, int col)
{
	int size=board[row][col].size();
	if(size==0)
		return all_moves;
	size=min(size,n);
	string pos=(char)(col+96)+to_string(n-row+1);
	int i, j;
	string move;
	bool capstop=false;
	if(board[row][col].top().second=='C') capstop=true;
	
	// generating moves for  -
	int index=0;
	int temp=row+1;
	int movelength=0;
	if(capstop==false)
	{
		while(temp<=n)
		{
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='S' || board[temp][col].top().second=='C')
					break;
			}
			index++;
			temp++;
		}
	}
	else
	{
		while(temp<=n)
		{
			if(!board[temp][col].empty()) {

				if(board[temp][col].top().second=='C')
					break;
				else if(board[temp][col].top().second=='S')
				{
					index++; break;
				}
			}
			index++;
			temp++;
		}
	}
	for(i=1; i<=size; i++) {
		for(j=0; j<possible[i].size(); j++) {
			move = possible[i][j];
			movelength=move.length();
			if(movelength <= index) {
				if(capstop==true && movelength==index && move[movelength-1]!='1') continue;
				all_moves.push_back(possible[i][0]+pos+"-"+move);
			}
			else
				break;
		}
	}
	
	//generating moves for  +
	index=0;
	temp=row-1;
	if(capstop==false)
	{
		while(temp>0)
		{
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='S' || board[temp][col].top().second=='C')
					break;
			}
			index++;
			temp--;
		}
	}
	else
	{
		while(temp>0)
		{
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='C')
					break;
				else if(board[temp][col].top().second=='S')
				{
					index++; break;
				}
			}
			index++;
			temp--;
		}
	}
	
	for(i=1; i<=size; i++) {
		for(j=0; j<possible[i].size(); j++) {
			move = possible[i][j];
			movelength=move.length();
			if(movelength <= index){
				if(capstop==true && movelength==index && move[movelength-1]!='1') continue;
				all_moves.push_back(possible[i][0]+pos+"+"+move);}
			else
				break;
		}
	}
	
	//genrating moves for >
	index=0;
	temp=col+1;
	if(capstop==false)
	{
		while(temp<=n)
		{
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='S' || board[row][temp].top().second=='C')
					break;
			}
			index++;
			temp++;
		}
	}
	else
	{
		while(temp<=n)
		{
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='C')
					break;
				else if(board[row][temp].top().second=='S')
				{
					index++; break;
				}
			}
			index++;
			temp++;
		}
	}
	for(i=1; i<=size; i++) {
		for(j=0; j<possible[i].size(); j++) {
			move = possible[i][j];
			movelength=move.length();
			if(movelength <= index){
				if(capstop==true && movelength==index && move[movelength-1]!='1') continue;
				all_moves.push_back(possible[i][0]+pos+">"+move);}
			else
				break;
		}
	}
	
	//generating moves for <
	index=0;
	temp=col-1;
	if(capstop==false)
	{
		while(temp>0)
		{
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='S' || board[row][temp].top().second=='C')
					break;
			}
			index++;
			temp--;
		}
	}
	else
	{
		while(temp>0)
		{
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='C')
					break;
				else if(board[row][temp].top().second=='S')
				{
					index++; break;
				}
			}
			index++;
			temp--;
		}

	}
	for(i=1; i<=size; i++) {
		for(j=0; j<possible[i].size(); j++) {
			string move = possible[i][j];
			movelength=move.length();
			if(movelength <= index){
				if(capstop==true && movelength==index && move[movelength-1]!='1') continue;
				all_moves.push_back(possible[i][0]+pos+"<"+move);}
			else
				break;
		}
	}
	
	return all_moves;
}

vector<string> generate_all_moves(int player) {
	
	string move;
	vector<string> all_moves;
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(board[i][j].empty()) {
				if(players[player].flats > 0) {
					move="F";
					move+=(char)(j+96);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
				if(players[player].flats > 0) {
					move="S";
					move+=(char)(j+96);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
				if(players[player].caps > 0) {
					move="C";
					move+=(char)(j+96);
					move+=to_string(n-i+1);
					all_moves.push_back(move);
				}
			}
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if((!board[i][j].empty()) && (board[i][j].top().first == player))
				all_moves = generate_stack_moves(all_moves, i, j);
		}
	}
	return all_moves;
}

void play() {
	string move;
	
	if(player_num == 1) {
		getline(cin,move);
		execute_move(move,1);
		
		if(move=="Fa1")
			move=string("F")+"a"+to_string(n);
		else
			move="Fa1";
		
		cout<<move<<"\n"<<flush;
		execute_move(move,0);
		
		getline(cin,move);
		execute_move(move,0);
	}
	else {
		cout<<"Fa1"<<"\n"<<flush;
		execute_move("Fa1",1);
		
		getline(cin,move);
		execute_move(move,0);
	}
	
	while(true) {
		
		vector<string> all_moves = generate_all_moves(player_num);
		int move_num = rand() % (all_moves.size());
		move = all_moves[move_num];
		execute_move(move,player_num);
		cout<<move<<"\n"<<flush;
		
		//print all valid moves
		// cout<<"\n";
		// for(int i=0;i<all_moves.size();i++) {
			// cout<<all_moves[i]<<"   ";
		// }
		// cout<<"\n\n";
		
		//print the board
		// vector<vector<stack<pair<int,int>>>> temp(board);
		// for(int i=1; i<=n; i++) {
			// for(int j=1; j<=n; j++) {
				// if(temp[i][j].empty())
					// cout<<"-";
				// while(!temp[i][j].empty()) {
					// cout<<temp[i][j].top().first+1<<(char)temp[i][j].top().second<<" ";
					// temp[i][j].pop();
				// }
				// cout<<"\t";
			// }
			// cout<<"\n";
		// }
		// cout<<"\n";
		
		getline(cin,move);
		execute_move(move, 1-player_num);
	}
}
