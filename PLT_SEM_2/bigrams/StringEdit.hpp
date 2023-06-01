#include <string>
#include <vector>

/*
.,:;!?!"<>(){}[]
*/

namespace stredit
{
	std::vector<std::string> splitOnSentences(const std::string text,const std::string delims)
	{
		unsigned long start=0;
		std::vector<std::string> ret;
		for(unsigned long i=0;i<text.size();++i)
		{
			for(unsigned long j=0;j<delims.size();++j)
			{
				if(text[i]==delims[j])
				{
					if(i-start==0)
					{
						start++;
						continue;
					}
					ret.push_back(text.substr(start,i-start));
					ret.push_back(".");
					start=i+1;
					break;
				}
			}
		}
		if(start<text.size())
			ret.push_back(text.substr(start));
		return ret;
	}

	std::vector<std::string> splitOnWords(const std::string text,const std::string delims)
	{
		unsigned long start=0;
		std::vector<std::string> ret;
		for(unsigned long i=0;i<text.size();++i)
		{
			for(unsigned long j=0;j<delims.size();++j)
			{
				if(text[i]==delims[j])
				{
					if(i-start==0)
					{
						start++;
						continue;
					}
					ret.push_back(text.substr(start,i-start));
					start=i+1;
					break;
				}
			}
		}
		if(start<text.size())
			ret.push_back(text.substr(start));
		return ret;
	}

	std::string trim(const std::string str)
	{
		for(unsigned long i=0;i<str.size();++i)
		{
			if(str[i]!=' ')
			{
				for(unsigned long j=str.size()-1;j>=0;--j)
				{
					if(str[j]!=' ')
						return str.substr(i, j-i+1);
				}
			}
		}
		return "";
	}

	std::string lowercase(std::string str)
	{
		for(int i=0;i<str.size();++i)
		{
			if(
				(str[i]>='A'&&str[i]<='Z')
				|| (unsigned int)str[i]>=4294967184&&(unsigned int)str[i]<=4294967215
			)
				str[i]=(unsigned char) ((unsigned int) str[i] + 32);
		}
		return str;
	}
}
