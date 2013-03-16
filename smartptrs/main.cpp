#include "lightweight smartpointer.hpp"
#include "buff_t.hpp"
typedef lightweight_smartpointer<buff_t> light_buff;
int main(int argc, char **argv)
{
	buff_t mybuff;
	light_buff first;
	light_buff second = light_buff(mybuff);
	first = second;
	light_buff * third = new light_buff(second);
	delete third;
	second.uniqueize();
	return 0;
}