#include "source/Evolve/World.h"
#include "source/tools/Random.h"
#include <set>
#include <vector>
#include "SymOrg.h"
#include "source/tools/random_utils.h"
#include "source/data/DataFile.h"

class SymWorld : public emp::World<Host>{
 private:
  double vertTrans = 0; 
  double mut_rate = 0;
  emp::Random random;
  
  emp::Ptr<emp::DataMonitor<double, emp::data::Histogram>> data_node_hostintval;
  emp::Ptr<emp::DataMonitor<double, emp::data::Histogram>> data_node_symintval;

 public:
  //set fun_print_org to equal function that prints hosts/syms correctly
 SymWorld(emp::Random &random) : emp::World<Host>(random) {
    fun_print_org = [](Host & org, std::ostream & os) {
      os << PrintHost(&org);
    };
  }
  
  void SetVertTrans(double vt) {
    vertTrans = vt;
  }
  void SetMutRate(double mut) {
    mut_rate = mut;
  }


  bool WillTransmit() {
    double transmit = random.GetDouble(0.0, 1.0);
    if (transmit < vertTrans) {
      return true;
    }  else {
      return false;
    }
    

  }

  emp::DataFile & SetupSymIntValFile(const std::string & filename) {
    auto & file = SetupFile(filename);
    auto & node = GetSymIntValDataNode();
    node.SetupBins(-1.0, 1.0, 20);
    file.AddVar(update, "update", "Update");
    file.AddMean(node, "mean_intval", "Average symbiont interaction value");
    file.AddHistBin(node, 0, "Hist_-1", "Count for histogram bin -1 to <-0.9");
    file.AddHistBin(node, 1, "Hist_-0.9", "Count for histogram bin -0.9 to <-0.8");
    file.AddHistBin(node, 2, "Hist_-0.8", "Count for histogram bin -0.8 to <-0.7");
    file.AddHistBin(node, 3, "Hist_-0.7", "Count for histogram bin -0.7 to <-0.6");
    file.AddHistBin(node, 4, "Hist_-0.6", "Count for histogram bin -0.6 to <-0.5");
    file.AddHistBin(node, 5, "Hist_-0.5", "Count for histogram bin -0.5 to <-0.4");
    file.AddHistBin(node, 6, "Hist_-0.4", "Count for histogram bin -0.4 to <-0.3");
    file.AddHistBin(node, 7, "Hist_-0.3", "Count for histogram bin -0.3 to <-0.2");
    file.AddHistBin(node, 8, "Hist_-0.2", "Count for histogram bin -0.2 to <-0.1");
    file.AddHistBin(node, 9, "Hist_-0.1", "Count for histogram bin -0.1 to <0.0");
    file.AddHistBin(node, 10, "Hist_0.0", "Count for histogram bin 0.0 to <0.1");
    file.AddHistBin(node, 11, "Hist_0.1", "Count for histogram bin 0.1 to <0.2");
    file.AddHistBin(node, 12, "Hist_0.2", "Count for histogram bin 0.2 to <0.3");
    file.AddHistBin(node, 13, "Hist_0.3", "Count for histogram bin 0.3 to <0.4");
    file.AddHistBin(node, 14, "Hist_0.4", "Count for histogram bin 0.4 to <0.5");
    file.AddHistBin(node, 15, "Hist_0.5", "Count for histogram bin 0.5 to <0.6");
    file.AddHistBin(node, 16, "Hist_0.6", "Count for histogram bin 0.6 to <0.7");
    file.AddHistBin(node, 17, "Hist_0.7", "Count for histogram bin 0.7 to <0.8");
    file.AddHistBin(node, 18, "Hist_0.8", "Count for histogram bin 0.8 to <0.9");
    file.AddHistBin(node, 19, "Hist_0.9", "Count for histogram bin 0.9 to 1.0");


    file.PrintHeaderKeys();

    return file;
  }
    emp::DataFile & SetupHostIntValFile(const std::string & filename) {
    auto & file = SetupFile(filename);
    auto & node = GetHostIntValDataNode(); 
    node.SetupBins(-1.0, 1.0, 20);

    file.AddVar(update, "update", "Update");
    file.AddMean(node, "mean_intval", "Average host interaction value");
    file.AddHistBin(node, 0, "Hist_-1", "Count for histogram bin -1 to <-0.9");
    file.AddHistBin(node, 1, "Hist_-0.9", "Count for histogram bin -0.9 to <-0.8");
    file.AddHistBin(node, 2, "Hist_-0.8", "Count for histogram bin -0.8 to <-0.7");
    file.AddHistBin(node, 3, "Hist_-0.7", "Count for histogram bin -0.7 to <-0.6");
    file.AddHistBin(node, 4, "Hist_-0.6", "Count for histogram bin -0.6 to <-0.5");
    file.AddHistBin(node, 5, "Hist_-0.5", "Count for histogram bin -0.5 to <-0.4");
    file.AddHistBin(node, 6, "Hist_-0.4", "Count for histogram bin -0.4 to <-0.3");
    file.AddHistBin(node, 7, "Hist_-0.3", "Count for histogram bin -0.3 to <-0.2");
    file.AddHistBin(node, 8, "Hist_-0.2", "Count for histogram bin -0.2 to <-0.1");
    file.AddHistBin(node, 9, "Hist_-0.1", "Count for histogram bin -0.1 to <0.0");
    file.AddHistBin(node, 10, "Hist_0.0", "Count for histogram bin 0.0 to <0.1");
    file.AddHistBin(node, 11, "Hist_0.1", "Count for histogram bin 0.1 to <0.2");
    file.AddHistBin(node, 12, "Hist_0.2", "Count for histogram bin 0.2 to <0.3");
    file.AddHistBin(node, 13, "Hist_0.3", "Count for histogram bin 0.3 to <0.4");
    file.AddHistBin(node, 14, "Hist_0.4", "Count for histogram bin 0.4 to <0.5");
    file.AddHistBin(node, 15, "Hist_0.5", "Count for histogram bin 0.5 to <0.6");
    file.AddHistBin(node, 16, "Hist_0.6", "Count for histogram bin 0.6 to <0.7");
    file.AddHistBin(node, 17, "Hist_0.7", "Count for histogram bin 0.7 to <0.8");
    file.AddHistBin(node, 18, "Hist_0.8", "Count for histogram bin 0.8 to <0.9");
    file.AddHistBin(node, 19, "Hist_0.9", "Count for histogram bin 0.9 to 1.0");


    file.PrintHeaderKeys();

    return file;
  }

