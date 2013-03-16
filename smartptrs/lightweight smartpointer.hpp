#pragma once
#include <cassert>
#include <stdio.h>
template<typename T>
class lightweight_smartpointer
{
public:
	template<typename T>
	class Body
	{
		friend class lightweight_smartpointer<T>;
		unsigned ref_count;
		T _dat;
	};
	lightweight_smartpointer() : data(NULL)
	{
	}
	lightweight_smartpointer(T const &src) : data(get_resource())
	{
		data->ref_count = 1;
		data->_dat= src;
	}
	lightweight_smartpointer(lightweight_smartpointer<T> const &src) : data(src.data)
	{
		if(data)
			++(data->ref_count);
	}
	lightweight_smartpointer & operator = (lightweight_smartpointer<T> const &src)
	{
		if(data)
		{
			if(!(--(data->ref_count)))
			{
				dispose_resource(data);
			}
		}
		if(src.data)
		{
			++(src.data->ref_count);
		}
		data= src.data;
		return *this;
	}
	~lightweight_smartpointer()
	{
		if(data)
		{
			if(!(--(data->ref_count)))
			{
				dispose_resource(data);
			}
		}
	}
	T * get_dat() const
	{
		if(data)
		{
			return &(data->_dat);
		}
		return NULL;
	}
	void uniqueize()
	{
		if(data)
		{
			if(data->ref_count > 1)
			{
				--(data->ref_count);
				Body<T> * unique = get_resource();
				unique->_dat = data->_dat;
				data = unique;
			}
		}
		else
		{
			data = get_resource();
		}
		data->ref_count = 1;
	}
	void overwrite(lightweight_smartpointer const &src)
	{
		assert(src.data);
		if(!data)
		{
			data = get_resource();
			data->ref_count= 1;
		}
		data->_dat = src.data->_dat;
	}

private:
	Body<T> * data;

	Body<T> * get_resource();
	void dispose_resource(Body<T>*);
};
template<typename T> typename lightweight_smartpointer<T>::Body<T> * lightweight_smartpointer<T>::get_resource()
{
	return new Body<T>();
}
template<typename T> void lightweight_smartpointer<T>::dispose_resource(Body<T> * object)
{
	delete object;
}