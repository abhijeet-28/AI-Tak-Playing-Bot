#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<deque>
#include<stack>
#include<stdlib.h>  //for srand
#include<time.h>   //for time(NULL) in srand
#include<algorithm>   //for find()

using namespace std;

void play();
int evaluate();
int checkroad();

struct Player {
	int flats;
	int caps;
}players[2];

int max_flats;
int max_capstones;

int checkroad();

clock_t start, end;
double aim;

int mul=1;

pair<int, int> stones[5];

vector<vector<string>> possible = { {}, {"1"}, {"2","11"}, {"3","21","12","111"}, {"4","31","13","22","211","121","112","1111"},
                                    {"5","41","14","32","23","311","131","113","221","212","122","2111","1211","1121","1112","11111"},
									{"6","51","15","42","24","33","411","141","114","123","132","213","231","321","312","222","3111","1311","1131","1113","1212","2121","2211","1221","1122","2112","21111","12111","11112","11121","11211","111111"},
									{"7","61","16","52","25","43","34","511","151","115","124","142","214","241","421","412","331","313","133","223","232","322","4111","1411","1141","1114","1213","1231","1321","3211","2131","1132","3121","3112","2311","1123","2113","1312","2212","2122","1222","2221","31111","13111","11113","11131","11311","21112","12112","22111","11122","21121","11212","12121","12211","21211","11221","211111","111211","111112","112111","121111","111121","1111111"}};


//'S' = 83,  'F' = 70,   'C' = 67
vector<vector<stack<pair<int,int>>>> board;
int n;
int player_num;
double time_limit;
double time_left;


// auto t_start = std::chrono::high_resolution_clock::now();
// auto t_current = std::chrono::high_resolution_clock::now();

int main() {
	
	srand (time(NULL));
	
	std::ios::sync_with_stdio(false);
	
	cin>>player_num>>n>>time_limit;
	// player_num=2;
	// n=5;
	// time_limit=200;
	time_left=time_limit;
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

void execute_move(string move_string, short player, bool &stand, bool isTempMove = false) {

	int row, col, count;
	char direction;
	
	row = n - move_string[2]+'0' + 1;
	col = move_string[1] - 96;
	
	if(isalpha(move_string[0])) {
		if(move_string[0] == 'F') {
			board[row][col].push(make_pair(player, move_string[0]));
			players[player].flats -= 1;
		}
		else if(move_string[0] == 'S') {
			board[row][col].push(make_pair(player, move_string[0]));
			players[player].flats -= 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col].push(make_pair(player, 'C'));
			players[player].caps -= 1;
		}
	}
	else {
		count = move_string.length()-4;
		
		direction = move_string[3];
		if(direction == '+') {
			for(int i=move_string.length()-1; i>=4; i--) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col].top();
					board[row][col].pop();
				}
				if(!board[row-count][col].empty()) {
					if(board[row-count][col].top().second == 83) {
						board[row-count][col].top().second = 'F';
						if(isTempMove)
							stand = true;
					}
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
					if(board[row+count][col].top().second == 83) {
						board[row+count][col].top().second = 'F';
						if(isTempMove)
							stand = true;
					}
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
					if(board[row][col+count].top().second == 83) {
						board[row][col+count].top().second = 'F';
						if(isTempMove)
							stand = true;
					}
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
					if(board[row][col-count].top().second == 83) {
						board[row][col-count].top().second = 'F';
						if(isTempMove)
							stand = true;
					}
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col-count].push(stones[j]);
				}
				count--;
			}
		}
	}
}

void reverse_execute_move(string move_string, short player, bool stand) {

	int row, col, count;
	char direction;
	
	row = n - move_string[2]+'0' + 1;
	col = (int)move_string[1] - 96;
		
	if(isalpha(move_string[0])) {
		if(move_string[0] == 'F') {
			board[row][col].pop();
			players[player].flats += 1;
		}
		else if(move_string[0] == 'S') {
			board[row][col].pop();
			players[player].flats += 1;
		}
		else if(move_string[0] == 'C') {
			board[row][col].pop();
			players[player].caps += 1;
		}
	}
	else {
		count = 1;
		direction = move_string[3];
		if(direction == '+') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row-count][col].top();
					board[row-count][col].pop();
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
			if(stand==true)
				board[row-count+1][col].top().second = 'S';
		}
		else if(direction == '-') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row+count][col].top();
					board[row+count][col].pop();
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
			if(stand==true)
				board[row+count-1][col].top().second = 'S';
		}
		else if(direction == '>') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col+count].top();
					board[row][col+count].pop();
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
			if(stand==true)
				board[row][col+count-1].top().second = 'S';
		}
		else if(direction == '<') {
			for(int i=4; i<move_string.length(); i++) {
				for(int j=0; j<move_string[i]-'0'; j++) {
					stones[j] = board[row][col-count].top();
					board[row][col-count].pop();
				}
				for(int j=move_string[i]-1-'0'; j>=0; j--) {
					board[row][col].push(stones[j]);
				}
				count++;
			}
			if(stand==true)
				board[row][col-count+1].top().second = 'S';
		}
	}
	
}

