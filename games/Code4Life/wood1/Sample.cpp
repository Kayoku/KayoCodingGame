#include "Sample.h"

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
