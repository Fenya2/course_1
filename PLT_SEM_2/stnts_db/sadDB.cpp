////////// Table realisation //////////
template <typename Entry> Table<Entry>::Table() {_isOpen=false;}

template <typename Entry> Table<Entry>::~Table()
{
	if(_isOpen)
		close();
}

template <typename Entry> std::string Table<Entry>::getPath()
{
	if(!_isOpen)
		throw "Table is not open.";
	return _path;
}

template <typename Entry> std::string Table<Entry>::getName()
{
	if(!_isOpen)
		throw "Table is not open.";
	return _name;
}

template <typename Entry> int Table<Entry>::getCurID()
{
	if(!_isOpen)
		throw "Table is not open.";
	return _curID;
}

template <typename Entry> int Table<Entry>::getEntryQNT()
{
	if(!_isOpen)
		throw "Table is not open.";
	return _entryQNT;
}

template <typename Entry> void Table<Entry>::create(std::string path)
{
	std::string n=sadstd::basename(path);
	if(n.size()>limits::TABLE_MAX_NAME_SIZE)
		throw "Table name size is too big.";
	std::fstream tblfile;
	tblfile.open(path,std::ios::out|std::ios::binary);
	if(!tblfile.is_open())
		throw "Table is not open.";
	strcpy(_name,n.c_str());
	_entryQNT=0; 
	_curID=0;
	tblfile.write(_FILE_DEF,sizeof(_FILE_DEF));
	tblfile.write(_name,sizeof(_name));
	tblfile.write((const char*)&_entryQNT,sizeof(int));
	tblfile.write((const char*)&_curID,sizeof(int));
	tblfile.close();
	_path=path;
	_isOpen=true;
}

template <typename Entry> bool Table<Entry>::open(std::string path)
{
	if(_isOpen)
		return false;
	std::fstream tblfile;
	tblfile.open(path,std::ios::in|std::ios::binary);
	if(!tblfile.is_open())
		return false;
	char pp[7];
	tblfile.read(pp,sizeof(pp));
	if(strcmp(pp,_FILE_DEF)!=0)
		return false;
	tblfile.read(_name,sizeof(_name));
	tblfile.read((char*)&_entryQNT,sizeof(int));
	tblfile.read((char*)&_curID,sizeof(int));
	tblfile.close();
	_path=path;
	_isOpen=true;
	return true;
}

template <typename Entry> void Table<Entry>::insert(const Entry* entryPtr)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::app|std::ios::binary);
	if(!tblfile.is_open())
		throw "Canot open table.";
	tblfile.write((const char*)&_curID,sizeof(int));
	tblfile.write((const char*)entryPtr,sizeof(Entry));
	tblfile.close();
	_curID++;
	_entryQNT++;
	updatePrefix(_curID,_entryQNT);
	return;
}

template <typename Entry> Entry Table<Entry>::getEntryWithID(int ID)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::binary);
	if(!tblfile.is_open())
		throw "Canot open table.";
	tblfile.seekg(getIDSeek(ID)+sizeof(int));
	Entry ret;
	tblfile.read((char*)&ret,sizeof(Entry));
	return ret;
}

template <typename Entry> void Table<Entry>::updateEntryWithID(int ID,const Entry* pattern)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::out|std::ios::binary);
	if(!tblfile)
		throw "Canot open table.";
	Entry entry;
	tblfile.seekg(getIDSeek(ID)+sizeof(int));
	tblfile.read((char*)&entry,sizeof(Entry));
	entry=*pattern;
	tblfile.seekg(-sizeof(Entry),std::ios::cur);
	tblfile.write((const char*)&entry,sizeof(Entry));
	tblfile.close();
}

template <typename Entry> void Table<Entry>::clearEntryWithID(int ID)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::out|std::ios::binary);
	if(!tblfile)
		throw "Canot open table.";
	tblfile.seekg(getIDSeek(ID));
	const int tmp=-1; // фии, гадость.
	tblfile.write((const char*)&tmp,sizeof(int));
	tblfile.close();
	_entryQNT--;
	updatePrefix(_curID,_entryQNT);
}

