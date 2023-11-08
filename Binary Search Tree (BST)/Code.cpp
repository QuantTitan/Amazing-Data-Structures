#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>

#include <cassert>
#include <bits/stdc++.h>
using namespace std;

class Vehicle;

class Trip
{
public:
    Trip(Vehicle *vehicle, std::string pick_up_location, std::string drop_location, int departure_time)
        : vehicle(vehicle), pick_up_location(pick_up_location), drop_location(drop_location), departure_time(departure_time), booked_seats(0) {}

    // Getter functions
    Vehicle *getVehicle() const
    {
        return vehicle;
    }

    std::string getPickUpLocation() const
    {
        return pick_up_location;
    }

    std::string getDropLocation() const
    {
        return drop_location;
    }

    int getDepartureTime() const
    {
        return departure_time;
    }

    int getBookedSeats() const
    {
        return booked_seats;
    }

    // Setter functions
    void setVehicle(Vehicle *v)
    {
        vehicle = v;
    }

    void setPickUpLocation(std::string location)
    {
        pick_up_location = location;
    }

    void setDropLocation(std::string location)
    {
        drop_location = location;
    }

    void setDepartureTime(int time)
    {
        departure_time = time;
    }

    void setBookedSeats(int seats)
    {
        booked_seats = seats;
    }

private:
    Vehicle *vehicle;
    std::string pick_up_location;
    std::string drop_location;
    int departure_time;
    int booked_seats;
};

// class BinaryTreeNode;

class BinaryTreeNode // switched the posn of BinaryTreeNode and TransportService class
{
public:
    BinaryTreeNode(int departuretime = 0, Trip *tripenodeptr = nullptr, BinaryTreeNode *parentptr = nullptr)
        : leftptr(nullptr), rightptr(nullptr), parentptr(parentptr), departuretime(departuretime), tripnodeptr(tripenodeptr) {}

    // Getter functions
    BinaryTreeNode *getLeftPtr() const
    {
        return leftptr;
    }

    BinaryTreeNode *getRightPtr() const
    {
        return rightptr;
    }

    BinaryTreeNode *getParentPtr() const
    {
        return parentptr;
    }

    int getDepartureTime() const
    {
        return departuretime;
    }

    Trip *getTripNodePtr() const
    {
        return tripnodeptr;
    }

    // Setter functions
    void setLeftPtr(BinaryTreeNode *left)
    {
        leftptr = left;
    }

    void setRightPtr(BinaryTreeNode *right)
    {
        rightptr = right;
    }

    void setParentPtr(BinaryTreeNode *parent)
    {
        parentptr = parent;
    }

    void setDepartureTime(int time)
    {
        departuretime = time;
    }

    void setTripNodePtr(Trip *trip)
    {
        tripnodeptr = trip;
    }

private:
    BinaryTreeNode *leftptr;
    BinaryTreeNode *rightptr;
    BinaryTreeNode *parentptr;
    int departuretime;
    Trip *tripnodeptr;
};

class TransportService
{
public:
    TransportService(std::string name) : name(name), BSThead(nullptr) {} // drop location

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    BinaryTreeNode *getBSTHead() const
    {
        return BSThead;
    }

    // Setter functions
    void setName(std::string service_name)
    {
        name = service_name;
    }

    void setBSTHead(BinaryTreeNode *node)
    {
        BSThead = node;
    }

    void addTrip(int key, Trip *trip)
    {
        // BinaryTreeNode *node = new BinaryTreeNode(trip->getDepartureTime(), trip);
        BinaryTreeNode *node = new BinaryTreeNode();
        node = insert(getBSTHead(), key, trip); // modification from try 5, put a trip parameter
        // node->setTripNodePtr(trip);                     //aren't you always inserting at the root using this stmt
        setBSTHead(node);
        // levelordertraversal(getBSTHead());
        // inorder(getBSTHead());
        // cout << " added " << trip->getVehicle() << " " << trip->getPickUpLocation() << " " << trip->getDropLocation() << endl;
    }

    BinaryTreeNode *get_newnode(int data)
    {
        BinaryTreeNode *node = new BinaryTreeNode(); // is not working outside TransportService
        node->setDepartureTime(data);
        node->setLeftPtr(NULL);
        node->setRightPtr(NULL);
        node->setParentPtr(NULL);
        return node;
    }

