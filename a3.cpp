// a3.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Karman Sidhu>
// St.# : <301456933>
// Email: <karman_sidhu@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not #include any other files!
//
#include "Announcement.h"
#include "JingleNet_announcer.h"
#include "Queue_base.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;
//helper functions

//takes a string and returns the second substring 
string extractString(int start, const string &str) 
{
    int startPos = start;
    int len = 0;

    for(int i = 0; (str[i] != ' ') && (i < str.size()); i++)
    {
        startPos++;
    }

    startPos++;

    for(int i = startPos; (str[i] != ' ') && (i < str.size()); i++)
    {
        len++;
    }

    string rank = str.substr(startPos,len);
    return rank;
}

class Queue : public Queue_base<Announcement>
{
    struct Node
    {
        Announcement an;
        Node *next;
    };
    
    int count = 0;
    Node *head = nullptr;
    Node *tail = nullptr;
   
    public:
        //
        // destructor de-allocates all memory allocated by class
        //
        ~Queue() 
        {  
            while(count != 0)
            {
                dequeue();
            }
        }

        //default constructor
        Queue(){}

        //
        // Returns the number of items currently in the queue.
        //
        // Performance: O(1) in the worst case
        //
        int size() const
        {
            return count;
        }

        //
        // Add an item to the back of the queue.
        //
        // Performance: O(1) in the worst case
        //
        void enqueue(const Announcement &item)
        {
            if(count == 0)
            {
                head = new Node{item,nullptr};    
                count++;
                tail = head;
            }

            else
            {
                tail->next = new Node{item,nullptr};
                count++;
                tail = tail->next;
            }
        }

        //
        // Return a constant reference to the item at the front of the queue. 
        //
        // If the queue is empty it throws a runtime_error exception like this:
        //
        //     throw runtime_error("front: queue is empty");
        //
        // Performance: O(1) in the worst case
        //
        const Announcement &front() const
        {
            if(count == 0)
            {
                throw runtime_error("front: queue is empty");
            }

            return head->an;
        }

        //
        // Remove the item at the front of the queue.
        //
        // If the queue is empty it throws a runtime_error exception like this:
        //
        //     throw runtime_error("dequeue: queue is empty");
        //
        // Performance: O(1) in the worst case
        //
        void dequeue()
        {
            if(count == 0)
            {
                throw runtime_error("dequeue: queue is empty");
            }

            if(head == tail)
            {
                tail = nullptr;
            }

            Node *temp = head;
            head = head->next;
            delete temp;

            count--;
        }
};

//stores 5 queues
class JingleNet 
{
    //highest priority
    Queue santa;
    //second highest priority
    Queue reindeer;
    //third highest priority
    Queue elf2;
    //fourth highest priority
    Queue elf1;
    //fifth highest priority
    Queue snowman;

    public:
        //default constructor
        JingleNet(){}
        
        //destructor
        ~JingleNet(){}
        
        //adds announcement from username to rank queue with text message
        void send (const string &announcement) 
        {
            //announcement without SEND command, in format username rank message
            const string announcementString = announcement.substr(5,(announcement.size()-1));
            Announcement an1(announcementString);
            string rank = extractString(0, announcementString);
      
            if(rank == "santa")
            {
                santa.enqueue(an1);
            }

            else if(rank == "reindeer")
            {
                reindeer.enqueue(an1);
            }

            else if(rank == "elf2")
            {
                elf2.enqueue(an1);
            }

            else if(rank == "elf1")
            {
                elf1.enqueue(an1);
            }
            
            else if(rank == "snowman")
            {
                snowman.enqueue(an1);
            }
        }

        //all announcements from username are removed from the JingleNet system
        void removeAll(const string &command)
        {
            string username = command.substr(11,(command.size()-1));
            Queue temp;          
           
            while(santa.size() > 0)
            {
                Announcement a1(santa.front());
                temp.enqueue(a1);
                santa.dequeue();
            }

            while(temp.size() > 0)
            {
                Announcement a2(temp.front());

                if(a2.get_sender_name() != username)
                {
                    santa.enqueue(a2);   
                }

                temp.dequeue();
            }

            while(reindeer.size() > 0)
            {
                Announcement a1(reindeer.front());
                temp.enqueue(a1);
                reindeer.dequeue();
            }

            while(temp.size() > 0)
            {
                Announcement a2(temp.front());

                if(a2.get_sender_name() != username)
                {
                    reindeer.enqueue(a2);   
                }

                temp.dequeue();
            }

            while(elf2.size() > 0)
            {
                Announcement a1(elf2.front());
                temp.enqueue(a1);
                elf2.dequeue();
            }

            while(temp.size() > 0)
            {
                Announcement a2(temp.front());

                if(a2.get_sender_name() != username)
                {
                    elf2.enqueue(a2);   
                }

                temp.dequeue();
            }

            while(elf1.size() > 0)
            {
                Announcement a1(elf1.front());
                temp.enqueue(a1);
                elf1.dequeue();
            }

            while(temp.size() > 0)
            {
                Announcement a2(temp.front());

                if(a2.get_sender_name() != username)
                {
                    elf1.enqueue(a2);   
                }

                temp.dequeue();
            }

            while(snowman.size() > 0)
            {
                Announcement a1(snowman.front());
                temp.enqueue(a1);
                snowman.dequeue();
            }

            while(temp.size() > 0)
            {
                Announcement a2(temp.front());

                if(a2.get_sender_name() != username)
                {
                    snowman.enqueue(a2);   
                }

                temp.dequeue();
            }
        }

