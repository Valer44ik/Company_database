#pragma once
#include "Libraries.h"
#include "Company.h"
#include "Member.h"

class Department
{
private:
	unsigned dep_id = 0, com_id = 0, num_mem = 0;
	string dep_name;
	vector<Department>departments;
public:
	//getters
	unsigned get_dep_id();
	unsigned get_num_mem();

	//func for creating deleting and printing deps
	void create_departments(vector<Department>&departmens);
	void delete_departments(vector<Department>& departments);
	void print_departments(vector<Department>departments);

	//func for choosing a dep
	unsigned choose_department(vector<Department>departments);
	unsigned choose_department_id(vector<Department>departments);

	//func for setting and removing deps
	void set_dep_to_com(vector<Department>&departments, unsigned com_id);
	void remove_dep_from_com(vector<Department>& departments, unsigned com_num);

	//func for sort 
	void sort_departments_ascend(vector<Department>departments);
	void sort_departments_descend(vector<Department>departments);
	void sort_departments_mem_count_asc(vector<Department>departments);
	void sort_departments_mem_count_desc(vector<Department>departments);

	//funstion for filtering deps by com_id
	vector<Department> filter_deps(vector<Department> departments, unsigned _com_id);

	//functiuons to calculate department count for company
	unsigned calculate_dep_counts(vector<Department>& departments, unsigned _com_id);

	//function for setting number of members in department
	void update_mem_count(vector<Department>& departments, unsigned _dep_id, unsigned mem_count_dep);

	//read and write to file
	void write_department_to_file(vector<Department>departments);
	void read_department_to_file(vector<Department>&departments);
};

