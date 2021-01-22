#include <iostream>
#include <stdlib.h>
#include <math.h>

#define SIZE_Q 100

using namespace std;

template <typename T>
class Queue{
	
	private:
		
		T *array;
		int capacity, left, right, sizeQ;
		
	public:
		
		Queue()
		{
			capacity = SIZE_Q;
			array = new T[SIZE_Q];
			
			left = -1;
			right = -1;
			sizeQ = 0;
		}
		
		Queue(int capacity)
		{
			this->capacity = abs(capacity);
			array = new T[this->capacity];
			
			left = -1;
			right = -1;
			sizeQ = 0;
		}
		
		void enQueue(T val)
		{
			if((left == 0 && right == capacity-1) || (right == left - 1))
			{
				cout<<"\nQueue Is Full.\n";
			}
			else if(left == -1 && right == -1)
			{
				left = right = 0;
				array[right] = val;
				sizeQ++;
			}
			else if(left != 0 && right == capacity-1)
			{
				right = 0;
				array[right] = val;
				sizeQ++;
			}
			else
			{
				right++;
				array[right] = val;
				sizeQ++;
			}
		}
		
		T deQueue()
		{
			T val;
			
			if(left == -1 && right == -1)
			{
				cout<<"\nQueue Is Empty.\n";
			}
			else if(left == capacity - 1)
			{
				val = array[left];
				left = 0;
				sizeQ--;
			}
			else if(left == right)
			{
				val = array[left];
				left = right = -1;
				sizeQ--;
			}
			else
			{
				val = array[left];
				left++;
				sizeQ--;
			}
			
			return val;
		}
		
		T peekQ()
		{
			if(!emptyQ())
			{
				return array[left];
			}
		}
		
		void clearQ()
		{
			left = right = -1;
		}
		
		int getSize()
		{
			return sizeQ;
		}
		
		int getCapacity()
		{
			return capacity;
		}
		
		bool emptyQ()
		{
			if(left == -1 && right == -1)
			{
				return 1;
			}
			return 0;
		}
		
		bool fullQ()
		{
			if((left == 0 && right == capacity-1) || (right == left - 1))
			{
				return 1;
			}
			return 0;
		}
		
		void displayQ()
		{
			if(left < right)
			{
				for(int i=left; i<=right; i++)
				{
					cout<<array[i]<<"\n";
				}
			}
			else if(right < left)
			{
				for(int i=0; i<=right; i++)
				{
					cout<<array[i]<<" \n";
				}
				
				for(int i=left; i<capacity; i++)
				{
					cout<<array[i]<<" \n";
				}
			}
			else
			{
				if(!emptyQ())
				{
					cout<<array[left]<<"\n";
				}
				else
				{
					cout<<"\nEmpty Queue\n";
				}
			}
		}
		
		~Queue()
		{
			if(array != 0)
			{
				delete[] array;
				array = 0;
			}
		}
};