    BinaryTreeNode *insert(BinaryTreeNode *root, int data, Trip *trip) // modification from try 5, put a trip parameter
    {
        BinaryTreeNode *node = new BinaryTreeNode();
        if (root == NULL)
        {
            root = get_newnode(data);
            root->setTripNodePtr(trip);
        }
        else if (data <= root->getDepartureTime())
        {
            node = insert(root->getLeftPtr(), data, trip);
            root->setLeftPtr(node);
            node->setParentPtr(root);
        }
        else
        {
            node = insert(root->getRightPtr(), data, trip);
            root->setRightPtr(node);
            node->setParentPtr(root);
        }
        return root;
    }

    void levelordertraversal(BinaryTreeNode *root)
    {
        queue<BinaryTreeNode *> qu;
        if (root == NULL)
        {
            return;
        }
        qu.push(root);
        while (!qu.empty())
        {
            BinaryTreeNode *current = qu.front();
            cout << current->getDepartureTime() << " ";
            if (current->getLeftPtr() != NULL)
                qu.push(current->getLeftPtr());
            if (current->getRightPtr() != NULL)
                qu.push(current->getRightPtr());
            qu.pop();
        }
        cout << endl;
    }

    void preorder(BinaryTreeNode *root)
    {
        if (root != NULL)
        {
            cout << root->getDepartureTime() << " ";
        }
        else
        {
            return;
        }
        if (root->getLeftPtr() != NULL)
        {
            preorder(root->getLeftPtr());
        }
        if (root->getRightPtr() != NULL)
        {
            preorder(root->getRightPtr());
        }
    }

    void inorder(BinaryTreeNode *root)
    {
        if (root != NULL)
        {
            if (root->getLeftPtr() != NULL)
            {
                inorder(root->getLeftPtr());
            }
            cout << root->getDepartureTime() << " ";
            if (root->getRightPtr() != NULL)
            {
                inorder(root->getRightPtr());
            }
        }
        cout << endl;
        return;
    }

private:
    std::string name;
    BinaryTreeNode *BSThead;
};

class Vehicle
{
public:
    Vehicle(std::string vehicle_number, int seating_capacity)
        : vehicle_number(vehicle_number), seating_capacity(seating_capacity) {}

    // Getter functions
    std::string getVehicleNumber() const
    {
        return vehicle_number;
    }

    int getSeatingCapacity() const
    {
        return seating_capacity;
    }

    vector<Trip *> getTrips() const
    {
        return trips;
    }

    // Setter functions
    void setVehicleNumber(std::string number)
    {
        vehicle_number = number;
    }

    void setSeatingCapacity(int capacity)
    {
        seating_capacity = capacity;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

private:
    std::string vehicle_number;
    int seating_capacity;
    std::vector<Trip *> trips;
};

class Location
{
public:
    Location(std::string name) : name(name) {} // ye pickup loc hai name

    // Getter functions
    std::string getName() const
    {
        return name;
    }

    TransportService *getServicePtr(std::string droplocation) const
    {
        for (const auto &it : serviceptrs)
        {
            if (droplocation.compare(it->getName()) == 0)
            {
                return it;
            }
        }
        // TransportService* TS = new TransportService(droplocation);
        // serviceptrs.push_back(TS);                                //does not work bcz of const
        return nullptr; // under consideration
    }

    TransportService *makeService(string droplocation)
    {
        TransportService *TS = new TransportService(droplocation);
        serviceptrs.push_back(TS);
        return TS;
    }

    vector<TransportService *> getservicevector()
    {
        return serviceptrs;
    }

    // Setter functions
    void setName(std::string location_name)
    {
        name = location_name;
    }

    TransportService *setServicePtr(std::string droplocation)
    {
        return nullptr;
    }

    void addTrip(Trip *trip)
    {
        trips.push_back(trip);
    }

private:
    std::string name;
    std::vector<TransportService *> serviceptrs;
    std::vector<Trip *> trips;
};

class BinaryTree
{
protected:
    BinaryTreeNode *root;

public:
    BinaryTree() : root(nullptr) {}

    int height(BinaryTreeNode *root) const
    {
        if (root == nullptr)
        {
            return 0;
        }
        return max(height(root->getLeftPtr()), height(root->getRightPtr())) + 1;
    }

    int getHeight() const
    {
        // Implement this function to return the height of the tree
        return height(root);
    }

