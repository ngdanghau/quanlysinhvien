#include "lop.h"

using namespace std;

DSLOPPTR ListLop;
void Initialize_LH(DSLOPPTR &ListLop){
   ListLop = NULL;
}

int DeleteInfo_LH(DSLOPPTR &ListLop, char *malh){  
	DSLOPPTR p = ListLop, q;
  	if (ListLop == NULL ) return 0;
  	if ( strcmp(ListLop->MALOP, malh) == 0 ) {
	    p = ListLop;
		ListLop = p->next;
		delete p; 
		
		return 1;
	}
    
	for ( p = ListLop; p->next!=NULL &&  strcmp(p->next->MALOP, malh) != 0; p = p->next);
	if (p->next!= NULL ) {
		q = p->next; 
		p->next=q->next;
		delete q; 
		return 1;
	}
	return 0;
}

void ClearList_LH(DSLOPPTR &ListLop){
   DSLOPPTR p, q;
   p = ListLop;
   while(ListLop != NULL)
   {
      p = ListLop;
      ListLop = ListLop->next;
      delete p;
   }
   ListLop = NULL;
}

int Reccount_LH(DSLOPPTR &ListLop) {
	if(ListLop == NULL) return 0;
	
	int count = 0;
	DSLOPPTR p = ListLop;
	while(p != NULL){
		count++;
		p = p->next;
	}
	return count;
}

void Traverse_LH(DSLOPPTR ListLop){
   	DSLOPPTR p = ListLop;
   	int stt = 0;
   	while(p != NULL)
   	{
      	printf("%3d %8s\t\n", ++stt, p->MALOP);
      	p = p->next;
   	}
}

DSLOPPTR Search_LH(DSLOPPTR ListLop, char *malh){
	if(ListLop == NULL) return NULL;
	DSLOPPTR p;
	for (p = ListLop;  p != NULL ; p=p->next ) 
        if ( strcmp(p->MALOP, malh) == 0  ) return p;
	return NULL;
}

void Insert_Last_LH(DSLOPPTR &ListLop, char *malh){
    DSLOPPTR p = new NodeLop;
    strcpy(p->MALOP, malh);
    p->next = NULL;
      
    if(ListLop == NULL) 
		ListLop = p;
    else{
      	DSLOPPTR Last = ListLop;
      	for(; Last->next != NULL; Last = Last->next);
      	Last->next = p;
	}
}

void Load_LopHoc()
{ 
	Initialize_LH(ListLop);
	char filename[50] = "data\\DSLH.TXT";
  	ifstream file(filename);
	
	if (!file.is_open())
	{
		cout << "File Khong Ton Tai";
		return;
	}
	
	string temp;
	char malophoc[50];
	while (!file.eof())
	{
		getline(file, temp);
		strcpy(malophoc, temp.c_str());
		Insert_Last_LH(ListLop, malophoc);
	}
	file.close();
}

void PrintDataLopHoc(){
	Traverse_LH(ListLop);
}


