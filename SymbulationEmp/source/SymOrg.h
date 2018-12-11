#include "source/tools/Random.h"
#include "source/tools/string_utils.h"
#include <set>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <vector>
#include "source/tools/random_utils.h"


class Symbiont {
 private:  
  double interaction_val;
  double points;
  //Added
  double vertTrans;
  std::set<int> res_types;
  //Added
  std::vector<std::string> injectors={"111"}; 


 public:

 Symbiont(double _intval=0.0, double _points = 0.0, std::set<int> _set = std::set<int>())
   : interaction_val(_intval), points(_points), res_types(_set) {}
  Symbiont(const Symbiont &) = default;
  Symbiont(Symbiont &&) = default;

  //Added
  // Symbiont(double _intval=0.0, double _points = 0.0, std::set<int> _set = std::set<int>(), std::vector<std::string> _in = std::vector<std::string>())
  // : interaction_val(_intval), points(_points), res_types(_set), injectors(_in) {}

  Symbiont & operator=(const Symbiont &) = default;
  Symbiont & operator=(Symbiont &&) = default;

  double GetIntVal() const {return interaction_val;}
  double GetPoints() {return points;}
  std::set<int> GetResTypes() const {return res_types;}
  //Added
  double GetVertTrans() {return vertTrans;}

  //Added
  std::vector<std::string> GetInjectors() {return injectors;}

  //Added
  void SetVertTrans(double _in){ vertTrans = _in;}
  
  void SetIntVal(double _in) { interaction_val = _in;}
  void SetPoints(double _in) { points = _in;}
  void AddPoints(double _in) { points += _in;}
  void SetResTypes(std::set<int> _in) {res_types = _in;}

  //Added
  void SetInjectors(std::vector<std::string> _in){injectors = _in;}

 
  void mutate(emp::Random &random, double mut_rate){
    interaction_val += random.GetRandNormal(0.0, mut_rate);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }

  //Added
  bool WillTransmit() {
    double transmit = ((double) rand() / (RAND_MAX));
    // std::cout<< "tran" << transmit;
    // double transmit =(double) random.GetDouble(0.0, 1.0);
    //std::cout << transmit << std::endl;
    if (transmit < vertTrans) {
      //std::cout << "Will transmit" << std::endl;
      return true;
    }  else {
      return false;
    }
    

  }



  

};



std::string PrintSym(Symbiont  org){
  if (org.GetPoints() < 0) return "-";
  double out_val = org.GetIntVal();  
  
  // this prints the symbiont with two decimal places for easier reading
  std::stringstream temp;
  temp << std::fixed << std::setprecision(2) << out_val;
  std::string formattedstring = temp.str();
  return formattedstring;
  
}

class Host {
 private:
  double interaction_val;
  Symbiont sym;
  std::set<int> res_types;
  double points;
  //Added
  std::vector<std::string> resource_request= {"111"};
  
  //Added
  std::vector<std::string> OuterProteins={"111"};

 public:
 Host(double _intval =0.0, Symbiont _sym = *(new Symbiont(0, -1)), std::set<int> _set = std::set<int>(), double _points = 0.0)
   : interaction_val(_intval), sym(_sym), res_types(_set), points(_points) { ; }
  Host(const Host &) = default;
  Host(Host &&) = default;

  //Added
  // Host(double _intval =0.0, Symbiont _sym = *(new Symbiont(0, -1)), std::set<int> _set = std::set<int>(), double _points = 0.0, std::vector<std::string> _in = std::vector<std::string>())
  // : interaction_val(_intval), sym(_sym), res_types(_set), points(_points), OuterProteins(_in) { ; }
  


  Host & operator=(const Host &) = default;
  Host & operator=(Host &&) = default;
  bool operator==(const Host &other) const { return (this == &other);}
  bool operator!=(const Host &other) const {return !(*this == other);}


  double GetIntVal() const { return interaction_val;}
  Symbiont GetSymbiont() { return sym;}
  std::set<int> GetResTypes() const { return res_types;}
  double GetPoints() { return points;}
  //Added
  std::vector<std::string> GetOuterProteins() {return OuterProteins;}


  void SetIntVal(double _in) {interaction_val = _in;}
  void SetSymbiont(Symbiont _in) {sym = _in;}
  void SetResTypes(std::set<int> _in) {res_types = _in;}
  void SetPoints(double _in) {points = _in;}
  void AddPoints(double _in) {points += _in;}
  //Added
  void SetOuterProteins(std::vector<std::string> _in) {OuterProteins= _in;}
  
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

  //TODO: mutate OuterProteins
  void mutate(emp::Random &random, double mut_rate){
    interaction_val += random.GetRandNormal(0.0, mut_rate);
    if(interaction_val < -1) interaction_val = -1;
    else if (interaction_val > 1) interaction_val = 1;
  }


  void DistribResources(int resources, double synergy) { 

    std::vector<std::string> sym_injectors = sym.GetInjectors();
    bool success = false;
    bool distribute = false;
    double hostIntVal = interaction_val; 
    double symIntVal = sym.GetIntVal();
    
    double hostPortion = 0.0;
    double hostDonation = 0.0;
    double symPortion = 0.0;
    double symReturn = 0.0;
    double bonus = synergy;

    //Added
    //Distribute only when host has certain protein to recept resources
    for(unsigned int i=0; i<OuterProteins.size();i++){
      for(unsigned int j=0; j<resource_request.size(); j++){
        if(OuterProteins.at(i)==resource_request.at(j)){
          distribute = true;
          break;
        }
      }
    }

    //Added
    for(unsigned int i=0; i<sym_injectors.size();i++){
      for(unsigned int j=0; j<OuterProteins.size();j++){
        if(sym_injectors.at(i)==OuterProteins.at(j)){
          success=true;
          break;
        }
      }
    }

    if(success && distribute){

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
  }

  void Process(emp::Random &random) {
    //Currently just wrapping to use the existing function
    //TODO: make the below config options
    DistribResources(100, 5); 

  }
  

};

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


