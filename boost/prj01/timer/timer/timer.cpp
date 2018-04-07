// timer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <string>


/*
This example demonstrates a simple use of periods for the calculation
of date information.

The example calculates if a given date is a weekend or holiday
given an exclusion set.  That is, each weekend or holiday is
entered into the set as a time interval.  Then if a given date
is contained within any of the intervals it is considered to
be within the exclusion set and hence is a offtime.

Output:
Number Excluded Periods: 5
20020202/20020203
20020209/20020210
20020212/20020212
20020216/20020217
In Exclusion Period: 20020216 --> 20020216/20020217
20020223/20020224

*/

#include <set>
#include <algorithm>

typedef std::set<boost::gregorian::date_period> date_period_set;

//Simple population of the exclusion set
date_period_set
	generateExclusion()
{
	using namespace boost::gregorian;
	date_period periods_array[] = 
	{ date_period(date(2002,Feb,2), date(2002,Feb,4)),//weekend of 2nd-3rd
	date_period(date(2002,Feb,9), date(2002,Feb,11)),
	date_period(date(2002,Feb,16), date(2002,Feb,18)),
	date_period(date(2002,Feb,23), date(2002,Feb,25)),
	date_period(date(2002,Feb,12), date(2002,Feb,13))//a random holiday 2-12
	};
	const int num_periods = sizeof(periods_array)/sizeof(date_period);

	date_period_set ps;
	//insert the periods in the set
	std::insert_iterator<date_period_set> itr(ps, ps.begin());
	std::copy(periods_array, periods_array+num_periods, itr );
	return ps;

}


