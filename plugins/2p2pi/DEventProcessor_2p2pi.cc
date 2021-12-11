#include <map>
using namespace std;

#include "DEventProcessor_2p2pi.h"

#include <DANA/DApplication.h>



// Routine used to create our DEventProcessor
extern "C"{
  void InitPlugin(JApplication *app){
    InitJANAPlugin(app);
    app->AddProcessor(new DEventProcessor_2p2pi());
  }
} // "C"

thread_local DTreeFillData DEventProcessor_2p2pi::dTreeFillData;

//------------------
// init
///------------------

jerror_t DEventProcessor_2p2pi::init(void)
{
  //TTREE INTERFACE
  //MUST DELETE WHEN FINISHED: OR ELSE DATA WON'T BE SAVED!!!
  
  string treeName = "tree_2p2pi";
  string treeFile = "tree_2p2pi.root";
  gPARMS->SetDefaultParameter("SRC_2P2PI:TREENAME", treeName);
  gPARMS->SetDefaultParameter("SRC_2P2PI:TREEFILE", treeFile);
  dTreeInterface = DTreeInterface::Create_DTreeInterface(treeName, treeFile);

  //TTREE BRANCHES
  DTreeBranchRegister locTreeBranchRegister;

  locTreeBranchRegister.Register_Single<Int_t>("eventNumber");
  locTreeBranchRegister.Register_Single<Int_t>("L1TriggerBits");

  locTreeBranchRegister.Register_Single<Int_t>("nPhotonCandidates");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("bmE",    "nPhotonCandidates");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("bmtime", "nPhotonCandidates");

  //locTreeBranchRegister.Register_FundamentalArray<Double_t>("RFTime_Measured", "RFTime_Measured");

  locTreeBranchRegister.Register_Single<Int_t>("nShower");
  locTreeBranchRegister.Register_Single<Int_t>("nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("piminus_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("piminus_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaPhi_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaZ_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackFCAL_DOCA_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_piminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_piminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_piminus", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("piplus_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_pipluscand", "nHyp");  
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_pipluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_pipluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_pipluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaPhi_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaZ_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackFCAL_DOCA_pipluscand", "nHyp");         
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("piplus_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_pipluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_piplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_piplus", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_proton0", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_proton0", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_proton0", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_proton0", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_proton0", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot0cand_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot0cand_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_prot0cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_prot0cand", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_proton1", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_proton1", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_proton1", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_proton1", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_proton1", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot1cand_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot1cand_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_prot1cand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_prot1cand", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("X_vertex", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Y_vertex", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Z_vertex", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("T_vertex", "nHyp");
  
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("CLKinFit", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSqFit", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Common_Time", "nHyp");

  //REGISTER BRANCHES
  dTreeInterface->Create_Branches(locTreeBranchRegister);

  return NOERROR;
}

//------------------ 
// brun
//------------------  
jerror_t DEventProcessor_2p2pi::brun(JEventLoop *eventLoop, int32_t runnumber)
{
  dKinFitUtils = new DKinFitUtils_GlueX(eventLoop);
  dKinFitter = new DKinFitter(dKinFitUtils);

  eventLoop->GetSingle(dAnalysisUtilities);

  return NOERROR;
}

//------------------
// evnt
//------------------

jerror_t DEventProcessor_2p2pi::evnt(JEventLoop *loop, uint64_t eventnumber)
{

  vector<const DChargedTrack*>ch_tracks;
  vector<const DBeamPhoton*> beam_ph;
  vector<const DNeutralShower*> showers;
  const DTrigger* Trigger = NULL;

  loop->Get(ch_tracks);
  loop->Get(beam_ph);
  loop->Get(showers);
  loop->GetSingle(Trigger);

  const DEventRFBunch* locEventRFBunch = NULL;
  loop->GetSingle(locEventRFBunch);
  const DParticleID* locParticleID = NULL;
  loop->GetSingle(locParticleID);


  if(!Trigger->Get_IsPhysicsEvent()) return NOERROR;
  if (ch_tracks.size()!=4) return NOERROR;

  map<Particle_t, int> targetParticles = {
	{Proton,2},
        {PiPlus,1},
        {PiMinus,1}
  };

   map<Particle_t, vector<const DChargedTrackHypothesis*> > emptyHypothesis;
   vector<map<Particle_t, vector<const DChargedTrackHypothesis*> > > hypothesisList;
   GetHypotheses(ch_tracks,targetParticles,emptyHypothesis,hypothesisList);
  

   Int_t _nHyp = hypothesisList.size();
    
   if(_nHyp == 0)  return NOERROR;

   LockState(); //ACQUIRE PROCESSOR LOCK

   dTreeFillData.Fill_Single<Int_t>("nHyp", _nHyp);

   //=== Photon Informatiion 
   Int_t  _nPhotonCandidates = beam_ph.size();

  dTreeFillData.Fill_Single<Int_t>("nPhotonCandidates", _nPhotonCandidates);
  
  if(_nPhotonCandidates>0){
     for(Int_t ii = 0; ii < _nPhotonCandidates; ii++){
        dTreeFillData.Fill_Array<Double_t>("bmE", beam_ph[ii]->momentum().Mag(), ii);
        dTreeFillData.Fill_Array<Double_t>("bmtime", beam_ph[ii]->time(), ii);
     }
  }
  //==========================
  //
  dTreeFillData.Fill_Single<Int_t>("eventNumber", eventnumber); 
  dTreeFillData.Fill_Single<Double_t>("L1TriggerBits", Trigger->Get_L1TriggerBits());
  dTreeFillData.Fill_Single<Int_t>("nShower",showers.size());


  dKinFitUtils->Reset_NewEvent();
  dKinFitter->Reset_NewEvent();


  dKinFitUtils->Reset_NewEvent();
  dKinFitter->Reset_NewEvent();

  for (Int_t j = 0; j < _nHyp; j++){
  
     map<Particle_t, vector<const DChargedTrackHypothesis*> > thisHyp = hypothesisList[j];

     //============ PiMinus Hypothesis ===========================================================//
     const DChargedTrackHypothesis *hyp_pi_min   = thisHyp[PiMinus][0];
     const DTrackTimeBased *pi_min_track = hyp_pi_min->Get_TrackTimeBased();            	    
     double FOM_piminuscand          = hyp_pi_min->Get_FOM();
     double NDF_piminuscand          = hyp_pi_min->Get_NDF();
     double ChiSq_piminuscand        = hyp_pi_min->Get_ChiSq();
     double piminus_dedx_dc_NDF      = hyp_pi_min->Get_NDF_DCdEdx();
     double piminus_dedx_dc_ChiSq    = hyp_pi_min->Get_ChiSq_DCdEdx();
     double Beta_Timing_piminuscand  = hyp_pi_min->measuredBeta();
     double NDF_Timing_piminuscand   = hyp_pi_min->Get_NDF_Timing();
     double ChiSq_Timing_piminuscand = hyp_pi_min->Get_ChiSq_Timing();
     double dEdx_TOF_piminuscand     = (hyp_pi_min->Get_TOFHitMatchParams() != NULL) ? hyp_pi_min->Get_TOFHitMatchParams()->dEdx : 0.0;
     double dEdx_ST_piminuscand      = (hyp_pi_min->Get_SCHitMatchParams()  != NULL) ? hyp_pi_min->Get_SCHitMatchParams()->dEdx : 0.0;
     double dEdx_CDC_piminuscand      = (hyp_pi_min->Get_TrackTimeBased() != NULL) ? hyp_pi_min->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
     double dEdx_FDC_piminuscand      = (hyp_pi_min->Get_TrackTimeBased() != NULL) ? hyp_pi_min->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
     const DBCALShower* showerpiminus = NULL;
     if (hyp_pi_min->Get_BCALShowerMatchParams() != NULL) showerpiminus = hyp_pi_min->Get_BCALShowerMatchParams()->dBCALShower;
     double Energy_BCAL_piminuscand  = (showerpiminus != NULL ) ? showerpiminus->E : 0.0;
     double Energy_BCALPreshower_piminuscand  = (showerpiminus != NULL ) ? showerpiminus->E_preshower : 0.0;
     double SigLong_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->sigLong : 0.0;
     double SigTheta_BCAL_piminuscand= (showerpiminus != NULL ) ? showerpiminus->sigTheta : 0.0;
     double SigTrans_BCAL_piminuscand= (showerpiminus != NULL ) ? showerpiminus->sigTrans : 0.0;
     double RMSTime_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->rmsTime : 0.0;
     double E_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->E : 0.0;
     double x_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->x : 0.0;
     double y_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->y : 0.0;
     double z_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->z : 0.0;
     double t_BCAL_piminuscand = (showerpiminus != NULL ) ? showerpiminus->t : 0.0;

     const DFCALShower* FCALshowerpiminus = NULL;
     if (hyp_pi_min->Get_FCALShowerMatchParams() != NULL) FCALshowerpiminus = hyp_pi_min->Get_FCALShowerMatchParams()->dFCALShower;
     double Energy_FCAL_piminuscand = (FCALshowerpiminus != NULL) ? FCALshowerpiminus->getEnergy() : 0.0;
     double E1E9_FCAL_piminuscand   = (FCALshowerpiminus != NULL) ? FCALshowerpiminus->getE1E9() : 0.0;
     double E9E25_FCAL_piminuscand  = (FCALshowerpiminus != NULL) ? FCALshowerpiminus->getE9E25() : 0.0;
     double SumU_FCAL_piminuscand   = (FCALshowerpiminus != NULL) ? FCALshowerpiminus->getSumU() : 0.0;
     double SumV_FCAL_piminuscand   = (FCALshowerpiminus != NULL) ? FCALshowerpiminus->getSumV() : 0.0;

     double TrackBCAL_DeltaPhi_piminuscand = ( hyp_pi_min->Get_BCALShowerMatchParams()  != NULL) ? hyp_pi_min->Get_BCALShowerMatchParams()->dDeltaPhiToShower : 999.0;
     double TrackBCAL_DeltaZ_piminuscand   = ( hyp_pi_min->Get_BCALShowerMatchParams()  != NULL) ? hyp_pi_min->Get_BCALShowerMatchParams()->dDeltaZToShower : 999.0;
     double TrackFCAL_DOCA_piminuscand     = ( hyp_pi_min->Get_FCALShowerMatchParams()  != NULL) ? hyp_pi_min->Get_FCALShowerMatchParams()->dDOCAToShower : 999.0;  

     double locStartTime_piminus         = locParticleID->Calc_PropagatedRFTime(hyp_pi_min, locEventRFBunch);
     auto  locTOFHitMatchParams_piminus = hyp_pi_min->Get_TOFHitMatchParams();     
     double locDeltaTOF_piminus = ( locTOFHitMatchParams_piminus != NULL ) ? locTOFHitMatchParams_piminus->dHitTime - locTOFHitMatchParams_piminus->dFlightTime - locStartTime_piminus : 999.0;  

     auto locBCALShowerMatchParams_piminus    = hyp_pi_min->Get_BCALShowerMatchParams();
    double locDeltaBCAL_piminus = 999.0;
    if(locBCALShowerMatchParams_piminus != NULL){
        const DBCALShower* locBCALShower_piminus = locBCALShowerMatchParams_piminus->dBCALShower;
        locDeltaBCAL_piminus = locBCALShower_piminus->t - locBCALShowerMatchParams_piminus->dFlightTime - locStartTime_piminus;
    }

     dTreeFillData.Fill_Array<Double_t>("FOM_piminuscand",FOM_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("NDF_piminuscand",NDF_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_piminuscand",ChiSq_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("piminus_dedx_dc_NDF",piminus_dedx_dc_NDF, j);
     dTreeFillData.Fill_Array<Double_t>("piminus_dedx_dc_ChiSq",piminus_dedx_dc_ChiSq, j);
     dTreeFillData.Fill_Array<Double_t>("Beta_Timing_piminuscand",Beta_Timing_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("NDF_Timing_piminuscand",NDF_Timing_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_piminuscand",ChiSq_Timing_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_piminuscand",ChiSq_Timing_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_piminuscand",dEdx_TOF_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_ST_piminuscand",dEdx_ST_piminuscand, j);	
     dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_piminuscand",dEdx_CDC_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_piminuscand",dEdx_FDC_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_piminuscand",Energy_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_piminuscand",Energy_BCALPreshower_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_piminuscand",SigLong_BCAL_piminuscand, j); 
     dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_piminuscand",SigTheta_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_piminuscand",SigTrans_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_piminuscand",RMSTime_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E_BCAL_piminuscand",E_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("x_BCAL_piminuscand",x_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("y_BCAL_piminuscand",y_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("z_BCAL_piminuscand",z_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("t_BCAL_piminuscand",t_BCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_piminuscand",Energy_FCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_piminuscand",E1E9_FCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_piminuscand",E9E25_FCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_piminuscand",SumU_FCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_piminuscand",SumV_FCAL_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaPhi_piminuscand",TrackBCAL_DeltaPhi_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaZ_piminuscand",TrackBCAL_DeltaZ_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackFCAL_DOCA_piminuscand",TrackFCAL_DOCA_piminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_piminus",locDeltaTOF_piminus, j);
     dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_piminus",locDeltaBCAL_piminus, j);

    //============ PiPlus Hypothesis ===========================================================//
    const DChargedTrackHypothesis *hyp_pi_plus   = thisHyp[PiPlus][0];
    const DTrackTimeBased *pi_plus_track = hyp_pi_plus->Get_TrackTimeBased();
    double FOM_pipluscand = hyp_pi_plus->Get_FOM();
    double NDF_pipluscand = hyp_pi_plus->Get_NDF();
    double ChiSq_pipluscand = hyp_pi_plus->Get_ChiSq();
    double piplus_dedx_dc_NDF = hyp_pi_plus->Get_NDF_DCdEdx();
    double piplus_dedx_dc_ChiSq  = hyp_pi_plus->Get_ChiSq_DCdEdx();
    double Beta_Timing_pipluscand = hyp_pi_plus->measuredBeta();
    double NDF_Timing_pipluscand   = hyp_pi_plus->Get_NDF_Timing();
    double ChiSq_Timing_pipluscand = hyp_pi_plus->Get_ChiSq_Timing();
    double dEdx_TOF_pipluscand = (hyp_pi_plus->Get_TOFHitMatchParams() != NULL) ? hyp_pi_plus->Get_TOFHitMatchParams()->dEdx : 0.0;
    double dEdx_ST_pipluscand  = (hyp_pi_plus->Get_SCHitMatchParams()  != NULL) ? hyp_pi_plus->Get_SCHitMatchParams()->dEdx : 0.0;
    double dEdx_CDC_pipluscand      = (hyp_pi_plus->Get_TrackTimeBased() != NULL) ? hyp_pi_plus->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
    double dEdx_FDC_pipluscand      = (hyp_pi_plus->Get_TrackTimeBased() != NULL) ? hyp_pi_plus->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
    const DBCALShower* showerpiplus = NULL;
    if (hyp_pi_plus->Get_BCALShowerMatchParams() != NULL) showerpiplus = hyp_pi_plus->Get_BCALShowerMatchParams()->dBCALShower;
    double Energy_BCAL_pipluscand  = (showerpiplus != NULL ) ? showerpiplus->E : 0.0;
    double Energy_BCALPreshower_pipluscand  = (showerpiplus != NULL ) ? showerpiplus->E_preshower : 0.0;
    double SigLong_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->sigLong : 0.0;
    double SigTheta_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->sigTheta : 0.0;
    double SigTrans_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->sigTrans : 0.0;
    double RMSTime_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->rmsTime : 0.0;
    double E_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->E : 0.0;
    double x_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->x : 0.0;
    double y_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->y : 0.0;
    double z_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->z : 0.0;
    double t_BCAL_pipluscand = (showerpiplus != NULL ) ? showerpiplus->t : 0.0;

    const DFCALShower* FCALshowerpiplus = NULL;
    if (hyp_pi_plus->Get_FCALShowerMatchParams() != NULL) FCALshowerpiplus = hyp_pi_plus->Get_FCALShowerMatchParams()->dFCALShower;
    double Energy_FCAL_pipluscand = (FCALshowerpiplus != NULL) ? FCALshowerpiplus->getEnergy() : 0.0;
    double E1E9_FCAL_pipluscand = (FCALshowerpiplus != NULL) ? FCALshowerpiplus->getE1E9() : 0.0;
    double E9E25_FCAL_pipluscand = (FCALshowerpiplus != NULL) ? FCALshowerpiplus->getE9E25() : 0.0;
    double SumU_FCAL_pipluscand = (FCALshowerpiplus != NULL) ? FCALshowerpiplus->getSumU() : 0.0;
    double SumV_FCAL_pipluscand = (FCALshowerpiplus != NULL) ? FCALshowerpiplus->getSumV() : 0.0;

    double TrackBCAL_DeltaPhi_pipluscand = ( hyp_pi_plus->Get_BCALShowerMatchParams()  != NULL) ? hyp_pi_plus->Get_BCALShowerMatchParams()->dDeltaPhiToShower : 999.0;
    double TrackBCAL_DeltaZ_pipluscand   = ( hyp_pi_plus->Get_BCALShowerMatchParams()  != NULL) ? hyp_pi_plus->Get_BCALShowerMatchParams()->dDeltaZToShower : 999.0;
    double TrackFCAL_DOCA_pipluscand     = ( hyp_pi_plus->Get_FCALShowerMatchParams()  != NULL) ? hyp_pi_plus->Get_FCALShowerMatchParams()->dDOCAToShower : 999.0;
 
     double locStartTime_piplus         = locParticleID->Calc_PropagatedRFTime(hyp_pi_plus, locEventRFBunch);
     auto  locTOFHitMatchParams_piplus   = hyp_pi_plus->Get_TOFHitMatchParams();
     double locDeltaTOF_piplus = ( locTOFHitMatchParams_piplus != NULL ) ? locTOFHitMatchParams_piplus->dHitTime - locTOFHitMatchParams_piplus->dFlightTime - locStartTime_piplus : 999.0;
     
    auto locBCALShowerMatchParams_piplus    = hyp_pi_plus->Get_BCALShowerMatchParams();
    double locDeltaBCAL_piplus = 999.0;
    if(locBCALShowerMatchParams_piplus != NULL){
        const DBCALShower* locBCALShower_piplus = locBCALShowerMatchParams_piplus->dBCALShower;
        locDeltaBCAL_piplus = locBCALShower_piplus->t - locBCALShowerMatchParams_piplus->dFlightTime - locStartTime_piplus;
    }

    dTreeFillData.Fill_Array<Double_t>("FOM_pipluscand",FOM_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("NDF_pipluscand",NDF_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("ChiSq_pipluscand",ChiSq_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("piplus_dedx_dc_NDF",piplus_dedx_dc_NDF, j);
    dTreeFillData.Fill_Array<Double_t>("piplus_dedx_dc_ChiSq",piplus_dedx_dc_ChiSq, j);
    dTreeFillData.Fill_Array<Double_t>("Beta_Timing_pipluscand",Beta_Timing_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("NDF_Timing_pipluscand",NDF_Timing_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_pipluscand",ChiSq_Timing_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_pipluscand",dEdx_TOF_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_ST_pipluscand",dEdx_ST_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_pipluscand",dEdx_CDC_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_pipluscand",dEdx_FDC_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_pipluscand",Energy_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_pipluscand",Energy_BCALPreshower_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_pipluscand",SigLong_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_pipluscand",SigTheta_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_pipluscand",SigTrans_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_pipluscand",RMSTime_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E_BCAL_pipluscand",E_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("x_BCAL_pipluscand",x_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("y_BCAL_pipluscand",y_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("z_BCAL_pipluscand",z_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("t_BCAL_pipluscand",t_BCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_pipluscand",Energy_FCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_pipluscand",E1E9_FCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_pipluscand",E9E25_FCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_pipluscand",SumU_FCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_pipluscand",SumV_FCAL_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaPhi_pipluscand",TrackBCAL_DeltaPhi_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaZ_pipluscand",TrackBCAL_DeltaZ_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackFCAL_DOCA_pipluscand",TrackFCAL_DOCA_pipluscand, j);
    dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_piplus",locDeltaTOF_piplus, j);
    dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_piplus",locDeltaBCAL_piplus, j);
     
    //============ Proton Hypothesis 0 ===========================================================//
    const DChargedTrackHypothesis *hyp_proton0   = thisHyp[Proton][0];
    const DTrackTimeBased *proton0_track = hyp_proton0->Get_TrackTimeBased();	    
    
   double FOM_prot0cand = hyp_proton0->Get_FOM();
   double NDF_prot0cand = hyp_proton0->Get_NDF();
   double ChiSq_prot0cand = hyp_proton0->Get_ChiSq();
   double prot0cand_dedx_dc_NDF  = hyp_proton0->Get_NDF_DCdEdx();
   double prot0cand_dedx_dc_ChiSq  = hyp_proton0->Get_ChiSq_DCdEdx();
   double Beta_Timing_prot0cand = hyp_proton0->measuredBeta();
   double NDF_Timing_prot0cand   = hyp_proton0->Get_NDF_Timing();
   double ChiSq_Timing_prot0cand = hyp_proton0->Get_ChiSq_Timing();
   double dEdx_TOF_prot0cand = (hyp_proton0->Get_TOFHitMatchParams() != NULL) ? hyp_proton0->Get_TOFHitMatchParams()->dEdx : 0.0;
   double dEdx_ST_prot0cand  = (hyp_proton0->Get_SCHitMatchParams()  != NULL) ? hyp_proton0->Get_SCHitMatchParams()->dEdx : 0.0;
   double dEdx_CDC_prot0cand      = (hyp_proton0->Get_TrackTimeBased() != NULL) ? hyp_proton0->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
   double dEdx_FDC_prot0cand      = (hyp_proton0->Get_TrackTimeBased() != NULL) ? hyp_proton0->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
   const DBCALShower* showerproton0 = NULL;
   if (hyp_proton0->Get_BCALShowerMatchParams() != NULL) showerproton0 = hyp_proton0->Get_BCALShowerMatchParams()->dBCALShower;
   double Energy_BCAL_prot0cand  = (showerproton0 != NULL ) ? showerproton0->E : 0.0;
   double Energy_BCALPreshower_prot0cand  = (showerproton0 != NULL ) ? showerproton0->E_preshower : 0.0;
   double SigLong_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->sigLong : 0.0;
   double SigTheta_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->sigTheta : 0.0;
   double SigTrans_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->sigTrans : 0.0;
   double RMSTime_BCAL_prot0cand  = (showerproton0 != NULL ) ? showerproton0->rmsTime : 0.0;
   double E_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->E : 0.0;
   double x_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->x : 0.0;
   double y_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->y : 0.0;
   double z_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->z : 0.0;
   double t_BCAL_prot0cand = (showerproton0 != NULL ) ? showerproton0->t : 0.0;

   const DFCALShower* FCALshowerproton0 = NULL;
   if (hyp_proton0->Get_FCALShowerMatchParams() != NULL) FCALshowerproton0 = hyp_proton0->Get_FCALShowerMatchParams()->dFCALShower;
   double Energy_FCAL_prot0cand = (FCALshowerproton0 != NULL) ? FCALshowerproton0->getEnergy() : 0.0;
   double E1E9_FCAL_prot0cand = (FCALshowerproton0 != NULL) ? FCALshowerproton0->getE1E9() : 0.0;
   double E9E25_FCAL_prot0cand = (FCALshowerproton0 != NULL) ? FCALshowerproton0->getE9E25() : 0.0;
   double SumU_FCAL_prot0cand = (FCALshowerproton0 != NULL) ? FCALshowerproton0->getSumU() : 0.0;
   double SumV_FCAL_prot0cand = (FCALshowerproton0 != NULL) ? FCALshowerproton0->getSumV() : 0.0;

   double locStartTime_prot0cand          = locParticleID->Calc_PropagatedRFTime(hyp_proton0, locEventRFBunch);
   auto  locTOFHitMatchParams_prot0cand   = hyp_proton0->Get_TOFHitMatchParams();
   double locDeltaTOF_prot0cand = ( locTOFHitMatchParams_prot0cand != NULL ) ? locTOFHitMatchParams_prot0cand->dHitTime - locTOFHitMatchParams_prot0cand->dFlightTime - locStartTime_prot0cand : 999.0;

   auto locBCALShowerMatchParams_prot0cand    = hyp_proton0->Get_BCALShowerMatchParams();
   double locDeltaBCAL_prot0cand = 999.0;
   if(locBCALShowerMatchParams_prot0cand != NULL){
	const DBCALShower* locBCALShower_prot0cand = locBCALShowerMatchParams_prot0cand->dBCALShower;
        locDeltaBCAL_prot0cand = locBCALShower_prot0cand->t - locBCALShowerMatchParams_prot0cand->dFlightTime - locStartTime_prot0cand;
   }
   dTreeFillData.Fill_Array<Double_t>("FOM_prot0cand",FOM_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_prot0cand",NDF_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_prot0cand",ChiSq_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("prot0cand_dedx_dc_NDF",prot0cand_dedx_dc_NDF, j);
   dTreeFillData.Fill_Array<Double_t>("prot0cand_dedx_dc_ChiSq",prot0cand_dedx_dc_ChiSq, j);
   dTreeFillData.Fill_Array<Double_t>("Beta_Timing_prot0cand",Beta_Timing_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_Timing_prot0cand",NDF_Timing_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_prot0cand",ChiSq_Timing_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_prot0cand",dEdx_TOF_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_ST_prot0cand",dEdx_ST_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_prot0cand",dEdx_CDC_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_prot0cand",dEdx_FDC_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_prot0cand",Energy_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_prot0cand",Energy_BCALPreshower_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_prot0cand",SigLong_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_prot0cand",SigTheta_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_prot0cand",SigTrans_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_prot0cand",RMSTime_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("E_BCAL_prot0cand",E_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("x_BCAL_prot0cand",x_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("y_BCAL_prot0cand",y_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("z_BCAL_prot0cand",z_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("t_BCAL_prot0cand",t_BCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_prot0cand",Energy_FCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_prot0cand",E1E9_FCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_prot0cand",E9E25_FCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_prot0cand",SumU_FCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_prot0cand",SumV_FCAL_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_prot0cand",locDeltaTOF_prot0cand, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_prot0cand",locDeltaBCAL_prot0cand, j);

   //============ Proton Hypothesis 1 ===========================================================//
   const DChargedTrackHypothesis *hyp_proton1   = thisHyp[Proton][1];
   const DTrackTimeBased *proton1_track = hyp_proton1->Get_TrackTimeBased();	    
    
   double FOM_prot1cand = hyp_proton1->Get_FOM();
   double NDF_prot1cand = hyp_proton1->Get_NDF();
   double ChiSq_prot1cand = hyp_proton1->Get_ChiSq();
   double prot1cand_dedx_dc_NDF  = hyp_proton1->Get_NDF_DCdEdx();
   double prot1cand_dedx_dc_ChiSq  = hyp_proton1->Get_ChiSq_DCdEdx();
   double Beta_Timing_prot1cand = hyp_proton1->measuredBeta();
   double NDF_Timing_prot1cand   = hyp_proton1->Get_NDF_Timing();
   double ChiSq_Timing_prot1cand= hyp_proton1->Get_ChiSq_Timing();
   double dEdx_TOF_prot1cand = (hyp_proton1->Get_TOFHitMatchParams() != NULL) ? hyp_proton1->Get_TOFHitMatchParams()->dEdx : 0.0;
   double dEdx_ST_prot1cand  = (hyp_proton1->Get_SCHitMatchParams()  != NULL) ? hyp_proton1->Get_SCHitMatchParams()->dEdx : 0.0;
   double dEdx_CDC_prot1cand      = (hyp_proton1->Get_TrackTimeBased() != NULL) ? hyp_proton1->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
   double dEdx_FDC_prot1cand      = (hyp_proton1->Get_TrackTimeBased() != NULL) ? hyp_proton1->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
   const DBCALShower* showerproton1 = NULL;
   if (hyp_proton1->Get_BCALShowerMatchParams() != NULL) showerproton1 = hyp_proton1->Get_BCALShowerMatchParams()->dBCALShower;
   double Energy_BCAL_prot1cand  = (showerproton1 != NULL ) ? showerproton1->E : 0.0;
   double Energy_BCALPreshower_prot1cand  = (showerproton1 != NULL ) ? showerproton1->E_preshower : 0.0;
   double SigLong_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->sigLong : 0.0;
   double SigTheta_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->sigTheta : 0.0;
   double SigTrans_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->sigTrans : 0.0;
   double RMSTime_BCAL_prot1cand  = (showerproton1 != NULL ) ? showerproton1->rmsTime : 0.0;
   double E_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->E : 0.0;
   double x_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->x : 0.0;
   double y_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->y : 0.0;
   double z_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->z : 0.0;
   double t_BCAL_prot1cand = (showerproton1 != NULL ) ? showerproton1->t : 0.0;

   const DFCALShower* FCALshowerproton1 = NULL;
   if (hyp_proton1->Get_FCALShowerMatchParams() != NULL) FCALshowerproton1 = hyp_proton1->Get_FCALShowerMatchParams()->dFCALShower;
   double Energy_FCAL_prot1cand = (FCALshowerproton1 != NULL) ? FCALshowerproton1->getEnergy() : 0.0;
   double E1E9_FCAL_prot1cand = (FCALshowerproton1 != NULL) ? FCALshowerproton1->getE1E9() : 0.0;
   double E9E25_FCAL_prot1cand = (FCALshowerproton1 != NULL) ? FCALshowerproton1->getE9E25() : 0.0;
   double SumU_FCAL_prot1cand = (FCALshowerproton1 != NULL) ? FCALshowerproton1->getSumU() : 0.0;
   double SumV_FCAL_prot1cand = (FCALshowerproton1 != NULL) ? FCALshowerproton1->getSumV() : 0.0;

   double locStartTime_prot1cand          = locParticleID->Calc_PropagatedRFTime(hyp_proton1, locEventRFBunch);
   auto  locTOFHitMatchParams_prot1cand   = hyp_proton1->Get_TOFHitMatchParams();
   double locDeltaTOF_prot1cand = ( locTOFHitMatchParams_prot1cand != NULL ) ? locTOFHitMatchParams_prot1cand->dHitTime - locTOFHitMatchParams_prot1cand->dFlightTime - locStartTime_prot1cand : 999.0;

   auto locBCALShowerMatchParams_prot1cand    = hyp_proton1->Get_BCALShowerMatchParams();
   double locDeltaBCAL_prot1cand = 999.0;
   if(locBCALShowerMatchParams_prot1cand != NULL){
	const DBCALShower* locBCALShower_prot1cand = locBCALShowerMatchParams_prot1cand->dBCALShower;
        locDeltaBCAL_prot1cand = locBCALShower_prot1cand->t - locBCALShowerMatchParams_prot1cand->dFlightTime - locStartTime_prot1cand;
   }
   dTreeFillData.Fill_Array<Double_t>("FOM_prot1cand",FOM_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_prot1cand",NDF_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_prot1cand",ChiSq_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("prot1cand_dedx_dc_NDF",prot1cand_dedx_dc_NDF, j);
   dTreeFillData.Fill_Array<Double_t>("prot1cand_dedx_dc_ChiSq",prot1cand_dedx_dc_ChiSq, j);
   dTreeFillData.Fill_Array<Double_t>("Beta_Timing_prot1cand",Beta_Timing_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_Timing_prot1cand",NDF_Timing_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_prot1cand",ChiSq_Timing_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_prot1cand",dEdx_TOF_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_ST_prot1cand",dEdx_ST_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_prot1cand",dEdx_CDC_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_prot1cand",dEdx_FDC_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_prot1cand",Energy_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_prot1cand",Energy_BCALPreshower_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_prot1cand",SigLong_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_prot1cand",SigTheta_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_prot1cand",SigTrans_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_prot1cand",RMSTime_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("E_BCAL_prot1cand",E_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("x_BCAL_prot1cand",x_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("y_BCAL_prot1cand",y_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("z_BCAL_prot1cand",z_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("t_BCAL_prot1cand",t_BCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_prot1cand",Energy_FCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_prot1cand",E1E9_FCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_prot1cand",E9E25_FCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_prot1cand",SumU_FCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_prot1cand",SumV_FCAL_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_prot1cand",locDeltaTOF_prot1cand, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_prot1cand",locDeltaBCAL_prot1cand, j);
   
   
   vector<const DTrackTimeBased*> locTrackTimeBasedVectorForVertexing;
   locTrackTimeBasedVectorForVertexing.push_back(pi_min_track);
   locTrackTimeBasedVectorForVertexing.push_back(pi_plus_track);
   locTrackTimeBasedVectorForVertexing.push_back(proton0_track);
   locTrackTimeBasedVectorForVertexing.push_back(proton1_track);
   DVector3 locRoughPosition = dAnalysisUtilities->Calc_CrudeVertex(locTrackTimeBasedVectorForVertexing);
   TVector3 locTRoughPosition(locRoughPosition.X(), locRoughPosition.Y(), locRoughPosition.Z());
   
   
   //--------------------------------
   // Kinematic fit
   //--------------------------------
   dKinFitter->Reset_NewFit();
   set<shared_ptr<DKinFitParticle>> FinalParticles, NoParticles;
   
   shared_ptr<DKinFitParticle>myProton0=dKinFitUtils->Make_DetectedParticle(proton0_track);
   shared_ptr<DKinFitParticle>myProton1=dKinFitUtils->Make_DetectedParticle(proton1_track);
   shared_ptr<DKinFitParticle>myPiMinus=dKinFitUtils->Make_DetectedParticle(pi_min_track);
   shared_ptr<DKinFitParticle>myPiPlus=dKinFitUtils->Make_DetectedParticle(pi_plus_track);
   
   FinalParticles.insert(myProton0);
   FinalParticles.insert(myProton1);
   FinalParticles.insert(myPiMinus);
   FinalParticles.insert(myPiPlus);
   
   //  Production Vertex constraint
   set<shared_ptr<DKinFitParticle>> locFullConstrainParticles;
   locFullConstrainParticles.insert(myPiPlus);
   locFullConstrainParticles.insert(myPiMinus);
   locFullConstrainParticles.insert(myProton0);
   locFullConstrainParticles.insert(myProton1);
   
   //shared_ptr<DKinFitConstraint_Vertex> locProductionVertexConstraint =  dKinFitUtils->Make_VertexConstraint(locFullConstrainParticles, NoParticles, proton_track->position());
   // maybe use a better vertex guess
   shared_ptr<DKinFitConstraint_Vertex> locProductionVertexConstraint =  dKinFitUtils->Make_VertexConstraint(locFullConstrainParticles, NoParticles, locTRoughPosition);
   
   dKinFitter->Add_Constraint(locProductionVertexConstraint);
   
   // PERFORM THE KINEMATIC FIT
   bool locFitStatus = dKinFitter->Fit_Reaction();
   if(!locFitStatus) continue;
   
   //GET THE FIT RESULTS
   double _CL = dKinFitter->Get_ConfidenceLevel();
   
   if (_CL>0){
     
     TVector3 vertex_kf;
     set<shared_ptr<DKinFitParticle>>myParticles=dKinFitter->Get_KinFitParticles();
     set<shared_ptr<DKinFitParticle>>::iterator locParticleIterator=myParticles.begin();
     
     //============= Fit Values ========================================================
     shared_ptr<DKinFitParticle> fitProton0 = NULL;
     shared_ptr<DKinFitParticle> fitProton1 = NULL;
     shared_ptr<DKinFitParticle> fitPiPlus = NULL;
     shared_ptr<DKinFitParticle> fitPiMinus = NULL;
     
     for(; locParticleIterator != myParticles.end(); ++locParticleIterator){
       if ((*locParticleIterator)->Get_KinFitParticleType()==d_DetectedParticle) {
	 vertex_kf=(*locParticleIterator)->Get_Position();
	 dTreeFillData.Fill_Array<Double_t>("T_vertex",  (*locParticleIterator)->Get_Time(),j);
       }
       
       int pid = (*locParticleIterator)->Get_PID();
       
       switch (pid){
       case 2212:
	 if (fitProton0 == NULL)
	   {
	     fitProton0 = (*locParticleIterator);
	   }
	 else
	   {
	     fitProton1 = (*locParticleIterator);
	   }
	 break;
       case 211:
	 fitPiPlus = (*locParticleIterator);
	 break;
       case -211:
	 fitPiMinus = (*locParticleIterator);
	 break;
       default:
	 break;
       }
     }
     
     
     //cout << hex << "0x" << fitProton << "  0x" << fitPiPlus << "  0x" << fitPiMinus << endl;
     
     dTreeFillData.Fill_Array<Double_t>("X_vertex",vertex_kf[0], j);
     dTreeFillData.Fill_Array<Double_t>("Y_vertex",vertex_kf[1], j);
     dTreeFillData.Fill_Array<Double_t>("Z_vertex",vertex_kf[2], j);
     dTreeFillData.Fill_Array<Double_t>("CLKinFit",_CL, j);
     dTreeFillData.Fill_Array<Double_t>("NDF", dKinFitter->Get_NDF(), j);
     dTreeFillData.Fill_Array<Double_t>("ChiSqFit", dKinFitter->Get_ChiSq(), j);
     dTreeFillData.Fill_Array<Double_t>("Common_Time", fitPiPlus->Get_CommonTime(), j);
     
     dTreeFillData.Fill_Array<Double_t>("pX_piminus", fitPiMinus->Get_Momentum().X(),j);
     dTreeFillData.Fill_Array<Double_t>("pY_piminus", fitPiMinus->Get_Momentum().Y(),j);
     dTreeFillData.Fill_Array<Double_t>("pZ_piminus", fitPiMinus->Get_Momentum().Z(),j);
     dTreeFillData.Fill_Array<Double_t>("E_piminus",  fitPiMinus->Get_Energy(),j);
     dTreeFillData.Fill_Array<Double_t>("t_piminus",  fitPiMinus->Get_Time(),j);
     
     dTreeFillData.Fill_Array<Double_t>("pX_piplus", fitPiPlus->Get_Momentum().X(),j);
     dTreeFillData.Fill_Array<Double_t>("pY_piplus", fitPiPlus->Get_Momentum().Y(),j);
     dTreeFillData.Fill_Array<Double_t>("pZ_piplus", fitPiPlus->Get_Momentum().Z(),j);
     dTreeFillData.Fill_Array<Double_t>("E_piplus",  fitPiPlus->Get_Energy(),j);
     dTreeFillData.Fill_Array<Double_t>("t_piplus",  fitPiPlus->Get_Time(),j);

     dTreeFillData.Fill_Array<Double_t>("pX_proton0", fitProton0->Get_Momentum().X(),j);
     dTreeFillData.Fill_Array<Double_t>("pY_proton0", fitProton0->Get_Momentum().Y(),j);
     dTreeFillData.Fill_Array<Double_t>("pZ_proton0", fitProton0->Get_Momentum().Z(),j);
     dTreeFillData.Fill_Array<Double_t>("E_proton0",  fitProton0->Get_Energy(),j);
     dTreeFillData.Fill_Array<Double_t>("t_proton0",  fitProton0->Get_Time(),j);

     dTreeFillData.Fill_Array<Double_t>("pX_proton1", fitProton1->Get_Momentum().X(),j);
     dTreeFillData.Fill_Array<Double_t>("pY_proton1", fitProton1->Get_Momentum().Y(),j); 
     dTreeFillData.Fill_Array<Double_t>("pZ_proton1", fitProton1->Get_Momentum().Z(),j);
     dTreeFillData.Fill_Array<Double_t>("E_proton1",  fitProton1->Get_Energy(),j);
     dTreeFillData.Fill_Array<Double_t>("t_proton1",  fitProton1->Get_Time(),j);
     
     dTreeInterface->Fill(dTreeFillData);
     
   }//CL
   
  }// for hyp
  
  UnlockState(); //RELEASE PROCESSOR LOCK
  
  return NOERROR;
  
}

//------------------
jerror_t DEventProcessor_2p2pi::erun(void)
{
	// Any final calculations on histograms (like dividing them)
	// should be done here. This may get called more than once.
	return NOERROR;
}

//------------------
// fini
//------------------

jerror_t DEventProcessor_2p2pi::fini(void)
{
	delete dTreeInterface; //saves trees to file, closes file
	return NOERROR;
}

// Recursive function for determining possible particle assignments

void DEventProcessor_2p2pi::GetHypotheses(vector<const DChargedTrack *> &tracks,
						map<Particle_t, int> &particles,
						map<Particle_t, vector<const DChargedTrackHypothesis*> > &assignmentHypothesis,
						vector<map<Particle_t, vector<const DChargedTrackHypothesis*> > > &hypothesisList
						) const
{

  const DChargedTrack * firstTrack = tracks.front();
  vector<const DChargedTrack *> otherTracks(tracks);
  otherTracks.erase(otherTracks.begin());
  map<Particle_t, int>::iterator partIt;

  for (partIt = particles.begin(); partIt != particles.end(); partIt++){

      if (partIt->second > 0){

	  Particle_t particle = partIt->first;
	  const DChargedTrackHypothesis *hyp=NULL;
	  
	  if ((hyp = firstTrack->Get_Hypothesis(particle)) != NULL){

	      double prob = TMath::Prob(hyp->Get_ChiSq(),hyp->Get_NDF());
	      if (prob < 0) continue; 
		map<Particle_t, vector<const DChargedTrackHypothesis*> > newHypothesis = assignmentHypothesis;
              
		if (assignmentHypothesis.find(particle) == assignmentHypothesis.end()){
			vector<const DChargedTrackHypothesis*> newVector;
			newHypothesis[particle] = newVector;
		}
		
		newHypothesis[particle].push_back(hyp);
	      
		if (otherTracks.empty()){
			hypothesisList.push_back(newHypothesis);
		} else {
			map<Particle_t, int> otherParticles(particles);
			otherParticles[particle]--;
			GetHypotheses(otherTracks, otherParticles, newHypothesis, hypothesisList); 
                }
        }
      }
  }

  return;

} // end GetHypotheses