    int non(BinaryTreeNode *root) const
    {
        int s = 0;
        if (root->getLeftPtr() != nullptr)
        {
            s += non(root->getLeftPtr());
        }
        if (root->getRightPtr() != nullptr)
        {
            s += non(root->getRightPtr());
        }
        return s + 1;
    }

    int getNumberOfNodes() const
    {
        // Implement this function to return the number of nodes in the tree
        return non(root);
    }

    void setroot(BinaryTreeNode *head)
    {
        root = head;
    }

    // void getroot()
};

class BinarySearchTree : public BinaryTree
{
public:
    BinarySearchTree() {}

    BinaryTreeNode *getElementWithMinimumKey() const
    {
        // Implement this function to return the element with the minimum key
        BinaryTreeNode *node = root;
        while (node->getLeftPtr() != nullptr)
        {
            node = node->getLeftPtr();
        }
        return node; // Placeholder
    }

    BinaryTreeNode *getElementWithMaximumKey() const
    {
        // Implement this function to return the element with the maximum key
        BinaryTreeNode *node = root;
        while (node->getRightPtr() != nullptr)
        {
            node = node->getRightPtr();
        }
        return node;
    }

    BinaryTreeNode *searchNodeWithKey(int key) const
    {
        // Implement this function to search for a node with the given key or the next larger key
        /*int dep_time = root->getDepartureTime();
        BinaryTreeNode* res;
        if (root == NULL)
        {
            return {};
            //return false;
        }
        else if (key == dep_time)
        {
            return root;
        }
        else if (key < dep_time)
        {
            BinarySearchTree* BST_obj = new BinarySearchTree();
            BST_obj->setroot(root->getLeftPtr());
            res = BST_obj->searchNodeWithKey(key);
            if(res == {})
            {
                return root->getParentPtr();
            }
        }
        else
        {
            return searchNodeWithKey(root->getRightPtr(), key);
        }

        return nullptr; // Placeholder*/

        BinaryTreeNode *current = root;
        BinaryTreeNode *result = nullptr;

        while (current != nullptr)
        {
            if (current->getDepartureTime() == key)
            {
                // Found the node with the given key
                result = current;
                break;
            }
            else if (current->getDepartureTime() < key)
            {
                // The key might be in the right subtree
                current = current->getRightPtr();
            }
            else
            {
                // The key might be in the left subtree or the current node is the next larger key
                result = current;
                current = current->getLeftPtr();
            }
        }

        return result;
    }

    BinaryTreeNode *getSuccessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the successor node of the given node
        int key = node->getDepartureTime();
        // now put the rest in get successor node by key
        /*BinaryTreeNode *successor = nullptr;

        while (node != nullptr)
        {
            if (node->getDepartureTime() > key)
            {
                successor = node;
                node = node->getLeftPtr();
            }
            else
            {
                node = node->getRightPtr();
            }
        }
        return successor; // Placeholder*/

        if (node->getRightPtr() != nullptr)
        {
            node = node->getRightPtr();
            while (node->getLeftPtr() != nullptr)
            {
                node = node->getLeftPtr();
            }
            // cout << "node is " << node->getDepartureTime() << endl;
            if (node->getDepartureTime() == key)
            {
                return getSuccessorNode(node);
            }
            return node;
        }
        else
        {
            while (node->getParentPtr() != nullptr)
            {
                node = node->getParentPtr();
                if (node->getDepartureTime() >= key)
                {
                    if (node->getDepartureTime() == key)
                    {
                        return getSuccessorNode(node);
                    }
                    return node;
                }
            }
        }
        return nullptr;
    }

    BinaryTreeNode *getSuccessorNodeByKey(int key) const
    {
        // Implement this function to return the successor node by key
        BinaryTreeNode *temp;
        BinaryTreeNode *node = root;
        while (node != nullptr)
        {
            if (key == node->getDepartureTime())
            {
                return getSuccessorNode(node);
            }
            else if (key < node->getDepartureTime())
            {
                temp = node;
                node = node->getLeftPtr();
            }
            else if (key > node->getDepartureTime())
            {
                node = node->getRightPtr();
            }
        }
        return temp;
    }

    BinaryTreeNode *getPredecessorNode(BinaryTreeNode *node) const
    {
        // Implement this function to return the predecessor node of the given node
        int key = node->getDepartureTime();
        if (node->getLeftPtr() != nullptr)
        {
            node = node->getLeftPtr();
            while (node->getRightPtr() != nullptr)
            {
                node = node->getRightPtr();
            }
            return node;
        }
        while (node->getParentPtr() != nullptr)
        {
            if (node->getParentPtr()->getDepartureTime() < key)
            {
                return node;
            }
            node = node->getParentPtr();
        }
        return nullptr;
    }

