#ifndef _INTERVAL_TREE_H
#define _INTERVAL_TREE_H

#include <iostream>
#include "interval.h"
#include <vector>
#include <memory>

template<typename T>
class interval_tree
{
public:
	using interval_collection = std::vector<T>;

private:
	//class node
	class node
	{
		enum direction
		{
			LEFT,
			RIGHT
		};
		
		using node_ptr = std::unique_ptr<node>;

		size_t               d_point;
		node_ptr             d_left;
		node_ptr			 d_right;
		interval_collection  d_intervals;

	public:
		node(const interval_collection& intervals)
			: d_point(0),
			  d_left(nullptr),
			  d_right(nullptr),
			  d_intervals()
		{
			d_point = determine_median(intervals);
			interval_collection to_left, to_right;
			for (const auto& i : intervals)
			{
				if (i.get_end() < d_point)
				{
					to_left.push_back(i);
				}
				else if (i.get_start() > d_point)
				{
					to_right.push_back(i);
				}
				else
				{
					d_intervals.push_back(i);
				}
			}

			if (to_left.size() > 0)
			{
				d_left.reset(new node(to_left));
			}
			if (to_right.size() > 0)
			{
				d_right.reset(new node(to_right));
			}
		}

		size_t determine_median(const interval_collection& intervals) const
		{
			size_t start = -1;
			size_t end = -1;
			for (const auto& i : intervals)
			{
				size_t cur_start = i.get_start();
				size_t cur_end = i.get_end();
				if (start == (size_t)-1 || cur_start < start)
				{
					start = cur_start;
				}
				if (end == (size_t)-1 || cur_end > end)
				{
					end = cur_end;
				}
			}

			return (start + end) / 2;
		}

		interval_collection find_overlaps(const T& i)
		{
			interval_collection overlaps;
			if (d_point < i.get_start())
			{
				add_to_overlaps(i, overlaps, find_overlapping_ranges(d_right, i));
				add_to_overlaps(i, overlaps, check_right_overlaps(i));
			}
			else if (d_point > i.get_end())
			{
				add_to_overlaps(i, overlaps, find_overlapping_ranges(d_left, i));
				add_to_overlaps(i, overlaps, check_left_overlaps(i));
			}
			else
			{
				add_to_overlaps(i, overlaps, d_intervals);
				add_to_overlaps(i, overlaps, find_overlapping_ranges(d_left, i));
				add_to_overlaps(i, overlaps, find_overlapping_ranges(d_right, i));
			}
			return interval_collection(overlaps);
		}
	protected:
		void add_to_overlaps(const T& i, interval_collection& overlaps, interval_collection new_overlaps) const 
		{  
			for (const auto& cur : new_overlaps) 
			{  
				if (cur != i) 
				{  
					overlaps.push_back(cur);  
				}  
			}  
		}  

		interval_collection check_left_overlaps(const T& i) const 
		{  
			return interval_collection(check_overlaps(i, LEFT));  
		}  

		interval_collection check_right_overlaps(const T& i) const 
		{  
			return interval_collection(check_overlaps(i, RIGHT));  
		}  

		interval_collection check_overlaps(const T& i, direction d) const 
		{  
			interval_collection overlaps;  
			for (const auto& cur : d_intervals) 
			{  
				switch (d) 
				{  
					case LEFT:  
						if (cur.get_start() <= i.get_end()) 
						{  
							overlaps.push_back(cur);  
						}  
						break;  
					case RIGHT:  
						if (cur.get_end() >= i.get_start()) 
						{  
							overlaps.push_back(cur);  
						}  
						break;  
				}  
			}  
			return interval_collection(overlaps);  
		}  

		interval_collection find_overlapping_ranges(node_ptr& node, const T& i) const 
		{  
			if (node) 
			{  
				return interval_collection(node->find_overlaps(i));  
			}  
			return interval_collection();  
		}  
	};

	node d_root; 

public:  
	interval_tree(const interval_collection& intervals)  
		: d_root(intervals) {}  

	interval_collection remove_overlaps(const interval_collection& intervals) 
	{  
		interval_collection result(intervals.begin(), intervals.end());  
		std::sort(result.begin(), result.end(), [](const T& a, const T& b) -> bool 
			{  
				if (b.size() - a.size() == 0) 
				{  
					return a.get_start() > b.get_start();  
				}  
				return a.size() > b.size();  
			});  

		std::set<T> remove_tmp;  
		for (const auto& i : result) 
		{  
			if (remove_tmp.find(i) != remove_tmp.end()) 
			{  
				continue;  
			}  
			auto overlaps = find_overlaps(i);  
			for (const auto& overlap : overlaps) 
			{  
				remove_tmp.insert(overlap);  
			}  
		}  
		for (const auto& i : remove_tmp) 
		{  
			result.erase(std::find(result.begin(), result.end(), i));  
		}  
		std::sort(result.begin(), result.end(), [](const T& a, const T& b) -> bool 
			{  
				return a.get_start() < b.get_start();  
			});  
		return interval_collection(result);  
	}  

	interval_collection find_overlaps(const T& i) 
	{  
		return interval_collection(d_root.find_overlaps(i));  
	}  
};


#endif







