#include<iostream>
#include<string>
using namespace std;

void f1();
void f2();	//body nai, so prototype declared here

int main(int argc, char **argv) {


	cout << "No of arguments: " << argc << " which is: " << string(argv[0]) << endl;
	cout << "Inside Main, calling f1, f2, f1, f2" << endl;
	f1();
	f2();
	f1();
	f2();

	return 0;
}
