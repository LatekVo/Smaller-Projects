#include <iostream>
#include <cmath>
#include <string>
int main(){
	std::string algo;
	char screen[80][40];
	while(1){		
		for(int y = 0; y < 40; y++){
			for(int x = 0; x < 80; x++){
				screen[x][y] = '`';
			}
		}

		//CALCULATION
		int i = 0;
		int in_algoType;
		int in_algo;
		while(1){
			std::cout << "Algorithm type: " << std::endl
				  << "1. Classic bigO's" << std::endl
				  << "2. Function waves" << std::endl;
			std::cin >> in_algoType;
			switch(in_algoType){
				case 1:
					std::cout << "Curve: " << std::endl
						  << "0 - Go Back" << std::endl
						  << "1. n" << std::endl
						  << "2. log(n)" << std::endl
						  << "3. n log(n)" << std::endl	
						  << "4. n^2" << std::endl
						  << "5. 2^n" << std::endl
						  << "6. n^n" << std::endl;
					std::cin >> in_algo;
					if(in_algo == 0) break;
					if(in_algo > 6 || in_algo < 0) continue;
				break;
				case 2:
					std::cout << "Curve: " << std::endl
						  << "0 - Go Back" << std::endl
						  << "1. cos(n*10) " << std::endl
						  << "2. mod6(n)^2" << std::endl
						  << "3. (10/x)^x  (x*5)" << std::endl;
					std::cin >> in_algo;
					if(in_algo == 0) break;
					if(in_algo > 3 || in_algo < 0) continue;
				break;
			}
			if(in_algo == 0) continue;
			break;
		}
		for(int x = 0; x < 80; x++){
			int iBackup = i;
			int p = 1;
			switch(in_algoType){
				case 1:
					switch(in_algo){
						case 1:	
							//n
							i = x;
						break;
						case 2:
							//log(n)
							i = (int)(std::round(std::log(x+1)));
						
						break;
						case 3:	
							//n log(n)
							i = (int)(std::round(x*std::log(x+1)));
						break;	
						case 4:
							//n^2
							i = x*x;
						break;
						case 5:
							//2^n
							
							i = std::pow(2, x);
						break;
						case 6:
							//n^n
							i = std::pow(x, x);
						break;
						//no default on porpouse
					}
				break;
				case 2:
					switch(in_algo){
						case 1:
							//cos(n*10)
							i = std::cos(x*10*3.14159/180)*12+20;
						break;
						case 2:
							//mod7(n) log n
							i = (int)(x%7*std::log(x%7));
						break;
						case 3:
							if(x == 0){i = 1; break;}
							i = (int)(std::pow( ( (float)(10) / ((float)(x)/5)), ((float)(x)/5) ) );
						break;
					}
				break;
			}

			bool offLimit = false;	
			if(i < 0) i = 0, offLimit = true;
			if(i > 39) i = 39, offLimit = true;
			
			if(!offLimit) screen[x][i] = '*';
			int offset = 0;
			if(i > iBackup) offset = 1;
			if(i < iBackup) offset = -1;
			if(std::abs(i - iBackup) >! 39){//removing artifacts
				if(offset > 0){	
					for(int a = iBackup+offset; a < i; a++){
						screen[x][a] = '*';
					}
				}else if(offset < 0){
					for(int a = iBackup+offset; a > i; a--){
						screen[x][a] = '*';
					}
				}
			}
		}
		//END OF CALCULATION

		std::system("clear");
		std::cout << "Simulation: " << std::endl;
		for(int y = 39; y >= 0; y--){
			std::cout << y << "\t"; 
			for(int x = 0; x < 80; x++){
				std::cout << screen[x][y] << " ";
			}
			std::cout << std::endl; 
		}
		switch(in_algoType){
			case 1:
				switch(in_algo){	
					case 1:	
						//n
						algo = "n";
					break;
					case 2:
						//log(n)
						algo = "log(n)";
					
					break;
					case 3:	
						//n log(n)
						algo = "n log(n)";
					break;	
					case 4:
						//n^2
						algo = "n^2";
					break;
					case 5:
						//2^n
						algo = "2^n";
					break;
					case 6:
						//n^n
						algo = "n^n";
					break;
					//no default on porpouse
				}
			break;
			case 2:
				switch(in_algo){
					case 1:
						algo = "cos(n)";
					break;
					case 2:
						algo = "mod(n)";
					break;
					case 3:
						algo = "(10/x)^x  (x*5)";
					break;
				}
			break;
		}
		std::cout << in_algoType << ": " << in_algo << ": " << algo << std::endl;
		std::cout << "Press any key to continue...";
		std::string placeholder;
		std::getline(std::cin.ignore(), placeholder);
		std::cout << std::endl;
	}
}