  double CalcIntVal(size_t i) {
    return pop[i]->GetIntVal(); 
  }

  double CalcSymIntVal(size_t i) {
    //TODO: this should probably be a reference to Symbiont    
    return pop[i]->GetSymbiont().GetIntVal();
  }

  emp::DataMonitor<double, emp::data::Histogram>& GetHostIntValDataNode() {
    if (!data_node_hostintval) {
      data_node_hostintval.New();
      OnUpdate(
	       [this](size_t){
		 data_node_hostintval->Reset();
		 for (size_t i = 0; i< pop.size(); i++) {
		   if (IsOccupied(i)) data_node_hostintval->AddDatum(CalcIntVal(i));
		 }
	       }
	       );
    }
    return *data_node_hostintval;
  }



  emp::DataMonitor<double, emp::data::Histogram>& GetSymIntValDataNode() {
    if (!data_node_symintval) {
      data_node_symintval.New();
      OnUpdate(
	       [this](size_t){
		 data_node_symintval->Reset();
		 for (size_t i = 0; i< pop.size(); i++) {
                   // CHANGED: Check if the organism has a symbiont before adding the data
		   if (IsOccupied(i) && pop[i]->HasSym()) data_node_symintval->AddDatum(CalcSymIntVal(i));
		 }
	       }
	       );
    }
    return *data_node_symintval;
  }
  
    
  /*
                                                                          Update()
   */   
    
  void Update(size_t new_resources=10) {
    emp::World<Host>::Update();

    //TODO: put in fancy scheduler at some point
    
    emp::vector<size_t> schedule = emp::GetPermutation(random, GetSize());
    
    // Distribute resources between host and symbiont in each cell 
    for (size_t i : schedule) {
      if (IsOccupied(i) == false) continue;  // no host at that cell
  	   
      pop[i]->Process(random);

      //Reproduction
      if (pop[i]->GetPoints() >= 1000) {  // host reproduction                                                                                
	Symbiont *sym_baby;
	if (pop[i]->HasSym() && WillTransmit()) { // symbiont's vertical transmission
	  sym_baby = new Symbiont(pop[i]->GetSymbiont().GetIntVal(), 0.0); // The offspring symbiont is born with its parent's interaction value and 0 resources
          sym_baby->SetInjector(pop[i]->GetSymbiont().GetInjector());// The offspring symbiont has the same injector as its parent
	  sym_baby->mutate(random, mut_rate); // mutate the offspring symbiont
	  pop[i]->GetSymbiont().mutate(random, mut_rate); //mutate the parent symbiont                                                                            
 
	}else{
	  // The offspring host will be born with no symbiont (i.e., a fake symbiont indicated by having -1 resources)
	  sym_baby = new Symbiont(0.0, -1.0);
	}

	Host *host_baby = new Host(pop[i]->GetIntVal(),*sym_baby,std::set<int>(), 0.0); 
        host_baby->SetOuterProteins(pop[i]->GetOuterProteins());
	host_baby->mutate(random, mut_rate);
	
	// Parent host mutates and loses current resources
	pop[i]->mutate(random, mut_rate); 
	pop[i]->SetPoints(0); // Reset the host's resources completely
	DoBirth(*host_baby, i); // Injects the offspring host into the population and replace a random host
      }

      
      if (pop[i]->HasSym() && pop[i]->GetSymbiont().GetPoints() >= 100) {  // symbiont's horizontal transmission
	pop[i]->ResetSymPoints(); // Symbiont reproduces and loses current resources
	Symbiont *sym_baby = new Symbiont(pop[i]->GetSymbiont());
	sym_baby->mutate(random, mut_rate);
	pop[i]->GetSymbiont().mutate(random, mut_rate);
	 	 
	// Pick new host to infect, if one exists at the new location and does not already have a symbiont
	int newLoc = GetRandomCellID();
	if (IsOccupied(newLoc) == true) {
          
        //search for specific receptor
        std::vector<std::string> hostprotein = pop[newLoc]->GetOuterProteins();
        std::vector<std::string>::iterator it;

        for(unsigned int i=0; i<sym_baby->GetInjector().size(); i++){
            std::string protein = sym_baby->GetInjector()[i];
            it = std::find(hostprotein.begin(), hostprotein.end(), protein);
            if(it != hostprotein.end()){
                break;
            }
        }
        
        if(it == hostprotein.end()){
        
        //One host has one symbiont
	  if (!pop[newLoc]->HasSym()) {
	    pop[newLoc]->SetSymbiont(*sym_baby);

	  }
	}
        //if there is no such receptor, it dies
    
      }                                                                                                                              
 
    }
  }
  }

};


