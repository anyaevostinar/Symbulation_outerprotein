#include "source/tools/Random.h"
#include "source/tools/string_utils.h"
#include <set>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <vector>


/*    
                                                       Symbiont Class

*/
class Symbiont {
 private:
    
    
  double interaction_val;
  double points;
  std::set<int> res_types; // The parameter res_types is not used in this program. It is here as a potential feature.
  //the ability to combine with certain type of receptor
  std::vector<std::string> injector;

 public:

 Symbiont(double _intval=0.0, double _points = 0.0, std::set<int> _set = std::set<int>()): interaction_val(_intval), points(_points), res_types(_set) {}
  
  Symbiont(const Symbiont &) = default;
  Symbiont(Symbiont &&) = default;
  

  Symbiont & operator=(const Symbiont &) = default;
  Symbiont & operator=(Symbiont &&) = default;

  double GetIntVal() const {return interaction_val;}
  double GetPoints() {return points;}
  std::set<int> GetResTypes() const {return res_types;}
  std::vector<std::string>& GetInjector() {return injector;}

  void SetIntVal(double _in) { interaction_val = _in;}
  void SetPoints(double _in) { points = _in;}
  void AddPoints(double _in) { points += _in;}
  void SetResTypes(std::set<int> _in) {res_types = _in;}
  void SetInjector(std::vector<std::string> _in) {injector = _in;}
    
  //TODO: mutate outer protein: random chance for each digit to flip(0/1)
  void mutate(emp::Random &random, double mut_rate){
    interaction_val += random.GetRandNormal(0.0, mut_rate);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }

};

/* This function is mainly for debugging purpose. It is not called anywhere in this program. */
std::string PrintSym(Symbiont  org){
  if (org.GetPoints() < 0) return "-";
  double out_val = org.GetIntVal();  
  
  // this prints the symbiont with two decimal places for easier reading
  std::stringstream temp;
  temp << std::fixed << std::setprecision(2) << out_val;
  std::string formattedstring = temp.str();
  return formattedstring;
  
  // return emp::to_string(out_val);  // creates a string without specifying format

}




/*    
                                                      Host Class

*/
class Host {
 private:
  double interaction_val;
  Symbiont sym;
  std::set<int> res_types; // Again, res_types is a potential feature. This parameter is not used in this program.
  double points;
  std::vector<std::string> outerproteins;
    
 public:
  /*
  Host() {
    interaction_val=0;
    sym=new Symbiont();
    res_types=std::set<int>();
    points=0;
    outerproteins=std::vector<std::string> (1,0);
    }*/
  
  // Constructor for the host class. Each host created from this constructor will have a fake symbiont that has an interaction value of 0 and points of -1.
 Host(double _intval =0.0, Symbiont _sym = *(new Symbiont(0, -1)), std::set<int> _set = std::set<int>(), double _points = 0.0): interaction_val(_intval), sym(_sym), res_types(_set), points(_points) { ; }
    
  Host(const Host &) = default;
  Host(Host &&) = default;


  Host & operator=(const Host &) = default;
  Host & operator=(Host &&) = default;
  bool operator==(const Host &other) const { return (this == &other);}
  bool operator!=(const Host &other) const {return !(*this == other);}


  double GetIntVal() const { return interaction_val;}
  Symbiont GetSymbiont() { return sym;}
  std::set<int> GetResTypes() const { return res_types;}
  double GetPoints() { return points;}
  std::vector<std::string>& GetOuterProteins() {return outerproteins;}


  void SetIntVal(double _in) {interaction_val = _in;}
  void SetSymbiont(Symbiont _in) {sym = _in;}
  void SetResTypes(std::set<int> _in) {res_types = _in;}
  void SetPoints(double _in) {points = _in;}
  void AddPoints(double _in) {points += _in;}
  void SetOuterProteins(std::vector<std::string> proteins){outerproteins=proteins;}
  