    BinaryTreeNode *getPredecessorNodeByKey(int key) const
    {
        // Implement this function to return the predecessor node by key
        BinaryTreeNode *temp;
        BinaryTreeNode *node = root;
        while (node != nullptr)
        {
            if (key == node->getDepartureTime())
            {
                return getPredecessorNode(node);
            }
            else if (key < node->getDepartureTime())
            {
                node = node->getLeftPtr();
            }
            else if (key > node->getDepartureTime())
            {
                temp = node;
                node = node->getRightPtr();
            }
        }
        return temp;
    }
};

class TravelDesk
{
public:
    void addTrip(std::string vehicle_number, int seating_capacity, std::string pick_up_location, std::string drop_location, int departure_time)
    {
        // Vehicle *vehicle = nullptr;
        Vehicle *v = new Vehicle("", 0); // isko dynamic alloc nahi karna haina?
        // Check if the vehicle already exists, if not, create a new one with the seating capacity
        int f = 0, f_loc = 0;
        // Vehicle *vehicle = new Vehicle();
        // cout << "vehicle no " << vehicle_number << endl;
        // cout << "seating cap" << seating_capacity << endl;
        // cout << "vehicle no " << pick_up_location << endl;
        // cout << "seating cap" << drop_location << endl;
        for (const auto &it : vehicles)
        {
            // cout <<
            if (vehicle_number.compare(it->getVehicleNumber()) == 0) // might have to check seating capacity too
            {
                f = 1;
                v = it;
                // Trip *trip_obj = new Trip(v, pick_up_location, drop_location, departure_time);
                //  Vehicle *v_obj = new Vehicle(vehicle_number, seating_capacity);
                // Location *l_obj = new Location(pick_up_location);
                // TransportService *TS_obj = new TransportService(drop_location);
                // TS_obj->addTrip(departure_time, trip_obj); // or instead use the setters o0f the v;
                // cout << "vehicle no " << v->getVehicleNumber() << endl;
                // cout << "seating cap" << v->getSeatingCapacity() << endl;
                break;
            }
        }
        if (f == 0)
        {
            v->setSeatingCapacity(seating_capacity);
            v->setVehicleNumber(vehicle_number);
            vehicles.push_back(v);
            // Vehicle *v_new = new Vehicle(vehicle_number, seating_capacity); // dynamic alloc
            // vehicles.push_back(v_new);
            // Trip *trip_obj = new Trip(v_new, pick_up_location, drop_location, departure_time);
            // Vehicle *v_obj = new Vehicle(vehicle_number, seating_capacity);
            // Location *l_obj = new Location(pick_up_location);
            // TransportService *TS_obj = new TransportService(drop_location);
            // TS_obj->addTrip(departure_time, trip_obj);
            //  cout << "vehicle no " << v_new->getVehicleNumber() << endl;
            //  cout << "seating cap" << v_new->getSeatingCapacity() << endl;
        }
        Trip *trip_obj = new Trip(v, pick_up_location, drop_location, departure_time);
        // vehicle obj addtrip
        Location *l_obj = new Location("");
        for (const auto &it : locations)
        {
            if (pick_up_location.compare(it->getName()) == 0)
            {
                f_loc = 1;
                l_obj = it;
                // cout << "pickup location " << l_obj->getName() << endl;
                break;
            }
        }
        if (f_loc == 0)
        {
            l_obj->setName(pick_up_location);
            locations.push_back(l_obj);
        }
        // TransportService *TS_obj = new TransportService(drop_location);
        // cout << "pickup loc " << pick_up_location << " location " << drop_location << endl;
        TransportService *TS_obj = new TransportService("");
        TS_obj = l_obj->getServicePtr(drop_location);
        if (TS_obj == nullptr)
        {
            TS_obj = l_obj->makeService(drop_location);
            // cout << "making new service" << endl;
        }
        // cout << "transport service drop loc name" << TS_obj->getName() << endl;
        TS_obj->addTrip(departure_time, trip_obj);
        l_obj->addTrip(trip_obj); // had forgotten this
        v->addTrip(trip_obj);     //""
    }