template <typename Entry> void Table<Entry>::select(const Entry* pattern,sadstd::List<std::pair<int,Entry>>* list)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::binary);
	if(!tblfile)
		throw "Canot open table.";
	tblfile.seekg(_PREFIX_SIZE,std::ios::beg);
	int id;
	std::pair<int,Entry> pair;
	for(int i=0;i<_entryQNT;++i)
	{
		tblfile.read((char*)&id,sizeof(id));
		if(id==-1) // пропуск удаленных записей.
		{
			tblfile.seekg(sizeof(Entry),std::ios::cur);
			i--;
			continue;
		}
		tblfile.read((char*) &(pair.second),sizeof(Entry));
		if(pair.second==*pattern)
		{
			pair.first=id;
			list->add(pair);	
		}
	}
	tblfile.close();
}

template <typename Entry> void Table<Entry>::update(const Entry* pattern, const Entry* update)
{
	sadstd::List<std::pair<int,Entry>> list=sadstd::List<std::pair<int,Entry>>();
	select(pattern,&list);
	list.itBeging();
	while(!list.itEnd())
	{
		updateEntryWithID(list.itValue().first,update);
		list.itNext();
	}
	return;
}

template <typename Entry> void Table<Entry>::clear(const Entry* pattern)
{
	sadstd::List<std::pair<int,Entry>> list;
	select(pattern,&list);
	list.itBeging();
	while(!list.itEnd())
	{
		clearEntryWithID(list.itValue().first);
		_entryQNT--;
		list.itNext();
	}
	updatePrefix(_curID,_entryQNT);
}

template <typename Entry> void Table<Entry>::updatePrefix(int ID,int QNT)
{
	if(!_isOpen)
		throw "Table is not open.";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::out|std::ios::binary);
	if(!tblfile)
		throw "Canot open table.";
	tblfile.seekg(sizeof(_FILE_DEF)+sizeof(_name));
	tblfile.write((const char*)&QNT,sizeof(int));
	tblfile.write((const char*)&ID,sizeof(int));
	tblfile.close();
	return;
}

template <typename Entry> int Table<Entry>::getIDSeek(int ID)
{
	if(ID<0||ID>=_curID)
		throw "Invalid ID";
	std::fstream tblfile;
	tblfile.open(_path,std::ios::in|std::ios::binary);
	if(!tblfile)
		throw "Canot open table.";
	int seek=_PREFIX_SIZE+(sizeof(int)+sizeof(Entry))*ID;
	tblfile.seekg(seek);
	int id;
	tblfile.read((char*)&id,sizeof(int));
	if(id==ID)
		return seek;
	throw "can't find seek on this ID.";
}

template <typename Entry> void Table<Entry>::close()
{
	updatePrefix(_curID,_entryQNT);
	_path="";
	_name[0]='\0';
	_isOpen=false;
	return;
}

////////// DB realisation //////////

DB::DB()
{
	if(!_specialtyTable.open("speciality.table"))
		_specialtyTable.create("speciality.table");
	if(!_groupsTable.open("groups.table"))
		_groupsTable.create("groups.table");
	if(!_studentsTable.open("students.table"))
		_studentsTable.create("students.table");
}