  void GiveSymPoints(double _in) {
    double distrib = _in;
    sym.AddPoints(distrib);
    
  }
  
  void ResetSymPoints() {
    sym.SetPoints(0.0);
  }
  	

  
  void SetSymIntVal (double _in) {
    sym.SetIntVal(_in);
  
  }
  
  void DeleteSym() {
    sym.SetPoints(-1.0);
  }
  
  bool HasSym() {
    if (sym.GetPoints() < 0) { 
      return false;
    } else {
      return true;
    }
  	
  }

  //TODO: mutate outer protein
  void mutate(emp::Random &random, double mut_rate){
    interaction_val += random.GetRandNormal(0.0, mut_rate);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }
  
  //TODO:certain outerprotein to allow absorbing resources from outside world.
  void DistribResources(int resources, double synergy) { 
    double hostIntVal = interaction_val;
    double symIntVal = sym.GetIntVal();
    
    double hostPortion = 0.0;
    double hostDonation = 0.0;
    double symPortion = 0.0;
    double symReturn = 0.0;
    double bonus = synergy; 

    if (hostIntVal >= 0 && symIntVal >= 0)  {  
      hostDonation = resources * hostIntVal;
      hostPortion = resources - hostDonation;
      
      if (symIntVal > 0){ //Do SymReturn and GiveSymPoints only when the host has a symbiont
        symReturn = (hostDonation * symIntVal) * bonus;  
        symPortion = hostDonation - (hostDonation * symIntVal);

        hostPortion += symReturn;
	    
        this->GiveSymPoints(symPortion);
      }
      
      this->AddPoints(hostPortion);
	    
    } else if (hostIntVal <= 0 && symIntVal < 0) {
      double hostDefense = -1.0 * (hostIntVal * resources);
      double remainingResources = 0.0;
      remainingResources = resources - hostDefense;
      
      if (symIntVal < hostIntVal) {
        double symSteals = (hostIntVal - symIntVal) * remainingResources;
        symPortion = symSteals;
        hostPortion = remainingResources - symSteals;
      } else { 
        symPortion = 0.0;
        hostPortion = remainingResources;
	     	
      }
   
      this->GiveSymPoints(symPortion);
      this->AddPoints(hostPortion);
	     
	
    } else if (hostIntVal > 0 && symIntVal < 0) {
      hostDonation = hostIntVal * resources;
      hostPortion = resources - hostDonation;
      resources = resources - hostDonation;
		
      double symSteals = -1.0 * (resources * symIntVal);
      hostPortion = hostPortion - symSteals;
      symPortion = hostDonation + symSteals;
		
      this->GiveSymPoints(symPortion);
      this->AddPoints(hostPortion);
		
		
    } else if (hostIntVal < 0 && symIntVal >= 0) {
      double hostDefense = -1.0 * (hostIntVal * resources);
      hostPortion = resources - hostDefense;
		
      if (symIntVal > 0){//Give symbiont points only if a symbiont exists
        symPortion = 0.0;
		
        this->GiveSymPoints(symPortion);
      }
      this->AddPoints(hostPortion);
    } else {
      
    }

  }

  void Process(emp::Random &random) {
    //Currently just wrapping to use the existing function
    DistribResources(100, 5); 

  }
  

};

// This function is primarily for debugging purpose and is not called anywhere in this program.
std::string PrintHost(Host * org) {
  if (!org) return "-/-";
  
  std::stringstream temp;
  temp << std::fixed << std::setprecision(2) << org->GetIntVal();
  std::string formattedstring = temp.str();
  
  std::string out_val = formattedstring + "/" + PrintSym(org->GetSymbiont());
  
  // std::string out_val = emp::to_string(org->GetIntVal(),"/", PrintSym(org->GetSymbiont()));  // not completely formatted
  return out_val;
}

std::string PrintOrg(Host * org) {return PrintHost(org);}


