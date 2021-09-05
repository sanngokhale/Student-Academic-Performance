/*
DSA Miniproject Semester 1
 Problem statement-
 To make a user-friendly application of the data structure to add, maintain and retrieve the academic details including
the toppers, failed students, rank holders etc. of a class.
Team-2923, 2924, 2925, 2914

Data Structure used - Singly Linked list
Sorting Technique used - Merge Sort 
 */

#include <iostream>
using namespace std;

int check(){                    //check if the input entered by the user is int or not
    string temp;
    cin>>temp;
    int flag=0;
    while(flag==0){
        for(int i=0;i<temp.size();i++){
            if(!isdigit(temp[i])){
                flag=0;
                break;
            }
            else{
                flag=1;
            }
        }
        if(flag==0){
            cout<<"\t\t\t\t\tEnter valid input!  :";
            cin>>temp;
        }
    }
    return stoi(temp);
}


class Student{
    protected:
	string Name;
	string grade;
	int rollNo;
	int DSA, OS, FCN, EM, MA;
    bool fate;
    int rank;

    public:
    double percentage;
    friend class Rank;
    friend class List;
    Student(){              //Student class constructor
        Name="";
        grade="X";
        rollNo=-1;
        fate=false;
        percentage=0.0;
        DSA=-1, OS=-1, FCN=-1, EM=-1, MA=-1;
        rank=-1;
    }

    void validate(){                    //checks if marks are valid
        cout<<"\t\t\t\t\tDSA: ";
        DSA=check();
        while(DSA<0 || DSA>100){
            cout<<"\t\t\t\t\tEnter valid marks for DSA!  :";
            DSA=check();
        }
        cout<<"\t\t\t\t\tOS: ";
        OS=check();
        while(OS<0 || OS>100){
            cout<<"\t\t\t\t\tEnter valid marks for OS!  :";
            OS=check();
        }
        cout<<"\t\t\t\t\tFCN: ";
        FCN=check();
        while(FCN<0 || FCN>100){
            cout<<"\t\t\t\t\tEnter valid marks for FCN!  :";
            FCN=check();
        }
        cout<<"\t\t\t\t\tEM: ";
        EM=check();
        while(EM<0 || EM>100){
            cout<<"\t\t\t\t\tEnter valid marks for EM!  :";
            EM=check();
        }
        cout<<"\t\t\t\t\tMA: ";
        MA=check();
        while(MA<0 || MA>100){
            cout<<"\t\t\t\t\tEnter valid marks for MA!  :";
            MA=check();
        }
    }



	void accept(){              //accept student details
		cout<<"\t\t\t\t\tEnter Name: ";
		cin.ignore(1,'\n');
		getline(cin,Name);
		cout<<"\t\t\t\t\tEnter Roll Number: ";
		rollNo=check();
		cout<<"\t\t\t\t\tEnter Marks: "<<endl;
		validate();
	}

    void percentage_calc(){                             //calculate percentage
    percentage = ((DSA + OS + FCN +EM + MA)*100)/500;
        }

    void _grade(){                                                        //set grade as per percentage
        if(percentage<=100 && percentage>90) {grade = "O";fate=true;}
        else if(percentage<=90 && percentage>80) {grade = "A+";fate=true;}
        else if(percentage<=80 && percentage>70) {grade = "A";fate=true;}
        else if(percentage<=70 && percentage>60) {grade = "B";fate=true;}
        else if(percentage<=60 && percentage>50) {grade ="C";fate=true;}
        else if(percentage<=50 && percentage>40) {grade ="D"; fate=true;}
        else if(percentage<=40 && percentage>30) {grade = "E"; }
        else if(percentage<=30 && percentage>0) {grade = "F"; }
    }

    void display(){
        cout<<"\t\t\t\t\t-----------------------------------------------------------------------------"<<endl;                                                   //display student details
        cout<<"\t\t\t\t\tStudent details : "<<endl;;
        cout<<"\t\t\t\t\tName: "<<Name<<endl<<"Roll No.: "<<rollNo<<endl;
    cout<<"\t\t\t\t\tPercentage: "<<percentage<<"%"<<endl;
        cout<<"\t\t\t\t\tGrade  : "<< grade<<endl;
        fate? cout<<"\t\t\t\t\t"<<Name<<" has passed !!" : cout<<"\t\t\t\t\t"<<Name<<" has failed !!"<<endl;
        cout<<"\t\t\t\t\tRank: "<<rank<<endl;
        cout<<"\t\t\t\t\t-----------------------------------------------------------------------------"<<endl;
        }
 };


