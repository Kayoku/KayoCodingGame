#include "include.h" 

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
