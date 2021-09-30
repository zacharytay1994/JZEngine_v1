#pragma once

#include <iostream>

namespace JZEngine
{
	class String
	{
		char* data ;
		unsigned length ;

	public:
		String ();
		String ( char c );
		String ( const char* );
		String ( const String& s );
		~String ();
		unsigned len () const;
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
		 * Concatenates two string or a string ad a char.
		 * @param lhs 
		 * String , character or pointer to the first character in a null terminated array.
		 * @param rhs 
		 * 
		 * @return 
		*/
		friend String operator + (const String& lhs, const String& rhs);
		friend String operator + (const String& lhs, char rhs);
		friend String operator + (const String& lhs, const char* rhs);
		friend String operator + (char lhs, const String& rhs);
		friend String operator + (const char* lhs, const String& rhs);

	};

}