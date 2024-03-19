#pragma once
#include "Libraries.h"
#include "Department.h"

class Company
{
private:
	unsigned com_id = 0, num_dep = 0, num_mem = 0;
	string com_name = "";
	vector<Company>companies;

public:
	//func for creating, deleting and printing companies
	void create_companies(vector<Company>&companies);
	void delete_companies(vector<Company>& companies);
	void print_companies(vector<Company>companies);

	//func for choosing one company by name and id
	unsigned choose_company(vector<Company>companies);
	unsigned choose_company_id(vector<Company>companies);

	//func for sorting
	void sort_companies_ascend(vector<Company>companies);
	void sort_companies_descend(vector<Company>companies);
	void sort_companies_num_mem_asc(vector<Company>companies);
	void sort_companies_num_mem_desc(vector<Company>companies);
	
	//func for setting number of members and departments to company
	void update_dep_count(vector<Company>&companies, unsigned _com_id, unsigned dep_count);
	void update_mem_count(vector<Company>& companies, unsigned _com_id, unsigned _mem_count);
	
	//read and write to file
	void write_company_to_file(vector<Company>&companies);
	void read_company_to_file(vector<Company>&coms);
};