int _tmain(int argc, _TCHAR* argv[])
{

	/* The following is a simple example that shows conversion of dates 
	* to and from a std::string.
	* 
	* Expected output:
	* 2001-Oct-09
	* 2001-10-09
	* Tuesday October 9, 2001
	* An expected exception is next: 
	* Exception: Month number is out of range 1..12
	*/

	using namespace boost::gregorian;

	try 
	{
		// The following date is in ISO 8601 extended format (CCYY-MM-DD)
		std::string s("2001-10-9"); //2001-October-09
		date d(from_simple_string(s));
		std::cout << to_simple_string(d) << std::endl;

		//Read ISO Standard(CCYYMMDD) and output ISO Extended
		std::string ud("20011009"); //2001-Oct-09
		date d1(from_undelimited_string(ud));
		std::cout << to_iso_extended_string(d1) << std::endl;

		//Output the parts of the date - Tuesday October 9, 2001
		date::ymd_type ymd = d1.year_month_day();
		greg_weekday wd = d1.day_of_week();
		std::cout << wd.as_long_string() << " "		//第几周
			//<< ymd.month.as_long_string() << " "	//第几月
			<< ymd.month.as_number() << " "	//第几月
			<< ymd.day.as_number() << ", " << ymd.year	// 第几日 - 第几年
			<< std::endl;

		//Let's send in month 25 by accident and create an exception
		std::string bad_date("20012509"); //2001-??-09
		std::cout << "An expected exception is next: " << std::endl;
		date wont_construct(from_undelimited_string(bad_date));
		//use wont_construct so compiler doesn't complain, but you wont get here!
		std::cout << "oh oh, you shouldn't reach this line: " \
			<< to_iso_string(wont_construct) << std::endl;

	}
	catch(std::exception& e) 
	{
		std::cout << "  Exception: " <<  e.what() << std::endl;
	}

	/*
	* 上面的代码主要使用了
	*	date xx() 构造函数
	*	from_undelimited_string(std::string());		//将string 转换成date 
	*	to_simple_string(date())					//将date 转换成 std::string
	*	as_long_string				// 将年月日输出英文 1
	*	as_number()					// 将年月日输出中文 1
	*/

	/* Short example that calculates the number of days since user was born.
	* Demonstrates comparisons of durations, use of the day_clock,
	* and parsing a date from a string.
	*/

	{
		std::string s("19941213");
		try
		{
			date birthday(from_undelimited_string(s));
			date today = day_clock::local_day();
			date dieDate = birthday + years(70);
			days days_alive = today - birthday;
			days days_still = dieDate - today;
			days one_day(1);
			if (days_alive == one_day) {
				std::cout << "Born yesterday, very funny" << std::endl;
			}
			else if (days_alive < days(0)) {
				std::cout << "Not born yet, hmm: " << days_alive.days() 
					<< " days" <<std::endl;
			}
			else {
				std::cout << "Days alive: " << days_alive.days() << std::endl;
			}

			std::cout << "Days still: " << days_still.days() << std::endl;
		}
		catch (...)
		{
			std::cout << "Bad date entered: " << s << std::endl;
		}
	}

	/************************************************************************/
	/*   这一块主要用到date 的运算                                                                  
	/*   时间点和时间点的加减法                                                                  
	/*   时间点和时间间隔的加减法                                                                    
	/*   时间点默认构造函数传入参数long型                                                                    
	/*   除此之外还有 months years days 三个长类                                                                  
	/************************************************************************/

	/* Define a series of char arrays for short and long name strings 
	* to be associated with German date output (US names will be 
	* retrieved from the locale). */
	const char* const de_short_month_names[] = 
	{
		"Jan", "Feb", "Mar", "Apr", "Mai", "Jun",
		"Jul", "Aug", "Sep", "Okt", "Nov", "Dez", "NAM" 
	};
	const char* const de_long_month_names[] =
	{
		"Januar", "Februar", "Marz", "April", "Mai",
		"Juni", "Juli", "August", "September", "Oktober",
		"November", "Dezember", "NichtDerMonat"
	};
	const char* const de_long_weekday_names[] = 
	{
		"Sonntag", "Montag", "Dienstag", "Mittwoch",
		"Donnerstag", "Freitag", "Samstag"
	};
	const char* const de_short_weekday_names[] =
	{
		"Son", "Mon", "Die","Mit", "Don", "Fre", "Sam"
	};


	// create some gregorian objects to output
	date d1(2002, Oct, 1);
	greg_month m = d1.month();
	greg_weekday wd = d1.day_of_week();

	// create a facet and a locale for German dates
	date_facet* german_facet = new date_facet();
	std::cout.imbue(std::locale(std::locale::classic(), german_facet));

	// create the German name collections
	date_facet::input_collection_type short_months, long_months, 
		short_weekdays, long_weekdays;
	std::copy(&de_short_month_names[0], &de_short_month_names[11],
		std::back_inserter(short_months));
	std::copy(&de_long_month_names[0], &de_long_month_names[11],
		std::back_inserter(long_months));
	std::copy(&de_short_weekday_names[0], &de_short_weekday_names[6],
		std::back_inserter(short_weekdays));
	std::copy(&de_long_weekday_names[0], &de_long_weekday_names[6],
		std::back_inserter(long_weekdays));

	// replace the default names with ours
	// NOTE: date_generators and special_values were not replaced as 
	// they are not used in this example
	german_facet->short_month_names(short_months);
	german_facet->long_month_names(long_months);
	german_facet->short_weekday_names(short_weekdays);
	german_facet->long_weekday_names(long_weekdays);

	// output the date in German using short month names
	german_facet->format("%d.%m.%Y");
	std::cout << d1 << std::endl; //01.10.2002

	german_facet->month_format("%B");
	std::cout << m << std::endl; //Oktober

	german_facet->weekday_format("%A");
	std::cout << wd << std::endl; //Dienstag


	// Output the same gregorian objects using US names
	date_facet* us_facet = new date_facet();
	std::cout.imbue(std::locale(std::locale::classic(), us_facet)); 

	us_facet->format("%m/%d/%Y");
	std::cout << d1 << std::endl; //  10/01/2002

	// English names, iso order (year-month-day), '-' separator
	us_facet->format("%Y-%b-%d");
	std::cout << d1 << std::endl; //  2002-Oct-01


	/*后面两段看不大明白*/
	date_period_set ps = generateExclusion();
	std::cout << "Number Excluded Periods: "  << ps.size() << std::endl;

	date d(2002,Feb,16);
	date_period_set::const_iterator i = ps.begin();
	//print the periods, check for containment
	for (;i != ps.end(); i++) {
		std::cout << to_iso_string(*i) << std::endl;
		//if date is in exclusion period then print it
		if (i->contains(d)) {
			std::cout << "In Exclusion Period: "
				<< to_iso_string(d) << " --> " << to_iso_string(*i)
				<< std::endl;
		}
	}




	return 0;
}