        //all announcements from username are moved to the next highest rank
        void promoteAnnouncements(const string &userName)
        {
            string user = userName.substr(22,(userName.size()-1));
            Queue temp;

            while(reindeer.size() > 0)
            {
                Announcement a1(reindeer.front());
                
                if(a1.get_sender_name() == user)
                {
                    Announcement a2(a1.get_sender_name(), Rank::SANTA, a1.get_text());
                    santa.enqueue(a2);
                    reindeer.dequeue();
                }

                else
                {
                    temp.enqueue(a1);
                    reindeer.dequeue();
                }
            }

            while(temp.size() > 0)
            {
                reindeer.enqueue(temp.front());
                temp.dequeue();
            }

            while(elf2.size() > 0)
            {
                Announcement a1(elf2.front());
                
                if(a1.get_sender_name() == user)
                {
                    Announcement a2(a1.get_sender_name(), Rank::REINDEER, a1.get_text());
                    reindeer.enqueue(a2);
                    elf2.dequeue();
                }

                else
                {
                    temp.enqueue(a1);
                    elf2.dequeue();
                }
            }

            while(temp.size() > 0)
            {
                elf2.enqueue(temp.front());
                temp.dequeue();
            }

            while(elf1.size() > 0)
            {
                Announcement a1(elf1.front());
                
                if(a1.get_sender_name() == user)
                {
                    Announcement a2(a1.get_sender_name(), Rank::ELF2, a1.get_text());
                    elf2.enqueue(a2);
                    elf1.dequeue();
                }

                else
                {
                    temp.enqueue(a1);
                    elf1.dequeue();
                }
            }

            while(temp.size() > 0)
            {
                elf1.enqueue(temp.front());
                temp.dequeue();
            }

            while(snowman.size() > 0)
            {
                Announcement a1(snowman.front());
                
                if(a1.get_sender_name() == user)
                {
                    Announcement a2(a1.get_sender_name(), Rank::ELF1, a1.get_text());
                    elf1.enqueue(a2);
                    snowman.dequeue();
                }

                else
                {
                    temp.enqueue(a1);
                    snowman.dequeue();
                }
            }

            while(temp.size() > 0)
            {
                snowman.enqueue(temp.front());
                temp.dequeue();
            }
        }

        //the next n announcements are printed to announcements.txt
        void announce(int n)
        {
            int counter = n;

            while((counter > 0) && (santa.size() > 0))
            {
                jnet.announce(santa.front());
                santa.dequeue();
                counter--;
            }

            while((counter > 0) && (reindeer.size() > 0))
            {
                jnet.announce(reindeer.front());
                reindeer.dequeue();
                counter--;
            }

            while((counter > 0) && (elf2.size() > 0))
            {
                jnet.announce(elf2.front());
                elf2.dequeue();
                counter--;
            }

            while((counter > 0) && (elf1.size() > 0))
            {
                jnet.announce(elf1.front());
                elf1.dequeue();
                counter--;
            }

            while((counter > 0) && (snowman.size() > 0))
            {
                jnet.announce(snowman.front());
                snowman.dequeue();
                counter--;
            }
        }
};

int main(int argc, char *argv[])
{
    // Check that the user provided a filename.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        //
        // Returning a non-zero value from main indicates the program ended
        // abnormally. We don't care about main return values, but in some cases
        // they are useful. If this program was used as part of a shell script,
        // then the script might check this return value in an if-statement.
        //
        return 1; 
    }

    //
    // Read the contents of the file named by argv[1], and print each line.
    //
    string filename = argv[1];
    cout << "Printing " << filename << " ..." << endl;
    ifstream infile(filename);
    string line;
    int num_lines = 0;
    string command;
    JingleNet jn;
    
    while (getline(infile, line))
    {
        num_lines++;
        int i = 0;
        int sze = line.size();
    
        while((line[i] != ' ') && (i < sze))
        {
            i++;
        }

        command = line.substr(0,i);

        if(command == "SEND")
        {
            jn.send(line);
        }

        else if(command == "REMOVE_ALL")
        {
            jn.removeAll(line);
        }

        else if(command == "PROMOTE_ANNOUNCEMENTS")
        {
            jn.promoteAnnouncements(line);
        }

        else if(command == "ANNOUNCE")
        {
            string intAsString = line.substr(9,(line.size()-1));
            int numAnnouncements = stoi(intAsString);
            jn.announce(numAnnouncements);
        }
       
    }

} // main