deque<string> generate_stack_moves(deque<string> all_moves, int row, int col)
{
	int size = board[row][col].size();
	size=min(size,n);
	int i, j;
	string pos=(char)(col+96)+to_string(n-row+1);
	string move;
	
	bool capstop=false;
	if(board[row][col].top().second=='C') capstop=true;
	
	// generating moves for  -
	int index=0;
	int temp=row+1;
	int movelength=0;
	if(capstop==false)
	{
		while(temp<=n) {
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='S')
					break;
				else if(board[temp][col].top().second=='C')
					break;
			}
			index++;
			temp++;
		}
	}
	else
	{
		while(temp<=n) {
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='C')
					break;
				else if(board[temp][col].top().second=='S') {
					index++;
					break;
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
			if(movelength < index) {
				all_moves.push_back(possible[i][0]+pos+"-"+move);
			}
			else if(movelength==index) {
				if(capstop==true) { 
					 if(move[movelength-1]!='1')
						continue;
				}
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
		while(temp>0) {
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='S')
					break;
				else if(board[temp][col].top().second=='C')
					break;
			}
			index++;
			temp--;
		}
	}
	else
	{
		while(temp>0) {
			if(!board[temp][col].empty()) {
				if(board[temp][col].top().second=='C')
					break;
				else if(board[temp][col].top().second=='S') {
					index++;
					break;
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
			if(movelength < index){
				all_moves.push_back(possible[i][0]+pos+"+"+move);
			}
			else if(movelength == index){
				if(capstop==true) {
					if(move[movelength-1]!='1')
						continue;
				}
				all_moves.push_back(possible[i][0]+pos+"+"+move);
			}
			else
				break;
		}
	}
	
	//genrating moves for >
	index=0;
	temp=col+1;
	if(capstop==false)
	{
		while(temp<=n) {
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='S')
					break;
				else if(board[row][temp].top().second=='C')
					break;
			}
			index++;
			temp++;
		}
	}
	else
	{
		while(temp<=n) {
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='C')
					break;
				else if(board[row][temp].top().second=='S') {
					index++;
					break;
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
			if(movelength < index){
				all_moves.push_back(possible[i][0]+pos+">"+move);
			}
			else if(movelength == index){
				if(capstop==true) {
					if(move[movelength-1]!='1')
						continue;
				}
				all_moves.push_back(possible[i][0]+pos+">"+move);
			}
			else
				break;
		}
	}
	
	//generating moves for <
	index=0;
	temp=col-1;
	if(capstop==false)
	{
		while(temp>0) {
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='S')
					break;
				else if(board[row][temp].top().second=='C')
					break;
			}
			index++;
			temp--;
		}
	}
	else
	{
		while(temp>0) {
			if(!board[row][temp].empty()) {
				if(board[row][temp].top().second=='C')
					break;
				else if(board[row][temp].top().second=='S') {
					index++;
					break;
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
			if(movelength < index){
				all_moves.push_back(possible[i][0]+pos+"<"+move);
			}
			if(movelength == index){
				if(capstop==true) {
					if(move[movelength-1]!='1')
						continue;
				}
				all_moves.push_back(possible[i][0]+pos+"<"+move);
			}
			else
				break;
		}
	}
	
	return all_moves;
}

deque<string> generate_all_moves(int player) {
	deque<string> all_moves;
	string move;
	
	if(players[player].flats > 1) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				if(board[i][j].empty()) {
					move="F";
					move+= (char)(j+96) + to_string(n-i+1);
					all_moves.push_back(move);
					move[0]='S';
					all_moves.push_back(move);
				}
			}
		}
	}
	if(players[player].caps > 0) {
		for(int i=1; i<=n; i++) {
			for(int j=1; j<=n; j++) {
				if(board[i][j].empty()) {
					move="C";
					move += (char)(j+96) + to_string(n-i+1);
					all_moves.push_back(move);
				}
			}
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=n; j++) {
			if(!board[i][j].empty())
				if(board[i][j].top().first == player)
					all_moves = generate_stack_moves(all_moves, i, j);
		}
	}
	return all_moves;
}

