#include "include.h"
#include "Robot.h"

int main()
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
        ////////////////////

        int sampleCount;
        cin >> sampleCount; cin.ignore();
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
        
            Sample sample(sampleId, carriedBy, rank, expertiseGain, health,
                          {costA, costB, costC, costD, costE});
            bibli.add_sample(sample);
        }
        
        robot.next_move(bibli);
    }
}
