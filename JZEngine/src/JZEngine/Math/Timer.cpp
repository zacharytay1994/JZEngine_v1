#include "PCH.h"
#include "Timer.h"


using namespace std::chrono;
std::chrono::steady_clock::time_point last_{};
std::vector <std::string> past_time_data_{};

JZEngine::Timer::Timer () noexcept
{
	last_ = steady_clock::now ();
}

float JZEngine::Timer::Mark () noexcept
{
	const auto old = last_ ;
	last_ = steady_clock::now ();
	const duration <float> frame_time = last_ - old ;
	return frame_time.count ();
}

void JZEngine::Timer::LastDuration ( float last_timer , const std::string& filename )
{
	std::cout << "Saving data to : " << filename << std::endl;
	std::ifstream inputstream;
	inputstream.open ( filename , std::ios::in );
	if( inputstream.is_open () )
	{
		std::cout << "Filename : " << filename << " Is available and open !" << std::endl;
	}
	else if( !inputstream )
	{
		std::cout << "Filename : " << filename << " Cannot open file/file does not exist." << std::endl;
	}
	std::string data_in_file{};
	std::vector<std::string> add_data_in_file;
	int number_of_lines{};
	while( std::getline ( inputstream , data_in_file ) )
	{
		add_data_in_file.push_back ( data_in_file );
		number_of_lines++;
	}

	std::ofstream outstream ;
	std::stringstream sstream;
	sstream << last_timer;

	if( number_of_lines < 5 )
	{
		outstream.open ( filename , std::ios::app );
	}
	else
	{
		outstream.open ( filename , std::ios::out );
	}

	if( outstream.is_open () )
	{
		std::cout << "Filename : " << filename << " Is available and open !" << std::endl;
	}
	else if( !outstream )
	{
		std::cout << "Filename : " << filename << " Cannot open file/file does not exist." << std::endl;
	}

	if( number_of_lines < 5 )
	{
		outstream << last_timer << "\n";
		for( int i = 0 ; i < add_data_in_file.size () ; i++ )
		{
			past_time_data_.push_back ( add_data_in_file[ i ] );
		}
		past_time_data_.push_back ( sstream.str () );
	}
	else
	{
		for( int i = 1 ; i < add_data_in_file.size () ; i++ )
		{
			outstream << add_data_in_file[ i ] << "\n";
			past_time_data_.push_back ( add_data_in_file[ i ] );
		}
		outstream << last_timer << "\n";
		past_time_data_.push_back ( sstream.str () );
	}

	outstream.close ();
}

float JZEngine::Timer::Peek ( const std::string& filename ) noexcept
{
	float timer = duration <float> ( steady_clock::now () - last_ ).count ();
	LastDuration ( timer , filename );
	return timer;
}

void JZEngine::Timer::TimerHistory () const noexcept
{
	bool check = true ;
	int i = 0;
	for( auto data : past_time_data_ )
	{
		if( check )
		{
			std::cout << "Processing data timer history : " << std::endl;
			check = false;
		}
		std::cout << "#" << i << ". " << data << std::endl;
		i++;
	}
}