void DB::run()
{
	std::string command;
	while(1)
	{
		std::cout<<"command<A|S|U|C|ST|Q>:";std::getline(std::cin,command);
		if(command=="A")
		{
			std::cout<<"\tadd<SP|G|ST>(or B):";std::getline(std::cin,command);
			if(command=="SP")
			{
				Specialty s=Specialty();
				fillSpecialty(s);
				addSpecialty(&s);
				continue;
			}
			else if(command=="G")
			{
				Group g=Group();
				fillGroup(g);
				addGroup(&g);
				continue;
			}
			else if(command=="ST")
			{
				Student s=Student();
				fillStudent(s);
				addStudent(&s);
				continue;
			}
			else if(command=="B")
				continue;
			else
			{
				std::cout<<"incorrect command"<<std::endl;
				continue;
			}
		}
		else if(command=="S")
		{
			std::cout<<"\tselect<SP|G|ST>(or B):";std::getline(std::cin,command);
			if(command=="SP")
			{
				Specialty pattern=Specialty();
				std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
				fillSpecialty(pattern);
				sadstd::List<std::pair<int,Specialty>> list=sadstd::List<std::pair<int,Specialty>>();
				selectSpecialtyes(&pattern,&list);
				list.itBeging();
				while(!list.itEnd()) 
				{
					std::cout<<list.itValue().first<<"|"<<list.itValue().second.name<<"|"<<list.itValue().second.subjects<<std::endl;
					list.itNext();
				}
				std::cout<<"total:"<<list.size()<<std::endl;
				continue;
			}
			else if(command=="G")
			{
				Group pattern=Group();
				std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
				fillGroup(pattern);
				sadstd::List<std::pair<int,Group>> list=sadstd::List<std::pair<int,Group>>();
				selectGroups(&pattern,&list);
				list.itBeging();
				while(!list.itEnd()) 
				{
					std::cout<<list.itValue().first<<"|"<<list.itValue().second.name<<"|"<<list.itValue().second.specialtyID<<std::endl;
					list.itNext();
				}
				std::cout<<"total:"<<list.size()<<std::endl;
				continue;
			}
			else if(command=="ST")
			{
				std::cout<<"G|SP(or B):";std::getline(std::cin,command);
				if(command=="G")
				{
					Student pattern=Student();
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillStudent(pattern);
					sadstd::List<std::pair<int,Student>> list=sadstd::List<std::pair<int,Student>>();
					selectStudents(&pattern,&list);
					list.itBeging();
					while(!list.itEnd()) 
					{
						std::cout<<list.itValue().first<<"|"<<list.itValue().second.surname<<"|"<<list.itValue().second.name<<"|"<<list.itValue().second.patronymic<<"|"<<list.itValue().second.groupID<<std::endl;
						list.itNext();
					}
					std::cout<<"total:"<<list.size()<<std::endl;
					continue;
				}
				else if(command=="SP")
				{
					std::cout<<"specialty id:";getline(std::cin,command);
					Student pattern;
					fillStudent(pattern);
					selectStudentsBySpecialty(std::stoi(command),&pattern);
				}
				else if(command=="B")
					continue;
				else
				{
					std::cout<<"incorrect command"<<std::endl;
					continue;
				}
			}
			else if(command=="B")
				continue;
			else
			{
				std::cout<<"incorrect command"<<std::endl;
				continue;
			}
		}
		else if(command=="U")
		{
			std::cout<<"\tupdate using<P|ID>(or B)";std::getline(std::cin,command);
			if(command=="P")
			{
				std::cout<<"\tupdate with pattern<SP|G|ST>(or B):";std::getline(std::cin,command);
				if(command=="SP")
				{
					Specialty pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillSpecialty(pattern);
					Specialty update;
					std::cout<<"\t\tupdate(DEFAULT if keep field same)"<<std::endl;
					fillSpecialty(update);
					updateSpecialtyes(&pattern,&update);
					continue;
				}
				else if(command=="G")
				{
					Group pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillGroup(pattern);
					Group update;
					std::cout<<"\t\tupdate(DEFAULT if keep field same)"<<std::endl;
					fillGroup(update);
					updateGroups(&pattern,&update);
					continue;
				}
				else if(command=="ST")
				{
					Student pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillStudent(pattern);
					Student update;
					std::cout<<"\t\tupdate(DEFAULT if keep field same)"<<std::endl;
					fillStudent(update);
					updateStudents(&pattern,&update);
					continue;
				}
				else if(command=="B")
					continue;
				else
				{
					std::cout<<"incorrect command"<<std::endl;
					continue;
				}
			}
			else if(command=="ID")
			{
				std::cout<<"\tupdate with pattern<SP|G|ST>(or B):";std::getline(std::cin,command);
				if(command=="SP")
				{
					std::cout<<"\t\tid:";std::getline(std::cin,command);
					Specialty pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillSpecialty(pattern);
					updateSpecialtyWithID(std::stoi(command),&pattern);
					continue;
				}
				else if(command=="G")
				{
					std::cout<<"\t\tid:";std::getline(std::cin,command);
					Group pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillGroup(pattern);
					updateGroupWithID(std::stoi(command),&pattern);
					continue;
				}
				else if(command=="ST")
				{
					std::cout<<"\t\tid:";std::getline(std::cin,command);
					Student pattern;
					std::cout<<"\t\tpattern(DEFAULT if field is not important)"<<std::endl;
					fillStudent(pattern);
					updateStudentWithID(std::stoi(command),&pattern);
					continue;
				}
				else if(command=="B")
					continue;
				else
				{
					std::cout<<"incorrect command"<<std::endl;
					continue;
				}
			}
			else if(command=="B")
				continue;
			else
			{
				std::cout<<"incorrect command"<<std::endl;
				continue;
			}
		}
		else if(command=="C")
		{
			std::cout<<"\tdelete using <P|ID>(or B):";std::getline(std::cin,command);
			if(command=="P")
			{
				std::cout<<"\tdelete using pattern <SP|G|ST>(or B):";std::getline(std::cin,command);
				if(command=="SP")
				{
					Specialty pattern;
					std::cout<<"\t\tfill patttern(DEFAULT if field not important)"<<std::endl;
					fillSpecialty(pattern);
					try
					{
						clearSpecialtyes(&pattern);
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="G")
				{
					Group pattern;
					std::cout<<"\t\tfill patttern(DEFAULT if field not important)"<<std::endl;
					fillGroup(pattern);
					try
					{
						clearGroups(&pattern);
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="ST")
				{
					Student pattern;
					std::cout<<"\t\tfill patttern(DEFAULT if field not important)"<<std::endl;
					fillStudent(pattern);
					try
					{
						clearStudents(&pattern);
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="B")
				{
					continue;
				}
				else
				{
					std::cout<<"incorrect command"<<std::endl;
					continue;
				}
			}
			else if(command=="ID")
			{
				std::cout<<"\tdelete by ID <SP|G|ST>(or B):";std::getline(std::cin,command);
				if(command=="SP")
				{
					std::cout<<"\t\tid:";getline(std::cin,command);
					try
					{
						clearSpecialtyWithID(std::stoi(command));
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="G")
				{
					std::cout<<"\t\tid:";getline(std::cin,command);
					try
					{
						clearGroupWithID(std::stoi(command));
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="ST")
				{
					std::cout<<"\t\tid:";getline(std::cin,command);
					try
					{
						clearStudentWithID(std::stoi(command));
					}
					catch(const char* e)
					{
						std::cerr<<"incorrect ID entered or etry already deleted."<<std::endl;
					}
					continue;
				}
				else if(command=="B")
					continue;
				else
				{
					std::cout<<"incorrect command"<<std::endl;
					continue;
				}
			}
			else if(command=="B")
				continue;
			else
			{
				std::cout<<"incorrect command"<<std::endl;
				continue;
			}
		}
		else if(command=="ST")
		{
			std::cout<<"group id:";getline(std::cin,command);
			makeStatement(std::stoi(command));
		}
		else if(command=="Q")
			break;
		else
		{
			std::cout<<"incorrect command"<<std::endl;
			continue;
		}
	}
}

void DB::makeStatement(int specialtyID)
{
	if(!specialtyExist(specialtyID))
	{
		std::cerr<<"No specialty with ID you try make statement."<<std::endl;
		return;
	}
	Specialty s=_specialtyTable.getEntryWithID(specialtyID);
	std::vector<std::string> subjects=stredit::split(s.subjects,",");
	for(int i=0;i<subjects.size();++i)
		subjects[i]=stredit::trim(subjects[i]);
	Group gpattern=Group("DEFAULT",specialtyID);
	sadstd::List<std::pair<int,Group>> glist;
	selectGroups(&gpattern,&glist);
	glist.itBeging();
	while(!glist.itEnd())
	{
		std::string dirname=glist.itValue().second.name;
		std::string path="./statement/"+dirname;
		if(mkdir(path.c_str(),S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)!=0)
		{
			std::cerr<<"something went wrong. Clear statement dir."<<std::endl;
			return;
		}
		Student spattern=Student("DEFAULT","DEFAULT","DEFAULT",glist.itValue().first);
		sadstd::List<std::pair<int,Student>> slist;
		selectStudents(&spattern,&slist);
		for(int i=0;i<subjects.size();++i)
		{
			std::fstream file;
			file.open(path+"/"+subjects[i],std::ios::out);
			file<<"=============================="<<std::endl;
			file<<"specialty:"<<s.name<<std::endl;
			file<<"group:"<<glist.itValue().second.name<<std::endl;
			file<<"subject:"<<subjects[i]<<std::endl;
			file<<"=============================="<<std::endl;
			slist.itBeging();
			while(!slist.itEnd())
			{
				file<<slist.itValue().second.surname<<"|"<<
				slist.itValue().second.name<<"|"<<
				slist.itValue().second.patronymic<<std::endl;
				slist.itNext();
			}
			file.close();
		}
		glist.itNext();
	}
}

bool DB::specialtyExist(int specialtyID)
{
	try
	{
		_specialtyTable.getEntryWithID(specialtyID);
		return true;
	}
	catch(const char* e)
	{
		return false;
	}
}

bool DB::groupExist(int groupID)
{
	try
	{
		_groupsTable.getEntryWithID(groupID);
		return true;
	}
	catch(const char* e)
	{
		return false;
	}
}

bool DB::studentExist(int studentID)
{
	try
	{
		_studentsTable.getEntryWithID(studentID);
		return true;
	}
	catch(const char* e)
	{
		return false;
	}
}

void DB::fillSpecialty(Specialty& s)
{
	std::string command;
	std::cout<<"\t\tspecialty name:";std::getline(std::cin,command);
	strcpy(s.name,command.c_str());
	std::cout<<"\t\tspecialty subjects:";std::getline(std::cin,command);
	strcpy(s.subjects,command.c_str());
}

void DB::fillGroup(Group& g)
{
	std::string command;
	std::cout<<"\t\tname:";std::getline(std::cin,command);
	strcpy(g.name,command.c_str());
	std::cout<<"\t\tspecialtyID:";std::getline(std::cin,command);
	if(strcmp("DEFAULT",command.c_str())==0)
	{
		g.specialtyID=-14;
		return;
	}
	g.specialtyID=std::stoi(command);
}

void DB::fillStudent(Student& s)
{
	std::string command;
	std::cout<<"\t\tsurname:";std::getline(std::cin,command);
	strcpy(s.surname,command.c_str());
	std::cout<<"\t\tname:";std::getline(std::cin,command);
	strcpy(s.name,command.c_str());
	std::cout<<"\t\tpatronymic:";std::getline(std::cin,command);
	strcpy(s.patronymic,command.c_str());
	std::cout<<"\t\tgroupID:";std::getline(std::cin,command);
	if(strcmp("DEFAULT",command.c_str())==0)
	{
		s.groupID=-14;
		return;
	}
	s.groupID=std::stoi(command);
}

void DB::addSpecialty(const Specialty* specialty)
{_specialtyTable.insert(specialty);}

void DB::addGroup(const Group* group)
{
	if(!specialtyExist(group->specialtyID))
	{
		std::cerr<<"Specialty for this group is not added. Add it at first."<<std::endl;
		return;
	}
	_groupsTable.insert(group);	
}

void DB::addStudent(const Student* s)
{
	if(!groupExist(s->groupID))
	{
		std::cerr<<"Group for this student is not added. Add it at first."<<std::endl;
		return;
	}
	_studentsTable.insert(s);
}

void DB::selectSpecialtyes(const Specialty* pattern,sadstd::List<std::pair<int,Specialty>>* list)
{_specialtyTable.select(pattern,list);}

void DB::selectGroups(const Group* pattern,sadstd::List<std::pair<int,Group>>* list)
{_groupsTable.select(pattern,list);}

void DB::selectStudents(const Student* pattern,sadstd::List<std::pair<int,Student>>* list)
{_studentsTable.select(pattern,list);}

void DB::selectStudentsBySpecialty(int specialtyID,Student* spattern)
{
	if(!specialtyExist(specialtyID))
	{
		std::cerr<<"Specialty with such ID is not exist."<<std::endl;
		return;
	}
	Specialty s=_specialtyTable.getEntryWithID(specialtyID);
	Group gpattern=Group("DEFAULT",specialtyID);
	sadstd::List<std::pair<int,Group>> glist;
	selectGroups(&gpattern,&glist);
	glist.itBeging();
	while(!glist.itEnd())
	{
		sadstd::List<std::pair<int,Student>> slist;
		spattern->groupID=glist.itValue().first;
		selectStudents(spattern,&slist);
		slist.itBeging();
		while(!slist.itEnd())
		{
			std::cout<<slist.itValue().second.surname<<"|"<<
			slist.itValue().second.name<<"|"<<
			slist.itValue().second.patronymic<<"|"<<
			glist.itValue().second.name<<"|"<<
			s.name<<std::endl;
			slist.itNext();
		}
		glist.itNext();
	}
}


void DB::updateSpecialtyWithID(int ID,const Specialty* update)
{_specialtyTable.updateEntryWithID(ID,update);}

void DB::updateGroupWithID(int ID,const Group* update)
{
	if(!specialtyExist(update->specialtyID))
	{
		std::cerr<<"no such specialty you try set up. Add it at first."<<std::endl;
		return;
	}
	try
	{
		_groupsTable.updateEntryWithID(ID,update);
	}
	catch(const char* e) 
	{
		std::cerr<<"No group with entered ID"<<std::endl;
	}
}

void DB::updateStudentWithID(int ID,const Student* update)
{
	if(!groupExist(update->groupID))
	{
		std::cerr<<"no such group you try set up. Add it at first."<<std::endl;
		return;
	}
	try
	{
		_studentsTable.updateEntryWithID(ID,update);
	}
	catch(const char* e) 
	{
		std::cerr<<"No student with entered ID"<<std::endl;
	}
}


void DB::updateSpecialtyes(const Specialty* pattern,const Specialty* updated)
{_specialtyTable.update(pattern,updated);}

void DB::updateGroups(const Group* pattern,const Group* update)
{
	if(update->specialtyID!=-14)
	{
		if(!specialtyExist(update->specialtyID))
		{
			std::cerr<<"no such specialty you try set up. Add it at first."<<std::endl;
			return;
		}
	}
	_groupsTable.update(pattern,update);
}

void DB::updateStudents(const Student* pattern,const Student* updated)
{
	if(updated->groupID!=-14)
	{
		if(!groupExist(updated->groupID))
		{
			std::cerr<<"no such group you try set up. Add it at first."<<std::endl;
			return;
		}
	}
	_studentsTable.update(pattern,updated);
}

void DB::clearSpecialtyWithID(int id)
{_specialtyTable.clearEntryWithID(id);}

void DB::clearGroupWithID(int id)
{_groupsTable.clearEntryWithID(id);}

void DB::clearStudentWithID(int id)
{_studentsTable.clearEntryWithID(id);}

void DB::clearSpecialtyes(Specialty* pattern)
{_specialtyTable.clear(pattern);}

void DB::clearGroups(Group* pattern)
{_groupsTable.clear(pattern);}

void DB::clearStudents(Student* pattern)
{_studentsTable.clear(pattern);}

DB::~DB()
{
	_studentsTable.close();
	_groupsTable.close();
	_specialtyTable.close();
}
