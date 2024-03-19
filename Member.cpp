#include "Member.h"

//func for creating, deleting and printing members
void Member::print_members(vector<Member>mems)
{
	int count{ 0 };
	for (long unsigned i{ 0 }; i < mems.size(); i++)
	{
		count++;
		cout << endl << count << " Member\n\n" << "Name: " << mems[i].mem_name << "\nId: " << mems[i].mem_id << "\nDepartment id: "
			<< mems[i].dep_id << "\nCompany id: " << mems[i].com_id << "\nSalary: " << mems[i].mem_salary << endl;
	}
}
void Member::create_members(vector<Member>&mems)
{
	Member member{};
	try
	{
		cout << "Enter member ID: ";
		if(cin >> member.mem_id) {}
		else
		{
			throw runtime_error("Error, incorrect id input!\n");
		}
		cout << "Enter member's salary: ";
		if(cin >> member.mem_salary) {}
		else
		{
			throw runtime_error("Error, incorrect salary input!\n");
		}
		cout << "Enter member's name: ";
		cin >> member.mem_name;
		mems.push_back(member);
	}
	catch (exception& e)
	{
		cerr << "Exception caught " << e.what();
		exit(1);
	}
}
void Member::delete_members(vector<Member>&mems)
{
	unsigned mem_num{ 0 };
	mem_num = choose_member(mems);
	if (mems[mem_num - 1].dep_id != 0)
	{
		cout << "\nFirstly you should remove member from department\n\n";
	}
	else 
	{
		mems.erase(mems.begin() + (mem_num - 1));
	}
}


//func for setting and removing from department
unsigned Member::choose_member(vector<Member>mems)
{
	unsigned mem_num;
	print_members(mems);
	cout << "Enter member number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> mem_num;
		if (mem_num <= mems.size())
		{
			return mem_num;
		}
		else if (mem_num < 0)
		{
			throw runtime_error("Error, mem_num cannot be less than zero!\n");
		}
		else if (mem_num == 0)
		{
			cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw runtime_error("Error, mem_num cannot exceed the given number of members!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}
void Member::set_mem_to_dep(vector<Member>& mems, unsigned _dep_id, unsigned _com_id)
{
	unsigned mem_num = choose_member(mems);
	if (mem_num != 0)
	{
		mems[mem_num - 1].dep_id = _dep_id;
		mems[mem_num - 1].com_id = _com_id;
	}
}
void Member::remove_mem_from_dep(vector<Member>& mems, unsigned _dep_id)
{
	vector<Member>filt_mems;
	for (long unsigned i{ 0 }; i < mems.size(); i++)
	{
		if (mems[i].dep_id == _dep_id)
		{
			filt_mems.push_back(mems[i]);
		}
	}
	unsigned mem_num = choose_member(filt_mems);
	if (mem_num != 0)
	{
		unsigned mem_id_to_remove = filt_mems[mem_num - 1].mem_id;
		for (long unsigned i{ 0 }; i < mems.size(); i++)
		{
			if (mems[i].mem_id == mem_id_to_remove)
			{
				mems[i].dep_id = 0;
				mems[i].com_id = 0;
			}
		}	
	}
}


//func for sorting members 
void Member::sort_members_ascend(vector<Member>mems)
{
	sort(mems.begin(), mems.end(), [](const Member& a, const Member& b)
		{
			return a.mem_name < b.mem_name;
		});
	print_members(mems);
}
void Member::sort_members_descend(vector<Member>mems)
{
	sort(mems.begin(), mems.end(), [](const Member& a, const Member& b)
		{
			return a.mem_name > b.mem_name;
		});
	print_members(mems);
}
void Member::sort_members_salary_asc(vector<Member>mems)
{
	sort(mems.begin(), mems.end(), [](const Member& a, const Member& b)
		{
			return a.mem_salary < b.mem_salary;
		});
	print_members(mems);
}
void Member::sort_members_salary_desc(vector<Member>mems)
{
	sort(mems.begin(), mems.end(), [](const Member& a, const Member& b)
		{
			return a.mem_salary > b.mem_salary;
		});
	print_members(mems);
}


//func for calculating mem_count to company and department
unsigned Member::calculate_mem_count_for_com(vector<Member> mems, unsigned _com_id)
{
	unsigned mem_count = 0;
	for (long unsigned i{ 0 }; i < mems.size(); i++)
	{
		if (mems[i].com_id == _com_id)
		{
			mem_count++;
		}
	}
	return mem_count;
}
unsigned Member::calculate_mem_count_for_dep(vector<Member> mems, unsigned _dep_id)
{
	unsigned mem_count = 0;
	for (long unsigned i{ 0 }; i < mems.size(); i++)
	{
		if (mems[i].dep_id == _dep_id)
		{
			mem_count++;
		}
	}
	return mem_count;
}


//read and write to file
void Member::write_member_to_file(vector<Member>mems)
{
	string fn{ "file_members.bin" };
	ofstream ofs{ fn, ios::binary };
	if (!ofs.is_open())
	{
		cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (long unsigned i{ 0 }; i < mems.size(); i++)
	{
		ofs.write(reinterpret_cast<const char*>(&mems[i].mem_id), sizeof(mems[i].mem_id));
		ofs.write(reinterpret_cast<const char*>(&mems[i].mem_salary), sizeof(mems[i].mem_salary));
		ofs.write(reinterpret_cast<const char*>(&mems[i].dep_id), sizeof(mems[i].dep_id));
		size_t mem_name_size = mems[i].mem_name.size();
		ofs.write(reinterpret_cast<const char*>(&mem_name_size), sizeof(mem_name_size));
		ofs.write(mems[i].mem_name.c_str(), mem_name_size);
	}
	ofs.close();
	cout << "\nMembers were successfully written to a file.\n";
	
}
void Member::read_member_to_file(vector<Member>&mems)
{
	mems.clear();
	Member member{};
	string fn{ "file_members.bin" };
	ifstream ifs{ fn, ios::binary };
	if (!ifs.is_open())
	{
		cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char*>(&member.mem_id), sizeof(member.mem_id));
		ifs.read(reinterpret_cast<char*>(&member.mem_salary), sizeof(member.mem_salary));
		ifs.read(reinterpret_cast<char*>(&member.dep_id), sizeof(member.dep_id));
		size_t mem_name_size;
		ifs.read(reinterpret_cast<char*>(&mem_name_size), sizeof(mem_name_size));
		string _mem_name(mem_name_size, '\0');
		ifs.read(&_mem_name[0], mem_name_size);
		member.mem_name = move(_mem_name);
		mems.push_back(member);
	}
	ifs.close();
	cout << "\nMembers were successfully read.\n";
}
