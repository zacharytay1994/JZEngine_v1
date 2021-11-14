/*	__FILE HEADER__
*	File:		Sound.cpp
	Primary:	Jee Jia Min
	Date:		01/07/21
	Brief:		Custom string class.
*/

#include <PCH.h>
#include "../DebugTools/DebugNew.h"
#include "String.h"

namespace JZEngine
{
	/*
	* New[] :
	* It is an operator to size/resize a dynamic array.
	* Takes a single value for the number of elements in the array.
	*/
	String::String ()
		:
		length ( 0 )
	{}

	/*
	* New() :
	* It is a constructor function to create and allocate an object for any class member.
	* Take arguments for setting object values.
	*/
	String::String ( char c )
		:
		length ( 1 )
	{
		data[ 0 ] = c;
		data[ 1 ] = '\0';
	}

	String::String ( const char* c )
		:
		length ( 0 )
	{
		if( c )
		{
			unsigned int n = 0;
			while( c[ n ] != '\0' )
			{
				n++;
			}
			length = n;
			for( unsigned int j = 0 ; j < n ; j++ )
			{
				data[ j ] = c[ j ];
			}
			data[ n ] = '\0';
		}
		else
		{
			length = 0 ;
			data[ 0 ] = '\0';
		}
	}

	String::String ( const String& s )
		:
		length ( s.size () )
	{
		for( unsigned int j = 0 ; j < length ; ++j )
		{
			data[ j ] = s[ j ];
		}
		data[ length ] = '\0';
	}

	String::~String ()
	{
		clear ();
	}

	
	unsigned int String::size () const
	{
		unsigned int n = 0 ;
		while( ( data[ n ] != '\0' ) && ( n <= MAX_STRING_SIZE ) )
		{
			n++;
		};
		const_cast < unsigned int& > ( length ) = n ;
		return length ;
	}

	int String::index ( char c ) const
	{
		for( unsigned j = 0; j < size (); j++ )
		{
			if( data[ j ] == c )
			{
				return ( int ) j;
			}
		}
		return -1;
	}

	void String::clear ()
	{
		length = 0 ;
		std::memset ( data , 0 , static_cast<size_t>(MAX_STRING_SIZE) );
	}

	void String::upcase ( unsigned first , unsigned last )
	{
		length = size ();

		if( ( first >= last ) || ( last >= length ) || ( last > MAX_STRING_SIZE ) )
		{
			JZ_ASSERT ( ( ( first < last ) && ( last < length ) ) , "Upcase Fail" )( first )( last );
		}
		for( unsigned j = first ; j < last ; ++j )
		{
			// The ASCII codes for a - z are 97 - 122.
			if( 'a' <= data[ j ] && data[ j ] <= 'z' )
			{
				// 'a' decimal code: 97 | 'A' decimal code: 65
				data[ j ] -= ( 'a' - 'A' );
			}
		}
	}

	void String::downcase ( unsigned first , unsigned last )
	{
		length = size ();

		JZ_ASSERT ( ( first < last ) && ( last < length ) , "Downcase Fail" )( first ) ( last );

		for( unsigned j = first; j < last; j++ )
		{
			// The ASCII codes for A-Z are 65-90.
			if( 'A' <= data[ j ] && data[ j ] <= 'Z' )
			{
				// To get a from A, you need to add 32.
				data[ j ] += ( 'a' - 'A' );
			}
		}
	}

	void String::togglecase ( unsigned first , unsigned last )
	{
		length = size ();

		if( ( first >= last ) || ( last >= length ) )
		{
			JZ_ASSERT ( ( first < last ) && ( last < length ) , "ToggleCase Fail" )( first )( last );
		}

		for( unsigned j = first ; j < last ; ++j )
		{
			if( 'A' <= data[ j ] && data[ j ] <= 'Z' )
			{
				data[ j ] += ( 'a' - 'A' );
			}
			else if( 'a' <= data[ j ] && data[ j ] <= 'z' )
			{
				data[ j ] -= ( 'a' - 'A' );
			}
		}
	}

	char String::operator[]( unsigned pos ) const
	{
		const_cast< unsigned int& > ( length ) = size ();

		if( pos >= length )
		{
			JZ_ASSERT ( ( pos < length ) , "Out of range" )( pos )( length );
		}
		return data[ pos ];
	}

	char& String::operator[]( unsigned pos )
	{
		length = size ();
		if( pos >= length )
		{
			JZ_ASSERT ( ( pos < length ) , "Out of range" )( pos )( length );
		}
		return data[ pos ];
	}

	String& String::operator=( const String& s )
	{
		if( this == &s )
		{
			return *this;
		}
		this->clear ();
		length = s.size ();
		for( unsigned int j = 0; j < length; j++ )
		{
			data[ j ] = s[ j ];
		}
		return *this;
	}

	String& String::operator+=( const String& s )
	{
		unsigned int len = length + s.size ();

		if( len > MAX_STRING_SIZE )
		{
			JZ_ASSERT ( len < MAX_STRING_SIZE , "unsigned int len = length + s.size ();" )( len )( length )( s.size () );
		}

		String str{};

		for( unsigned int j = 0; j < length; j++ )
			str[ j ] = data[ j ];

		for( unsigned int i = 0; i < s.size (); i++ )
			str[ length + i ] = s[ i ];

		length = len;
		*this = str;
		return *this;
	}

