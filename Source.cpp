#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

class Question
{
private:
    string question;
    string alternatives[4];
    int answer;

public:
    Question() {}
    Question(string question, string alternatives[4], int answer)
    {
        this->question = question;
        for (int i = 0; i < 4; ++i) {
            this->alternatives[i] = alternatives[i];
        }
        this->answer = answer;
    }
    string getQuestion() { return question; }
    string* getAlternatives() { return alternatives; }
    int getAnswer() { return answer; }
    void setAnswer(int answer) { this->answer = answer; }

    ~Question() {} //destructor to free any dynamic memory
};

void printQuestion(Question question)
{
    cout << question.getQuestion() << endl;
    string* alternatives = question.getAlternatives();
    for (int i = 0; i < 4; ++i)
    {
        cout << (i + 1) << ") " << alternatives[i] << endl;
    }
}

void printAllQuestions(vector<Question>& questions)
{
    for (int i = 0; i < questions.size(); ++i)
    {
        printQuestion(questions[i]);
    }
}

int getChoice()
{
    cout << "==================================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    fflush(stdin);
    cout << "==================================================" << endl;
    return choice;
}

int printMenu()
{
    cout << "==================================================" << endl;
    cout << "1. Initialise (clear all questions)!" << endl;
    cout << "2. Save your questions to the file" << endl;
    cout << "3. Read questions from the file" << endl;
    cout << "4. Add a new question" << endl;
    cout << "5. Take the Quiz" << endl;
    cout << "6. List all of the questions" << endl;
    cout << "0. Exit" << endl;
    return getChoice();
}

void randomNum(int *&randNums, int elements, int size)
{
    randNums = new int[elements];
    for (int i = 0; i < elements; ++i)
    {
        bool same;
        do
        {
            same = false;
            randNums[i] = rand() % size;
            for (int check = 0; check < i; check++)
            {
                if (randNums[i] == randNums[check])
                {
                    same = true;
                    break;
                }
            }
        } while (same);
    }
}

int main()
{
    vector<Question> questions;
    while (true)
    {
        int choice = printMenu();
        if (choice == 1)
        {
            questions.clear();
            cout << "Good to start fresh!" << endl;
        }
        else if (choice == 2)
        {
            ofstream fout("questions.txt");
            fout << questions.size() << endl;
            for (int i = 0; i < questions.size(); ++i)
            {
                fout << questions.at(i).getQuestion() << endl;
                string* alternatives = questions.at(i).getAlternatives();
                for (int i = 0; i < 4; ++i)
                {
                    fout << alternatives[i] << endl;
                }
                fout << questions.at(i).getAnswer() << endl;
            }
            cout << "Successfully Written" << endl;
        }
        else if (choice == 3)
        {
            ifstream fin("questions.txt");
            string size;
            getline(fin, size, '\n');
            for (int i = 0; i < atoi(size.c_str()); ++i)
            {
                string question;
                getline(fin, question, '\n');
                string alt[4];
                getline(fin, alt[0], '\n');
                getline(fin, alt[1], '\n');
                getline(fin, alt[2], '\n');
                getline(fin, alt[3], '\n');
                string answer;
                getline(fin, answer, '\n');
                Question q(question, alt, atoi(answer.c_str()));
                questions.push_back(q);
            }
            cout << "You may now start the Quiz with option 5" << endl;
        }
        else if (choice == 4)
        {
            string question;
            
            cout << "Enter Question: ";
            getline(cin, question, '\n');
            string alt[4];
            cout << "Enter Alternative 1: ";
            getline(cin, alt[0], '\n');
            cout << "Enter Alternative 2: ";
            getline(cin, alt[1], '\n');
            cout << "Enter Alternative 3: ";
            getline(cin, alt[2], '\n');
            cout << "Enter Alternative 4: ";
            getline(cin, alt[3], '\n');
            Question q(question, alt, 0);
            printQuestion(q);
            cout << "Enter Answer (1,2,3,4): ";
            int answer;
            cin >> answer;
            q.setAnswer(answer);
            questions.push_back(q);
            cout << "The question has been successfully added" << endl;
            
        }
        else if (choice == 5)
        {
            int* numbers;
            const int totalQues = 5;
            srand(static_cast<int>(time(0)));//seeding the random number generator
            randomNum(numbers, totalQues, questions.size());//shuffling the questions
            int score = 0;
            for (int i = 0; i < totalQues; i++)
            {
                int answer;
                Question q = questions.at(numbers[i]);
                printQuestion(q);
                cout << "Your answer: "; 
                while (true) {
                    cin >> answer;
                    if (answer > 0 && answer < 5) { //checking for answers in range 1-4
                        if (answer == q.getAnswer()) {//checking for the correct answer
                            cout << "You got it right!\n" << endl;
                            score++;
                        }
                        else { cout << "Oops! That was a nice try.\n" << endl; }
                        break;
                    }
                    else { cout << "Invalid answer! Try from the options(1-4): " << endl; }                        
                }
            }
            cout << "Your Score is " << score << " out of 5\n" << endl;
        }
        else if (choice == 6)
        {
            printAllQuestions(questions);
        }
        else if (choice == 0)
        {
            cout << "Exiting." << endl;
            break;
        }
        else
        {
            cout << "Invalid Input. Please select from the range (0-6)" << endl;
        }
    }
    return 0;
}