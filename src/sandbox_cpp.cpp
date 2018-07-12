//============================================================================
// Name        : sandbox_cpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "msg.h"

using namespace std;

dispacher MyDispacher;

class IO
{
public:
	IO(){
		MyDispacher.reg(0x01, std::bind(&IO::bt_msg, this, std::placeholders::_1));
	}

	void bt_msg(std::shared_ptr<Imsg> msg)
	{
		std::shared_ptr<wifi_status>derived_msg = std::dynamic_pointer_cast<wifi_status>(msg);
		cout<<"Fui Chamado\n";
		printf("Status = %d\n", derived_msg->get_status());
	}
};

int main() {
	IO MyIO;


	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	std::shared_ptr<wifi_status> p_msg = std::make_shared<wifi_status>(1);
	MyDispacher.new_msg(p_msg);

	return 0;
}
