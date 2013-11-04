#include "LibExecutive.h"

/*class CLChildObserver : public CLMessageObserver
{
public:
	CLChildObserver(){}
	~CLChildObserver(){}
	void setFilename(string filename, string dirname)
	{
		m_filename = filename;
		m_dirname = dirname;
	}

	virtual CLStatus Initialize(CLMessageLoopManager *pMessageLoop,void* pContext)
	{
		pMessageLoop->Register(CHILD_WORK_FINISH_MESSAGE_ID, (CallBackForMessageLoop)(&CLChildObserver::On_Word_Process));
		
		CLSharedExecutiveCommunicationByNamedPipe *pSender = new CLSharedExecutiveCommunicationByNamedPipe("mainThread");
		pSender->RegisterSerializer(CHILD_WORK_FINISH_MESSAGE_ID, new CLWorkFinishMessageSerializer);
		CLExecutiveNameServer::GetInstance()->Register("mainThread", pSender);
		//CLExecutiveNameServer::PostExecutiveMessage("father_pipe",pChildInitMsg);
        
		return CLStatus(0,0);
	}

	CLStatus On_Word_Process(CLMessage *pm)
	{
		CLWorkFinishMessage *pMessage = dynamic_cast<CLWorkFinishMessage*>(pm);
		if(0 == pMessage)
			return CLStatus(0,0);

		CLWordCount wordCount(m_filename);
		wordCount.process();
		
		return CLStatus(0,0);
	}

private:
	string m_filename;
	string m_dirname;
};

int main(int argc, char *argv[])
{
	if(3 != argc)
	{
		cerr << "usage : ./a.out filename dirname" << endl;
		exit(-1);
	}

	if(!CLLibExecutiveInitializer::Initialize().IsSuccess())
	{
		cerr << "initialize error" << endl;
		return 0;
	}


	CLChildObserver *myObserver = new CLChildObserver;
	myObserver->setFilename(argv[1], argv[2]);

	CLNonThreadForMsgLoop mainThread(myObserver, "mainThread", EXECUTIVE_BETWEEN_PROCESS_USE_PIPE_QUEUE);
	mainThread.run(0);

	if(!CLLibExecutiveInitializer::Destroy().IsSuccess())
	{
		cerr << "destroy error" << endl;
	}

	return 0;
}
*/

class CLWordCount
{
public:
	CLWordCount(string dirname, filename)
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
			return -1;
		}
		if(0 == S_ISDIR(statbuf.st_mode))
		{
			perror("the file is not a directory");
			return -1;
		}

		if(NULL == (dp = opendir(dirname.c_str())))
		{
			perror("opendir error : ");
			return -1;
		}

		while((dirp = readdir(dp)) != NULL)
		{
			if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
				continue;
			string entry = dirname + '/' + dirp->d_name;
			if(lstat(entry, &statbuf) < 0)
			{
				perror("lstat error : ");
				return -1;
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
		fs.open(m_filename, fstream::in | fstream::out | fstream::app);
		map<string, int>::iterator it;
		for(it = m_map.begin(); it != m_map.end(); ++it)
		{
			sstream content;
			content << it->first << " " << it->second << '\n';
			fs << content.c_str();
		}
		fs.close();

		CLSharedExecutiveCommunicationByNamedPipe *pSender = new CLSharedExecutiveCommunicationByNamedPipe("mainThread");
		pSender->RegisterSerializer(CHILD_WORK_FINISH_MESSAGE_ID, new CLWorkFinishMessageSerializer);
		CLExecutiveNameServer::GetInstance()->Register("mainThread", pSender);
		CLExecutiveNameServer::PostExecutiveMessage("mainThread", CLWorkFinishMessage);
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

	CLWordCount wordCount(argv[1], argv[2]);
	wordCount.process();

	CLSharedExecutiveCommunicationByNamedPipe *pSender = new CLSharedExecutiveCommunicationByNamedPipe("mainThread");
	pSender->RegisterSerializer(CHILD_WORK_FINISH_MESSAGE_ID, new CLWorkFinishMessageSerializer);
	CLExecutiveNameServer::GetInstance()->Register("mainThread", pSender);
	CLMessage *pMessage = new CLWorkFinishMessage;
	pMessage->m_filename = argv[2];
	CLExecutiveNameServer::PostExecutiveMessage("mainThread", pMessage);

	return 0;
}

