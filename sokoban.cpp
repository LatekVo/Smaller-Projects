#include <iostream>
#include <deque>
#include <thread>
#include <cstdlib>
#include <vector>

// #include "rawinput.h"

#include <unistd.h>
#include <termios.h>

class Term{
    private:
        struct termios old_tio, new_tio;
	bool safety = true;
    public:
        void init(){
            if(safety){	
                tcgetattr(STDIN_FILENO, &old_tio);
                new_tio=old_tio;
                new_tio.c_lflag &=(~ICANON & ~ECHO);
                tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
                safety = false;
            }
        }

        void kill(){
            tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
        }
};

int goals = 0, score = 0;
int xPos = 0, yPos = 0;
char game[20][20];

//	goto x	| goto y
bool mov(int x, int y){
	
	//NOTE: x y is where you want to move,
	//	not where you actually are.

	//left = -1 right = 1
	//down = -1 up = 1
	int xDir = x - xPos,  
	    yDir = y - yPos;

	if(game[x][y] == '`'){ //free space
		game[xPos][yPos] = '`';
		xPos = x; yPos = y;
		return true;
	}else if(game[x][y] == '#'){ //box + [ ]
		if(game[x+xDir][y+yDir] == '`'){ //box then air
			game[x+xDir][y+yDir] = '#';
			game[xPos][yPos] = '`';
			xPos = x; yPos = y;
			return true;
		}else if(game[x+xDir][y+yDir] == '_'){ //box goal
			game[x+xDir][y+yDir] = '=';
			score++;
			game[xPos][yPos] = '`';
			xPos = x; yPos = y;
			return true;	
		}else{ //box box
			return false;
		} 
	}else{//filled hole
		return false;
	}
}

int main(){
	Term term;
	term.init();

	/* BOARD FLIPPED FOR 
	 * CONVINIENCE, ITS NOW:
	 * 3 * - - *
	 * 2 |     |
	 * 1 |     |
	 * 0 * - - *
	 *   0 1 2 3 
	 * ------------------- */
	
	//screen init
	for(int y = 19; y >= 0; y--){ for(int x = 0; x < 20; x++){
			game[x][y] = '`';
	}	}
	
	char c;	

	//score = 0;
	goals = 4;
	//boxes = goals; //useless
	
	//MAP GEN
	std::vector<int> xTaken, yTaken;
	int boxes = 0; //not only boxes, overall taken spots
	for(int i = 0; i < goals; i++){
		//[0 to 17] + [1] = [1 to 18]
		int randXbox = rand()%18+1, 
		    randYbox = rand()%18+1;
		int randXgoal = rand()%18+1, 
		    randYgoal = rand()%18+1;
		if(randXbox == randXgoal && randYbox == randYgoal){
			i--;
			continue;
		}
		bool badBatch = false;
		for(int i = 0; i < boxes; i++){
			if(   (randXbox == xTaken[i] && randYbox == yTaken[i])
			   || (randXgoal == xTaken[i] && randYgoal == yTaken[i]) ){
				i--;
				//ahh, goto causes vim to freak out, fine then.
				badBatch = true;
			}
		}
		if(!badBatch){
			xTaken.push_back(randXbox); yTaken.push_back(randYbox);
			xTaken.push_back(randXgoal); yTaken.push_back(randYgoal);
			game[randXbox][randYbox] = '#';
			game[randXgoal][randYgoal] = '_';
		}
	}
	//END MAP GEN

	do{
		//std::thread timer (wait, 800);
		c=getchar();

		switch(c){
			case 'w': mov(xPos,yPos+1); break;
			case 's': mov(xPos,yPos-1); break;
			case 'a': mov(xPos-1,yPos); break;
			case 'd': mov(xPos+1,yPos); break;
			default: /*blank for now*/  break;
		}

		game[xPos][yPos] = 'O';
		
		system("clear");
		for(int y = 19; y >= 0; y--){
			
			for(int x = 0; x < 20; x++){
				std::cout << game[x][y] << " " << game[x][y] << " ";
			}std::cout << std::endl;
			
			for(int x = 0; x < 20; x++){
				std::cout << game[x][y] << " " << game[x][y] << " ";
			}std::cout << std::endl;
		}
		if(score == goals){
			std::cout << "Level clear" << std::endl;
			c = 'q';
		}
	}while(c != 'q');

	term.kill();
	return 0;
}
