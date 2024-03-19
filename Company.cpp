#include "Company.h"

//func for creating, delelting and printing companies
void Company::create_companies(vector<Company>& coms)
{
	Company company{};
	try 
	{
		cout << "Enter company id: ";
		if(cin >> company.com_id){}
		else
		{
			throw runtime_error("Error, incorrect id input!\n");
		}
		cout << "Enter company name: ";
		cin >> company.com_name;
		coms.push_back(company);
	}
	catch (exception& e)
	{
		cerr << "Exception caught " << e.what();
		exit(1);
	}
}
void Company::delete_companies(vector<Company>& coms)
{
	unsigned com_num{ 0 };
	com_num = choose_company(coms);
	if (coms[com_num - 1].num_dep != 0)
	{
		cout << "\nFirstly you should remove all departments.\n\n";
	}
	else
	{
		coms.erase(coms.begin() + (com_num-1));
	}
}
void Company::print_companies(vector<Company>coms)
{
	int count{ 0 };
	for (long unsigned i{ 0 }; i < coms.size(); i++)
	{
		count++;
		cout << endl << count << " company\n\n" << "Id:" << coms[i].com_id << "\nName: " << coms[i].com_name 
			<< "\nNumber of departments: " << coms[i].num_dep << "\nNumber of members: " << coms[i].num_mem << endl;
	}
}


//func for choosing one company by name and id
unsigned Company::choose_company(vector<Company> coms)
{
	unsigned com_num;
	print_companies(coms);
	cout << "Enter company number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> com_num;
		if (com_num <= coms.size())
		{
			return com_num;
		}
		else if (com_num < 0)
		{
			throw runtime_error("Error, com_num cannot be less than zero!\n");
		}
		else if (com_num == 0)
		{
			cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw runtime_error("Error, com_num cannot exceed the given number of companies!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}
unsigned Company::choose_company_id(vector<Company>coms)
{
	unsigned com_num;
	print_companies(coms);
	cout << "Enter company number you wanna choose(Enter \"0\" if you want to return back): ";
	try 
	{
		cin >> com_num;
		if (com_num > 0 && com_num <= coms.size())
		{
			return coms[com_num - 1].com_id;
		}
		else if (com_num < 0)
		{
			throw runtime_error("Error, com_num cannot be less than zero!\n");
		}
		else if (com_num == 0)
		{
			return 0;
		}
		else
		{
			throw runtime_error("Error, com_num cannot exceed the given number of companies!\n");
		}
	}
	catch (exception&e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}	
}


//func for sorting companies
void Company::sort_companies_ascend(vector<Company>coms)
{
	sort(coms.begin(), coms.end(), [](const Company & a, const Company & b)
		{
			return a.com_name < b.com_name;
		});
	print_companies(coms);
}

void Company::sort_companies_descend(vector<Company>coms)
{
	sort(coms.begin(), coms.end(), [](const Company& a, const Company& b)
		{
			return a.com_name > b.com_name;
		});
	print_companies(coms);
}
void Company::sort_companies_num_mem_asc(vector<Company>coms)
{
	sort(coms.begin(), coms.end(), [](const Company& a, const Company& b)
		{
			return a.num_mem < b.num_mem;
		});
	print_companies(coms);
}
void Company::sort_companies_num_mem_desc(vector<Company>coms)
{
	sort(coms.begin(), coms.end(), [](const Company& a, const Company& b)
		{
			return a.num_mem > b.num_mem;
		});
	print_companies(coms);
}


//func for setting number of members and departments to company
void Company::update_dep_count(vector<Company>& coms, unsigned _com_id, unsigned dep_count)
{
	for (long unsigned i{ 0 }; i < coms.size(); i++)
	{
		if (coms[i].com_id == _com_id)
		{
			coms[i].num_dep = dep_count;
		}
	}
}
void Company::update_mem_count(vector<Company>& coms, unsigned _com_id, unsigned _mem_count)
{
	for (long unsigned i{ 0 }; i < coms.size(); i++)
	{
		if (coms[i].com_id == _com_id)
		{
			coms[i].num_mem = _mem_count;
		}
	}
}


//read and write to file
void Company::write_company_to_file(vector<Company>& coms)
{
	string fn{ "file_companies.bin" };
	ofstream ofs{ fn, ios::binary };
	if (!ofs.is_open())
	{
		cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (unsigned i{ 0 }; i < coms.size(); i++)
	{
		ofs.write(reinterpret_cast<const char*>(&coms[i].com_id), sizeof(coms[i].com_id));
		size_t com_name_size = coms[i].com_name.size();
		ofs.write(reinterpret_cast<const char*>(&com_name_size) , sizeof(com_name_size));
		ofs.write(coms[i].com_name.c_str(), com_name_size);
		ofs.write(reinterpret_cast<const char*>(&coms[i].num_dep), sizeof(coms[i].num_dep));
		ofs.write(reinterpret_cast<const char*>(&coms[i].num_mem), sizeof(coms[i].num_mem));
	}
	ofs.close();
	cout << "\nCompanies were successfully written to a file.\n";
}

void Company::read_company_to_file(vector<Company>&coms)
{
	coms.clear();
	Company company{};
	string fn{ "file_companies.bin" };
	ifstream ifs{ fn, ios::binary };
	if (!ifs.is_open())
	{
		cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char*>(&company.com_id), sizeof(company.com_id));
		size_t com_name_size;
		ifs.read(reinterpret_cast<char*>(&com_name_size) , sizeof(com_name_size));
		string _com_name(com_name_size, '\0');
		ifs.read(&_com_name[0], com_name_size);
		company.com_name = move(_com_name);
		ifs.read(reinterpret_cast<char*>(&company.num_mem), sizeof(company.num_mem));
		ifs.read(reinterpret_cast<char*>(&company.num_dep), sizeof(company.num_dep));
		coms.push_back(company);
	}
	ifs.close();
	cout << "\nCompanies were successfully read.\n";	
}
