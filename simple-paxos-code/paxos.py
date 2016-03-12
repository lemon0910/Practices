# 一轮Paxos协议的流程
# 此处为了清晰将proposer和acceptor的逻辑分开写了，实际上原论文中一个server既可以做proposer也可以做acceptor

# 对每一个值(比如logid唯一的一条日志)可能会同时发起写请求(比如两个客户端并发访问qorumn里面的两个server)
# 所以此时这两个server都是proposer，针对同一条logid发起不同ballot number的决议请求。此时，如果是ballot number 
# 小的那个决议请求先达到多数派，那么应该保证后到的ballot number的请求使用相同的值。所以Acceptor需要做的事情如下：
# prepare phase:
# 1.如果请求的req_ballot_id比当前server已经应答过的last_ballot_id小，此时直接忽略，因为有更新的投票决议。
# 2.如果请求的req_ballot_id大于等于当前server已经应答过的last_ballot_id，此时使用req_ballot_id更新last_ballot_id，
#   并返回last_voted_value，注意这个可以是空，说明要么是当前这个server以前未参与此值的多数派投票，要么是此值还未达成过多数派投票。
# commit phase:
# 1.如果commit消息数据中的ballot_id与last_ballot_id不同，则放弃
# 2.否则更新相应的值，并写日志
class Acceptor(object):
    last_ballot_id = None #我正在等着
    last_voted_value = None
    last_voted_ballot_id = None 
    servers = []
    def handleProposalRequest(self, reqData):
        req_ballot_id = reqData.ballot_id
        if req_ballot_id <= self.last_ballot_id:
            pass # return nothing 
        else:
            self.last_ballot_id = req_ballot_id 
            return (self.last_ballot_id, self.last_voted_value, self.last_voted_ballot_id)

    def handleCommitRequest(self, reqData):
        commit_ballot_id = reqData.last_sent_ballot_id
        client_value = reqData.client_req_value 
        if commit_ballot_id != self.last_ballot_id:
            pass 
        self.last_ballot_id = self.last_voted_ballot_id = reqData.last_sent_ballot_id
        self.last_voted_value = client_value 
        writelog((self.last_ballot_id, self.last_voted_ballot_id, self.last_voted_value))

    def writelog(self, data):
        pass 

# 1.如果有acceptor接收到其他proposal发出的更大ballot_id的决议请求，那么放弃此次决议　
# 2.如果为达到多数派，放弃此次决议
# 3.如果acceptor中返回的last_voted_value不为空，则将当前proposal的值设置为相同值，进入commit阶段，
#   否则直接用client_req_value作为值进入commit
class Proposer(object):
    last_sent_ballot_id = None 
    client_req_value = None 
    res_data = []
    servers = []
    quorumn_number = 5
    
    def sendRequest(self, data):
        pass 
    def sendProposal(self):
        self.last_sent_ballot_id += 1
        reqData.ballot_id = self.last_sent_ballot_id
        for i in self.servers:
            sendRequest(i, reqData)

    def readData(server):
        pass
    def handleEachProposalResponse(self, server):
        resData = self.readData(server)
        self.res_data.append((resData.last_ballot_id, resData.last_voted_value, resData.last_voted_ballot_id))
    def handleProposalResponse(self):
        for i in servers:
            handleEachProposalResponse(servers[i])
        res_ballot_id = max([i[0] for i in self.res_data])
        if res_ballot_id > self.last_sent_ballot_id:
            pass # maybe another proposer has finished a proposal for the value, what should we give back to client? 
        elif len(res_data) < (self.quorumn_number / 2 + 1):
            pass # failed, maybe timeout due to network or server crash?
        else:
            voted_data = [(i[1], i[2]) for i in self.res_data]
            voted_data.sort()
            if voted_data[0][1] is not None:
                self.client_req_value = voted_data[0][1] 
            self.commit((self.last_sent_ballot_id, self.client_req_value))

    def commit(self, reqData):
        pass