#ifndef GAME_H
#define GAME_H

#include "Game.h"

enum board
{
	CA1=0b00000000000000100000000000000000,
	CA2=0b00000000000000010000000000000000,
	CA3=0b00000000000000001000000000000000,
	CB1=0b00000000000000000100000000000000,
	CB2=0b00000000000000000010000000000000,
	CB3=0b00000000000000000001000000000000,
	CC1=0b00000000000000000000100000000000,
	CC2=0b00000000000000000000010000000000,
	CC3=0b00000000000000000000001000000000,
	ZA1=0b00000000000000000000000100000000,
	ZA2=0b00000000000000000000000010000000,
	ZA3=0b00000000000000000000000001000000,
	ZB1=0b00000000000000000000000000100000,
	ZB2=0b00000000000000000000000000010000,
	ZB3=0b00000000000000000000000000001000,
	ZC1=0b00000000000000000000000000000100,
	ZC2=0b00000000000000000000000000000010,
	ZC3=0b00000000000000000000000000000001,
};
	const std::string game::turnsQueue[] {"C","Z"};
	const std::string game::fieldsStr[] {"A1","A2","A3","B1","B2","B3","C1","C2","C3"};
	const std::string game::turnsStr[] {"CA1","CA2","CA3","CB1","CB2","CB3","CC1","CC2","CC3","ZA1","ZA2","ZA3","ZB1","ZB2","ZB3","ZC1","ZC2","ZC3"};
	constexpr unsigned int outcomes[16] {board::CA1|board::CA2|board::CA3,board::CB1|board::CB2|board::CB3,board::CC1|board::CC2|board::CC3,board::CA1|board::CB1|board::CC1,board::CA2|board::CB2|board::CC2,board::CA3|board::CB3|board::CC3,board::CA1|board::CB2|board::CC3,board::CA3|board::CB2|board::CC1,board::ZA1|board::ZA2|board::ZA3,board::ZB1|board::ZB2|board::ZB3,board::ZC1|board::ZC2|board::ZC3,board::ZA1|board::ZB1|board::ZC1,board::ZA2|board::ZB2|board::ZC2,board::ZA3|board::ZB3|board::ZC3,board::ZA1|board::ZB2|board::ZC3,board::ZA3|board::ZB2|board::ZC1};

bool game::validateTurn(const std::string& turn)
{
	if(turn.size()!=3)
		return false;
	if(!(turn[0]=='C'||turn[0]=='Z'))
		return false;
	if(turn[1]<'A'||turn[1]>'C')
		return false;
	if(turn[2]<'1'||turn[2]>'3')
		return false;
	return true;
}

unsigned int game::makeTurn(const std::string& turn, unsigned int state)
{
	unsigned int field=0b1;
	if(turn[0]=='C')
		field<<=9;
	field<<=(unsigned int)252-(3*turn[1]+turn[2]);
	return state|field;
}

bool game::canMakeTurn(const std::string& turn, const unsigned int state)
{
	unsigned int field=0b1;
	field<<=(unsigned int)252-(3*turn[1]+turn[2]);
	if(field&state)
		return false;
	field=0b1;
	field<<=9;
	field<<=(unsigned int)252-(3*turn[1]+turn[2]);
	if(field&state)
		return false;
	return true;
}

std::string game::getFieldValue(const std::string& turn, unsigned int state)
{
	if(!validateTurn(turn))
		return "E";
	unsigned int field=0b1;
	field<<=(unsigned int)252-(3*turn[1]+turn[2]);
	if(field&state)
		return "0";
	field=0b1;
	field<<=9;
	field<<=(unsigned int)252-(3*turn[1]+turn[2]);
	if(field&state)
		return "X";
	return " ";
}

char game::whoWon(unsigned int state)
{
	unsigned int check;
	for(int i=0;i<16;++i)
	{
		check=state&outcomes[i];
		if(check==outcomes[i])
		{
			if(i<8) return 'C';
			else return 'Z';
		}
	}
	return '0';
}

unsigned long long game::generatePair(unsigned int s1, unsigned int s2)
{
	long long ret=s1;
	ret<<=32;
	return ret+s2;
}

unsigned int game::getPairFirst(unsigned long long pair) {return pair>>32;}
unsigned int game::getPairSecond(unsigned long long pair) {return pair;} 

bool game::noTurns(const unsigned int state)
{
	for(int i=0;i<9;++i)
	{
		if(canMakeTurn(turnsStr[i],state))
			return false;
	}
	return true;
}

std::string game::to_string(unsigned int state)
{
	std::string header=" |A|B|C|";
	std::string ret="1| | | |\n2| | | |\n3| | | |\n";
	std::map<std::string,int> fields={{"CA1",2},{"CB1",4},{"CC1",6},{"CA2",11},{"CB2",13},{"CC2",15},{"CA3",20},{"CB3",22},{"CC3",24}};
	for(int i=0;i<9;++i)
		ret.replace(fields[turnsStr[i]],1,getFieldValue(turnsStr[i],state));
	return header+"\n"+ret;
}
#endif
