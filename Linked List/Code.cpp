#include <bits/stdc++.h>
using namespace std;

class StudentRecord{
private:
    string studentName;
    string rollNumber;

public:
    string get_studentName() {
        return studentName;
    }
    void set_studentName(string Name) {
        studentName = Name;
    }
    string get_rollNumber() {
        return rollNumber;
    }
    void set_rollNumber(string rollnum) {
        rollNumber = rollnum;
    }
};

class Node{
	private:
		Node* next;
		StudentRecord* element;
	public:
	    Node* get_next() 
        {
	        return next;                         //kya ye correct hai? i think so nullptr ki jahah next
	    }
	    StudentRecord* get_element() 
        {
	        return element;                         //""nullptr ki jagah element
	    }

	    void set_next(Node* value)
        {
	    	next = value;
	    }
	    void set_element(StudentRecord* student)
        {
	    	element = student;
	    }
};

class Entity 
{
private:
    string name;
    Node* iterator;

public:
    string get_name() {
        return name;
    }
    void set_name(string Name) {
        name = Name;
    }
    Node* get_iterator() {
        return iterator;
    }
    void set_iterator(Node* iter) {
        iterator = iter;
    }
};

class LinkedList : public Entity 
{
    public:
        void add_student(StudentRecord& student)
        {
            Node* head = new Node();
            head = get_iterator();            //wow moment!
            Node* n = new Node();
            StudentRecord* pointer_s = &student;
            n->set_element(pointer_s);
            n->set_next(head);
            set_iterator(n);
        }
        void delete_student(string studentName)
        {
            int n = 0,i;
            Node* temp = get_iterator();
            Node* temp2;
            StudentRecord* ptr;
            while(temp != NULL)
            {
                n++;
                ptr = temp->get_element();
                if(studentName.compare(ptr->get_studentName()) == 0)
                {
                    break;
                }
                temp = temp->get_next();
            }
            //try except block for n = 0;

            if(n == 0)
            {
                cerr << "Such an entry does not exist!" << endl;
                return;
            }

            temp = get_iterator();
            if(n==1)
            {
                set_iterator(temp->get_next());
                free(temp);
            }
            else
            {
                for(i=1;i<n-1;i++)
                {
                    temp = temp->get_next();
                }
                temp2 = temp->get_next();
                temp->set_next(temp2->get_next());
                free(temp2);
            }
        }
};

vector<StudentRecord> students;
vector<LinkedList> EntityArray;

void read_input_file(string file_path)
{
    int f,f2, pos, len,i;
    LinkedList* e = new LinkedList();
    string line = "";
    fstream file(file_path,ios::in);

    string stuname;
    string rno;
    string entity;
    
    //check for duplicate entries
    
    while(getline(file,line))
    {
        stringstream inputstream(line);
        getline(inputstream, stuname, ',');
        getline(inputstream, rno, ',');
        f2 = 0;
        for(auto& it : students)
        {
            if(it.get_rollNumber()==rno && it.get_studentName()==stuname)
            {
                cerr << "Duplicate entry" << endl;
                f2 = 1;
            }
        }
        if(f2 == 1)
        {
            continue;
        }
        StudentRecord* s = new StudentRecord();                        //will this work when everytime the identifier is the same??
        s->set_studentName(stuname);
        s->set_rollNumber(rno);
        students.push_back(*s);
        while(getline(inputstream, entity, ','))   //does this take into account the second last delimiter? YES
        {
            f = 1;
            len = entity.length();
            if(entity[0] == '[')
            {
                entity = entity.substr(1,len-1);          //substr(1st_posn,len_of_subtring)
            }

            len = entity.length();
            if(entity[len-1] == ']')
            {
                len = entity.length();
                entity = entity.substr(0,len-1);
            }

            for(auto& it_e : EntityArray)
            {
                if(entity.compare(it_e.get_name()) == 0)               //== checks for semantic equality while .compare checks semantically
                {
                    f = 0;
                    e = &it_e;

                    break;
                }
            }           

            if(f == 1)
            {
                LinkedList* e_new = new LinkedList();
                e_new->set_name(entity);
                Node* head = NULL;
                e_new->set_iterator(head);
                e_new->add_student(*s);
                EntityArray.push_back(*e_new);
            }
            else
            {
                e->add_student(*s);
            }                                  
        }
    }
}
