#include <iostream>
#include <windows.h>
#include <fstream>
#include <ctime>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class User { //класс пользователя

	public:
		string user_name = "";
		float user_mov = 0.0;
		int user_kp = 1000;
		int user_wins=0;

		User(){
			this->user_name = "";
			this->user_mov = 0.0;
			this->user_kp = 0;
			this->user_wins = 0;
		}

		User(string user_name, float user_mov, int user_kp, int user_wins) {
			this->user_name=user_name;
			this->user_mov=user_mov;
			this->user_kp=user_kp;
			this->user_wins=user_wins;
		}
		
		void printInfo() {
			cout<<user_name<<" "<<user_mov<<" "<<user_kp;
		}
};

class Table{
	public:
		int table_id;
		User* first_player;
		User* second_player;
		
		
};



int letterSizeCheck(string letter){ //проверка размера слова
	int name_length=0;
	for (int y=0; letter[y]!='\0'; y++){
			name_length++;
		}
	return name_length;
}

void printLetter(char letter,int letter_num,int letter_size){ //умный вывод символов
	if ((letter!=' ')&&(letter!='\0')&&(letter_num<letter_size)){
		cout<<letter;
	} else cout<<" ";
}

void showGrid(int user_count, int max_name_length, User* user) { //отрисовка турнирной сетки
	
	int i=0;
	int vertical_length=4;
	int mov_length=4;
	int kill_point_length=4;
	int length_grid=vertical_length+max_name_length+mov_length+kill_point_length+2;
	int letter_count=0;
	string mov[user_count];
	string kill[user_count];
	
	for(i=0; i<user_count;i++){
		mov[i]=to_string(user[i].user_mov);
		kill[i]=to_string(user[i].user_kp);
	}
	
	for (int x=0, i=-1; x<user_count+user_count+1; x++) {
		cout<<"\n";
		if(x%2==1){
			i++;
		}
		
		for(int y=0;y<length_grid;y++){
			if(x%2==0) { //??? ????uo ????
				cout<<"-";
			} else if((x%2!=0)&&((y==0)||(y==max_name_length+1)||(y==max_name_length+mov_length+2)||(y==max_name_length+mov_length+kill_point_length+3)||(y==max_name_length+mov_length+kill_point_length+5))) { //??? ????uo ???
				cout<<"|";
				letter_count=0;
			} else if((x%2!=0)&&(y!=0)&&(y<max_name_length+1)) { //????				
				printLetter(user[i].user_name[letter_count], letter_count, letterSizeCheck(user[i].user_name));
				letter_count++;
			} else if((x%2!=0)&&(y!=0)&&(y>max_name_length+1)&&(y<max_name_length+mov_length+2)) { //????				
				printLetter(mov[i][letter_count], letter_count, letterSizeCheck(mov[i]));
				letter_count++;
			} else if((x%2!=0)&&(y!=0)&&(y>max_name_length+1)&&(y>max_name_length+mov_length+2)&&(y<<max_name_length+mov_length+kill_point_length+3)) { //???
				printLetter(kill[i][letter_count], letter_count, letterSizeCheck(kill[i]));
				letter_count++;
			}
			else if((x%2!=0)&&(y!=0)&&(y>max_name_length+1)&&(y>max_name_length+mov_length+2)&&(y<<max_name_length+mov_length+kill_point_length+4)) { //???
				cout<<user[i].user_wins;
				letter_count++;
			}
		}
		
	}
	
	cout<<endl;
}



int participants(User* user,int user_count,int max_name_length=0){
	ofstream member_list("member.txt");
	for (int x=0; x<user_count; x++){
		if((x==user_count-1)&&(user_count%2==0)) {
			user[x].user_name="Proksibot";	
			member_list<<"["<<x<<"] - "<<user[x].user_name<<";";	
		} else{
			cout<<"Введите имя участника № "<<x<<"\n"; 
			cin>>user[x].user_name;
			member_list<<"["<<x<<"] - "<<user[x].user_name;
			if(x==user_count-1)
				member_list<<";";
			else member_list<<"\n";	
		}
		
		int name_length=0;
		name_length=letterSizeCheck(user[x].user_name);
		if(name_length>max_name_length){
			max_name_length=name_length;
		}
		cout<<"\n";
	}
	return max_name_length;
}

int participants_count(string file_output){
	int participant_count=1;
	for(int x=0; file_output[x]!='\0';x++){
		cout<<file_output<<"\n";
		if (file_output[x]=='\n'){
				participant_count++;
				cout<<"ya tut";
			}
	}
	return participant_count;
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUS");
	SetConsoleCP(1251);
  	SetConsoleOutputCP(1251);
	int game_stat=1;
	
	while(game_stat!=-1){ //Запуск приложения
		cout<<"Что вы хотите сделать?\n 1-Начать турнир\n 2-Продолжить турнир\n";
		cin>>game_stat;
		if (game_stat == 1){ //Создание турнира
			cout<<"Введите количество игроков\n";
			int user_count=0;
			int max_name_length=0;
			cin>>user_count;
			if(user_count%2==1) user_count++;
			User* user = new User[user_count];
			max_name_length=participants(user,user_count);
		
			showGrid(user_count,max_name_length,user);
			
		} else if(game_stat == 2){ //продолжение турнира
			
			int user_count = 0;
			string file_data=" ";
			int file_size=0;
			ifstream file_output("member.txt");
			
			do{
				getline(file_output, file_data);
				user_count++;
			}while(file_data[file_data.size()-1]!=';');
			
			User* user = new User[user_count+1];
			user_count=0;
			file_output.seekg( 0 );             
			int max_name_length=0;
			
			do{
				int x,size,letter_size=0;
				getline(file_output, file_data);
				size=letterSizeCheck(file_data);
				
				for(x=6;(x<size)&&(file_data[x]!='\n')&&(file_data[x]!=';');x++){
					user[user_count].user_name+=file_data[x];
					letter_size++;
				}
				
				if(letter_size>max_name_length)
					max_name_length=letter_size;
				
				user_count++;
			}while(file_data[file_data.size()-1]!=';');
			
			showGrid(user_count,max_name_length,user);
		}
	}
}