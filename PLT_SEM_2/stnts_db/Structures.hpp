#include <cstring>

struct Specialty
{
    char name[40];
    char subjects[200];
    Specialty()
	{
        strcpy(name,"UNDEFINED");
        strcpy(subjects,"UNDEFINED");
    }
    Specialty(const char name[40],const char subjects[20])
	{
        strcpy(this->name,name);
        strcpy(this->subjects,subjects);
    }
    bool operator==(const Specialty pattern)
	{
        if(!strcmp(name,pattern.name)||!strcmp("DEFAULT",pattern.name))
            if(!strcmp(subjects,pattern.subjects)||!strcmp("DEFAULT",pattern.subjects))
                return true;
        return false;
    }  
    Specialty& operator=(const Specialty& pattern)
	{
        if(strcmp("DEFAULT",pattern.name)!=0)
            strcpy(name,pattern.name);
        if(strcmp("DEFAULT",pattern.subjects)!=0)
            strcpy(subjects,pattern.subjects);
        return *this;
    }
};

struct Group
{
    char name[50];
    int specialtyID;
    Group()
	{
        strcpy(name,"UNDEFINED");
		specialtyID=-100;
    }
    Group(const char name[50],int specialtyID)
	{
        strcpy(this->name,name);
		this->specialtyID=specialtyID;
    }
    bool operator==(const Group pattern)
	{
        if(strcmp(name,pattern.name)==0||strcmp("DEFAULT",pattern.name)==0)
            if(specialtyID==pattern.specialtyID||pattern.specialtyID==-14)
                return true;
        return false;
    }
    Group& operator=(const Group& pattern)
	{
        if(strcmp("DEFAULT",pattern.name)!=0)
            strcpy(name,pattern.name);
        if(pattern.specialtyID!=-14)
			specialtyID=pattern.specialtyID;
        return *this;
    }
};

struct Student
{
    char surname[20];
    char name[20];
    char patronymic[20];
    int groupID;
    Student()
	{
        strcpy(name,"UNDEFINED");
        strcpy(surname,"UNDEFINED");
        strcpy(patronymic,"UNDEFINED");
		groupID=-100;
    }
    Student(const char surname[20],const char name[20],const char patronymic[20],int groupID)
	{
        strcpy(this->surname,surname);
        strcpy(this->name,name);
        strcpy(this->patronymic,patronymic);
		this->groupID=groupID;
    }
    bool operator==(const Student pattern)
	{
        if (!strcmp(name,pattern.name)||!strcmp("DEFAULT",pattern.name))
            if (!strcmp(surname,pattern.surname)||!strcmp("DEFAULT",pattern.surname))
                if (!strcmp(patronymic,pattern.patronymic)||!strcmp("DEFAULT",pattern.patronymic))
                    if (groupID==pattern.groupID||pattern.groupID==-14)
                        return true;
        return false;
    }
    Student& operator=(const Student& pattern)
	{
        if(strcmp("DEFAULT",pattern.name)!=0)
            strcpy(name,pattern.name);
        if(strcmp("DEFAULT",pattern.surname)!=0)
            strcpy(surname,pattern.surname);
        if(strcmp("DEFAULT",pattern.patronymic)!=0)
            strcpy(patronymic,pattern.patronymic);
        if(pattern.groupID!=-14)
			groupID=pattern.groupID;
        return *this;
    }
};