    std::vector<Trip *> showTrips(std::string pick_up_location, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range
        int f = 0;
        int t;
        vector<Trip *> result;
        if (after_time > before_time)
        {
            t = after_time;
            after_time = before_time;
            before_time = t;
        }
        Location *l_obj = new Location("");
        l_obj = getLocation(pick_up_location);
        /*for (const auto &it : locations)
        {
            if (pick_up_location.compare(it->getName()) == 0)
            {
                f = 1;
                l_obj = it;
                break;
            }
        }*/
        // check condition where location is not present with locations
        if (l_obj == nullptr)
        {
            cerr << "The pickup location " << pick_up_location << " does not have a service yet!" << endl;
            return result;
        }
        TransportService *TS_obj = new TransportService("");
        vector<TransportService *> serviceptrs = l_obj->getservicevector();
        for (auto &it : serviceptrs)
        {
            TS_obj = it;
            if (TS_obj == nullptr)
            {
                continue;
            }
            // cout << "destination is " << TS_obj->getName() << endl;
            BinaryTreeNode *head = TS_obj->getBSTHead();
            BinaryTreeNode *node;
            BinarySearchTree *BST_obj = new BinarySearchTree();
            BST_obj->setroot(head);
            node = BST_obj->searchNodeWithKey(after_time);
            // result.push_back();
            while (node != nullptr && node->getDepartureTime() < before_time)
            {
                result.push_back(node->getTripNodePtr());
                // node = BST_obj->getSuccessorNodeByKey(node->getDepartureTime());
                node = BST_obj->getSuccessorNode(node);
            }
        }
        return result;
    }
    std::vector<Trip *> showTripsbydestination(std::string pick_up_location, std::string destination, int after_time, int before_time)
    {
        // Implement this function to retrieve trips within a specified time range form pickup to droplocatin
        int f = 0;
        int t;
        vector<Trip *> result;
        if (after_time > before_time)
        {
            t = after_time;
            after_time = before_time;
            before_time = t;
        }
        Location *l_obj = new Location("");
        l_obj = getLocation(pick_up_location);
        /*for (const auto &it : locations)
        {
            if (pick_up_location.compare(it->getName()) == 0)
            {
                f = 1;
                l_obj = it;
                break;
            }
        }*/
        // check condition where location is not present with locations
        if (l_obj == nullptr)
        {
            cerr << "The pickup location " << pick_up_location << " does not have a service yet!" << endl;
            return result;
        }
        TransportService *TS_obj = new TransportService("");
        TS_obj = l_obj->getServicePtr(destination);
        if (TS_obj == nullptr)
        {
            cerr << "The pickup location - drop location pair does not have a service yet!" << endl;
            return result;
        }
        // cout << "destination is " << TS_obj->getName() << endl;
        BinaryTreeNode *head = TS_obj->getBSTHead();
        BinaryTreeNode *node;
        BinarySearchTree *BST_obj = new BinarySearchTree();
        BST_obj->setroot(head);
        node = BST_obj->searchNodeWithKey(after_time);
        // result.push_back();
        while (node != NULL && node->getDepartureTime() < before_time)
        {
            result.push_back(node->getTripNodePtr());
            // node = BST_obj->getSuccessorNodeByKey(node->getDepartureTime());
            node = BST_obj->getSuccessorNode(node);
        }
        return result; // Placeholder
    }

    Trip *bookTrip(std::string pick_up_location, std::string drop_location, std::string vehicle_number, int departure_time)
    {
        // Implement this function to book a trip
        int f = 0;
        int t;
        Trip *result = nullptr;
        Location *l_obj = new Location("");
        l_obj = getLocation(pick_up_location);
        /*for (const auto &it : locations)
        {
            if (pick_up_location.compare(it->getName()) == 0)
            {
                f = 1;
                l_obj = it;
                break;
            }
        }*/
        // check condition where location is not present with locations
        if (l_obj == nullptr)
        {
            cerr << "The pickup location " << pick_up_location << " does not have a service yet!" << endl;
            return result;
        }
        TransportService *TS_obj = new TransportService("");
        TS_obj = l_obj->getServicePtr(drop_location);
        if (TS_obj == nullptr)
        {
            cerr << "The pickup location - drop location pair does not have a service yet!" << endl;
            return result;
        }
        BinaryTreeNode *head = TS_obj->getBSTHead();
        BinaryTreeNode *node;
        BinarySearchTree *BST_obj = new BinarySearchTree();
        BST_obj->setroot(head);
        node = BST_obj->searchNodeWithKey(departure_time);
        if (node == nullptr)
        {
            cerr << "The pickup location - drop location at the given time does not have a trip yet!" << endl;
            return result;
        }
        result = node->getTripNodePtr();
        if (result->getBookedSeats() == result->getVehicle()->getSeatingCapacity())
        {
            cerr << "The vehicle is fully booked for the trip!" << endl;
            return result;
        }
        result->setBookedSeats(result->getBookedSeats() + 1);
        return result;
    }
    Location *getLocation(std::string location)
    {
        for (const auto &it : locations)
        {
            if (location.compare(it->getName()) == 0)
            {
                return it;
            }
        }
        return nullptr;
    }

private:
    std::vector<Vehicle *> vehicles;
    std::vector<Location *> locations;
};

