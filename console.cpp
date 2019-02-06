#include "console.h"
#include <iomanip>

bool e_std::accept(const std::string question, const std::string match)
{
    std::string input;
    std::cout << question << "\n";

    std::cin >> input;

    if (match.compare(input) == 0) return true;
    else return false;
}

void e_std::store(const std::string question, std::string* storeTo)
{
    std::string input;
    std::cout << question << "\n";

    std::cin >> input;
    *storeTo = input;
}

int e_std::acceptIntln(const std::string question, const int range_bottom, const int range_top)
{
    return e_std::acceptInt(question+"\n", range_bottom, range_top);
}

int e_std::acceptInt(const std::string question, const int range_bottom, const int range_top)
{
    std::string input;

    std::cout << question;
    std::string::size_type size;

    std::cin >> input;
    int answer = 0;

    try
    {
        answer = (std::stoi(input, &size));
    }
    catch(const std::invalid_argument& ia)
    {
        std::cout << "Invalid argument: " << input << "!\n";
        return acceptInt(question, range_bottom, range_top);
    }

    if(answer == EXIT_CODE)
    {
        exit(1);
    }

    if((answer > range_top && range_top != NO_RANGE) || (answer < range_bottom && range_top != NO_RANGE))
    {
        std::cout << "Entered value not within range.\nMaximum: " << range_top << "\nMinimum: " << range_bottom <<"\n";
        return acceptInt(question, range_bottom, range_top);
    }

    return answer;
}

int e_std::loopAccept(const std::string question, const std::string match, std::string* storeTo,  const int type, const int range_bottom, const int range_top)
{
    bool invalid = true;
    int answer = 0;

    do
    {
        switch(type)
        {
            case ACCEPT:
            {
                invalid = accept(question, match);

                if(invalid)
                {
                    std::cout << "Invalid Answer!\n";
                }
            }
            break;
            case STORE:
            {
                store(question, storeTo);
                invalid = false;
            }
            break;
            case ACCEPT_INT:
            {
                answer = acceptInt(question, range_bottom, range_top);
                invalid = false;
            }
            break;
            default:
            {
                std::cout << "Invalid Accept Type!\n";
                invalid = false;
            }
        }
    }
    while(invalid);

    return answer;
}

void e_std::println(const std::string str)
{
    std::cout << str << "\n";
}

int e_std::randInt(int min, int max)
{
    return ((rand() % (max - min)) + min);
}

//Unix systems only
void e_std::clear()
{
	std::string clear = ESCAPE + "c";
    std::cout << clear.c_str();
}

void e_std::setColor(const int fore_color, const int back_color)
{
	std::cout << ESCAPE_COLOR << fore_color << ";" << back_color << "m";
}

void e_std::setFore(const int fore_color)
{
    std::cout << ESCAPE_COLOR << fore_color << "m";
}

void e_std::setTextAppearance(const int choice)
{
	std::cout << ESCAPE_COLOR << choice << "m";
}

void e_std::resetText()
{
	std::cout << ESCAPE_COLOR << 0 << "m";
}

void e_std::fill(const int num_spaces, const char c)
{
	std::cout << std::setfill(c) << std::setw(num_spaces);
}

void e_std::offset(const int amount)
{
	std::cout << std::setw(amount);
}

void e_std::printOffset(const int amount, const std::string str)
{
	std::cout << std::setw(amount);
	print(str);
}

void e_std::printlnOffset(const int amount, const std::string str)
{
	std::cout << std::setw(amount);
	println(str);
}

void e_std::print(const std::string str)
{
	std::cout << str;
}
