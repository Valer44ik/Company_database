#pragma once
#include "Libraries.h"
#include "Department.h"

class Member
{
private:
	unsigned mem_id = 0, mem_salary = 0, dep_id = 0, com_id = 0;
	string mem_name;
	vector<Member>members;

public:
	//func for print, create and delete
	void print_members(vector<Member>members);
	void create_members(vector<Member>&members);
	void delete_members(vector<Member>& members);

	//func for setting and removing mem
	unsigned choose_member(vector<Member>members);
	void set_mem_to_dep(vector<Member>& members, unsigned _dep_id, unsigned _com_id);
	void remove_mem_from_dep(vector<Member>&members, unsigned _dep_id);

	//func for sort
	void sort_members_ascend(vector<Member>members);
	void sort_members_descend(vector<Member>members);
	void sort_members_salary_asc(vector<Member>members);
	void sort_members_salary_desc(vector<Member>members);

	//func for calculating mem_count to company and department
	unsigned calculate_mem_count_for_com(vector<Member>members, unsigned _com_id);
	unsigned calculate_mem_count_for_dep(vector<Member>members, unsigned _dep_id);

	//read and write to file
	void write_member_to_file(vector<Member>members);
	void read_member_to_file(vector<Member>&members);
};

