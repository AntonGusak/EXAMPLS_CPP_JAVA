// Декілька варіантів підрахунку щасливих квитків
#include <iostream>
using namespace std;

int main()
{
	system("color 1f");
	setlocale(LC_ALL, ".1251");

	int N, c, count;
	
	cout << "\n\tÏåðøèé âàðiàíò ðiøåííÿ:\n";
	cout << "\t-------------------------------------------\n";
	count = 0;
	for (int d = 0; d < 28; d++)
	{

		N = d;
		c = 0;
		cout << "\n\t(N<28)  ñóìà ïåðøèõ òðüîõ öèôð N=" << N;

		for (int q = 0; q < 10; q++) {
			for (int w = 0; w < 10; w++) {
				for (int e = 0; e < 10; e++) {
					for (int r = 0; r < 10; r++) {
						for (int t = 0; t < 10; t++) {
							for (int y = 0; y < 10; y++) {
								if ((q + w + e == r + t + y) && (q + w + e == N)) c++;
							}
						}
					}
				}
			}
		}
		cout << "\tóñüîãî òàêèõ ÷èñåë: " << c << "\n";
		count += c;
	}

	cout << "\n\n\tÎòæå óñüîãî ùàñëèâèõ êâèòêiâ ç 6-òèçíà÷íèì íîìåðîì: " << count;
	cout << "\n\n\t";
	
	cout << "\n\tÄðóãèé âàðiàíò ðiøåííÿ:\n";
	cout << "\t-------------------------------------------\n";
	count = 0;
	for (int d = 0; d< 28; d++)
	{
		N = d;
		c = 0;
		cout << "\n\t(N<28)  ñóìà ïåðøèõ òðüîõ öèôð N=" << N;

		//öèêë, ïåðåáèðàþùèé âñå âàðèàíòû ïåðâîé öèôðû 
		//òðåõçíà÷íîãî ÷èñëà
		for (int i = 0; i < 10; i++)
		{
			//âëîæåííûé öèêë, ïåðåáèðàþùèé âñå 
			//âàðèàíòû âòîðîé öèôðû
			for (int j = 0; j < 10; j++)
			{
				//óñëîâèå äëÿ òðåòüåé öèôðû
				if (N - i - j >= 0 && N - i - j < 10)
				{
					//ïîäñ÷åò ïîäõîäÿùèõ íîìåðîâ
					c++;
				}
			}
		}
		//óâåëè÷åíèå êîëè÷åñòâà â c ðàç äëÿ øåñòèçíà÷íîãî ÷èñëà
		cout << "\tóñüîãî òàêèõ ÷èñåë: " << c * c << "\n";

		count += (c*c);

	}

	cout << "\n\n\tÎòæå óñüîãî ùàñëèâèõ êâèòêiâ ç 6-òèçíà÷íèì íîìåðîì: " << count;
	cout << "\n\n\t";

	cout << "\n\tÒðåòié âàðiàíò ðiøåííÿ:\n";
	cout << "\t-------------------------------------------\n";
	count = 0;
	for (int d = 0; d < 28; d++)
	{

		N = d;
		c = 0;
		cout << "\n\t(N<28)  ñóìà ïåðøèõ òðüîõ öèôð N=" << N;

		for (int i = 0; i < 1000; i++)
		{
			int s = i % 10 + (i / 10) % 10 + (i / 100) % 10;
			if (s == N) c++;
		}
		cout << "\tóñüîãî òàêèõ ÷èñåë: " << c * c << "\n";

		count += (c*c);
	}

	
	cout << "\n\n\tÎòæå óñüîãî ùàñëèâèõ êâèòêiâ ç 6-òèçíà÷íèì íîìåðîì: " << count;
	cout << "\n\n\t";


	cout << "\n\n\t";
	system("pause");
	return 0;
}
