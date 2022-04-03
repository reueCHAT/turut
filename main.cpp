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

		User(){
			this->user_name = "";
			this->user_mov = 0.0;
			this->user_kp = 0;
		}

		User(string user_name, float user_mov, int user_kp) {
			this->user_name=user_name;
			this->user_mov=user_mov;
			this->user_kp=user_kp;
		}
		
		void printInfo() {
			cout<<user_name<<" "<<user_mov<<" "<<user_kp;
		}
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
	int length_grid=vertical_length+max_name_length+mov_length+kill_point_length;
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
			if(x%2==0) { //�������� �������������� ������������
				cout<<"-";
			} else if((x%2!=0)&&((y==0)||(y==max_name_length+1)||(y==max_name_length+mov_length+2)||(y==max_name_length+mov_length+kill_point_length+3))) { //�������� ������������ ��������
				cout<<"|";
				letter_count=0;
			} else if((x%2!=0)&&(y!=0)&&(y<max_name_length+1)) { //����� ����
				printLetter(user[i].user_name[letter_count], letter_count, letterSizeCheck(user[i].user_name));
				letter_count++;
			} else if((x%2!=0)&&(y!=0)&&(y>max_name_length+1)&&(y<max_name_length+mov_length+2)) { //����� ����
				printLetter(mov[i][letter_count], letter_count, letterSizeCheck(mov[i]));
				letter_count++;
			} else if((x%2!=0)&&(y!=0)&&(y>max_name_length+1)&&(y>max_name_length+mov_length+2)&&(y<<max_name_length+mov_length+kill_point_length+3)) { //����� ��
				printLetter(kill[i][letter_count], letter_count, letterSizeCheck(kill[i]));
				letter_count++;
			}
		}
		
	}
	
	cout<<endl;
}


int participants(User* user,int user_count,int max_name_length=0){
	for (int x=0; x<user_count; x++){ // ���� ����� ������������� � ������
		cout<<"������� ������������ �"<<x<<"\n";
		cin>>user[x].user_name;
		int name_length=0;
		name_length=letterSizeCheck(user[x].user_name);
		if(name_length>max_name_length){
			max_name_length=name_length;
		}
		cout<<"\n";
	}
	return max_name_length;
}


int main(int argc, char** argv) {
	setlocale(LC_ALL, "RUS");
	int game_stat=1;
	
	while(game_stat!=-1){
		cout<<"��� �� ������ �������?\n 1-������� ������\n 2-���������� ����� ������";
		cin>>game_stat;
			cout<<"������� ������� ������ �� ������?\n";
			int user_count=0;
			int max_name_length=0;
			cin>>user_count;
			User* user = new User[user_count];
			
			max_name_length=participants(user,user_count);
			showGrid(user_count,max_name_length,user);
			return 0;
	}
}