#ifndef FRAC
#define FRAC

class Frac
{
	public:
	
		Frac( int a, int b )
		{
			if( b == 0 )
			{
				throw "0 division error.";
			}
			else
			{
				_a = a;
				_b = b;
			}
		}
		
		Frac( int n ) : _a(n), _b(1) {}
		
		int &geta() { return _a; }
		int &getb() { return _b; }
		
		void normSign()
		{
			if( _b < 0 )
			{
				_a = -1*_a;
				_b = -1*_b;
			}
		}
		
		void simplify()
		{
			normSign();
			
			int grcd = gcd(_a,_b);
			_a = _a/grcd;
			_b = _b/grcd;
		}
		
		Frac rec()
		{
			if( _a < 0 )
			{
				return Frac(-1*_b,-1*_a);
			}
			else if( _a == 0 )
			{
				throw "0 division error.";
			}
			else
			{
				return Frac(_b,_a);
			}
		}
		
		bool neg()
		{
			if( (_a < 0) ^ (_b < 0) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		bool poz()
		{
			return !neg();
		}
		
		Frac abs()
		{
			normSign();
			
			if( _a < 0 )
			{
				return Frac(-1*_a,_b);
			}
			else
			{
				return Frac(_a,_b);
			}
		}
		
		Frac times( Frac &other )
		{
			normSign();
			int grcd = gcd(_a,other.getb())*gcd(_b,other.geta());
			return Frac(_a*other.geta()/grcd,_b*other.getb()/grcd);
		}

		Frac div( Frac &other )
		{
			Frac f = other.rec();
			return times(f);
		}
		
		Frac add( Frac &other )
		{
			normSign();
			other.normSign();
			
			if( _b == other.getb() )
			{
				Frac f(_a + other.geta(),_b);
				f.simplify();
				
				return f;
			}
			else
			{
				int grcd = gcd(_b,other.getb());
				
				
				Frac f( _a*(other.getb()/grcd) + other.geta()*(_b/grcd) ,(_b/grcd)*other.getb());
				f.simplify();
				
				return f;
			}
		}
		
		Frac negate()
		{
			return Frac(-1*_a,_b);
		}
		
		Frac minus( Frac &other )
		{
			Frac f = other.negate();
			return add( f );
		}
		
		Frac timesInt( int c )
		{
			int grcd = gcd(_b,c);
			Frac f(_a*(c/grcd),_b/grcd);
			
			return f;
		}
		
		Frac divInt( int c )
		{
			if( c == 0 )
			{
				throw "0 division error.";
			}
			else
			{
				int grcd = gcd(_a,c);
				Frac f(_a/grcd,_b*(c/grcd));
				
				return f;
			}
		}
		
	private:
	
		int _a; // fraction in form _a/_b
		int _b;
	
		int gcd( int a, int b )
		{
			if( a > b )
			{
				if( a < 0 )
				{
					return GCD(-1*a,-1*b);
				}
				else if( b < 0 )
				{
					return GCD(a,-1*b);
				}
				else
				{
					return GCD(a,b);
				}
			}
			else if( a == b )
			{
				if( a < 0 )
				{
					return -1*a;
				}
				else
				{
					return a;
				}
			}
			else
			{
				if( b < 0 )
				{
					return GCD(-1*b,-1*a);
				}
				else if( a < 0 )
				{
					return GCD(b,-1*a);
				}
				else
				{
					return GCD(b,a);
				}
			}
		}
		
		int GCD( int a, int b ) // a > b > 0
		{
			if( b == 0 )
			{
				return a;
			}
			else
			{
				return GCD(b,a%b);
			}
		}
};

std::ostream& operator<<( std::ostream &strm, Frac f )
{
	f.normSign();
	
	if( f.geta() % f.getb() == 0 )
	{
		strm << f.geta()/f.getb();
	}
	else
	{
		strm << f.geta() << '/' << f.getb();
	}
	
	return strm;
}

Frac operator+( Frac f, Frac g )
{
	return f.add(g);
}

Frac operator-( Frac f, Frac g )
{ 
	return f.minus(g);
}

Frac operator*( Frac f, Frac g )
{ 
	return f.times(g);
}

Frac operator*( Frac f, int c )
{ 
	return f.timesInt(c);
}

Frac operator*( int c, Frac f )
{ 
  return f.timesInt(c);
}

Frac operator/( Frac f, Frac g )
{
	return f.div(g); 
}

Frac operator/( Frac f, int c )
{ 
	return f.divInt(c);
}

Frac operator/( int c, Frac f )
{ 
	return (f.rec()).timesInt(c);
}

bool operator<( Frac f, Frac g )
{
	f.normSign();
	g.normSign();
	
	return f.geta()*g.getb() < g.geta()*f.getb();
}

bool operator==( Frac f, Frac g ){ return f.geta()*g.getb() == g.geta()*f.getb(); }
bool operator!=( Frac f, Frac g ) { return f.geta()*g.getb() != g.geta()*f.getb(); }
bool operator<=( Frac f, Frac g ) { return !(g<f); }
bool operator>=( Frac f, Frac g ) { return !(f<g); }
bool operator>( Frac f, Frac g )  { return g<f; }

#endif
