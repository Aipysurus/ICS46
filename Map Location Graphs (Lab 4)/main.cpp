// main.cpp
//
// ICS 46 Spring 2016
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"
#include <map>
#include <iomanip>
#include <cmath>
#include <math.h>
std::vector<double> format_time(double s)
{
	double hours = 0, minutes = 0,seconds = 0;
	std::vector<double> formatted;
	hours = s / 3600.00;
	minutes = (((s/ 3600) - (int)hours) * 60);
	seconds = (((s / 60) - (int)minutes) * 60);
	if (hours > 1)
	{
		formatted.push_back(hours);
	}
	if (minutes > 1)
	{
		formatted.push_back(minutes);
	}

	formatted.push_back(seconds);
	return formatted;
}

void print_formatTime(std::vector<double> v_times)
{
	if (v_times.size() == 3)
	{
		std::cout << std::round(v_times[0]) << " hrs " << int(v_times[1]) << " mins "
		<<std::roundf(v_times[2] * 10) / 10 << " secs";
	}
	else if(v_times.size() == 2)
	{
		std::cout <<int(v_times[0]) << " mins " << std::roundf(v_times[1] * 10) / 10 << " secs";
	}
	else
		std::cout << std::roundf(v_times[0] * 10) / 10 << " secs)";	
}
int main()
{
	std::function<double(const RoadSegment&)> shortestpath = [](RoadSegment rs){return rs.miles;};
	std::function<double(const RoadSegment&)> shortesttime = [](RoadSegment rs){return rs.milesPerHour/ rs.miles;};
	RoadMapReader rr;
	InputReader ir = InputReader(std::cin);
	RoadMap rm = rr.readRoadMap(ir);

	TripReader tr;
	std::vector<Trip> trips = tr.readTrips(ir);
	struct info
	{
		int vertex;
		std::string street;
		RoadSegment data;
	};

	std::map<int,int> alpha;
for(std::vector<Trip>::iterator i = trips.begin(); i!= trips.end(); i++)
	{
	std::vector<info> final_trip;
		if (i ->metric == TripMetric::Distance)
			alpha = rm.findShortestPaths(i -> startVertex, shortestpath);
		else 
			alpha = rm.findShortestPaths(i -> startVertex, shortesttime);

	int beta = i->endVertex; 
	info last_item = info{beta, rm.vertexInfo(beta), rm.edgeInfo(alpha[beta], beta)};
	final_trip.push_back(last_item);

	double final_distance = last_item.data.miles;
	while(beta != i -> startVertex)
	{
		int temporary = beta;
		beta = alpha[beta];
		final_trip.push_back(info{beta, rm.vertexInfo(beta), rm.edgeInfo(beta, temporary)});
		if (beta != i-> startVertex)
			final_distance += rm.edgeInfo(beta,temporary).miles;
	}

	double final_time = 0;
	if (i -> metric == TripMetric::Distance)
	{
		std::cout << "Shortest distance from " << rm.vertexInfo(final_trip.back().vertex) 
		<<" to "<< rm.vertexInfo(final_trip.front().vertex) << std::endl;

		std::cout << "\t Begin at " << final_trip[final_trip.size() - 1].street << std::endl;
		for (int i = final_trip.size() - 2; i >= 0; i--)
		{
			std::cout << "\t Continue to " << final_trip[i].street << " (" <<final_trip[i].data.miles << " miles)" << std::endl;
		}
		std::cout << "Total Distance: " << std::setprecision(2) <<final_distance << " miles" << std::endl;
	}

	else
	{
		std::cout << "Shortest driving time from " << rm.vertexInfo(final_trip.back().vertex) <<
		" to " << rm.vertexInfo(final_trip.front().vertex) << std::endl;
		std::cout << "\t Begin at " << final_trip[final_trip.size() - 1].street << std::endl;
		for (int i = final_trip.size() - 2; i >= 0; i--)
		{
			double time_sec = (final_trip[i].data.miles / final_trip[i].data.milesPerHour) * 3600;
			std::vector<double> times = format_time(time_sec);

			std::cout << "\t Continue to " << final_trip[i].street << " (" << final_trip[i].data.miles 
				<< " miles @" << final_trip[i].data.milesPerHour << "mph = ";
				
			final_time += time_sec;
			print_formatTime(times);
			std::cout << ")" << std::endl;
		}
		std::vector<double> final_timePrint = format_time(final_time);
		std::cout << "Total time: ";
		print_formatTime(final_timePrint);
		std::cout<< "\n" << std::endl;
	}
}
    return 0;
}

