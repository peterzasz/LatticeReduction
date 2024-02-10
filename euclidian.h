#ifndef EUCLIDIAN
#define EUCLIDIAN

#include <vector>
#include <math.h>

#include <iostream>

template <typename T>
class Vector
{
	public:
		Vector( std::vector<T> _v ) : v(_v), dim(_v.size()) {};
		
		T &at(int i)
		{
			if( dim <= i || i < 0 )
			{
				throw("Index is out of range!");
			}
			else
			{
				return v[i];
			}
		}
		
		int get_dim() { return dim; }
		
		Vector<T> times( T c )
		{
			Vector<T> new_vector(v);
			for( int i = 0; i < dim; ++i )
			{
				new_vector.at(i) = new_vector.at(i)*c;
			}
			
			return new_vector;
		}
		
		Vector<T> div( T c )
		{
			Vector<T> new_vector(v);
			for( int i = 0; i < dim; ++i )
			{
				new_vector.at(i) = new_vector.at(i)/c;
			}
			
			return new_vector;
		}
		
		Vector<T> add( Vector<T> &u )
		{
			if( u.get_dim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				Vector<T> new_vector(u);
				
				for( int i = 0; i < dim; ++i )
				{
					new_vector.at(i) = v[i] + new_vector.at(i);
				}
				
				return new_vector;
			}
		}
		
		Vector<T> minus( Vector<T> &u )
		{
			if( u.get_dim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				Vector<T> new_vector(u);
				
				for( int i = 0; i < dim; ++i )
				{
					new_vector.at(i) = v[i] - new_vector.at(i);
				}
				
				return new_vector;
			}
		}
		
		T product( Vector<T> &u )
		{
			if( u.get_dim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				T prod(0);

				for( int i = 0; i < dim; ++i )
				{
					prod = prod + (u.at(i) * at(i));
				}
				
				return prod;
			}
		}

		T squared()
		{
			T prod(0);
			
			for( int i = 0; i < dim; ++i )
			{
				prod = prod + v[i] * v[i];
			}
			
			return prod;
		}

		T get_squared_length()
		{
			if( squared_length == -1 )
			{
				squared_length = squared();
			}

			return squared_length;
		}

		std::vector<T> &get_vector() { return v; }


		Vector<T> operator+( Vector<T>& u )
		{
			return add(u);
		}

		Vector<T> operator-( Vector<T>& u)
		{ 
			return minus(u);
		}

		T operator*( Vector<T>& u )
		{ 
			return product(u);
		}

		Vector<T> operator*( T c )
		{ 
			return times(c);
		}

		Vector<T> operator/( T c )
		{ 
			return div(c);
		}

		bool operator==( Vector<T>& u ){ return u.get_vector() == v; }

		bool operator!=( Vector<T>& u ) { return !(u == v); }
	
	private:
		std::vector<T> v;
		T squared_length = -1;
		int dim;
};

template <typename T>
std::ostream& operator<<( std::ostream& strm, Vector<T> v )
{
	strm << '[';
	
	for( int i = 0; i < v.get_dim()-1; ++i )
	{
		strm << v.at(i) << ", ";
	}
	
	strm << v.at(v.get_dim()-1) << ']';
	
	return strm;
}

template <typename U, typename T>
Vector<T> operator*( U c, Vector<T>& v )
{ 
	return v.times(c);
}

template <typename U, typename T>
Vector<T> operator*( Vector<T>& v, U c )
{ 
	return v.times(c);
}

#endif
