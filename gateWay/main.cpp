
#include <stdlib.h>
#include <string>
#include <iostream>
#include "Serial/inc/SerialClass.h"
#include "Serial/inc/Robot.h"

int main(){
	/*3 is COM3 of gateway*/
	int choice = 0;
	std::cout << "Please put your choice: 1(Receive),2(send). ";
	std::cin >> choice;

	while (choice != 1 || choice != 2){
		if (choice == 1 || choice == 2){
			break;
		}
		std::cout << "Please put your choice: 1(Receive),2(send). ";
		std::cin >> choice;
	}

	switch (choice){
		case 1:
			SerialReadTest(3);  
			break;
		case 2:
			SerialWriteTest(3);
			break;
	}
	system("pause");
	return 0;
}