bool checkvertical(int x,int y, int path[],int player)
{
	int i=x-1,j=y-1;
	if(board[x][y].empty()) return false;
	if(board[x][y].top().first!=player) return false;
	if(board[x][y].top().second=='S') return false;

	path[i*n+j]=1;
	if(x==n) return true;
	if(path[i*n+j+1]==0)
	{
		if(checkvertical(x,y+1,path,player))
		{
			return true;
		}
	}
	if(x!=1)
	{
		if(path[(i-1)*n+j]==0)
		{
			if(checkvertical(x-1,y,path,player))
				return true;
		}
	}
	if(x!=n)
	{
		if(path[(i+1)*n+j]==0)
		{
			if(checkvertical(x+1,y,path,player))
				return true;
		}
	}
	if(y!=1)
	{
		if(path[i*n+j-1]==0)
		{
			if(checkvertical(x,y-1,path,player))
				return true;
		}
	}
	path[i*n+j]=0;
	return false;


}


bool checkhorizontal(int x,int y, int path[],int player)
{
	int i=x-1,j=y-1;
	if(board[x][y].empty()) return false;
	if(board[x][y].top().first!=player) return false;
	if(board[x][y].top().second=='S') return false;
	path[i*n+j]=1;
	if(y==n) return true;

	if(path[(i+1)*n+j]==0)
	{
		if(checkhorizontal(x+1,y,path,player))
		{
			return true;
		}
	}
	if(x!=1)
	{
		if(path[(i-1)*n+j]==0)
		{
			if(checkhorizontal(x-1,y,path,player))
				return true;
		}
	}
	if(y!=n)
	{
		if(path[i*n+j+1]==0)
		{
			if(checkhorizontal(x,y+1,path,player))
				return true;
		}
	}
	if(y!=1)
	{
		if(path[i*n+j-1]==0)
		{
			if(checkhorizontal(x,y-1,path,player))
				return true;
		}
	}
	path[i*n+j]=0;
	return false;


}

bool winmove(string move,int player)
{
	bool stand=false;
	int i,j;
	execute_move(move,player,stand,true);
	// for(i=1;i<=n;i++)
	// {
	// 	for(j=1;j<=n;j++)
	// 	{
	// 		if(board[i][j].empty()) break;
	// 		if(board[i][j].top().first!=player) break;
	// 		if(board[i][j].top().second=='S') break;
	// 	}
	// 	if(j==n+1) {reverse_execute_move(move,player,stand); return true;}
	// }
	// for(i=1;i<=n;i++)
	// {
	// 	for(j=1;j<=n;j++)
	// 	{
	// 		if(board[j][i].empty()) break;
	// 		if(board[j][i].top().first!=player) break;
	// 		if(board[j][i].top().second=='S') break;
	// 	}
	// 	if(j==n+1) {reverse_execute_move(move,player,stand); return true;}
	// }
	// reverse_execute_move(move,player,stand);
	// return false;


	int numb=n*n;
	int path[numb];
	int k;
	for(k=0;k<numb;k++) path[k]=0;
	for(i=1;i<=n;i++)
	{
		;
		//cout<<xx<<" "<<player<<endl;
		if(checkvertical(1,i,path,player)) 
		{
			//cout<<"move found "<<i<<endl;
			reverse_execute_move(move,player,stand);
			return true;
		}
	}
	for(k=0;k<numb;k++) path[k]=0;
	for(i=1;i<=n;i++)
	{
		
		if(checkhorizontal(i,1,path,player))
		{
			//cerr<<"vertical "<<endl;
			reverse_execute_move(move,player,stand);
			return true;
		}
	}
	reverse_execute_move(move,player,stand);
	return false;




}



string losemove()
{
	string result="";
	int i;
	deque<string> oppmoves=generate_all_moves(1-player_num);
	int size=oppmoves.size();
	for(i=0;i<size;i++)
	{
		if(winmove(oppmoves[i],1-player_num))
		{
			result=oppmoves[i].substr(1,2);
		}
	}
	return result;
}