int extract_time(string time)
{
    int int_time = 0;
    int pow = 1;
    for (int i = time.length() - 1; i >= 0; i--)
    {
        if (time[i] == ':')
        {
            continue;
        }
        int_time += (time[i] - '0') * (pow);
        pow *= 10;
    }
    return int_time;
}

void readrecords(string filename)
{
    string line, cmd;
    fstream input(filename, ios::in);
    TravelDesk TD_obj; // dynamic alloc?
    while (getline(input, line, '\n'))
    {
        stringstream line_stream(line);
        getline(line_stream, cmd, ' ');
        // put commands in an array
        // cout << "command" << cmd << endl;
        if (cmd.compare("ADDTRIP") == 0) // forgot the == 0
        {
            string vno, cap_str, pickup_loc, drop_loc, dep_str;
            int cap = 0, i = 0, pow = 1, dep_time = 0;
            getline(line_stream, vno, ' ');
            getline(line_stream, cap_str, ' ');
            // cout << "capacity string " << cap_str << endl;
            for (i = cap_str.length() - 1; i >= 0; i--)
            {
                cap += (cap_str[i] - '0') * (pow);
                pow *= 10;
            }
            // cout << "capacity " << cap << endl;
            getline(line_stream, pickup_loc, ' ');
            getline(line_stream, drop_loc, ' ');
            getline(line_stream, dep_str, '\r');
            dep_time = extract_time(dep_str);
            pow = 1;
            /*for (i = dep_str.length() - 1; i >= 0; i--)
            {
                if (dep_str[i] == ':')
                {
                    continue;
                }
                dep_time += (dep_str[i] - '0') * (pow);
                pow *= 10;
            }*/
            TD_obj.addTrip(vno, cap, pickup_loc, drop_loc, dep_time);
            // cout << "Vehicle Number " << vno << endl;
            // cout << "pickup loc " << pickup_loc << endl;
            // cout << "drop_loc " << drop_loc << endl;
            // cout << "dep_time " << dep_time << endl;
        }
        else if (cmd.compare("SHOWTRIPSBYDESTINATION") == 0)
        {
            string pickup_loc, drop_loc, start_str, end_str;
            int time_start, time_end;
            vector<Trip *> res;
            getline(line_stream, pickup_loc, ' ');
            getline(line_stream, drop_loc, ' ');
            getline(line_stream, start_str, ' ');
            getline(line_stream, end_str, '\r');
            time_start = extract_time(start_str);
            time_end = extract_time(end_str);
            res = TD_obj.showTripsbydestination(pickup_loc, drop_loc, time_start, time_end);
            for (const auto &it : res)
            {
                cout << "vehicle no" << it->getVehicle() << endl;
            }
            // by params of showtripsby desination we have determied the order
            // cout << "pickup location " << pickup_loc << endl;
            // cout << "drop location " << drop_loc << endl;
            // cout << "start time int" << time_start << endl;
            // cout << "end time int " << time_end << endl;
        }
        else if (cmd.compare("SHOWTRIPS") == 0)
        {
            string pickup_loc, start_str, end_str;
            int time_start, time_end;
            getline(line_stream, pickup_loc, ' ');
            getline(line_stream, start_str, ' ');
            getline(line_stream, end_str, '\r');
            time_start = extract_time(start_str);
            time_end = extract_time(end_str);
            // by params of showtrips we have determied the order and that loc is pickup_loc
            TD_obj.showTrips(pickup_loc, time_start, time_end);
        }
    }
}

