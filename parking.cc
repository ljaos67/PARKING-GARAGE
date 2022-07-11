/*************************************************************************************************************
CSCI 340 - Assignment 05 - Fall 2020

Programmer: Leonart Jaos
Z-ID: z1911688
Section: 0002
TA: Saiteja Alubelli
Date Due: Cctober 7th, 2020

Purpose: The purpose of this program is to implement the abstraction of a parking garage that accepts cars
in the back but has cars leave from the front. We use the structure 'CAR' to represent each collection of
traits that each car has. We store the cars in  deque, for it is the best structure to enable removal and
insertion at both ends. A car either arrives or departs. We read information on the car, such as the license
plate and its action, from standard input. When a car departs, we want to preserve its order, so we place the
cars from the front of the deque into the top of a stack until we can get the information of the car that is
leaving and pop that car out as well. The cars that were moved have their movement tracked, and are placed 
back into the deque-thus preserving the order. The arrivals and departures are also output as they come in 
from standard input. 

**************************************************************************************************************/

// pre-processing directives that allow usage of the deque and stack containers, the string class and 
// input/output
#include <iostream>
#include <deque>
#include <string>
#include <stack>

using namespace std;

// Definition for car. Each car has an ID based off arrival, a licence plate, and an int to track movements
typedef struct
{
	int id;		// id starts at 1
	string lp;	// license plate of car
	int no_mv;	// number of times the car has been moved
}CAR;

// Function used to interpret line input from standard input
// The line is captured in the main function and input as a string in the &line parameter
// A car struct also has its members passed inside so that they can be parsed from the string and changed
// in the car struct
// The action is always the first char, so when the index is at the beginning, the char captured is stored
// in a variable defined in main. That variable is used in an if statement to invoke the function for
// error, arrival, or departure. The license plate is also changed in the car object defined in main 
void get_input_vals(const string &line, char &act, string &lp)
{
	for(auto it=line.begin(); it!=line.end();++it)
		{
			if(it==line.begin())
			{
				act = *it;
			}
			else if((*it)==':')
			{
				continue;
			}
			else
			{
				lp=lp+(*it);
			}
		}
}

// This function pushes to the back of the deque a car with its parameters defined in main or from the 
// get_input_vals() function. The car is pushed, granted the garage isnt at max capacity with 10 cars.
// An error message is printed if the deque has 10 elements before insertion
void arrival(const CAR &car, deque<CAR> &D)
{
	cout << "Car " << car.id << " with license plate " << "\"" << car.lp << "\"" << " has arrived.\n";
	if(D.size() < 10)
	{
		D.push_back(car);
	}
	else
	{
		cout << "    But the garage has full!\n";
	}
	cout<< "\n";

}

// This function removes cars from the deque granted the license plate can be located. If the license
// plate cannot be found within any of the cars in the deque, an error message is printed
// each iteration through the deque checks for the license plate in each car. If the license plate is
// found, the members of the car are recorded and placed into variables and the car is popped from
// the deque.The loop ends with the break statement.
// If the current index is does not match the license plate, it is popped off from the 
// front of the deque and pushed into the stack for later.
// If the license plate was never found, the cars are put back and an error message is printed.
// So after poppping of the car and recording its date, the top of the stack is stored into the 
// front of the deque to maintain the original order.
// The departed car outputs its date members, including the movements, which were recorded into
// variables previously in the function 
void departure(const string &lp, deque<CAR> &D, stack<CAR> &S)
{
	CAR tmp;
	int NM=0;
	int NID=0;
	string lo="";
	bool flag=0;
	for(auto it=D.begin();it!=D.end();++it)
	{
		tmp=(*it);
		if(tmp.lp==lp)
		{
			flag=1;
			NM=tmp.no_mv;
			NID=tmp.id;
			lo=tmp.lp;
			D.pop_front();
			break;
		}
		else
		{
			tmp.no_mv++;
			S.push(tmp);
			D.pop_front();
		}
	}
	if(flag)
	{
		while(!S.empty())
		{
			D.push_front(S.top());
			S.pop();
		}
		cout << "Car " << NID <<" with license plate "<< "\"" << lo << "\"" <<" has departed,\n";
		if(NM==1)
		{
			cout << "    car was moved " << NM << " time in the garage.\n\n";
		}
		else
		{
			cout << "    car was moved " << NM << " times in the garage.\n\n";
		}
	}
	else
	{
		cout<<"No car with license plate "<< "\"" << lp << "\"" << " is in the garage.\n";
		while(!S.empty())
		{
			S.top().no_mv--;
			D.push_front(S.top());
			S.pop();
		}
	}
}
// main function declares the deques and stacks that we use along with the action taken from 
// standard input. The choice of function to invoke was stored into choice from the input_vals
// function, so that is how the correct action is invoked. 
int main()
{
	string input;
	deque<CAR> D;
	stack<CAR> S;
	int id1=1;
	char status;
	while(getline(cin,input))
	{
		CAR u;

		get_input_vals(input,status,(u.lp));

		if(status =='A')
		{
			u.id=id1;
			u.no_mv=1;
			arrival(u,D);
			id1++;
		}
		else if(status =='D')
		{
			departure(u.lp,D,S);
		}
		else
		{
			cout << "\'" << status << "\'" << ": invalid action!\n\n";

		}
	}


	return 0;
}
