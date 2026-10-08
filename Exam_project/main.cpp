#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Participant
{
protected:
    string name;
    int maxRun;
    int maxJump;

public:
    Participant(string name, int maxRun, int maxJump)
        : name(name), maxRun(maxRun), maxJump(maxJump)
    {
    }

    virtual ~Participant() {}

    virtual void run()
    {
        cout << name << " біжить" << endl;
    }

    virtual void jump()
    {
        cout << name << " стрибає" << endl;
    }

    string getName()
    {
        return name;
    }

    int getMaxRun()
    {
        return maxRun;
    }

    int getMaxJump()
    {
        return maxJump;
    }
};

class Human : public Participant
{
public:
    Human(string name)
        : Participant(name, 1000, 2)
    {
    }

    void run() 
    {
        cout << "Людина " << name << " біжить" << endl;
    }

    void jump() 
    {
        cout << "Людина " << name << " стрибає" << endl;
    }
};

class Cat : public Participant
{
public:
    Cat(string name) : Participant(name, 500, 3)
    {
    }

    void run() 
    {
        cout << "Кіт " << name << " біжить" << endl;
    }

    void jump() 
    {
        cout << "Кіт " << name << " стрибає" << endl;
    }
};

class Robot : public Participant
{
public:
    Robot(string name)
        : Participant(name, 2000, 1)
    {
    }

    void run() 
    {
        cout << "Робот " << name << " біжить" << endl;
    }

    void jump() 
    {
        cout << "Робот " << name << " стрибає" << endl;
    }
};


class Obstacle
{
protected:
    string name;

public:
    Obstacle(string name)
        : name(name)
    {
    }
    
    virtual ~Obstacle() {}

    virtual bool overcome(Participant* participant) = 0;

    string getName()
    {
        return name;
    }
};

class RunningTrack : public Obstacle
{
private:
    int length;

public:
    RunningTrack(string name, int length)
        : Obstacle(name), length(length)
    {
    }

    bool overcome(Participant* participant) 
    {
        participant->run();

        if (participant->getMaxRun() >= length)
        {
            cout << "Учасник[" << participant->getName()
                << "] пройшов перешкоду[" << name
                << "] на дистанції[" << length << "]" << endl;

            return true;
        }

        cout << "Учасник[" << participant->getName()
            << "] не пройшов перешкоду[" << name
            << "] на дистанції[" << length
            << "]. Пройдено[" << participant->getMaxRun() << "]" << endl;

        return false;
    }
};

class Wall : public Obstacle
{
private:
    int height;

public:
    Wall(string name, int height) : Obstacle(name), height(height)
    {
    }

    bool overcome(Participant* participant) 
    {
        participant->jump();

        if (participant->getMaxJump() >= height)
        {
            cout << "Учасник[" << participant->getName()
                << "] пройшов перешкоду[" << name
                << "] на висоті[" << height << "]" << endl;

            return true;
        }

        cout << "Учасник[" << participant->getName()
            << "] не пройшов перешкоду[" << name
            << "] на висоті[" << height
            << "]. Пройдено[" << participant->getMaxJump() << "]" << endl;

        return false;
    }
};


int main()
{
    system("chcp 65001");
    vector<Participant*> participants;

    participants.push_back(new Human("Андрій"));
    participants.push_back(new Cat("Маркіз"));
    participants.push_back(new Robot("Roboboss"));

    vector<Obstacle*> obstacles;

    obstacles.push_back(new RunningTrack("Довга доріжка", 800));
    obstacles.push_back(new Wall("Висока стіна", 2));
    obstacles.push_back(new RunningTrack("Дуже довга доріжка", 1000));
    obstacles.push_back(new Wall("Низька стіна", 1));

    for (Participant* participant : participants)
    {
        cout << "------------------------" << endl;
        cout << "Учасник: " << participant->getName() << endl;

        bool isActive = true;

        for (Obstacle* obstacle : obstacles)
        {
            if (!isActive)
                break;

            isActive = obstacle->overcome(participant); 
        }
    }

    for (Participant* participant : participants)
    {
        delete participant;
    }

    for (Obstacle* obstacle : obstacles)
    {
        delete obstacle;
    }

    return 0;
}