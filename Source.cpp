

//  0 ISLAMABAD
//  1 RAWALPINDI
//  2 JHELUM
//  3 GUJRANWALA
//  4 LAHORE
//  5 SIALKOT
//  6 FAISALABAD
//  7 MULTAN
//  8 BAHAWALPUR
//  9 RAHIMYARKHAN
//  10 CHITRAL
//  11 MINGORA
//  12 MARDAN
//  13 PESHAWAR
//  14 BANNU
//  15 MIANWALI
//  16 ZHOB
//  17 DERA GHAZI KHAN
//  18 QUETTA
//  19 NOK KUNDI
//	20 GWADAR
//  21 SUKKUR
//  22 HYDERABAD
//  23 KARACHI


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctype.h>
#include<list>


using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class weightedgraph
{
private:
	int vertice;
	struct node
	{
		int connectedto;
		int weight;
	};

	int gsize;
	list<node> *arr;

	int **weights;
	int *smallestweight;
	bool *weightfound;

public:
	weightedgraph()
	{
		gsize = 0;
	}
	void setweightsmatrix(int, node);
	void readfile();
	void insert(int, node);
	void printadjlist();
	void printadjmatrix();
	void input();
	int asciisum(string);
	void shortestpath(int, int);
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weightedgraph::readfile()
{

	node obj;
	fstream infile;
	infile.open("uzair.txt");

	infile >> gsize;


	weights = new int*[gsize];
	for (int i = 0; i < gsize; i++)   // Making 1 D array and assigning value to every index/location equal to the value of array size
	{
		weights[i] = new int[gsize];
	}
	for (int i = 0; i < gsize; i++)  // Initializing 2D array, and "setting weight of each array to 9999" i.e so that those array in which we have to set value will have
		// the weight/distance, and all the remianing ones will have weight 9999 i.e infinity i.e no path from **** city to **** city
	{
		for (int j = 0; j < gsize; j++)
		{
			weights[i][j] = 9999;
		}
	}
	for (int i = 0; i < gsize; i++) //Assigning value of zero, if you want to travel within your city
	{
		weights[i][i] = 0;
	}


	smallestweight = new int[gsize];
	for (int i = 0; i < gsize; i++) //Setting smallest weight for each city to 0, so when we will calculate new distance from one city to another, than 
		//new value will be changes from 0 to the calculated value 
	{
		smallestweight[i] = 0;
	}

	weightfound = new bool[gsize];
	for (int i = 0; i < gsize; i++) //setting all weights to false
	{
		weightfound[i] = false;
	}

	arr = new list<node>[gsize]; //Assigning the size read from the file to the array, so that we can run the for loop
	for (int index = 0; index < gsize; index++)
	{
		infile >> vertice; // Read the city name (in our file, we have assigned number to each city)

		infile >> obj.connectedto; // Reading the name of city to which it is connected to 

		infile >> obj.weight;

		while (obj.connectedto != -999) // read this and pass the value in the row, until the file reads -999 means, that the row is over
		{
			insert(vertice, obj);
			setweightsmatrix(vertice, obj);
			infile >> obj.connectedto;
			if (obj.connectedto == -999) //Agar next city exist he nahi karta, matlab city ki jagah -999 para hua ha tou break kar jaye
				//otherwise vo obj.weight sa next city ka distance read karay ga
				break;
			infile >> obj.weight;
		}
	}
	infile.close(); // CLOSING FILE 
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weightedgraph::insert(int vertice, node obj)
{
	arr[vertice].push_back(obj); //insert element at the end 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weightedgraph::setweightsmatrix(int vertice, node obj)
{
	weights[vertice][obj.connectedto] = obj.weight; //  The weight array will have first city, obj.connected will have the city which we want to go, and this 2D
	//array will have value which is equal to the distance between them
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void weightedgraph::printadjlist()
{
	cout << setw(30) << "ADJACENCY LIST" << endl;

	cout << "\nGRAPH SIZE: " << gsize << endl << endl;

	node temp;
	list <node>::iterator it;            //function for printing the elements in a list 

	for (int i = 0; i < gsize; i++)
	{
		cout << i << "-> ";
		for (it = arr[i].begin(); it != arr[i].end(); it++)
		{
			temp = *it;
			cout << "CT: " << temp.connectedto << " ";
			cout << "W: " << temp.weight << " ";
			cout << "\t";
		}
		cout << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weightedgraph::printadjmatrix()
{
	cout << setw(30) << "ADJACENCY MATRIX" << endl;

	cout << "\nGRAPH SIZE: " << gsize << endl << endl;

	cout << "   ";                             //printing space at first 
	for (int i = 0; i < gsize; i++)
	{
		cout << i << " ";                       //printing the row first 
	}
	cout << endl;
	for (int i = 0; i < gsize; i++)
	{
		cout << i; //Ye first city ka naam show karay ga
		cout << "  ";
		for (int j = 0; j < gsize; j++)
		{
			cout << weights[i][j] << " "; //Ye agar us city sa directly connected ho ga tou us city tak ka distance show karay ga, warna ye 9999 show karay ga
			//Uzair ne ye is liye daala ha k agar ye apny aap sa apny aap tak ka distance poochay ga tou ye zero show karay ga
		}
		cout << endl;
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void weightedgraph::input()
{
	cout << setw(30) << "SHORTEST PATH FINDER" << endl;

	string text;
	int a = 0;
	int b = 0;
	int start = 0;
	int end = 0;

	cout << "Enter Starting point:";
	getline(cin, text);
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == ' ')
		{
			text.erase(i, 1);
			i = i - 1;
		}
		else
			text[i] = tolower(text[i]);
	}
	a = asciisum(text);

	switch (a)
	{
	case 926:
		cout << "ISLAMABAD" << endl;
		start = 0;
		break;
	case 1067:
		cout << "RAWALPINDI" << endl;
		start = 1;
		break;
	case 645:
		cout << "JHELUM" << endl;
		start = 2;
		break;
	case 1068:
		cout << "GUJRANWALA" << endl;
		start = 3;
		break;
	case 635:
		cout << "LAHORE" << endl;
		start = 4;
		break;
	case 759:
		cout << "SIALKOT" << endl;
		start = 5;
		break;
	case 1016:
		cout << "FAISALABAD" << endl;
		start = 6;
		break;
	case 657:
		cout << "MULTAN" << endl;
		start = 7;
		break;
	case 1063:
		cout << "BAHAWALPUR" << endl;
		start = 8;
		break;
	case 1279:
		cout << "RAHIMYARKHAN" << endl;
		start = 9;
		break;
	case 743:
		cout << "CHITRAL" << endl;
		start = 10;
		break;
	case 749:
		cout << "MINGORA" << endl;
		start = 11;
		break;
	case 627:
		cout << "MARDAN" << endl;
		start = 12;
		break;
	case 859:
		cout << "PESHAWAR" << endl;
		start = 13;
		break;
	case 532:
		cout << "BANNU" << endl;
		start = 14;
		break;
	case 850:
		cout << "MIANWALI" << endl;
		start = 15;
		break;
	case 435:
		cout << "ZHOB" << endl;
		start = 16;
		break;
	case 1361:
		cout << "DERA GHAZI KHAN" << endl;
		start = 17;
		break;
	case 660:
		cout << "QUETTA" << endl;
		start = 18;
		break;
	case 867:
		cout << "NOK KUNDI" << endl;
		start = 19;
		break;
	case 630:
		cout << "GWADAR" << endl;
		start = 20;
		break;
	case 677:
		cout << "SUKKUR" << endl;
		start = 21;
		break;
	case 932:
		cout << "HYDERABAD" << endl;
		start = 22;
		break;
	case 723:
		cout << "KARACHI" << endl;
		start = 23;
		break;
	}


	cout << "Enter Ending point:";
	getline(cin, text);
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == ' ')
		{
			text.erase(i, 1);
			i = i - 1;
		}
		else
			text[i] = tolower(text[i]);
	}
	b = asciisum(text);

	switch (b)
	{
	case 926:
		cout << "ISLAMABAD" << endl;
		end = 0;
		break;
	case 1067:
		cout << "RAWALPINDI" << endl;
		end = 1;
		break;
	case 645:
		cout << "JHELUM" << endl;
		end = 2;
		break;
	case 1068:
		cout << "GUJRANWALA" << endl;
		end = 3;
		break;
	case 635:
		cout << "LAHORE" << endl;
		end = 4;
		break;
	case 759:
		cout << "SIALKOT" << endl;
		end = 5;
		break;
	case 1016:
		cout << "FAISALABAD" << endl;
		end = 6;
		break;
	case 657:
		cout << "MULTAN" << endl;
		end = 7;
		break;
	case 1063:
		cout << "BAHAWALPUR" << endl;
		end = 8;
		break;
	case 1279:
		cout << "RAHIMYARKHAN" << endl;
		end = 9;
		break;
	case 743:
		cout << "CHITRAL" << endl;
		end = 10;
		break;
	case 749:
		cout << "MINGORA" << endl;
		end = 11;
		break;
	case 627:
		cout << "MARDAN" << endl;
		end = 12;
		break;
	case 859:
		cout << "PESHAWAR" << endl;
		end = 13;
		break;
	case 532:
		cout << "BANNU" << endl;
		end = 14;
		break;
	case 850:
		cout << "MIANWALI" << endl;
		end = 15;
		break;
	case 435:
		cout << "ZHOB" << endl;
		end = 16;
		break;
	case 1361:
		cout << "DERA GHAZI KHAN" << endl;
		end = 17;
		break;
	case 660:
		cout << "QUETTA" << endl;
		end = 18;
		break;
	case 867:
		cout << "NOK KUNDI" << endl;
		end = 19;
		break;
	case 630:
		cout << "GWADAR" << endl;
		end = 20;
		break;
	case 677:
		cout << "SUKKUR" << endl;
		end = 21;
		break;
	case 932:
		cout << "HYDERABAD" << endl;
		end = 22;
		break;
	case 723:
		cout << "KARACHI" << endl;
		end = 23;
		break;
	}

	shortestpath(start, end);

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int weightedgraph::asciisum(string letter)
{
	int sum = 0;
	for (int i = 0; i < letter.size(); i++)
	{
		char x = letter[i];
		sum = sum + int(x);
	}
	cout << "SUM:" << sum << endl;
	return sum;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void weightedgraph::shortestpath(int start, int end)
{
	for (int i = 0; i < gsize; i++)
	{
		smallestweight[i] = weights[start][i]; //Searching array for Starting City
	}
	weightfound[start] = true;
	smallestweight[start] = 0;  //This array will have calculate the sum of all weights

	for (int i = 0; i < gsize - 1; i++)
	{
		double minweight = DBL_MAX;                    //maximum value 
		int v;
		for (int j = 0; j < gsize; j++)
			if (!weightfound[j]) // Agar oper weight found ho gaya tou ye condition chal paray gi, it means that if we have ISB, then this condition will be false and it will not run 
				if (smallestweight[j] < minweight)
				{
					v = j;
					minweight = smallestweight[v];
				}
		weightfound[v] = true;
		for (int j = 0; j < gsize; j++)
			if (!weightfound[j])
				if (minweight + weights[v][j] < smallestweight[j])
					smallestweight[j] = minweight + weights[v][j];
	}


	cout << endl;
	for (int i = 0; i < gsize; i++)
	{
		cout << "INDEX(" << i << "): " << smallestweight[i] << endl;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	weightedgraph g;
	g.readfile();

	char choice = NULL;
	cout << setw(30) << "Welcome to PTDC Tour Guide Application" << endl << endl;
	cout << "(1) Print Adjacency List\n(2) Print Adjacency Matrix\n(3) Find Shortest Path\n(e) EXIT\n";

	while (1)
	{
		cin >> choice;

		switch (choice)
		{

		case '1':
			g.printadjlist();
			break;
		case '2':
			g.printadjmatrix();
			break;
		case '3':
			cin.ignore();
			g.input();
			break;
		case 'E':
		case 'e':
			cout << "Thank you!\n";
			exit(0);
			break;
		default:
			cout << "Not a valid choice. Select again!\n";
			break;
		}
		cout << endl;
		cout << setw(30) << "Welcome to PTDC Tour Guide Application" << endl << endl;
		cout << "(1) Print Adjacency List\n(2) Print Adjacency Matrix\n(3) Find Shortest Path\n(e) EXIT\n";
	}
}