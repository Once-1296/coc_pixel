#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<fstream>
#include<bitset>
#include<sstream>
using namespace std;
string bintostr(string in)
{
	string ans = "";
	stringstream sstream(in);
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		ans += char(bits.to_ulong());
	}
	return ans;
}
int main()
{
	sf::Image image;
	//image.loadFromFile("pixel.jpeg");
	if (!image.loadFromFile("pixel3.jpeg"))cout << "NOT FOUND";
	std::fstream file("binary.txt", ios::out);
	for (int i = 0; i < 1600; i+=50)
	{
		for (int j = 0; j < 1600; j+=50)
		{
			int stj = j,sti=i;
			int bc = 0, wc = 0;
			while(i<sti+50)
			{
				while (j < stj + 50)
				{
					sf::Color pixel = image.getPixel(j, i);
					if (pixel == sf::Color::Black)bc++;
					else wc++;
					j++;
				}
				j = stj;
				i++;
			}
			if (bc > wc)file << "0";
			else file << "1";
			i = sti;
			j = stj;
		}
		file << "\n";
	}
	file.close();
	fstream f2("binary.txt", ios::in);
	vector<vector<char>>grid(32,vector<char>(32));
	string line;
	int i = 0, j = 0;
	while (getline(f2, line))
	{
		for (auto& a : line)
		{
			grid[i][j] = a;
			j++;
		}
		cout << j << "\n";
		j = 0;
		i++;
	}
	fstream f3("binzig.txt",ios::out);
	int ti = 31, tj = 31;
	bool md = 1;
	int cnt = 0;
	while (true)
	{
		f3 << grid[ti][tj] << grid[ti][tj - 1];
		cout<<grid[ti][tj] << grid[ti][tj - 1];
		cnt+=2;
		if (cnt >= 1024)break;
		if (md)
		{
			if (ti == 0)
			{
				tj -= 2;
				md = 0;
			}
			else ti--;
		}
		else
		{
			if (ti == 31)
			{
				tj -= 2;
				md = 1;
			}
			else ti++;
		}
	}
	f3.close();
	fstream f4("binzig.txt", ios::in);
	string strb;
	getline(f4, strb);
	cout << "\n";
	cout << bintostr(strb);
	fstream f5("binbin.txt", ios::in);
	string t2;
	getline(f5, t2);
	cout << "\n";
	if (t2 == bintostr(strb))cout << "yayayyyyyy\n";
	return 0;
}
