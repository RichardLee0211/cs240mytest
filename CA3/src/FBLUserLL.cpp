#include<iostream>
#include<vector>
#include<climits>

#include"FBLUserLL.h"
#include"FBLUser.h"
#include"util.h"

/**
 * constructor
 */
FBLUserLL::FBLUserLL(){
    this->head = NULL;
    this->end = NULL;
    this->curr = NULL;
    this->number = 0;
};

/**
 * deconstructor
 */
FBLUserLL::~FBLUserLL(){
    //cause free work has been down by quit()
    return;
}

/**
 * operate<<
 * TODO:
 */


/*
int FBLUserLL::create(){
    if(this->number==0){
        this->head = new FBLUser();
        this->end = this->head;
        this->curr = this->head;
        this->head->prev = NULL;
        this->end->next = NULL;
    }else{
        this->end->next = new FBLUser();
        this->end->next->prev = this->end;
        this->end=this->end->next;
        this->end->next = NULL;
    }
    this->number++;
    return 0;

};
*/

/**
 * CREATE <Userid> <Password> <First> <Last>
 * check out if userid is duplicate
 */
int FBLUserLL::create(string userID, string passwd, string firstName, string lastName){
    //TODO: check inputs

    /* check if userID is duplicate */
    FBLUser * tmp = this->head;
    while(tmp != NULL){
        if(tmp->getUserID() == userID){
            //TODO: how to do it with exception??
            return -1; //flag for duplicate
        }
        tmp = tmp->next;
    }

    /* if 0 */
    if(this->number==0){
        this->head = new FBLUser(userID, passwd, firstName, lastName);
        this->end = this->head;
        this->curr = this->head;
        this->head->prev = NULL;
        this->end->next = NULL;
    }
    /* if 1 or more */
#if 0
    // insert and the end of the list
    else{
        this->end->next = new FBLUser(userID, passwd, firstName, lastName);
        this->end->next->prev = this->end;
        this->end=this->end->next;
        this->end->next = NULL;
    }
#endif
    // insert to the head of the list
    else{
        this->head->prev= new FBLUser(userID, passwd, firstName, lastName);
        this->head->prev->next = this->head;
        this->head = this->head->prev;
        this->head->prev = NULL;
    }
    this->number++;
    return 0;

};

/**
 * LOGIN
 */
int FBLUserLL::login(){
    string userID;
    cout<<"please input your userID: ";
    cin>>userID;
    if(!userID.empty()){
        if(this->login(userID) != 0)
            return -1;
    }
    return 0;
};

/**
 * LOGIN <Userid>
 */
int FBLUserLL::login(string userID){
    string passwd;
    cout<<"input your passwd: ";
    cin>>passwd;
    if(this->login(userID, passwd) != 0)
        return -1;
    return 0;
}

/**
 * LOGIN <userid> <passwd>
 */
int FBLUserLL::login(string userID, string passwd){
    //TODO: to exam the userID

    uint count = 0;
    this->curr = this->head;
    while(this->curr != NULL){
        if(this->curr->getUserID() == userID &&
                this->curr->isCorrectPasswd(passwd)){
            this->curr->mainLoop();
            break;
        }
        this->curr = this->curr->next;
        count++;
    }
    if(count == this->number){
        return -1;
    }
    return 0;
}

/**
 * QUIT
 */
int FBLUserLL::quit(){
    cout<<endl<<"clearing allocated memory ..."<<endl;
    FBLUser* tmp = this->head;
    while(tmp != NULL){
        this->curr = tmp->next;
        delete tmp;
        tmp = this->curr;
    }
    return 1;
};

