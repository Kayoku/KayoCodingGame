#include "Robot.h"

/**
 * Fonctions du robot
 **/
void Robot::next_move(BibliSample& bibli)
{
    switch(state)
    {
      case Robot_State::ST_START:
      {
        state = Robot_State::ST_DIAGNOSIS;
        cout << "GOTO DIAGNOSIS" << endl;
        break;
      }
      case Robot_State::ST_DIAGNOSIS:
      {
        // Trier les trucs par vie, et par nombre de molecule nécessaire,
        // et prendre le plus gros
        Sample best_sample = bibli.get_better();
        state = Robot_State::ST_DIAGNOSIS_DONE;
        take_sample(best_sample.get_id());
        cout << "CONNECT " << best_sample.get_id() << endl;
        break;
      }
      case Robot_State::ST_DIAGNOSIS_DONE:
      {
        state = Robot_State::ST_MOLECULES;
        cout << "GOTO MOLECULES" << endl;
        break;
      }
      case Robot_State::ST_MOLECULES:
      {
        for (auto n : bibli.search_id(current_sample).get_mols())
            cerr << n << ' ';
        cerr << endl;
        for (auto n : storages)
            cerr << n << ' ';
        cerr << endl;
        auto needed = what_need(bibli.search_id(current_sample));
        for (auto n : needed)
            cerr << n << ' ';
        cerr << endl;
        int num_mol = -1;
        for (int i = 0 ; i < needed.size() ; i++)
            if (needed[i] < 0)
            {
                num_mol = i;
                break;
            }
        
        string str = "CONNECT ";
        if (num_mol == 0)
            str += "A";
        else if (num_mol == 1)
            str += "B";
        else if (num_mol == 2)
            str += "C";
        else if (num_mol == 3)
            str += "D";
        else if (num_mol == 4)
            str += "E";
        else
            str = "GOTO LABORATORY";

        if (accumulate(needed.begin(), needed.end(), 0) == 0)
            state = Robot_State::ST_LABORATORY;

        cout << str << endl;
        break;
      }
      case Robot_State::ST_MOLECULES_DONE:
      {
        state = Robot_State::ST_LABORATORY;
        cout << "GOTO LABORATORY" << endl;
        break;
      }
      case Robot_State::ST_LABORATORY:
      {
        state = Robot_State::ST_START;
        cout << "CONNECT " << current_sample << endl;
        break;
      }
    };
}

void Robot::update(string target, int eta, int score, vector<int> storages, vector<int> expertises)
{
    this->target = target;
    this->eta = eta;
    this->score = score;
    this->storages = storages;
    this->expertises = expertises;
}

vector<int> Robot::what_need(Sample s)
{
    vector<int> needed = {0, 0, 0, 0, 0};
    auto sample_mols = s.get_mols();

    for (int i = 0 ; i < needed.size() ; i++)
        needed[i] = storages[i] - sample_mols[i];

    return needed;
}