class Node{                   //Node class
    public:
  Student *data;
  Node *next;
  Node()
  {
      next=NULL;
  }
};

class Rank{                     //Rank class to sort by percentage
public:
 Node* createNew(Student* s1){
   Node *temp=new Node();
   temp->data=s1;
   return temp;
 }


Node *midNode(Node* head, Node* tail){          //calculate mid node of linked list
    Node *fast = head;
    Node*slow = head;
    while(fast!=tail && fast->next!=tail ){
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}


Node *merge(Node * head1, Node* head2){         //to merge two linked lists
Node* p1 = head1;
Node*p2 = head2;
Node* sorted = new Node();
Node* p3 = sorted;                              //p3 traverses the new linked list
	while(p1!=NULL && p2!=NULL){
	if(p1->data->percentage > p2->data->percentage){
		p3->next = p1;
		p1=p1->next;
	}
	else{
		p3->next = p2;
		p2 = p2->next;
	}
	p3 = p3->next;
	}
	while(p1!=NULL){
		p3->next = p1;
		p1 = p1->next; p3 = p3->next;
		}
	while(p2!=NULL){
		p3->next = p2;
		p2 = p2->next; p3 = p3->next;
	}
	return sorted->next;
}


Node* mergeSort(Node* head, Node* tail){        //merge sort to sort given linked list
	if(head==tail){
        Node* base = new Node();
        base = createNew(head->data);
        return base;
	}
        Node *mid = midNode(head,tail);                     //find mid of linked list
        Node* first_half = mergeSort(head, mid);            //call recursively on left part of the linked list
        Node* second_half = mergeSort(mid->next , tail);      //call recursively on right part of the linked list
        Node* completeList = merge(first_half, second_half);    //merge the two parts
        return completeList;
	}
};


class List: public Rank{
  public:
  Node *head;
  Node *tail;
  List(){
      head=NULL;
      tail=NULL;
  }
  void create();
  void search();
  void deleteNode();
  void displayList();
  void display();
  void insert();
  int count();
  void setRank();
  void topper();
  void fail();
  float average();
  void avgCompare(float);
 };

void List::setRank(){               //traverse the sorted list and set rank
	Node * ptr = head;
	int Rank = 1;
	while(ptr!=0){
		ptr->data->rank = Rank;
		Rank++;
		ptr= ptr->next;
	}
}


void List::create(){		    	//create a new student record and add it to the list
	int choice;
	while(choice){		            //while the user wants to add more students
		Student *s1=new Student();
		cout<<"\t\t\t\t\t------Enter the Student details------"<<endl;;
		s1->accept();
		Node * ptr=head;
		bool flag=false;
		while(ptr!=0){
            if(s1->rollNo==ptr->data->rollNo){
                flag=true;
                break;
            }
            ptr=ptr->next;
		}
		if(!flag){
		s1->percentage_calc();
		s1->_grade();
		Node *temp=new Node();
		temp->data=s1;
		if(head==NULL){             //if list is empty add to head
			head=temp;
			tail = temp;
		}
		else{                       //else traverse till the end
			Node *ptr=head;
			while(ptr->next!=NULL){
				ptr=ptr->next;
		}
		ptr->next=temp;
		tail = temp;
		}
	   }
	   else{
        cout<<"\t\t\t\t\tRoll number already exists! Cannot add this student!"<<endl;
	   }
	   cout<<"\t\t\t\t\tDo you want to add 1 more student?? 1.Yes 0.No   ";
	   cin>>choice;
	}
   head=mergeSort(head, tail);        //call merge sort to sort the recently added students by percentage
   setRank();                           //set rank in sorted list
}


void List::search(){            //search a given roll no.
    if(head==NULL){
        cout<<"\t\t\t\t\tList is empty!"<<endl;
        return;
    }
     int key_roll;
     cout<<"\t\t\t\t\tEnter Roll number whose performance is to be displayed: ";
     key_roll=check();
     Node *ptr=head;
     while(ptr!=NULL && ptr->data->rollNo!=key_roll){
        ptr=ptr->next;
     }
     if(ptr==NULL){                         //if ptr reached the end and haven't found the roll no.
         cout<<"\t\t\t\t\tNot found"<<endl;
     }
     else {
     ptr->data->display();                  //else display data
     }
}



void List::displayList(){                   //display full linked list
	if(head==NULL){
		cout<<"\t\t\t\t\tList is empty!"<<endl;
		return;
	}
     Node *ptr=head;
    cout<<"\t\t---------------------------------------------------------------------------------------"<<endl;
     cout<<"\t\t\t\t\tStudents List :"<<endl;
    while(ptr!=NULL){
      cout<<"\t\t\t\t\tRank : "<<ptr->data->rank<<"  Roll no.: "<<ptr->data->rollNo<<"   Name : "<<ptr->data->Name<<endl;
      ptr=ptr->next;
     }

}

void List::deleteNode(){                            //delete student by roll no.
	if(head==NULL)cout<<"\t\t\t\t\tCannot delete as the list is empty"<<endl;
		else{
			int rollN, flag=0;
			cout<<"\t\t\t\t\tEnter Roll no to be deleted : ";
			rollN=check();
			Node*ptr, *prev;
			ptr = prev = head;
			if(head->data->rollNo==rollN){      //if found in head, update head
				Node*temp = head;
				head = head->next;
				flag = 1;
				delete temp;
			}
			else{                               //else traverse till the end
			while(ptr!=NULL){
				if(ptr->data->rollNo==rollN)        //if found, set flag, break out of the loop
				{
				    flag=1;
				    break;
				}
				prev=ptr;
				ptr=ptr->next;
			  }
            if(flag==1){                            //if found delete
				prev->next=ptr->next;
				cout<<"\t\t\t\t\tThe record of "<<ptr->data->Name<<" is deleted."<<endl;
				delete ptr;
            }
		}
			if(flag==0)cout<<"\t\t\t\t\tRoll no not found!!"<<endl;       //not found
		}
	setRank();                                                  //update rank after deletion
}


int List::count(){          //count total number of students in list
    Node *ptr=head;
    int cnt=0;
    while(ptr!=NULL)
    {
        cnt++;
        ptr=ptr->next;
    }
    return cnt;
}


float List::average(){                                   //calculate average of the class
	if(head==NULL){cout<<"\t\t\t\t\tList is empty!!"<<endl;return 0;}
	else{
     Node* ptr=head;
     float total=0;
    while(ptr!=0){                          //traverse till the end and add percentages to total
        total+=ptr->data->percentage;
        ptr=ptr->next;
    }
  return total/count();                     //return average
	}
}
void List::avgCompare(float avg){
    int rn;                             //Compare the student's percentage with the class average
    int flag=0;                         //and print whether the student's score is below or above average
    Node* ptr=head;
    if(head==NULL){
    	return;
    }
    cout<<"\t\t\t\t\tEnter Roll no to be compared : ";
	rn=check();
	if(head->data->rollNo==rn){
       ptr=head;
       flag=1;
	}
	else {
        while(ptr!=0){                //search for the roll no.
        	if(ptr->data->rollNo==rn){
        		flag=1;					//if roll number is now found, break from the loop
        		break;
        	}
            ptr=ptr->next;
        }
	}
        if(flag==1){
		cout<<"\t\t\t\t\tClass average: "<<avg<<"   "<<"Student's Percentage: "<<ptr->data->percentage<<endl;
		if(ptr->data->percentage>=avg){
			cout<<"\t\t\t\t\t"<<ptr->data->Name<<"'s percentage is above average."<<endl;
		}
		else{
			 cout<<"\t\t\t\t\t"<<ptr->data->Name<<"'s percentage is below average."<<endl;
		}
        }
        else cout<<"\t\t\t\t\tRoll no not found !!"<<endl;
}


void List::topper(){                //find rank holders of the list
    if(head==NULL){
        cout<<"\t\t\t\t\tList is empty!"<<endl;
        return;
		}
    Node* ptr=head;
    cout<<"\t\t"<<"+------------------------------------------------------------------------+"<<endl;
    for(int i=0;i<3 && ptr!=0;i++,ptr=ptr->next){
        cout<<"\t\t   Rank: "<<ptr->data->rank<<"  Roll no.: "<<ptr->data->rollNo<<"\t"<<"Name : "<<ptr->data->Name<<"\t"<<"Percentage : "<<ptr->data->percentage<<"% "<<endl;
    }
    cout<<"\t\t"<<"+------------------------------------------------------------------------+"<<endl;
}


void List::fail(){          //find the students who have failed
    if(head==NULL){
        cout<<"\t\t\t\t\tList is empty!"<<endl;
        return;
    }
	Node *ptr=head;
	int count = 0;      //to count number of failed students
	for(; ptr!=0 && ptr->data->fate==true ; ptr=ptr->next);     //traverse from head till all passed students are done
	while(ptr!=0){                                              //traverse from the start of failed students and display them
		cout<<"\t\t\t\t\tRoll no.:"<<ptr->data->rollNo<<"\t"<<"Name:"<<ptr->data->Name<<"\t"<<"Percentage: "<<ptr->data->percentage<<"%"<<endl;
		ptr=ptr->next;
		count += 1;
	  }
	if(count==0)cout<<"\t\t\t\t\tNo one has failed !!"<<endl;
	else cout<<"\t\t\t\t\tNumber of failed students: "<<count<<endl;
}


int main(){
List l;
int choice=-1;
cout<<"\t\t-------------------------------------------------------------------------------------------"<<endl;
cout<<"\t\t\t\t\t**********  Students Academic Performance   **********"<<endl<<endl;
 while(choice){
	    cout<<endl<<"\t\t-------------------------------------------------------------------------------------------"<<endl;

	  cout<<"\t\t\t\t\t0.Exit\n\t\t\t\t\t1.Add a new student\n\t\t\t\t\t2.Display Student list\n\t\t\t\t\t3.Display a Student's performance\n\t\t\t\t\t4.Average Score of class"<<endl;
    cout<<"\t\t\t\t\t5.Display Rank holders\n\t\t\t\t\t6.Display failed Students\n\t\t\t\t\t7.Delete a student Record\n\t\t\t\t\t8.Total number of students\n\t\t\t\t\t9.Compare with Average"<<endl;
  cout<<"\t\t\t\t\tEnter choice: ";
  choice=check();
    	switch(choice){
    	case 1 : //Add a new student
    		 l.create();
    		break;
    	case 2 : //Display Student list
    	    l.displayList();
    	    break;
    	case 3 : //Display a Student's performance
    	    l.search();
    	    break;
    	case 4 : //Average Score of class
    		l.average()? cout<<"Average of class: "<<l.average()<<"%"<<endl : cout<<"Cannot find Average"<<endl;
    	    break;
    	case 5 : //Display 5 Toppers
    	    l.topper();
    	    break;
    	case 6 : //Display failed Students
                l.fail();
    	     break;
    	case 7 ://Delete A student Record
    	    l.deleteNode();
    	    break;
    	case 8 : //Total number of students
    	    cout<<"Total number of Students: "<<l.count()<<endl;
    	    break;
        case 9 : //Compare with Average
            l.avgCompare(l.average());
    		break;
        default: cout<<"Enter valid input"<<endl;
            break;
    	}
    }
}

/*
=======================================================================================
TIME COMPLEXITIES:

void Student::accept()              =   O(1)
void Student::percentage_calc()     =   O(1)
void Student::_grade()              =   O(1)
void Student::display()             =   O(1)

Node* mergeSort()		    = O(nlogn)

void List::setRank()                =   O(n)
void List::topper()                 =   O(1)
int List::count()                   =   O(n)
void List::search()                 =   O(n)
void List::create()                 =   O(n)
void List::displayList()            =   O(n)
void List::deleteNode()             =   O(n)
float List::average()               =   O(n)
void List::avgCompare()		    =   O(n)
void List::fail()                   =   O(n)

===================================================================================================

*/










