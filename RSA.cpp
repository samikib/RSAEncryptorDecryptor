#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

const std::string eoutfile = "incrypted.txt";
const std::string doutfile = "decrypted.txt";


bool isPrime(int n); //helper
int findP(int n);
int findQ(int n, int p);
void checkN(int n, int p, int q);
int eulersTotient(int n, int p, int q);
int gcd(int a, int b); //helper
void checkE(int n, int e);
int findingD(int e, int phi);
int lettertoNumber(char M); //helper
char numbertoLetter(int C); //helper
int encrypt(int e, int n, char M);
char decrypt(int d, int n, int C);
int calculateMod(int base, int exp, int modnum); //helper




int main(int argc, char* argv[])
{
	int e, n;
	char choice;
	std::string fileName;

	std::size_t pos;

	e = std::stoi(argv[1], &pos);
	n = std::stoi(argv[2], &pos);

	int p = findP(n);
	int q = findQ(n, p);

	choice = *argv[3];


	if (choice == 'e')
	{
		std::string letter;

		
		fileName = argv[4];

		const std::string fName = fileName;

		std::ifstream inFile;
		std::ofstream outFile;

		inFile.open(fName);
		outFile.open(eoutfile);

		while (!inFile.eof())
		{

			std::getline(inFile, letter);
			if (!inFile.fail())
			{
				for (int i = 0; i < letter.size(); i++)
				{
					if (i == 0)
					{
						outFile << encrypt(e, n, letter[i]);
					}
					else
					{
						outFile << " " << encrypt(e, n, letter[i]);
					}
				}

			}
		}																					
		inFile.close();
		outFile.close();
	}

	if (choice == 'd')
	{
		int code;
		int phi = eulersTotient(n, p, q);
		int d = findingD(e, phi);

		fileName = argv[4];
		const std::string fName = fileName;

		std::ifstream inFile;
		std::ofstream outFile;

		inFile.open(fName);
		outFile.open(doutfile);

		while (!inFile.eof())
		{
			inFile >> code;
			if (!inFile.fail())
			{
				outFile << decrypt(d, n, code);
			}
		}

		inFile.close();
		outFile.close();


	}

	return 0;
}




int main1()
{

	int e, n;
	char choice;
	std::string fileName;

	std::cout << "Enter private key (as e n): ";
	std::cin >> e >> n;

	int p = findP(n);
	int q = findQ(n, p);
	//checkN(n, p, q);

	std::cout << "Do you want to encrypt or decrypt (e/d): ";
	std::cin >> choice;


	if (choice == 'e')
	{
		std::string letter;

		std::cout << "What is the name of the file you wish to encrypt: ";
		std::cin >> fileName;
		const std::string fName = fileName;

		std::ifstream inFile;
		std::ofstream outFile;


		try
		{
			inFile.open(fName);

			if (!inFile.is_open())
			{
				throw std::runtime_error("Error reading file.");
			}

			outFile.open("encrypted.txt");
			if (!outFile.is_open())
			{
				throw std::runtime_error("Error writing to file.");
			}


			while (!inFile.eof())
			{
				
				std::getline(inFile, letter);
				if (!inFile.fail())
				{
					for (int i = 0; i < letter.size(); i++)
					{
						if (i == 0)
						{
							outFile << encrypt(e, n, letter[i]);
						}
						else
						{
							outFile << " " << encrypt(e, n, letter[i]);
						}
					}
					
				}
			}
		}
		catch (const std::exception& err)
		{
			std::cout << err.what();
		}

		inFile.close();
		outFile.close();


	}

	if (choice == 'd')
	{
		int code;
		int phi = eulersTotient(n, p, q);
		int d = findingD(e, phi);

		std::cout << "What is the name of the file you wish to decrypt: ";
		std::cin >> fileName;
		const std::string fName = fileName;

		std::ifstream inFile;
		std::ofstream outFile;


		try
		{
			inFile.open(fName);

			if (!inFile.is_open())
			{
				throw std::runtime_error("Error reading file.");
			}

			outFile.open("decrypted.txt");
			if (!outFile.is_open())
			{
				throw std::runtime_error("Error writing to file.");
			}

			while (!inFile.eof())
			{
				inFile >> code;
				if (!inFile.fail())
				{
					outFile << decrypt(d, n, code);
				}
			}
		}
		catch (const std::exception & err)
		{
			std::cout << err.what();
		}

		inFile.close();
		outFile.close();


	}

	return 0;
}

bool isPrime(int n)
{
	bool primeNums[842];

	for (int i = 0; i < 842; i++)
	{
		primeNums[i] = true;
	}

	primeNums[0] = false;
	primeNums[1] = false;

	for (int i = 2; i <= 29; i++)
	{
		if (primeNums[i] == true)
		{
			for (int j = (i * i); j < 842; j = j + i)
			{
				primeNums[j] = false;
			}
		}
	}
	return primeNums[n];
}

bool isPrimenonArr(int n)
{
	int rootN = pow(n, .5);

	if (n == 1 || n == 0)
	{
		return false;
	}

	for (int i = 2; i < rootN + 1; i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
}

int findP(int n)
{
	int rootN = pow(n, .5);

	for (int i = 0; i < rootN + 1; i++)
	{
		if (isPrime(i) && n % i == 0)
		{
			return i;
		}
	}

	return 1;
}

int findQ(int n, int p)
{
	return n / p;
}

void checkN(int n, int p, int q)
{
	if (isPrime(n) || !isPrime(q) || p == q)
	{
		throw std::runtime_error("n is not the factor of 2 distinct primes");
	}
}

int eulersTotient(int n, int p, int q)
{
	return ((p - 1) * (q - 1));
}

int gcd(int a, int b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return gcd(b, a % b);
	}
}

void checkE(int n, int e)
{
	int phi = eulersTotient(n, findP(n), findQ(n, findP(n)));

	if (gcd(phi, e) != 1)
	{
		throw std::runtime_error("e is not relatively prime with Euler's Totient of n.");
	}
}

int findingD(int e, int phi)
{
	for (int i = 2; i < phi; i++)
	{
		if ((((i * e) - 1) % phi) == 0)
		{
			return i;
		}
	}

	return 1;
}

int lettertoNumber(char M)
{
	int m;

	if (M == ' ')
	{
		m = 28;
		return 28;
	}
	m = static_cast<int>(M);
	if (m >= 65 && m <= 90)
	{
		m = m - 63;
		return m;
	}
	if (m >= 97 && m <= 122)
	{
		m = m - 95;
		return m;
	}
	else
	{
		throw std::runtime_error("Invalid character for encryption. Only alphabetic characters and spaces are allowed.");
	}
}

char numbertoLetter(int C)
{
	if (C == 28)
	{
		return ' ';
	}
	else
	{
		return static_cast<char>(C + 63);
	}
}

int encrypt(int e, int n, char m)
{
	int M = lettertoNumber(m);
	int C = calculateMod(M, e, n);
	if (C < 0)
	{
		C = C + n;
	}

	return C;
}

char decrypt(int d, int n, int C)
{
	int m = calculateMod(C, d, n);
	return numbertoLetter(m);
}

int calculateMod(int base, int exp, int modnum)
{
	if (exp == 1)
	{
		return base % modnum;
	}
	if (exp % 2 == 1)
	{
		return (calculateMod(base, 1, modnum) * calculateMod(base, exp - 1, modnum)) % modnum;
	}
	if (exp % 2 == 0)
	{
		base = (base * base) % modnum;
		return calculateMod(base, exp / 2, modnum) % modnum;
	}
}