int recurse(deque<string> moves, int depth, int player,int alpha,int beta)
{
	// cout<<"\nDepth "<<depth<<" started in: "<<chrono::duration<double, milli>(chrono::high_resolution_clock::now()-t_start).count()<<"\n";

	int len=moves.size(), i, val, temp;
	if(depth>=(rand()%2+2))
	// if(depth>=3)
	{
		val = evaluate();   //value for first move
		if(player==player_num)
		{
			for(i=1;i<len;i++)
			{
				temp = evaluate();
				if(temp>val)
					val=temp;
			}
		}
		else
		{
			for(i=1;i<len;i++)
			{
				temp=evaluate();
				if(temp<val)
					val=temp;
			}
		}
	}
	else
	{
		if(player==player_num) {
			val = INT32_MIN;
			for(i=0;i<len;i++) {
				bool stand = false;
				execute_move(moves[i],player, stand, true);
				deque<string> all=generate_all_moves(player);
				
				if(all.size()>0)
					temp = recurse(all,depth+1,1-player,alpha,beta);
				else
					temp = evaluate();

				alpha=max(temp,alpha);
				if(alpha>=beta) {
					reverse_execute_move(moves[i],player, stand);
					return temp;
				}

				if(temp>val)
					val = temp;
				reverse_execute_move(moves[i],player,stand);
			}
		}
		else {
			val = INT32_MAX;
			for(i=0;i<len;i++) {
				bool stand = false;
				execute_move(moves[i],player, stand,true);
				deque<string> all=generate_all_moves(player);
				
				if(all.size()>0)
					temp = recurse(all,depth+1,1-player,alpha,beta);
				else
					temp = evaluate();
				beta=min(temp,beta);
				if(alpha>=beta) {
					reverse_execute_move(moves[i],player, stand);
					return temp;
				}
								
				if(temp<val)
					val = temp;
				reverse_execute_move(moves[i],player, stand);
			}
		}
	}
	return val;
}


int evaluate()
{
	int roadlength=checkroad();
	//out<<roadlength<<" " ;
	//if(roadlength==5) {return 10000*roadlength;}
	//cout<<"max= "<<roadlength<<endl;
	int sum=0,tempsize,maxlen,i,j;
	int stackfavour=70;
	if(players[1-player_num].flats-players[player_num].flats>=4) stackfavour=100;
	sum=100*roadlength;
	int mystones=0;
	int oppstones=1;
	for(i=1;i<=n;i++)
	{
		
		for(j=1;j<=n;j++)
		{
			if(!board[i][j].empty())
			{
				if(board[i][j].top().first==player_num) mystones++;
				else oppstones++;
				int tmpsize=board[i][j].size();
				if(tmpsize>=3){
					if(board[i][j].top().first==player_num)
					{
						if(board[i][j].top().second=='C')
							sum+=stackfavour*tmpsize;
						else
							sum+=(stackfavour-10)*tmpsize;
					}
					else
					{
					if(board[i][j].top().second=='C')
						sum=-stackfavour*tmpsize;
					else
						sum-=(stackfavour-10)*tmpsize;
					}
				}
			}
		}
	}
	// sum+=25*(mystones-oppstones);
	return sum;
}
int check(int row,int col,int hor,int ver,int arr[][8])
{
	int var1=ver;
	if(row!=n)
	{ 
		if(arr[row+1][col]==0){
		if(!board[row+1][col].empty())
		{ 
			if(board[row+1][col].top().first==player_num) 
			{
				if(board[row+1][col].top().second!='S')
				{arr[row+1][col]=1; 
				var1=check(row+1,col,hor,ver+1,arr);}
			}
		}
		}
	}
	int var2=hor;
	if(col!=n)
	{
		if(arr[row][col+1]==0){
		if(!board[row][col+1].empty())
		{
			if(board[row][col+1].top().first==player_num)
			{
				if(board[row][col+1].top().second!='S') 
				{
					arr[row][col+1]=1;
					var2=check(row,col+1,hor+1,ver,arr);}
			}
		}
		}
	}
	if(var1>var2) return var1;
	else return var2;
	
}

int checkroad()
{
	int arr[8][8];
	int i,j;
	for(i=0;i<=n;i++)
	{
		for(j=0;j<=n;j++)
			arr[i][j]=0;
	}
	int tmp=0,max=0;
	for(i=1;i<n;i++)
	{
		for(j=1;j<n;j++)
		{
			if(arr[i][j]==1) continue; 
			if(board[i][j].empty()) continue;
			if(board[i][j].top().first!=player_num) continue;
			
			if(board[i][j].top().second=='S') continue;
			arr[i][j]=1;
			tmp=check(i,j,1,1,arr);
			if(tmp>max) max=tmp;
		}
	}
	return max;
}

