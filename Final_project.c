// include required libraries and my defined datatypes
#include <stdio.h>
#include <stdlib.h>
#include "std_types.h"
#define null 0

// define node (structre) for the patient information 
typedef struct pat{
	u8 name[200];
	u16 id;
	u16 gender;
	u16 age;
	s16 slot;
	struct pat *next;
}pat;

u8 i;
u16 slot[5] ; // array for reservation slots of the clinc
pat * head = null;

void verify (); // verification of admin password
void admin_mode(); // the features of admin mode  
void user_mode(); // the features of user mode 
void add(); // add new patient's record 
void delete(); // delete new patient's record
void edit(); //edit new patient's record
void view(); // show information of some patient
void view_patients(); // view full list of patients 
void view_slots(); // view list of reservation slots
void reserve(); // reserve a time slot in the clinc 
void cancel(); // cancel the reserved time slot 
pat* search(u16 id_req,u16 flag); // search about patient with id number (flag is the second parameter to return either pointer to node itself or address of pre node) 
u16 isempty(); // check if list is empty



void main(){
	
	while(1){
		u16 mode;
	
		printf("\n\t\tWelcome to Clinc Managment system\t\t\n");
		printf("For exit press 0\n");
		printf("For admin mode press 1\n");
		printf("For user mode press 2\n");
		printf("Enter:- ");
		scanf("%d",&mode);
	
		if(mode == 0){
			break;
		}
		
		else if(mode == 1){
			verify();
		}
    
		else if(mode == 2){
			user_mode();
		}

		else {
			printf("\nInvalid selection\n");
		}
		
	}
	
}












void verify(){
	
	// check three times for password 
	i=3;
	u16 password;
	do{
		printf("Please Enter the password:- ");
		scanf("%d",&password);
	}while(password != 1234 && (--i)>0);
	
	if(!i)
		printf("three times of incorrect password\nThank you\n\n");
	else
		admin_mode();
}
















void admin_mode(){
	
	u16 choice;
	
	printf("\n\nWelcome to the admin mode\n");
    printf("what do you want?\n");
    printf("1-Add patient record\n");
	printf("2-Edit patient record\n");
	printf("3-Delete patient record\n");
	printf("4-Reserve slot\n");
	printf("5-Cancel slot\n");
	printf("6-View all slots\n");
	printf("7-view all patients records\n");
	printf("8-view such patient\n");
	printf("0-exit\n");
    printf("choice:- ");
    scanf("%d",&choice);
	
	switch(choice){
		case 0:
			return ;
		break;
		case 1:
			add();
		break;
		case 2:
			edit();
		break;
		case 3:
			delete();
		break;
		case 4:
			reserve();
		break;
		case 5:
			cancel();
		break;
		case 6:
			view_slots();
		break;
		case 7:
			view_patients();
		break;
		case 8:
			view();
		break;
		default:
			printf("Invalid operation\n");
		break;
	}
	admin_mode();
}











void user_mode(){
	
	u16 choice;
	
	printf("\n\nWelcome to the user mode\n");
	printf("what do you want?\n");
	printf("1-View all slots\n");
	printf("2-View such patient\n");
	printf("0-exit\n");
    printf("choice:- ");
    scanf("%d",&choice);
	
	switch(choice){
		case 0:
			return ;
		break;
		case 1:
			view_slots();
		break;
		case 2:
			view();
		break;
		default:
			printf("Invalid operation\n");
		break;
	}
	user_mode();
}









void add(){
	
	
	u16 id_req;
	printf("Enter ID number:- ");
	scanf("%d",&id_req);
	
	// search with id (if the id is used , it will ask for a new one)
	while(search(id_req,0) != null){
		printf("\nthis id already exist\nEnter another id:- ");
		scanf("%d",&id_req);
	}
	
	pat * newnode = (pat *) malloc(sizeof(pat)); 
	
	newnode->id = id_req ;
	
    printf("Enter the name:- ");
	scanf("\n");
	scanf("%[^\n]%*c",newnode->name);
	
	printf("Enter the gender:- ");
	scanf("%d",&newnode->gender);
	
	printf("Enter the age:- ");
	scanf("%d",&newnode->age);
	
	newnode->slot = -1;
	newnode->next = null;
	
	if(head == null){ // for first time insertion 
		head = newnode;
	}
	else{ // for any insertion after that
		pat *curptr = head;
		
		while(curptr->next != null){
			curptr = curptr->next;
		}
		
		curptr->next = newnode;
	}
	
}












void edit(){
	if(isempty()){ // chech to avoid run time errors 
	printf("the list is empty\n");
	return ; 
	}
	
	u16 id_req;
	printf("Enter Id:- ");
	scanf("%d",&id_req);
	
	pat* ptr = search(id_req,0);
	
	if(ptr != null){
		printf("Enter the name:- ");
		scanf("\n");
		scanf("%[^\n]%*c",ptr->name);
	
		printf("Enter the age:- ");
		scanf("%d",&ptr->age);
	
		printf("Enter the gender:- ");
		scanf("%d",&ptr->gender);
	}
	else{
		printf("\nthis id not exist !!!!!\n");
	}
	
}








