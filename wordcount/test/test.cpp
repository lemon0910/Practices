#include "LibExecutive.h"
#include "../MessageClass.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

class CLWordCount
{
public:
	CLWordCount(string dirname, string filename)
	{
		m_dirname = dirname;
		m_filename = filename;
	}
	~CLWordCount()
	{}

	void fileWordCount(string filename)
	{
		FILE *fp = fopen(filename.c_str(), "r+");
		if(NULL == fp)
		{
			perror("fopen error");
			return;
		}
		string mystr;
		int ch;
		while((ch = getc(fp)) != EOF)
		{
			if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
				mystr += ch;
			else
			{
                if(mystr != "")
                {
                    map<string, int>::iterator it;
                    if(m_map.find(mystr) != m_map.end())
                    {
                        int temp = m_map[mystr];
                        m_map[mystr] = temp + 1;
                    }
                    else
                    {
                        m_map[mystr] = 1;
                    }

                    mystr = "";
                }
			}
		}
	}

	void dirWordCount(string dirname)
	{
		struct stat statbuf;
		struct dirent *dirp;
		DIR *dp;
		char *ptr;
		int ret = 0;

		if(lstat(dirname.c_str(), &statbuf) < 0)
		{
			perror("lstat error : ");
			return;
		}
		if(0 == S_ISDIR(statbuf.st_mode))
		{
			perror("the file is not a directory");
			return;
		}

		if(NULL == (dp = opendir(dirname.c_str())))
		{
			perror("opendir error : ");
			return;
		}

		while((dirp = readdir(dp)) != NULL)
		{
			if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
				continue;
			string entry = dirname + '/' + dirp->d_name;
			if(lstat(entry.c_str(), &statbuf) < 0)
			{
				perror("lstat error : ");
				return;
			}
			if(S_ISDIR(statbuf.st_mode))
			{
				dirWordCount(entry);
			}
			else
			{
            	fileWordCount(entry);
			}
		}
	}

	void process()
	{
		dirWordCount(m_dirname);
		fstream fs;
		fs.open(m_filename.c_str(), fstream::in | fstream::out | fstream::app);
		map<string, int>::iterator it;
		for(it = m_map.begin(); it != m_map.end(); ++it)
		{
			stringstream content;
			content << it->first << " " << it->second << '\n';
			fs << content.str();
		}
		fs.close();

	    CLWorkFinishMessage *pMessage = new CLWorkFinishMessage;
        pMessage->m_filename = "./test/" + m_filename;
		CLExecutiveNameServer::PostExecutiveMessage("mainThread", pMessage);
        CLExecutiveNameServer::GetInstance()->ReleaseCommunicationPtr("mainThread");
	}

private:
	string m_dirname;
	string m_filename;
	map<string, int> m_map;
};
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cerr << "usage ./a.out filename dirname" << endl;
		exit(-1);
	}

    if(!CLLibExecutiveInitializer::Initialize().IsSuccess())
    {
        cout << "Initialize error" << endl;
        return 0;
    }
	CLSharedExecutiveCommunicationByNamedPipe *pSender = new CLSharedExecutiveCommunicationByNamedPipe("mainThread");
	pSender->RegisterSerializer(CHILD_WORK_FINISH_MESSAGE_ID, new CLWorkFinishMessageSerializer);
	CLExecutiveNameServer::GetInstance()->Register("mainThread", pSender);
	CLWordCount wordCount(argv[1], argv[2]);
	wordCount.process();

    if(!CLLibExecutiveInitializer::Destroy().IsSuccess())
    {
        cout << "Destroy error" << endl;
    }
	return 0;
}

