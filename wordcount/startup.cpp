#include "LibExecutive.h"
#include "CLMyMessage.h"

class CLWordObserver : public CLMessageObserver
{
public:
	CLWordObserver()
	{}
	~CLWordObserver()
	{
		for(int i = 0; i < m_processNumber; ++i)
			if(m_childprocess[i] != NULL)
				m_childprocess[i]->WaitForDeath();

		delete m_childprocess[i];
	}
	
	void getDirectory(string dirname)
	{
		m_dir.push_back(dirname);
	}

	virtual CLStatus Initialize(CLMessageLoopManager *pMessageLoop, void* pContext)
	{
		m_processNumber = m_dir.size();
		m_quitNumber = m_processNumber;
		m_childprocess = new CLExecutive *[m_processNumber];

		for(int i = 0; i < m_processNumber; ++i)
			m_childprocess[i] = NULL;

		pMessageLoop->Register(CHILD_FINISH_MESSAGE_ID, (CallBackForMessageLoop)(&CLFatherWordCountObserver::On_Child_Work_Finish));

		for(int i = 0; i < m_processNumber; ++i)
		{
			stringstream index;
			index << i;
			string directory = m_dir[i];
			string cmdForChild = string("./test/a.out") + " " + directory + " " + index;
			m_childprocess[i] = new CLProcess(new CLProcessFunctionForExec, true);
			if(!((m_childprocess[i]->Run((void*)(cmdForChild.c_str()))).IsSuccess()))
			{
				cerr << "process start error" << endl;
				m_childprocess[i] = NULL;
			}
		}

		return CLStatus(0, 0);
	}

	CLStatus On_Child_Work_Finish(CLMessage *pMessage)
	{
		CLWorkFinishMessage *pFinish = dynamic_cast<CLWorkFinishMessage*>(pMessage);
		string path = pFinish->m_filename;
		FILE *fp = fopen(path, "r");
		char buffer[101];
		string content;
		while(true)
		{
			if(NULL != fgets(buffer, 100, fp))
				content = buffer;
			else
				break;

			string word;
			int num = 0;
			int i = 0;
			while(content[i] != ' ')
			{
				word += content[i++];
			}
			i++;
			num = num * 10 + content[i++] - '0';
			if(m_wordMap.end() == m_wordMap.find(word))
			{
				m_wordMap.insert(pair<string, int>(word, num));
			}
			else
			{
				int temp = m_wordMap[word];
				m_wordMap[word] = temp + num;
			}
		}

		fclose(fp);		
		m_quitNumber--;
		if(0 == m_quitNumber)
		{
			map<string, int>::iterator it;
			for(it = m_wordMap.begin(); it != m_wordMap.end(); ++it)
			{
			cout << it->first << "  " << it->second << endl;
			}
			exit(0);
		}

		return CLStatus(0, 0);
	}

private:
	vector<string> m_dir;
	int m_processNumber;
	int m_quitNumber;
	CLExecutive **m_childprocess;
	map<string, int> m_wordMap;
};

int main(int argc, char *argv[])
{
	if(!CLLibExecutiveInitializer::Initialize().IsSuccess())
	{
		cerr << "initialize error" << endl;
		return 0;
	}

	if(argc < 2)
	{
		cout << "usage : dirname1 dirname2 ..." << endl;
		exit(-1);
	}

	CLWordObserver *myObserver = new CLWordObserver;
	for(int i = 0; i < argc - 1; ++i)
	{
		myObserver->getDirectory(argv[i + 1]);
	}

	CLNonThreadForMsgLoop mainThread(myObserver, "mainThread", EXECUTIVE_BETWEEN_PROCESS_USE_PIPE_QUEUE);
	mainThread.run(0);

	if(!CLLibExecutiveInitializer::Destroy().IsSuccess())
	{
		cerr << "destroy error" << endl;
	}

	return 0;
}