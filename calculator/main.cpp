#include <iostream>
#include <vector>
/*
float sum(float n1, float n2);
float sub(float n1, float n2);
float div(float n1, float n2);
float mul(float n1, float n2);
*/

void menu(void);
bool is_number(const std::string _s);

std::vector<double> nums = std::vector<double>();
std::vector<char> ops = std::vector<char>();
double currentNum = .0f;
double total = .0f;

enum OP_STATE
{
    NUMBER,
    OPERATOR,
    TOTAL
};

OP_STATE calState;

int main()
{
    calState = OP_STATE::NUMBER;
    bool isRunning = true;

    do
    {
        std::string opInput = "";
        std::string numInput = "";

        system("clear");
        std::cout << " ______________________________________" << std::endl;
        std::cout << "|                                      |" << std::endl;
        std::cout << "|         CALCULATOR BY KAL-SEC        |" << std::endl;
        std::cout << "|                                      |" << std::endl;
        std::cout << "|    + --->      Sum                   |" << std::endl;
        std::cout << "|    - --->      Subtraction           |" << std::endl;
        std::cout << "|    * --->      Multiplication        |" << std::endl;
        std::cout << "|    / --->      Division              |" << std::endl;
        std::cout << "|    = --->      Total                 |" << std::endl;
        std::cout << "|______________________________________|" << std::endl;

        std::cout << "\nOperation: \n";
        switch (calState)
        {

        case OP_STATE::NUMBER:
        {
            for (short unsigned n1 = 0; n1 < nums.size(); n1++)
                std::cout << nums[n1] << " " << ops[n1] << " ";

            std::cout << "\n\nType your number: ";
            std::cin >> numInput;

            if (!is_number(numInput))
                continue;

            nums.push_back(stod(numInput));
            calState = OP_STATE::OPERATOR;
            continue;
        }

        case OP_STATE::OPERATOR:
        {
            ops.push_back(' ');

            for (int n1 = 0; n1 < nums.size(); n1++)
                std::cout << nums[n1] << " " << ops[n1] << " ";

            std::cout << "\n\n";
            std::cout << "Type your operation type: ";
            std::cin >> opInput;

            if (opInput.length() != 1)
            {
                ops.pop_back();
                calState = OP_STATE::OPERATOR;
                continue;
            }

            if (opInput[0] == '+' || opInput[0] == '-' || opInput[0] == '/' || opInput[0] == '*')
            {
                ops[ops.size() - 1] = opInput[0];
                calState = OP_STATE::NUMBER;
                continue;
            }

            if (opInput[0] == '=')
            {
                ops[ops.size() - 1] = opInput[0];
                calState = OP_STATE::TOTAL;
                continue;
            }

            ops.pop_back();
            calState = OP_STATE::OPERATOR;
            continue;
        }

        case OP_STATE::TOTAL:
        {
            if (ops[ops.size() - 1] != '=')
            {
                calState = OP_STATE::OPERATOR;
                continue;
            }

            float total = .0f;

            for (int n1 = 0; n1 < nums.size(); n1++)
                std::cout << nums[n1] << " " << ops[n1] << " ";

            int prioritaryOpsCount = 0;
            for (int n = 0; n < ops.size(); n++)
            {
                while (ops[n] == '/')
                {
                    double _total = nums[n] / nums[n + 1];
                    nums.erase(nums.begin() + n, nums.begin() + (n + 1));
                    nums.insert(nums.begin() + n, _total);
                    ops.erase(ops.begin() + n);
                    continue;
                }

                while (ops[n] == '*')
                {
                    double _total = nums[n] * nums[n + 1];
                    nums.erase(nums.begin() + n, nums.begin() + (n + 1));
                    nums.insert(nums.begin() + n, _total);
                    ops.erase(ops.begin() + n);
                    continue;
                }
            }

            total = nums[0];

            for (unsigned short n = 1; n < nums.size(); n++)
            {
                if (ops[n - 1] == '-')
                    total -= nums[n];

                if (ops[n - 1] == '+')
                    total += nums[n];
            }

            std::string action = "";
            std::cout << total << std::endl
                      << std::endl;
            std::cout << "Do you want to do another operation? [Y/N]";
            std::cin >> action;

            if (action == "Y")
            {
                nums.clear();
                ops.clear();

                calState = OP_STATE::NUMBER;
            }
            else
            {
                nums.clear();
                ops.clear();
                exit(0);
            }
        }
        }

    } while (isRunning);

    return 0;
}

bool is_number(std::string _s)
{
    int dotCount = 0;
    bool isDigit = true;

    try
    {
        for (short unsigned n = 0; n < _s.length(); n++)
        {
            if (_s[n] == '.' || _s[n] == ',')
            {
                dotCount++;
                continue;
            }

            if (!std::isdigit(_s[n]))
                isDigit = false;
        }

        if (dotCount > 1)
            isDigit = false;

        int numInt = stoi(_s);
        float numFloat = stod(_s);
    }
    catch (...)
    {
        isDigit = false;
    }

    return isDigit;
}