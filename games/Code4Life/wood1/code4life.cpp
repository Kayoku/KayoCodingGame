#include "include.h"
#include "Robot.h"

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
