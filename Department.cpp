#include "Department.h"


//getters
 unsigned Department::get_dep_id(){ return dep_id; }
 unsigned Department::get_num_mem() { return num_mem; }


//func for creating deleting and printing deps
void Department::print_departments(vector<Department>deps)
{
	int count{ 0 };
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		count++;
		cout << endl << count << " Department\n\n" << "Name: " << deps[i].dep_name << "\nId: " << deps[i].dep_id << "\nCompany id: " 
			<< deps[i].com_id << "\nTotal number of members: " << deps[i].num_mem << endl;
	}
}
void Department::create_departments(vector<Department>& deps)
{
	Department department{};
	try
	{
		cout << "Enter department ID: ";
		if(cin >> department.dep_id) {}
		else
		{
			throw runtime_error("Error, incorrect id input!\n");
		}
		cout << "Enter department name: ";
		cin >> department.dep_name;
		deps.push_back(department);
	}
	catch (exception& e)
	{
		cerr << "Exception caught " << e.what();
		exit(1);
	}
}
void Department::delete_departments(vector<Department>& deps)
{
	unsigned dep_num{ 0 };
	dep_num = choose_department(deps);
	if (deps[dep_num - 1].num_mem != 0)
	{
		cout << "\nFirstly you should remove all members.\n\n";
	}
	else if (deps[dep_num - 1].com_id != 0)
	{
		cout << "\nFirstly you should remove department from company.\n\n";
	}
	else
	{
		deps.erase(deps.begin() + (dep_num-1));
	}
}


//func for choosing a dep
unsigned Department::choose_department(vector<Department>deps)
{
	unsigned dep_num;
	print_departments(deps);
	cout << "Enter department number you wanna choose(Enter \"0\" if you want to return back): ";	
	try
	{
		cin >> dep_num;
		if (dep_num <= deps.size())
		{
			return dep_num;
		}
		else if (dep_num < 0)
		{
			throw runtime_error("Error, dep_num cannot be less than zero!\n");
		}
		else if (dep_num == 0)
		{
			cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw runtime_error("Error, dep_num cannot exceed the given number of departments!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}
unsigned Department::choose_department_id(vector<Department>deps)
{
	unsigned dep_num;
	print_departments(deps);
	cout << "Enter department number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> dep_num;
		if (dep_num > 0 && dep_num <= deps.size())
		{
			return deps[dep_num - 1].dep_id;
		}
		else if (dep_num < 0)
		{
			throw runtime_error("Error, dep_num cannot be less than zero!\n");
		}
		else if (dep_num == 0)
		{
			return 0;
		}
		else
		{
			throw runtime_error("Error, dep_num cannot exceed the given number of companies!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}


//func for setting and removing deps
void Department::set_dep_to_com(vector<Department>& deps,unsigned _com_id)
{
	unsigned long dep_num = choose_department(deps);
	if (dep_num != 0)
	{
		deps[dep_num - 1].com_id = _com_id;
	}
}
void Department::remove_dep_from_com(vector<Department>&deps, unsigned _com_id)
{
	vector<Department>filt_deps;
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		if (deps[i].com_id == _com_id)
		{
			filt_deps.push_back(deps[i]);
		}
	}
	if (filt_deps.size() == 0)
	{
		cout << "\nNo departments to remove\n\n";
	}
	else
	{
		unsigned dep_num = choose_department(filt_deps);
		if (dep_num != 0)
		{
			if (filt_deps[dep_num - 1].num_mem != 0)
			{
				cout << "\nFirstly remove all members from department\n\n";
			}
			else
			{
				unsigned dep_id_to_remove = filt_deps[dep_num - 1].dep_id;
				for (long unsigned i{ 0 }; i < deps.size(); i++)
				{
					if (deps[i].dep_id == dep_id_to_remove)
					{
						deps[i].com_id = 0;
					}
				}
			}
		}
	}
}


//func for sort
void Department::sort_departments_ascend(vector<Department>deps)
{
	sort(deps.begin(), deps.end(), [](const Department& a, const Department& b)
		{
			return a.dep_name < b.dep_name;
		});
	print_departments(deps);
}
void Department::sort_departments_descend(vector<Department>deps)
{
	sort(deps.begin(), deps.end(), [](const Department& a, const Department& b)
		{
			return a.dep_name > b.dep_name;
		});
	print_departments(deps);
}
void Department::sort_departments_mem_count_asc(vector<Department>deps)
{
	sort(deps.begin(), deps.end(), [](const Department& a, const Department& b)
		{
			return a.num_mem < b.num_mem;
		});
	print_departments(deps);
}
void Department::sort_departments_mem_count_desc(vector<Department>deps)
{
	sort(deps.begin(), deps.end(), [](const Department& a, const Department& b)
		{
			return a.num_mem > b.num_mem;
		});
	print_departments(deps);
}


//funstion for filtering deps by com_id
vector<Department> Department::filter_deps(vector<Department> deps, unsigned _com_id)
{
	vector <Department> filt_deps;
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		if (deps[i].com_id == _com_id)
		{
			filt_deps.push_back(deps[i]);
		}
	}
	return filt_deps;
}


//functiuons to calculate department count for company
unsigned Department::calculate_dep_counts(vector<Department>& deps, unsigned _com_id)
{
	unsigned dep_count = 0;
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		if (deps[i].com_id == _com_id)
		{
			dep_count++;
		}
	}
	return dep_count;
}


//function for setting number of members in department
void Department::update_mem_count(vector<Department>& deps, unsigned _dep_id, unsigned mem_count_dep)
{
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		if (deps[i].dep_id == _dep_id)
		{
			deps[i].num_mem = mem_count_dep;
		}
	}
}


//read and write to file
void Department::write_department_to_file(vector<Department>deps)
{
	string fn{ "file_departments.bin" };
	ofstream ofs{ fn, ios::binary };
	if (!ofs.is_open())
	{
		cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (long unsigned i{ 0 }; i < deps.size(); i++)
	{
		ofs.write(reinterpret_cast<const char*>(&deps[i].dep_id), sizeof(deps[i].dep_id));
		size_t dep_name_size = deps[i].dep_name.size();
		ofs.write(reinterpret_cast<const char*>(&dep_name_size), sizeof(dep_name_size));
		ofs.write(deps[i].dep_name.c_str(), dep_name_size);
		ofs.write(reinterpret_cast<const char*>(&deps[i].com_id), sizeof(deps[i].com_id));
		ofs.write(reinterpret_cast<const char*>(&deps[i].num_mem), sizeof(deps[i].num_mem));
	}
	ofs.close();
	cout << "\nDepartments were successfully written to a file.\n";
}
void Department::read_department_to_file(vector<Department>&deps)
{
	deps.clear();
	Department department{};
	string fn{ "file_departments.bin" };
	ifstream ifs{ fn, ios::binary };
	if (!ifs.is_open())
	{
		cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char*>(&department.dep_id), sizeof(department.dep_id));
		size_t dep_name_size;
		ifs.read(reinterpret_cast<char*>(&dep_name_size), sizeof(dep_name_size));
		string _dep_name(dep_name_size, '\0');
		ifs.read(&_dep_name[0], dep_name_size);
		department.dep_name = move(_dep_name);
		ifs.read(reinterpret_cast<char*>(&department.com_id), sizeof(department.com_id));
		ifs.read(reinterpret_cast<char*>(&department.num_mem), sizeof(department.num_mem));
		deps.push_back(department);
	}
	ifs.close();
	cout << "\nDepartments were successfully read.\n";
}