// timer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <iostream>
#include <string>


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
		上面的代码主要使用了
		date xx() 构造函数
		from_undelimited_string(std::string());		//将string 转换成date 
		to_simple_string(date())					//将date 转换成 std::string
		as_long_string			// 将年月日输出英文 1
		as_number()				// 将年月日输出中文 1

	*/



	return 0;
}

