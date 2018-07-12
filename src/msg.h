/*
 * msg.h
 *
 *  Created on: 12/07/2018
 *      Author: jcabral
 */

#ifndef MSG_H_
#define MSG_H_

#include <cstdint>
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>


static constexpr uint8_t N_TASKS = 9;
static constexpr uint8_t N_MSG =  2;


class Imsg
{
public:

	Imsg(uint8_t id): msgID(id){}

	uint8_t get_msg_ID() const
	{
		return msgID;
	}


	virtual ~Imsg(){}

	const uint8_t msgID;

protected:

};

class button: public Imsg
{
public:

	button(void): Imsg(0x00), button_number(0), duration(0){}

	uint8_t button_number;
	uint8_t duration;
};

class wifi_status: public Imsg
{
public:
	wifi_status(): Imsg(0x01), status(0){}
	wifi_status(uint8_t s):Imsg(0x01), status(s){}

	uint8_t get_status(void){return status;}
private:
	uint8_t status;
};


class dispacher
{
public:
	dispacher(){
		handler_list.resize(N_MSG);
		std::for_each(handler_list.begin(), handler_list.end(), [](std::vector< std::function<void(std::shared_ptr<Imsg>)> > i){
			i.reserve(N_TASKS);
		});
	}

	void reg(uint8_t id, std::function<void(std::shared_ptr<Imsg>)> f){
		// protected from task race
		handler_list[id].push_back(f);
	}

	void new_msg(std::shared_ptr<Imsg> m)
	{
//		uint8_t call_n_times = handler_list[m.get_msg_ID()].size();

		std::for_each(handler_list[m->get_msg_ID()].begin(), handler_list[m->get_msg_ID()].end(), [m](std::function<void(std::shared_ptr<Imsg>)> f){
			if(f != NULL)
			{
				f(m);
			}
		});
	}

protected:

	std::vector< std::vector< std::function<void(std::shared_ptr<Imsg>)> > > handler_list;
//	=
//			std::vector< std::vector< std::function<void(void)> > >(N_MSG, std::vector<std::function<void(void)> >(N_TASKS));
};



#endif /* MSG_H_ */