	/*std::ostream& operator<<( std::ostream& os , const String& s )
	{
		if( s.size () > 0 )
		{
			for( unsigned j = 0 ; j < s.size () ; ++j )
			{
				os << s[ j ];
			}
		}
		else
			os << "";

		return os ;
	}

	std::istream& operator>>( std::istream& is , String& s )
	{
		is >> s.data;
		return is ;
	}*/

	String operator+ ( const String& lhs , const String& rhs )
	{
		return String ( lhs ) += rhs;
	}

	String operator+ ( const String& lhs , char rhs )
	{
		return String ( lhs ) += String ( rhs );
	}

	String operator+ ( const String& lhs , const char* rhs )
	{
		return String ( lhs ) += String ( rhs );
	}

	String operator+ ( char lhs , const String& rhs )
	{
		return String ( lhs ) += rhs;
	}

	String operator+ ( const char* lhs , const String& rhs )
	{
		return String ( lhs ) += rhs;
	}

	bool operator== ( const String& lhs , const String& rhs )
	{
		if( lhs.size () != rhs.size () )
		{
			return false;
		}
		unsigned int cap = lhs.size ();
		unsigned int n = 0;
		while( ( n < cap ) && ( lhs[ n ] == rhs[ n ] ) )
		{
			n++;
		}

		return ( n == cap );
	}

	bool operator== ( const String& lhs , char rhs )
	{
		return ( lhs == String ( rhs ) );
	}

	bool operator== ( const String& lhs , const char* rhs )
	{
		return ( lhs == String ( rhs ) );
	}

	bool operator== ( char lhs , const String& rhs )
	{
		return ( String ( lhs ) == rhs );
	}

	bool operator== ( const char* lhs , const String& rhs )
	{
		return ( String ( lhs ) == rhs );
	}

	bool operator> ( const String& lhs , const String& rhs )
	{
		unsigned int cap = ( lhs.size () < rhs.size () ) ? lhs.size () : rhs.size ();
		unsigned int n = 0;
		while( ( n < cap ) && ( lhs[ n ] == rhs[ n ] ) ) n++;
		if( n == cap ) return ( lhs.size () > rhs.size () );

		if( ( ( 'A' <= lhs[ n ] && lhs[ n ] <= 'Z' ) || ( 'a' <= lhs[ n ] && lhs[ n ] <= 'z' ) ) &&
			( ( 'A' <= rhs[ n ] && rhs[ n ] <= 'Z' ) || ( 'a' <= rhs[ n ] && rhs[ n ] <= 'z' ) ) )
		{
			char A = ( lhs[ n ] & ~32 );
			char B = ( rhs[ n ] & ~32 );
			if( A != B ) return ( A > B );
		}
		return lhs[ n ] > rhs[ n ];
	}

	bool operator> ( const String& lhs , char rhs )
	{
		return ( lhs > String ( rhs ) );
	}

	bool operator> ( const String& lhs , const char* rhs )
	{
		return ( lhs > String ( rhs ) );
	}

	bool operator> ( char lhs , const String& rhs )
	{
		return ( String ( lhs ) > rhs );
	}

	bool operator> ( const char* lhs , const String& rhs )
	{
		return ( String ( lhs ) > rhs );
	}

	bool operator!= ( const String& lhs , const String& rhs )
	{
		return !( lhs == rhs );
	}

	bool operator!= ( const String& lhs , char rhs )
	{
		return !( lhs == rhs );
	}

	bool operator!= ( const String& lhs , const char* rhs )
	{
		return !( lhs == rhs );
	}

	bool operator!= ( char lhs , const String& rhs )
	{
		return !( lhs == rhs );
	}

	bool operator!= ( const char* lhs , const String& rhs )
	{
		return !( lhs == rhs );
	}

	bool operator< ( const String& lhs , const String& rhs )
	{
		return !( lhs == rhs ) && !( lhs > rhs );
	}

	bool operator< ( const String& lhs , char rhs )
	{
		return !( lhs == rhs ) && !( lhs > rhs );
	}

	bool operator< ( const String& lhs , const char* rhs )
	{
		return !( lhs == rhs ) && !( lhs > rhs );
	}

	bool operator< ( char lhs , const String& rhs )
	{
		return !( lhs == rhs ) && !( lhs > rhs );
	}

	bool operator< ( const char* lhs , const String& rhs )
	{
		return !( lhs == rhs ) && !( lhs > rhs );
	}

	bool operator<= ( const String& lhs , const String& rhs )
	{
		return !( lhs > rhs );
	}

	bool operator<= ( const String& lhs , char rhs )
	{
		return !( lhs > rhs );
	}

	bool operator<= ( const String& lhs , const char* rhs )
	{
		return !( lhs > rhs );
	}

	bool operator<= ( char lhs , const String& rhs )
	{
		return !( lhs > rhs );
	}

	bool operator<= ( const char* lhs , const String& rhs )
	{
		return !( lhs > rhs );
	}

	bool operator>= ( const String& lhs , const String& rhs )
	{
		return ( lhs == rhs ) || ( lhs > rhs );
	}

	bool operator>= ( const String& lhs , char rhs )
	{
		return ( lhs == rhs ) || ( lhs > rhs );
	}

	bool operator>= ( const String& lhs , const char* rhs )
	{
		return ( lhs == rhs ) || ( lhs > rhs );
	}

	bool operator>= ( char lhs , const String& rhs )
	{
		return ( lhs == rhs ) || ( lhs > rhs );
	}

	bool operator>= ( const char* lhs , const String& rhs )
	{
		return ( lhs == rhs ) || ( lhs > rhs );
	}

}