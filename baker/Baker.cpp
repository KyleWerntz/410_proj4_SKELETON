#include <mutex>
#include <vector>
#include "../includes/baker.h"
#include "../includes/externs.h"
using namespace std;

Baker::Baker(int id):id(id)
{
}

Baker::~Baker()
{
}

void Baker::bake_and_box(ORDER &anOrder) {
	int donutsMade = 0;
	vector<Box> boxes;
	Box b;
	DONUT d;
	while (donutsMade != anOrder.number_donuts)	{ //TODO fix in3
		b.addDonut(d);
		donutsMade+=1;
		if (b.size() == DOZEN)	{
			boxes.push_back(b);
			b.clear();
		}

	}
	if (b.size() > 0)
		boxes.push_back(b);
	anOrder.boxes = boxes;
}

void Baker::beBaker() {
	while (true)	{
		unique_lock<mutex> m(mutex_order_inQ);
		while (!(order_in_Q.size() > 0) && !b_WaiterIsFinished)
			cv_order_inQ.wait(m);

		if (order_in_Q.size() > 0)	{
			bake_and_box(order_in_Q.front());
			order_out_Vector.push_back(order_in_Q.front());
			order_in_Q.pop();
		}
		if (order_in_Q.size() == 0 && b_WaiterIsFinished)	{
			break;
		}
	}
}
