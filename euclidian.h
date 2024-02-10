#ifndef EUCLIDIAN
#define EUCLIDIAN

#include<vector>
#include<iostream>

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
		
		int getDim() { return dim; }
		
		template <typename U>
		Vector<U> times( U c )
		{
			Vector<U> new_vector(v);
			for( int i = 0; i < dim; ++i )
			{
				new_vector.at(i) = new_vector.at(i)*c;
			}
			
			return new_vector;
		}
		
		template <typename U>
		Vector<U> div( U c )
		{
			Vector<U> new_vector(v);
			for( int i = 0; i < dim; ++i )
			{
				new_vector.at(i) = new_vector.at(i)/c;
			}
			
			return Vector<U>(new_vector);
		}
		
		template<typename U>
		Vector<U> add( Vector<U> &u )
		{
			if( u.getDim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				Vector<U> new_vector(u);
				
				for( int i = 0; i < dim; ++i )
				{
					new_vector.at(i) = v[i] + new_vector.at(i);
				}
				
				return new_vector;
			}
		}
		
		template<typename U>
		Vector<U> minus( Vector<U> &u )
		{
			if( u.getDim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				Vector<U> new_vector(u);
				
				for( int i = 0; i < dim; ++i )
				{
					new_vector.at(i) = v[i] - new_vector.at(i);
				}
				
				return new_vector;
			}
		}
		
		template<typename U>
		U product( Vector<U> &u )
		{
			if( u.getDim() != dim )
			{
				throw("Two vectors are not of the same dimension!");
			}
			else
			{
				U prod;
				
				for( int i = 0; i < dim; ++i )
				{
					prod = prod + u.at(i) * v[i];
					std::cout << prod << '\n';
				}
				
				return prod;
			}
		}
	
	private:
		std::vector<T> v;
		int dim;
};

template <typename T>
std::ostream& operator<<( std::ostream& strm, Vector<T> v )
{
	strm << '[';
	
	for( int i = 0; i < v.getDim()-1; ++i )
	{
		strm << v.at(i) << ", ";
	}
	
	strm << v.at(v.getDim()-1) << ']';
	
	return strm;
}

template <typename T>
Vector<T> operator+( Vector<T>& u, Vector<T>& v )
{
	return u.add(v);
}

template <typename T>
Vector<T> operator-( Vector<T>& u, Vector<T>& v )
{ 
	return u.minus(v);
}

template <typename T>
T operator*( Vector<T>& u, Vector<T>& v )
{ 
	return u.product(v);
}

template <typename T>
Vector<T> operator*( T c, Vector<T>& v )
{ 
	return v.times(c);
}

template <typename T>
Vector<T> operator*( Vector<T>& v, T c )
{ 
	return v.times(c);
}

template <typename T>
Vector<T> operator*( int c, Vector<T>& v )
{ 
	T cc(c);
	return v.times(cc);
}

template <typename T>
Vector<T> operator*( Vector<T>& v, int c )
{ 
	T cc(c);
	return v.times(cc);
}

template <typename T>
Vector<T> operator/( Vector<T>& v, T c )
{ 
	return v.div(c);
}

template <typename T>
bool operator==( Vector<T>& u, Vector<T>& v ){ return u == v; }

template <typename T>
bool operator!=( Vector<T> u, Vector<T> v ) { return u != v; }


#endif
