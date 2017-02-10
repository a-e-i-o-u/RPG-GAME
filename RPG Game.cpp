#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "Map.h"

using namespace std;

void Start();
void Print();
void getAction();
void Attack();
void Move(int, int, int, int);
void changeMap(int, int);
void Options();


struct Character { 
	/*struct é o mesmo que class só que em vez de os membros serem privados como padrão eles são publicos, ou seja,
	é como se aqui estivesse escrito "public:"*/
	int yPos, xPos, hp; //posição y,posição x,healthpoints (pontos de vida)
	Character(int yPos,int xPos,int hp) { 
		//Declara o construtor (função que é chamada quando o objecto é criado) da classe Character
		this->yPos = yPos; //yPos da classe Character é igual ao parametro yPos cujo identifier é o mesmo
		this->xPos = xPos; //xPos da classe Character é igual ao parametro xPos cujo identifier é o mesmo
		this->hp = hp; //hp da classe Character é igual ao parametro hp cujo identifier é o mesmo
	}
};
struct Player : Character{
	Player(int yPos,int xPos,int hp) : Character(yPos,xPos,hp){} 
	/*Declara o construtor da classe Player,que deriva da class Character:
	 Os valores inseridos nos parâmetros de Player() serão inseridos na mesma ordem nos parâmetros de Character
	 (automaticamente chama o construtor de Character)
	*/
}p(4, 5, 100); //Declara o objecto p, que vai ser o único objecto Player

bool game_on = true,last_wasEnemy = false; 
//Declara dois booleans,game_on e last_wasEnemy
unsigned int curMap;	//Unsigned to only have positive numbers only.

int main()
{
	//MENU
	cout << "WELCOME TO THE RPG GAME" << endl;
	cout << "1 - START GAME" << endl;
	cout << "2 - CONTINUE" << endl;   
	cout << "3 - OPTIONS" << endl;

	char choice = _getch(); //a variável choice é igual à próxima tecla que o utilizador pressionar

	switch (choice) {
	case '1': //Se choice é 1
		//NOVO JOGO COMEÇA
		curMap = 0; //O mapa é igual a 0
		Start(); //Chamar a função Start()
		
		break;
	case '2':
		break;   //AINDA POR FAZER
	case '3':
		break;
	}
	
	
    return 0;
}
void Start() {
	Map[curMap][p.yPos][p.xPos] = '@'; //O char na posição do player é igual a '@' ('@' é o char do player)
	Print(); //Printar uma vez

	while (game_on) { //Enquanto o jogo n acabou
		getAction(); //Chamar a função getAction()
		
	}
}
void Print() {
	system("cls"); //Limpar a consola
	for (int y = 0; y < 100; y++) {
		for (int x = 0; x < 100; x++) {
			if (Map[curMap][y][x] == NULL) break; //Se o char é nulo(Não faz parte do mapa), parar o loop
			cout << Map[curMap][y][x]; //Printar o character correspondente
		}
		if (Map[curMap][y][0] == NULL) break; //Se o char é nulo(Não faz parte do mapa), parar o loop
			cout << endl; //Descer uma linha na consola
	}
	cout << "Healthpoints: " << p.hp << endl; //Printar a vida do jogador
}
void getAction() {
	//Chama 4 vezes a função Move(), para captar os movimentos cima,baixo,esquerda e direita
	Move(VK_UP, 'W', p.yPos - 1, p.xPos); 
	Move(VK_DOWN, 'S', p.yPos + 1, p.xPos);
	Move(VK_RIGHT, 'D', p.yPos, p.xPos + 1);
	Move(VK_LEFT, 'A', p.yPos, p.xPos - 1);
	//Chama a função Attack() para verificar se o player clicou na tecla 'F' (a tecla de atacar)
	Attack();
}
void Move(int key, int key2, int yNum, int xNum) {
	//Os argumentos da função: Tecla1,Tecla2,posição yNova,posição xNova
	if (GetAsyncKeyState(key) || GetAsyncKeyState(key2)) { //Se a tecla premida é uma das teclas nos argumentos
		if (Map[curMap][yNum][xNum] != '#') { //Se o char na posição que o player vai se mover é diferente de '#'
			if(last_wasEnemy) Map[curMap][p.yPos][p.xPos] = '$', last_wasEnemy = false;
			//Se last_wasEnemy é verdadeiro a posição que o player está é igual a '$' (se o player acabou de "partilhar o char" com um inimigo
			else Map[curMap][p.yPos][p.xPos] = ' '; //Se last_wasEnemy não é verdadeiro a posição em que o player está é igual a ' ' (o player sai da posição)
			if (Map[curMap][yNum][xNum] == 'E') p.hp -= 20, last_wasEnemy = true;
			//Se o char na posição em que o player deve se mover é 'E' (inimigo) o player perde 20 de vida e a var last_wasEnemy é verdadeira
			if (Map[curMap][yNum][xNum] == 'b' || Map[curMap][yNum][xNum] == 'B' || Map[curMap][yNum][xNum] == '|' 
			    || Map[curMap][yNum][xNum] == '_') { changeMap(yNum, xNum); return; }
			//Se o char na posição em que o player deve se mover é 'b','B','|' ou '_' chamar a função changeMap e logo a seguir terminar a função Move()
			
			p.yPos = yNum; 
			p.xPos = xNum;
			//Se não, a posição y do player é igual à posição yNova e a posição x é igual à posição xNova
			Map[curMap][p.yPos][p.xPos] = '@'; //O char na posição do player é igual a '@'

			Print(); //Chamar a função Print()
		}
	}
}
void Attack() {
	if (GetAsyncKeyState('F')) { //Se a tecla premida é 'F'
		if (Map[curMap][p.yPos + 1][p.xPos] == 'E') Map[curMap][p.yPos + 1][p.xPos] = '$';
		else if (Map[curMap][p.yPos - 1][p.xPos] == 'E') Map[curMap][p.yPos - 1][p.xPos] = '$';
		else if (Map[curMap][p.yPos][p.xPos + 1] == 'E') Map[curMap][p.yPos][p.xPos + 1] = '$';
		else if (Map[curMap][p.yPos][p.xPos - 1] == 'E') Map[curMap][p.yPos][p.xPos - 1] = '$';
		//Se o char nas posições acima referidas for 'E' esse char na tal posição é igual a '$'
		Print();
	}
}
void Options() {
	system("cls");


}
void changeMap(int yNum,int xNum) {
	switch (curMap) { //Se o mapa atual for:
	case 0: 
		if (Map[curMap][yNum][xNum] == 'b') { //Se o "edifício" for um bar
			curMap = 1; //O mapa atual muda para 1
			p.yPos = 2; //As posições do player mudam
			p.xPos = 1;
		}
		else if (Map[curMap][yNum][xNum] == 'B') {
			curMap = 2; //O mapa atual muda para 2
			p.yPos = 4; //As posições do player mudam
			p.xPos = 16;
		}
		break;
	case 1:
		curMap = 0; //O mapa atual muda para 0
		p.yPos = 6; //As posições do player mudam
		p.xPos = 2;
		break;
	case 2:
		curMap = 0; //O mapa atual muda para 0
		p.yPos = 2; //As posições do player mudam
		p.xPos = 6;
		break;
	}
	Map[curMap][p.yPos][p.xPos] = '@'; //O char na posição em que o player está é igual a '@'
	Print(); //Chamar a função Print()
}
