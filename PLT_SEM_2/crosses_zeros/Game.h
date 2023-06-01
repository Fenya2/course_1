#include <string>
#include <map>
namespace game
{
	/*
	 структура состояния игры в беззнаковом инте.
		  0000000000000|000000000|000000000
		               |1-------0|0-------0
		               |1-------9|8-------0
		               |крестики |нолики
	 поле
		________
		 |A|B|C|
		1| | | |
		2| | | |
		3| | | |
		--------
	*/
	bool validateTurn(const std::string&);
	unsigned int makeTurn(const std::string&,unsigned int);
	bool canMakeTurn(const std::string&,const unsigned int);
	std::string getFieldValue(const std::string&,unsigned int);
	char whoWon(unsigned int);
	unsigned long long generatePair(unsigned int,unsigned int);
	unsigned int getPairFirst(unsigned long long);
	unsigned int getPairSecond(unsigned long long);
	bool noTurns(const unsigned int);
	std::string to_string(unsigned int);

	extern const std::string turnsQueue[];
	extern const std::string fieldsStr[];
	extern const std::string turnsStr[];
}
