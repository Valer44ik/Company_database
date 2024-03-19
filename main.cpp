#include "Company.h"
#include "Member.h"
#include "Department.h"


int main()
{
	vector<Member>members;
	Member member;
	vector<Company>companies;
	Company company;
	vector<Department>departments;
	Department department;
	int choice{ 0 };
	while (true)
	{
		cout << "======================================== Menu ==========================================\n";
		cout << "1.  Create company				15. sort companies descending\n";
		cout << "2.  Create department				16. sort companies num_mem ascending\n";
		cout << "3.  Create member				17. sort companies num_mem descending\n";
		cout << "4.  Delete company				18. sort departments ascending\n";
		cout << "5.  Delete department				19. sort departments descending\n";
		cout << "6.  Delete member				20. sort departments member count ascending\n";
		cout << "7.  Print companies				21. sort departments member count descending\n";
		cout << "8.  Print departmets				22. sort members ascending\n";
		cout << "9.  Print members				23. sort members descending\n";
		cout << "10. Set department to company			24. sort members salary ascending\n";
		cout << "11. Set member to department			25. sort members salary descending\n";
		cout << "12. Remove department from company		26. Write to file\n";
		cout << "13. Remove member from department		27. Read from a file\n";
		cout << "14. sort companies ascending			28. Exit\n";
		cout << "========================================================================================\n";
		cout << "Enter your choice: ";
				cin >> choice;
				switch (choice) 
				{
				case 1:
					company.create_companies(companies);
					break;
				case 2:
					department.create_departments(departments);				
					break;				
				case 3:					
					member.create_members(members);
					break;		
				case 4:
					if (companies.size() == 0)
					{
						cout << "Firstly you should create company.\n";
						break;
					}
					company.delete_companies(companies);
					break;
				case 5:
					if (departments.size() == 0)
					{
						cout << "Firstly you should create department.\n";
						break;
					}
					department.delete_departments(departments);
					break;
				case 6:
					if (members.size() == 0)
					{
						cout << "Firstly you should create member.\n";
						break;
					}
					member.delete_members(members);
				case 7:
					if (companies.size() == 0)
					{
						cout << "Firstly you should create company.\n";
						break;
					}
					company.print_companies(companies);
					break;
				case 8:
					if (departments.size() == 0)
					{
						cout << "Firstly you should create department.\n";
						break;
					}
					department.print_departments(departments);
					break;
				case 9:
					if (members.size() == 0)
					{
						cout << "Firstly you should create member.\n";
						break;
					}
					member.print_members(members);
					break;
				case 10:
				{
					if (companies.size() == 0 || departments.size() == 0)
					{
						cout << "Firstlty you should create a company/department.\n";
						break;
					}
					unsigned _com_id = company.choose_company_id(companies);
					if (_com_id == 0)
					{
						continue;
					}
					department.set_dep_to_com(departments, _com_id);
					unsigned dep_count = department.calculate_dep_counts(departments, _com_id);
					company.update_dep_count(companies, _com_id, dep_count);
					unsigned mem_count_com = member.calculate_mem_count_for_com(members, _com_id);
					company.update_mem_count(companies, _com_id, mem_count_com);
					break; 
				}	
				case 11:
				{
					if (companies.size() == 0 || departments.size() == 0 || members.size() == 0)
					{
						cout << "Firstly you should create a company/department/member\n";
						break;
					}
					unsigned _com_id = company.choose_company_id(companies);
					vector <Department>sort_deps = department.filter_deps(departments, _com_id);
					if (sort_deps.size() == 0)
					{
						cout << "\nThere is no departments for company.\n\n";
						break;
					}
					unsigned _dep_id = department.choose_department_id(sort_deps);
					if (_dep_id == 0)
					{
						continue;
					}
					member.set_mem_to_dep(members, _dep_id, _com_id);
					unsigned mem_count_dep = member.calculate_mem_count_for_dep(members, _dep_id);
					department.update_mem_count(departments, _dep_id, mem_count_dep);
					unsigned mem_count_com = member.calculate_mem_count_for_com(members, _com_id);
					company.update_mem_count(companies, _com_id, mem_count_com);
					break;
				}				
				case 12:
				{
					if (companies.size() == 0 || departments.size() == 0)
					{
						cout << "Firstlty you should create a company/department.\n";
						break;
					}
					unsigned _com_id = company.choose_company_id(companies);
					if (_com_id == 0)
					{
						continue;
					}
					department.remove_dep_from_com(departments, _com_id);
					unsigned dep_count = department.calculate_dep_counts(departments, _com_id);
					company.update_dep_count(companies, _com_id, dep_count);
					unsigned mem_count_com = member.calculate_mem_count_for_com(members, _com_id);
					company.update_mem_count(companies, _com_id, mem_count_com);
					break;
				}					
				case 13:
				{
					if (companies.size() == 0 || departments.size() == 0 || members.size() == 0)
					{
						cout << "Firstly you should create a company/department/member\n";
						break;
					}
					unsigned _com_id = company.choose_company_id(companies);
					vector <Department>sort_deps = department.filter_deps(departments, _com_id);
					if (sort_deps.size() == 0)
					{
						cout << "\nThere is no departments for company.\n\n";
						break;
					}
					unsigned _dep_id = department.choose_department_id(sort_deps);
					unsigned short exit_flag = 0;
					for (long unsigned i{ 0 }; i < sort_deps.size(); i++)
					{
						if (sort_deps[i].get_dep_id() == _dep_id)
						{
							if (sort_deps[i].get_num_mem() == 0)
							{
								cout << "\nNo members to remove.\n\n";
								exit_flag = 1;
								break;
							}
						}
					}
					if (exit_flag == 1)
					{
						break;
					}
					if (_dep_id == 0)
					{
						continue;
					}
					member.remove_mem_from_dep(members, _dep_id);
					unsigned mem_count_dep = member.calculate_mem_count_for_dep(members, _dep_id);
					department.update_mem_count(departments, _dep_id, mem_count_dep);
					unsigned mem_count_com = member.calculate_mem_count_for_com(members, _com_id);
					company.update_mem_count(companies, _com_id, mem_count_com);
					break;
				}					
				case 14:
					if (companies.size() < 2)
					{
						cout << "You should have at least 2 companies to sort\n";
						break;
					}
					company.sort_companies_ascend(companies);
					break;
				case 15:
					if (companies.size() < 2)
					{
						cout << "You should have at least 2 companies to sort\n";
						break;
					}
					company.sort_companies_descend(companies);
					break;
				case 16:
					if (companies.size() < 2)
					{
						cout << "You should have at least 2 companies to sort\n";
						break;
					}
					company.sort_companies_num_mem_asc(companies);
					break;
				case 17:
					if (companies.size() < 2)
					{
						cout << "You should have at least 2 companies to sort\n";
						break;
					}
					company.sort_companies_num_mem_desc(companies);
					break;
				case 18:
					if (departments.size() < 2)
					{
						cout << "You should have at least 2 departments to sort\n";
						break;
					}
					department.sort_departments_ascend(departments);
					break;
				case 19:
					if (departments.size() < 2)
					{
						cout << "You should have at least 2 departments to sort\n";
						break;
					}
					department.sort_departments_descend(departments);
					break;
				case 20:
					if (departments.size() < 2)
					{
						cout << "You should have at least 2 departments to sort\n";
						break;
					}
					department.sort_departments_mem_count_asc(departments);
					break;
				case 21:
					if (departments.size() < 2)
					{
						cout << "You should have at least 2 departments to sort\n";
						break;
					}
					department.sort_departments_mem_count_desc(departments);
					break;
				case 22:
					if (members.size() < 2)
					{
						cout << "You should have at least 2 members to sort\n";
						break;
					}
					member.sort_members_ascend(members);
					break;
				case 23:
					if (members.size() < 2)
					{
						cout << "You should have at least 2 members to sort\n";
						break;
					}
					member.sort_members_descend(members);
					break;
				case 24:
					if (members.size() < 2)
					{
						cout << "You should have at least 2 members to sort\n";
						break;
					}
					member.sort_members_salary_asc(members);
					break;
				case 25:
					if (members.size() < 2)
					{
						cout << "You should have at least 2 members to sort\n";
						break;
					}
					member.sort_members_salary_desc(members);
					break;
				case 26:
				{
					company.write_company_to_file(companies);
					department.write_department_to_file(departments);
					member.write_member_to_file(members);
					break;
				}
				case 27:
				{
					company.read_company_to_file(companies);
					department.read_department_to_file(departments);
					member.read_member_to_file(members);
					break;
				}
				case 28:
					cout << "\nGoodbye\n";
					return 0;
				default:
					cerr << "Error, no such an option available!\n";
					return 1;
				}
	}
}