void play() {
	string move;
	bool stand = false;
	
	if(player_num == 1) {
		getline(cin,move);
		start = clock();
		
		// t_start = std::chrono::high_resolution_clock::now();
		execute_move(move,1, stand);
		
		if(move=="Fa1")
			move=string("F")+"a"+to_string(n);
		else
			move="Fa1";
		
		execute_move(move,0,stand);
		cout<<move<<"\n"<<flush;
		time_left -= (double)(clock() - start) / CLOCKS_PER_SEC;
		// time_left-=chrono::duration<double, milli>(chrono::high_resolution_clock::now()-t_start).count()/1000;
		
		getline(cin,move);
		start = clock();
		// t_start = std::chrono::high_resolution_clock::now();
		execute_move(move,0,stand);
	}
	else {
		// t_start = std::chrono::high_resolution_clock::now();
		start = clock();
		execute_move("Fa1",1,stand);
		cout<<"Fa1"<<"\n"<<flush;
		time_left -= double(clock() - start) / CLOCKS_PER_SEC;
		// time_left-=chrono::duration<double, milli>(chrono::high_resolution_clock::now()-t_start).count()/1000;
		
		getline(cin,move);
		start = clock();
		// t_start = std::chrono::high_resolution_clock::now();
		execute_move(move,0,stand);
	}
	
	while(true) {
		
		deque<string> all_moves = generate_all_moves(player_num);
		mul*=all_moves.size();
		
		if(time_left<=time_limit/10) {
			move = all_moves[rand()%all_moves.size()];
		}
		else {
			int temp_val;
			int squares_left = 0;
			for(int i=0; i<n; i++)
				for(int j=0; j<n; j++)
					if(board[i][j].empty())
						squares_left++;
			
			aim=time_left/(10+2*squares_left);
			
			bool tm=false;
			int l=all_moves.size(),i;
			for(i=0;i<l;i++)
			{
				if(winmove(all_moves[i],player_num))
				{
					move=all_moves[i];
					tm=true;
				}
			}
			
			if(tm==false){
				string address=losemove();
								string add="S"+address;
				if(address!="" && find(all_moves.begin(),all_moves.end(),add)!=all_moves.end())
				{
					move=add;
				}
				else{
				
					// calling recurse function for all moves of depth 0
					int val = INT32_MIN;
					for(int i=0;i<all_moves.size();i++) {
						bool stand2 = false;
						execute_move(all_moves[i],player_num,stand2,true);
						deque<string> all=generate_all_moves(player_num);
						int vecsize=all.size();
						
						if(all.size()>0)
							temp_val = recurse(all,1,player_num,INT32_MIN,INT32_MAX);
						else
							temp_val = evaluate();
										
						if(temp_val>val) {
							val = temp_val;
							move = all_moves[i];
						}
						reverse_execute_move(all_moves[i],player_num, stand2);
						
					}
				}
			}
		}
		execute_move(move,player_num, stand);
		cerr<<"\nTime left: "<<time_left<<"\n";
		cout<<move<<"\n"<<flush;
		time_left -= (double)(clock() - start) / CLOCKS_PER_SEC;
		// time_left-=chrono::duration<double, milli>(chrono::high_resolution_clock::now()-t_start).count()/1000;
		
		
		//print all valid moves
		// cerr<<"\n";
		// for(int i=0;i<all_moves.size();i++) {
			// cerr<<all_moves[i]<<"   ";
		// }
		// cerr<<"\n\n";
		
		//print the board
		// vector<vector<stack<pair<int,int>>>> temp(board);
		// for(int i=1; i<=n; i++) {
			// for(int j=1; j<=n; j++) {
				// if(temp[i][j].empty())
					// cerr<<"-";
				// while(!temp[i][j].empty()) {
					// cerr<<temp[i][j].top().first+1<<(char)temp[i][j].top().second<<" ";
					// temp[i][j].pop();
				// }
				// cerr<<"\t";
			// }
			// cerr<<"\n";
		// }
		// cerr<<"\n";
		
		getline(cin,move);
		start = clock();
		// t_start = std::chrono::high_resolution_clock::now();
		execute_move(move, 1-player_num, stand);
	}
	
	// for(int i=0; i<100000; i++) {
		// execute_move("Fa1", 1-player_num, stand);
		// execute_move("Sa2", player_num, stand);
		// deque<string> all_moves = generate_all_moves(player_num);
		// all_moves = generate_all_moves(player_num);
		// execute_move("Ca3", 1-player_num, stand);
		// all_moves = generate_all_moves(player_num);
		// execute_move("1a1+1", player_num, stand);
		// all_moves = generate_all_moves(player_num);
		// execute_move("2a2+2", 1-player_num, stand);
		// all_moves = generate_all_moves(player_num);
		// execute_move("3a3+111", player_num, stand);
		// all_moves = generate_all_moves(player_num);
	// }
	
}
