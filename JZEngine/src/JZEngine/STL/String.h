#pragma once

#include <iostream>
// https://github.com/bryangoodrich/cpp_String/blob/master/String.h
namespace JZEngine
{
	class String
	{
		char* data ;
		unsigned length ;

	public:
		/*---CONSTUCTOR---*/
		/**
		 * @brief 
		 * Constructs new string from a variety of data sources and
		   optionally using user supplied allocator alloc.
		*/
		String ();
		String ( char c );
		String ( const char* );
		String ( const String& s );

		/*---DESTRUCTOR---*/
		/**
		 * @brief 
		   destroys the string, deallocating internal storage if used.
		 */
		~String ();

		/*---PUBLIC MEMBER FUNCTION---*/
		/**
		 * @brief 
		 * Returns the number of characters.
		 
		 * @return 
		 * The number of CharT elements in the string.
		*/
		unsigned size () const;
		/**
		 * @brief 
		 * String index of a character.
		 
		 * @param c
		 * A char literal.

		 * @return 
		 * The index of a c in String . if exists else return -1.
		*/
		int index ( char c ) const ;



		void upcase ( unsigned first , unsigned last );
		void downcase ( unsigned first , unsigned last );
		void togglecase ( unsigned first , unsigned last );

		/*---INPUT/OUTPUT---*/
		/*
		* Friend function in C++ is defined as a function that can access
		* private , protected and public embers of a function class
		*/
		/**
		 * @brief
		 * Stream operators .
		
		 * @param so
		 * A stream object .
		 
		 * @param s
		 * A string object .
		
		 * @return
		 * Stream object containing String content .
		*/
		friend std::ostream& operator << ( std::ostream& so , const String& s );
		friend std::istream& operator >> ( std::istream& so , String& s );

		/*---ELEMENT ACCESS---*/
		/**
		 * @brief
		 * Access String character .
		 
		 * @param pos
		 * Index value in String
		 
		 * @return
		 * Index of String Data
		*/
		char operator [] ( unsigned pos ) const ;
		char& operator [] ( unsigned pos );


		/**
		 * @brief
		 * Replaces the contents of the string .
		 
		 * @param s
		 * A String object .
		 
		 * @return
		 * A string reference to *this .
		*/
		String& operator = ( const String& s );

		/**
		 * @brief
		 * Append to String
		 
		 * @param s
		 * A String object
		 
		 * @return
		 * A string reference to *this .
		*/
		String& operator += ( const String& s );

		/*---NON MEMBER FUNCTION---*/
		/**
		 * @brief 
		 * Concatenates two string or a string and a char.
		 
		 * @param lhs 
		 * String , character or pointer to the first character in a null terminated array.
		  
		 * @param rhs 
		 * String , character or pointer to the first character in a null terminated array.
		  
		 * @return 
		*/
		friend String operator + (const String& lhs, const String&	rhs);
		friend String operator + (const String& lhs, char			rhs);
		friend String operator + (const String& lhs, const char*	rhs);
		friend String operator + (char			lhs, const String&	rhs);
		friend String operator + (const char*	lhs, const String&	rhs);

		/*---COMPARES TWO STRINGS---*/
		/**
		 * @brief 
		 * String equality 
		 
		* @param lhs 
		 * Strings whose contents to compare .
		 
		 * @param rhs 
		 * Strings whose contents to compare .
		 
		 * @return 
		 * True if lhs and rhs have the same lenght and each character on their
		 * String data are identical in both value and index.
		*/
		friend bool operator== (const String&	lhs, const String&	rhs);
		friend bool operator== (const String&	lhs, char			rhs);
		friend bool operator== (const String&	lhs, const char*	rhs);
		friend bool operator== (char			lhs, const String&	rhs);
		friend bool operator== (const char*		lhs, const String&	rhs);
		/**
		 * @brief 
		 * String inequality: Greater-than. 
		 
		 * @param lhs 
		 * Strings whose contents to compare .
		 
		 * @param rhs 
		 * Strings whose contents to compare .
		 
		 * @return 
		 * True if the corresponding comparison holds, false otherwise.
		*/
		friend bool operator> (const String&	lhs, const String&	rhs);
		friend bool operator> (const String&	lhs, char			rhs);
		friend bool operator> (const String&	lhs, const char*	rhs);
		friend bool operator> (char				lhs, const String&	rhs);
		friend bool operator> (const char*		lhs, const String&	rhs);
		/**
		 * @brief 
		 * String non-equality.
		 
		 * @param lhs 
		 * Strings whose contents to compare .
		 
		 * @param rhs 
		 * Strings whose contents to compare .
		 
		 * @return
		 * True if the lhs doesn't equal to rhs .
		*/
		friend bool operator!= (const String&	lhs, const String&	rhs);
		friend bool operator!= (const String&	lhs, char			rhs);
		friend bool operator!= (const String&	lhs, const char*	rhs);
		friend bool operator!= (char			lhs, const String&	rhs);
		friend bool operator!= (const char*		lhs, const String&	rhs);
		/**
		 * @brief 
		 * String inequality : Less than.
		 
		  * @param lhs 
		 * Strings whose contents to compare .
		 
		 * @param rhs 
		 * Strings whose contents to compare .
		 * 
		 * @return 
		*/
		friend bool operator< (const String&	lhs, const String&	rhs);
		friend bool operator< (const String&	lhs, char			rhs);
		friend bool operator< (const String&	lhs, const char*	rhs);
		friend bool operator< (char				lhs, const String&	rhs);
		friend bool operator< (const char*		lhs, const String&	rhs);

		friend bool operator<= (const String& lhs, const String& rhs);
		friend bool operator<= (const String& lhs, char          rhs);
		friend bool operator<= (const String& lhs, const char* rhs);
		friend bool operator<= (char          lhs, const String& rhs);
		friend bool operator<= (const char* lhs, const String& rhs);

		friend bool operator>= (const String& lhs, const String& rhs);
		friend bool operator>= (const String& lhs, char          rhs);
		friend bool operator>= (const String& lhs, const char* rhs);
		friend bool operator>= (char          lhs, const String& rhs);
		friend bool operator>= (const char* lhs, const String& rhs);
	};

}