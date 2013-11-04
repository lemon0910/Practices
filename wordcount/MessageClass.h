#ifndef MESSAGECLASS_H
#define MESSAGECLASS_H

#define CHILD_WORK_FINISH_MESSAGE_ID 0

class CLWorkFinishMessage : public CLMessage
{
public:
	CLWorkFinishMessage() : CLMessage(CHILD_WORK_FINISH_MESSAGE_ID)
	{}
private:
	string m_filename;
};

class CLWorkFinishMessageSerializer : public CLMessageSerializer
{
public:
	virtual char *Serialize(CLMessage *pMsg,unsigned int *pFullLength,unsigned int HeadLength)
	{
		CLWorkFinishMessage *pMessage = dynamic_cast<CLWorkFinishMessage *>(pMsg);
		if(0 == p)
		{
			cerr "CLWorkFinishMessage error" << endl;
			return 0;
		}

		unsigned int t_len = pMessage->m_filename.size();
        *pFullLength = HeadLength  + sizeof(long) + sizeof(unsigned int) + t_len;
		char *pBuf = new char[*pFullLength];

		long *pId = (long *)(pBuf + HeadLength);
		*pId = p->m_clMsgID;

		unsigned int *len = (unsigned int *)(pBuf + HeadLength + sizeof(long));
		*len = t_len;
     
        char *filename = (char *)(pBuf + HeadLength + sizeof(long) + sizeof(unsigned int));
		memcpy(filename, p->m_filename.c_str(), t_len);

		return pBuf;
	}
};

class CLWorkFinishMessageDeserializer : public CLMessageDeserializer
{
public:
	virtual CLMessage *Deserialize(char *pBuffer)
	{
		long id = *((long *)pBuffer);
		if(id != CHILD_WORK_FINISH_MESSAGE_ID)
			return 0;

		CLChildInitMsg *pMessage = new CLWorkFinishMessage;
		
		unsigned int t_len = *((unsigned int *)(pBuffer + sizeof(id)));
		char str[t_len + 1];
		memset(str,0,sizeof(char) * (t_len + 1));

		const char* filedname = (char *)(pBuffer + sizeof(id) + sizeof(t_len));
		memcpy(str, filename, t_len);
		pMessage->m_filename = string(str);

		return pMessage;
	}
};

#endif