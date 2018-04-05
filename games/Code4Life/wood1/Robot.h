#include "include.h"
#include "Robot_State.h"
#include "Sample.h"

/*
 * Robot Class
 **/

class Robot
{
    private:
        Robot_State state;

        // Robot variable
        string target;
        int eta;
        int score;
        vector<int> storages;
        vector<int> expertises;
        
        int current_sample;

    public:
        Robot():
            state(Robot_State::ST_START)
        {}
        
        void next_move(BibliSample& bibli);
        void update(string target, int eta, 
                    int score, vector<int> storages, 
                    vector<int> expertises);
        vector<int> what_need(Sample sample);
        void take_sample(int id) { current_sample = id; }
};