int FBLUserLL::mainLoop(){
    while(1){
        string strCmd;
        vector<string> vectCmd;
        cout<<endl;
        cout<<"this is Top interface"<<endl;
        cout<<"$create $login $users"<<endl;
        cout<<"$help"<<endl;
        cout<<"$quit"<<endl;
        cout<<"please input command:";
        getline(cin, strCmd);
#if DEBUG
        cout<<endl;
        cout<<"cmd from test: "<<strCmd<<endl;
        cout<<endl;

#endif
        splitString(strCmd, vectCmd, " ");
        if(vectCmd.empty()){
            cout<<"wrong cmd: empty cmd"<<endl;
#if DEBUG
            cout<<"ctrl-c to exit"<<endl;
            while(1);
#endif
        }
        else if(vectCmd[0]=="create" ||
                vectCmd[0]=="Create" ||
                vectCmd[0]=="CREATE"){
            if(vectCmd.size() == 5){
                this->create(vectCmd[1], vectCmd[2], vectCmd[3], vectCmd[4]);
            }else{
                this->create();
            }
        }
        else if(vectCmd[0]=="login" ||
                vectCmd[0]=="Login" ||
                vectCmd[0]=="LOGIN"){
            int result = -1;
            if(vectCmd.size() == 3){
                result = this->login(vectCmd[1], vectCmd[2]);
            }
            else if(vectCmd.size() == 2){
                result = this->login(vectCmd[1]);
            }
            else{
                result = this->login();
            }

            if(result == -1 ){
                cout<<"login fall"<<endl;
            }
        }
        else if(vectCmd[0]=="view" ||
                vectCmd[0]=="View" ||
                vectCmd[0]=="VIEW"){
            this->printLL();
        }
        else if(vectCmd[0]=="users" ||
                vectCmd[0]=="Users" ||
                vectCmd[0]=="USERS"){
            this->printLL();
        }
        else if(vectCmd[0]=="sortusers" ||
                vectCmd[0]=="SortUsers" ||
                vectCmd[0]=="SORTUSERS"){
            this->sortUsers();
        }
        else if(vectCmd[0]=="help" ||
                vectCmd[0]=="Help" ||
                vectCmd[0]=="HELP" ||
                vectCmd[0]=="h"){
            cout<<"$create: CREATE <Userid> <Password> <First> <Last>"<<endl;
            cout<<"$login: LOGIN <userID> <passwd>"<<endl;
            cout<<"$view: print out info of userLL"<<endl;
            cout<<"$quit: just quit, and recycle of allocated memory "<<endl;
        }
        else if(vectCmd[0]=="quit" ||
                vectCmd[0]=="Quit" ||
                vectCmd[0]=="QUIT"){
            this->quit();
            cout<< "good bye"<<endl;
            break;
        }
        else{
            cout<<endl<<"wrong cmd: "<<strCmd<<endl;
        }
    }

    return 0;
};

int FBLUserLL::printLL(){
    FBLUser* tmp = this->head;
    while(tmp != NULL){
        tmp->printUser();
        tmp = tmp->next;
    }
    return 0;

};

FBLUser* FBLUserLL::getPointer(string userID){
    FBLUser* tmp = this->head;
    while(tmp != NULL){
        if(tmp->getUserID() == userID)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
};

int FBLUserLL::sortUsers(){
    /* use simplest bubble sort */
    // not a good idea, cause tmp is float inside list,
    // for(FBLUser* tmp=this->head; tmp!=NULL && tmp->next!=NULL; tmp=tmp->next){
    for(uint i=0; i<this->number; i++){
        for(FBLUser* tmp2=this->head; tmp2!=NULL && tmp2->next!=NULL; tmp2=tmp2->next){
            if(*tmp2 > *tmp2->next){
                swap(tmp2, tmp2->next);
                tmp2 = tmp2->prev;
            }
        }
        /* reset this->head to head  */
        FBLUser* tmp=this->head;
        for(; tmp!=NULL && tmp->prev!=NULL; tmp=tmp->prev)
            ;
        this->head = tmp;
#if 0
        /* a other way to reset this->head */
        while(1){
            if(tmp!=NULL && tmp->prev != NULL){
                tmp = tmp->prev;
                continue;
            }
            else if(tmp!=NULL && tmp->prev==NULL)
                break;
        }
#endif
    }
    /* reset this->end to end */
    FBLUser* tmp=this->end;
    for(; tmp!=NULL && tmp->next!=NULL; tmp=tmp->next)
        ;
    this->end= tmp;
    return 0;
};
