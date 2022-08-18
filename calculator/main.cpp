#include <iostream>
/*
float sum(float n1, float n2);
float sub(float n1, float n2);
float div(float n1, float n2);
float mul(float n1, float n2);
*/

void menu(void);

int main()
{
    bool isRunning = true;

    do
    {
        int opIdx = 0;

        system("clear"); 
        std::cout << "***** CALCULATOR BY KAL-SEC *****" << std::endl << std::endl;
        std::cout << "1 -> Sum" << std::endl;
        std::cout << "2 -> Subtraction" << std::endl;
        std::cout << "3 -> Multiplication" << std::endl;
        std::cout << "4 -> Division" << std::endl;
        std::cout << "5 -> Exit" << std::endl;
    
        std::cout << "\nChoose your operation: ";
        std::cin >> opIdx;

    }
    while(isRunning);

    return 0;
}

void menu(void)
{

}