#include <bits/stdc++.h>
#include "Flattening.h"
#include "Node.h"

/* Constructors */
Flattening::Flattening(std::vector<std::vector<int> > originalGraph){
    if(!check(originalGraph)){
        std::cout << "This graph is not suitable to represent a tree-like network" << std::endl;
        exit(0);
    }
    this->size = (int)originalGraph.size();
    for(int i = 0; i < this->size; i++)
        this->rede.push_back(new Node());
    for(int i = 0; i < this->size; i++)
        for(int x : originalGraph[i]){
            if(this->rede[i]->getParentID() == this->rede[x]->getMyID()) continue;
            this->rede[i]->addChild(this->rede[x]);
        }
}
/* End of Constructors */

/* Getters */
Node *Flattening::getNode(int id){
    if(id > this->size) return new Node(-1);
    for(auto x : this->rede){
        if(x->amI(id))
            return x;
    }
    return new Node(-1);
}
Node *Flattening::getNextNode(Node *curr, Node *target){
    if(curr->isRightDesc(target->getMyID()))
        return curr->getRightChild();
    if(curr->isLeftDesc(target->getMyID()))
        return curr->getLeftChild();
    return curr->getParent();
}
/* End of Getters */

/* Algorithms */
int Flattening::bottomUP(Node *curr, Node *req, Node *target, Node *pref){
    Node *parentNode = curr->getParent();
    Node *grandParent = parentNode->getParent();
    int typ = (curr->amRightChild() << 1) + parentNode->amRightChild();
    replaceChild(curr, parentNode, typ);
    grandParent->fix(curr, parentNode);
    if(!curr->amHigh(target->getMyID()))
		return this->bottomUP(curr, req, target, parentNode) + 1;
	return 1;
}
int Flattening::topDownSemi(Node *curr, Node *req, Node *target, Node *newParent){
    if(curr->amI(target->getMyID()) or curr->isChild(target->getMyID()))
        return 0;
    Node *nextNode = getNextNode(curr, target);
    Node *otherNode = curr->getOtherChild(nextNode);
    Node *dbNextNode = getNextNode(nextNode, target);
    childSwap(nextNode, curr, dbNextNode, otherNode);
	return topDownSemi(dbNextNode, req, target, curr) + 1;
}
int Flattening::hybridFlatten(Node *req, Node *target, int qryID){
    req->activate();
    target->activate();
    int ret = 0;
	if(!req->amHigh(target->getMyID())){
        Node *pref;
        if(req->getLeftChildID() != -1)
            pref = req->getLeftChild();
        else
            pref = req->getRightChild();
        ret += bottomUP(req, req, target, pref);
    }
    if(!req->isChild(target->getMyID())){
        ret += topDownSemi(req, req, target, req->getParent());
    }
    this->exportGraph(qryID);
	return ret;
}
/* End of Algorithms */

/* Auxiliary Functions */
int dfs(int u, int p, std::vector<int> &v, std::vector<std::vector<int> > originalGraph){
    v[u] = 1;
    int flag = 1;
    for(int w : originalGraph[u])
        if(!v[w]) flag &= dfs(w, u, v, originalGraph);
        else if(p != w) return 0;
    return flag;
}
int check(std::vector<std::vector<int> > originalGraph){
    std::vector<int> v;
    int isBinary = 1;
    for(int i = 0; i < (int)originalGraph.size(); i++){
        v.push_back(0);
        isBinary &= (originalGraph[i].size() <= 3);
    }
    int hasCycles = dfs(0, -1, v, originalGraph);
    int isConnected = 1;
    for(int x : v) isConnected &= x;
    return isConnected && hasCycles && isBinary;
}
void Flattening::printNetwork(){
    std::cout << "--------------------------" << std::endl;
    for(Node *toPrint : this->rede){
        printNode(toPrint);
        std::cout << "--------------------------" << std::endl;
    }
}
void Flattening::exportGraph(int qryID){
    std::string fileName = "./output/graph_states/graph" + std::to_string(qryID) + ".txt";
    std::ofstream outFile;
    outFile.open(fileName);
    if (!outFile) {
        std::cout << "Unable to open output file" << std::endl;
        exit(1); // terminate with error
    }
    int center = -1;
    outFile << this->size << std::endl;
    for(Node *x : this->rede)
        if(x->getParentID() == -1)
            center = x->getMyID();
    std::stack<std::pair<int, std::pair<int, std::pair<int, int> > > > auxStack;
    auxStack.push({center, {300,{1, 10000}}});
    while(!auxStack.empty()){
        auto par = auxStack.top(); auxStack.pop();
        Node *curr = getNode(par.first);
        int y = par.second.first;
        int x = (par.second.second.first+par.second.second.second)/2;
        outFile << curr->getMyID() << " " << curr->getCounter() << " " << x << " "  << y;
        if(curr->getLeftChildID() != -1){
            auxStack.push(std::make_pair(curr->getLeftChildID(), std::make_pair(y-10, std::make_pair(par.second.second.first, x))));
            outFile << " " << curr->getLeftChildID();
        }
        if(curr->getRightChildID() != -1){
            auxStack.push(std::make_pair(curr->getRightChildID(), std::make_pair(y-10, std::make_pair(x+1, par.second.second.second))));
            outFile << " " << curr->getRightChildID();
        }
        outFile << std::endl;
    }
    outFile << center << std::endl;
    outFile.close();
}
/* End of Auxiliary Functions */
