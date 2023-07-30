#include <string>
#include <ctime>
#define MAX_KEY 50

class KeyClass
{
public:
	clock_t keydown[MAX_KEY];
	clock_t keyup[MAX_KEY];
	char keypressed[MAX_KEY];

	int total_presses;

	bool Validate();
	double GetHoldInterval(int index);
	double GetTransferInterval(int index);

	std::string ToString();
};