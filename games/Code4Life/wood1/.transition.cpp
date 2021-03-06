#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

enum class Robot_State
{
    ST_START,
    ST_SAMPLES,
    ST_SAMPLES_DONE,
    ST_DIAGNOSIS,
    ST_DIAGNOSIS_DONE,
    ST_MOLECULES,
    ST_MOLECULES_DONE,
    ST_LABORATORY
};

class Sample
{
    private:
        int id;
        int carried;
        int rank;
        string gain;
        int health;
        vector<int> mols;
        bool analyzed;
        
    public:
        Sample()
        {}
    
        Sample(int id,
               int carried,
               int rank,
               string gain,
               int health,
               vector<int> mols):
            id(id), carried(carried), rank(rank),
            gain(gain), health(health), mols(mols)
        {}
        
        int get_health() { return health; }
        int get_total_mols() { return std::accumulate(mols.begin(), mols.end(), 0); }
        vector<int> get_mols() { return mols; }
        int get_carried() { return carried; }
        int get_id() { return id; }
};

class BibliSample
{
  private:
    vector<Sample> samples;

  public:
    BibliSample()
    {}
    
    void add_sample(Sample s) { samples.push_back(s); }
    vector<Sample>& get_samples() { return samples; }
    Sample search_id(int id);
    Sample get_better();
};

////////////////////////////////////////////////////////////////////////////
Sample BibliSample::search_id(int id)
////////////////////////////////////////////////////////////////////////////
{
    for (auto s : samples)
        if (s.get_id() == id)
            return s;
}

////////////////////////////////////////////////////////////////////////////
Sample BibliSample::get_better()
////////////////////////////////////////////////////////////////////////////
{
    cerr << "Size: " << samples.size() << endl;
    Sample best_sample = samples[0];
    for (auto s: samples)
        if (best_sample.get_carried() == 1)
			/*||
            (s.get_carried() == -1 &&
            best_sample.get_health() <= s.get_health() &&
            best_sample.get_total_mols() <= s.get_total_mols()))*/
            best_sample = s;
    return best_sample;
}

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

////////////////////////////////////////////////////////////////////////////
void Robot::next_move(BibliSample& bibli)
////////////////////////////////////////////////////////////////////////////
{
    switch(state)
    {
      case Robot_State::ST_START:
      {
        state = Robot_State::ST_SAMPLES;
        cout << "GOTO SAMPLES" << endl;
        break;
      }
      case Robot_State::ST_SAMPLES:
      {
	cout << "CONNECT 2" << endl;
	state = Robot_State::ST_SAMPLES_DONE;
	break;
      }
      case Robot_State::ST_SAMPLES_DONE:
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

////////////////////////////////////////////////////////////////////////////
void Robot::update
////////////////////////////////////////////////////////////////////////////
(
 string target,
 int eta,
 int score,
 vector<int> storages,
 vector<int> expertises
)
{
    this->target = target;
    this->eta = eta;
    this->score = score;
    this->storages = storages;
    this->expertises = expertises;
}

////////////////////////////////////////////////////////////////////////////
vector<int> Robot::what_need(Sample s)
////////////////////////////////////////////////////////////////////////////
{
    vector<int> needed = {0, 0, 0, 0, 0};
    auto sample_mols = s.get_mols();

    for (int i = 0 ; i < needed.size() ; i++)
        needed[i] = storages[i] - sample_mols[i];

    return needed;
}

////////////////////////////////////////////////////////////////////////////
int main()
////////////////////////////////////////////////////////////////////////////
{
    // IGNORE /////////
    int projectCount;
    cin >> projectCount; cin.ignore();
    for (int i = 0; i < projectCount; i++) {
        int a;
        int b;
        int c;
        int d;
        int e;
        cin >> a >> b >> c >> d >> e; cin.ignore();
	cerr << a << " " << b << " " << c << " " << d << " " << e << endl;
    }
    ////////////////////

    Robot robot;

    while (1) {
        for (int i = 0; i < 2; i++) {
            string target;
            int eta;
            int score;
            int storageA;
            int storageB;
            int storageC;
            int storageD;
            int storageE;
            int expertiseA;
            int expertiseB;
            int expertiseC;
            int expertiseD;
            int expertiseE;
            cin >> target >> eta >> score >> storageA >> storageB >> storageC >> storageD >> storageE >> expertiseA >> expertiseB >> expertiseC >> expertiseD >> expertiseE; cin.ignore();
	    cerr << target << " " << eta << " " << score << " " << storageA << " " << storageB << " " << storageC << " " << storageD << " " << storageE << " " << expertiseA << " " << expertiseB << " " << expertiseC << " " << expertiseD << " " << expertiseE << endl;
        
            if (i == 0)
                robot.update(target, eta, score,
                            {storageA, storageB, storageC, storageD, storageE},
                            {expertiseA, expertiseB, expertiseC, expertiseD, expertiseE});
        }
        
        // IGNORE /////////
        int availableA;
        int availableB;
        int availableC;
        int availableD;
        int availableE;
        cin >> availableA >> availableB >> availableC >> availableD >> availableE; cin.ignore();
	cerr << availableA << " " << availableB << " " << availableC << " " << availableD << " " << availableE << endl;

        ////////////////////

        int sampleCount;
        cin >> sampleCount; cin.ignore();
	cerr << sampleCount << endl;
        BibliSample bibli;
        for (int i = 0; i < sampleCount; i++) {
            int sampleId;
            int carriedBy;
            int rank;
            string expertiseGain;
            int health;
            int costA;
            int costB;
            int costC;
            int costD;
            int costE;
            cin >> sampleId >> carriedBy >> rank >> expertiseGain >> health >> costA >> costB >> costC >> costD >> costE; cin.ignore();
	    cerr << sampleId << " " << carriedBy << " " << rank << " " << expertiseGain << " " << health << " " << costA << " " << costB << " " << costC << " " << costD << " " << costE << endl;
        
            Sample sample(sampleId, carriedBy, rank, expertiseGain, health,
                          {costA, costB, costC, costD, costE});
            bibli.add_sample(sample);
        }
        cerr << "SIZE: " << bibli.get_samples().size() << endl; 
        robot.next_move(bibli);
    }
}