void view(){
	
	if(isempty()){
	printf("the list is empty\n");
	return ; 
	}
	
	u16 id_req;
	printf("Enter Id:- ");
	scanf("%d",&id_req);
	
	pat* ptr = search(id_req,0);
	
	if(ptr != null){
		printf("\nID:- %d\n",ptr->id);
		printf("Name:- %s\n",ptr->name);
		printf("Gender:- %d\n",ptr->gender);
		printf("Age:- %d\n",ptr->age);
		printf("today slots:- %d\n\n",ptr->slot);
	}
	else{
		printf("\nthis id not exist !!!!!\n");
	}
	
}







pat* search(u16 id_req,u16 flag){
	
	//flag 1 for delete function to can connect pre node of deleted node with next node 
	//flag 0 for other functions 
	pat* curptr = head;
	pat* preptr = null;
	
	while(curptr != null){
		if(curptr->id == id_req){
			return (!flag) ? curptr : preptr; 
		}			
		preptr = curptr;
		curptr = curptr->next;
	}
	
	return curptr ; //return null if id wasn't found
}







void delete(){
	if(isempty()){
		printf("the list is empty\n");
		return;
	}
	
	
	pat* curptr = head;
	pat* preptr = null;
	pat* temp = head ;
	u16 id_req;
	printf("Enter Id:- ");
	scanf("%d",&id_req);
	
	if(curptr->id == id_req){ // check if first node will be deleted 
		head  =  head -> next ;
		if(temp->slot != -1){ // check if this patient already has a reservation
		slot[(temp->slot)-1] = 0;
		temp->slot = -1;
		}
		free(temp);
		return ;
	}
	
	pat* ptr = search(id_req,1);
	
	if(ptr == null){
		printf("ID not Founed!!!!\n");
		return ;
	}
	
	
	temp = ptr->next;
	ptr->next = temp->next;
	if(temp->slot != -1){
		slot[(temp->slot)-1] = 0;
		temp->slot = -1;
	}
	free(temp);
	
}










void view_patients(){
	if(isempty()){
		printf("the list is empty\n");
		return ;
	}
	
	pat *curptr = head;
		
	while(curptr != null){
		printf("\nID:- %d\n",curptr->id);
		printf("Name:- %s\n",curptr->name);
		printf("Gender:- %d\n",curptr->gender);
		printf("Age:- %d\n",curptr->age);
		printf("today slots:- %d\n",curptr->slot);
		curptr = curptr->next;
	}
		
	printf("\n__________________\n");
}










void reserve(){
	if(isempty()){
		printf("the list is empty\n");
		return ;
	}
	
	u16 hour=2,min=3;
	printf("\nAvalibale slots\n"); 
	for(i=0;i<5;i++){
		if (!slot[i]){
			printf("%d- From %d:%d0 to",i+1,hour,min%6);
			min += 3 , hour += min/6 , min = min%6;
			printf("%d:%d0\n",hour,min);
		}
	}
	
	u16 id_req,slot_req;
	
	printf("Enter the slot you want:- ");
	scanf("%d",&slot_req);
	printf("Enter id:-");
	scanf("%d",&id_req);
	
	pat * ptr = search(id_req,0);
	
	if((ptr == null) || (slot_req > 5 || 1 > slot_req)){
		printf("\nInvalid id or slot number\n");
		return ;
	}
	
	if(slot[slot_req-1]){ // check availability of time slot 
		printf("Reserved slot\n");
		return ;
	}
	
	if(ptr->slot != -1){ //check reservation time of patient
		printf("The patient already has a reservation\n");
		return ;
	}
	
	ptr->slot = slot_req;
	slot[slot_req-1] = id_req;
	
}


















void cancel(){
	
	if(isempty()){
		printf("the list is empty\n");
		return ;
	}
	
	u16 id_req;
	
	printf("Enter id:-");
	scanf("%d",&id_req);
	
	pat * ptr = search(id_req,0);
	
	if(ptr == null){
		printf("\nID Not Found\n");
		return ;
	}
	
	if(ptr->slot != -1){
		slot[(ptr->slot)-1] = 0;
		ptr->slot = -1;
	}
	
}




















void view_slots(){
	printf("from 2:30 to 3:00:- ");
	(!slot[0]) ? printf("Availabale\n") : printf("Reserved:%d\n",slot[0]) ;
	printf("from 3:00 to 3:30:- ");
	(!slot[1]) ? printf("Availabale\n") : printf("Reserved:%d\n",slot[1]) ;
	printf("from 3:30 to 4:00:- ");
	(!slot[2]) ? printf("Availabale\n") : printf("Reserved:%d\n",slot[2]) ;
	printf("from 4:00 to 4:30:- ");
	(!slot[3]) ? printf("Availabale\n") : printf("Reserved:%d\n",slot[3]) ;
	printf("from 4:30 to 5:00:- ");
	(!slot[4]) ? printf("Availabale\n") : printf("Reserved:%d\n",slot[4]) ;
}


u16 isempty(){
    return (head == null) ?  1 : 0 ; 
}














