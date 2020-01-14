#include "DumpTriggerTimestamps.h"

#include <sstream>

DumpTriggerTimestamps::DumpTriggerTimestamps():Tool(){}


bool DumpTriggerTimestamps::Initialise(std::string configfile, DataModel &data){

  /////////////////// Useful header ///////////////////////
  if(configfile!="") m_variables.Initialise(configfile); // loading config file
  //m_variables.Print();

  m_data= &data; //assigning transient data pointer
  /////////////////////////////////////////////////////////////////

  m_variables.Get("OutputFile",outputfile);
  outf.open(outputfile.c_str(), std::fstream::out | std::fstream::binary | std::fstream::app );

  return true;
}


bool DumpTriggerTimestamps::Execute(){
  if (m_data->CStore.Has("TrigData")) {  
    Log("DTT");
    TriggerData td;
    m_data->CStore.Get("TrigData",td);
    cout << td.TimeStampSize << endl;
    outf.write((char*)td.TimeStampData.data(),td.TimeStampData.size()*sizeof(uint32_t));
    if (td.FIFOOverflow > 0) {
      Log("FIFO Overflow");
    }
  }
  return true;
}


bool DumpTriggerTimestamps::Finalise(){
  outf.close();
  return true;
}
