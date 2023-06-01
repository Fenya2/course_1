#ifndef SADDB_HPP
#define SADDB_HPP

#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include "sadstd.h"
#include <sys/stat.h>

#include "Structures.hpp"
#include "StringEdit.hpp"

namespace sadDB
{
	enum limits
	{
		TABLE_MAX_NAME_SIZE=30,
	};

	template <typename Entry> class Table
	{
		const char _FILE_DEF[7]="sadTBL";
		const int _PREFIX_SIZE=sizeof(_FILE_DEF)+ 
					limits::TABLE_MAX_NAME_SIZE+ 
					2*sizeof(int);
		char _name[limits::TABLE_MAX_NAME_SIZE];
		std::string _path;
		int _curID;
		int _entryQNT;
		bool _isOpen;
		void updatePrefix(int,int);
		int getIDSeek(int);
	public:
		Table();
		std::string getPath();
		std::string getName();
		int getCurID();
		int getEntryQNT();
		void create(std::string);
		bool open(std::string);
		void close();
		void insert(const Entry*);
		Entry getEntryWithID(int);
		void updateEntryWithID(int,const Entry*);
		void clearEntryWithID(int);
		void select(const Entry*,sadstd::List<std::pair<int,Entry>>*);
		void update(const Entry*,const Entry*);
		void clear(const Entry*);
		~Table();
	};

	class DB
	{
		Table<Specialty> _specialtyTable;
		Table<Group> _groupsTable;
		Table<Student> _studentsTable;
	public:
		DB();

		void run();
		void makeStatement(int);

		bool specialtyExist(int); 
		bool groupExist(int);
		bool studentExist(int);

		void fillSpecialty(Specialty&);
		void fillGroup(Group&);
		void fillStudent(Student&);

		void addSpecialty(const Specialty*);
		void addGroup(const Group*);
		void addStudent(const Student*);

		void selectSpecialtyes(const Specialty*,sadstd::List<std::pair<int,Specialty>>*);
		void selectGroups(const Group*,sadstd::List<std::pair<int,Group>>*);
		void selectStudents(const Student*,sadstd::List<std::pair<int,Student>>*);
		void selectStudentsBySpecialty(int,Student*);

		void updateSpecialtyWithID(int,const Specialty*);
		void updateGroupWithID(int,const Group*);
		void updateStudentWithID(int,const Student*);

		void updateSpecialtyes(const Specialty*,const Specialty*);
		void updateGroups(const Group*,const Group*);
		void updateStudents(const Student*,const Student*);

		void clearSpecialtyWithID(int);
		void clearGroupWithID(int);
		void clearStudentWithID(int);

		void clearSpecialtyes(Specialty*);
		void clearGroups(Group*);
		void clearStudents(Student*);

		~DB();
	};

	#include "sadDB.cpp"
}
#endif
