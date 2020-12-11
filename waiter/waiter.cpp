#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/file_IO.h"
#include "../includes/externs.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder){
	return myIO.getNext(anOrder);
}

void Waiter::beWaiter() {
	int i = SUCCESS;
	while (i == SUCCESS) {
		ORDER anOrder;
		i = getNext(anOrder);
		order_in_Q.push(anOrder);
		cv_order_inQ.notify_all();
	}
	b_WaiterIsFinished = true;
	cv_order_inQ.notify_all();
}

