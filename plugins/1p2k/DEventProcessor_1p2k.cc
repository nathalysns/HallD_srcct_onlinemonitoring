#include <map>
using namespace std;

#include "DEventProcessor_1p2k.h"

#include <DANA/DApplication.h>



// Routine used to create our DEventProcessor
extern "C"{
  void InitPlugin(JApplication *app){
    InitJANAPlugin(app);
    app->AddProcessor(new DEventProcessor_1p2k());
  }
} // "C"

thread_local DTreeFillData DEventProcessor_1p2k::dTreeFillData;

//------------------
// init
///------------------

jerror_t DEventProcessor_1p2k::init(void)
{
  //TTREE INTERFACE
  //MUST DELETE WHEN FINISHED: OR ELSE DATA WON'T BE SAVED!!!
  
  string treeName = "tree_1p2k";
  string treeFile = "tree_1p2k.root";
  gPARMS->SetDefaultParameter("SRC_1P2K:TREENAME", treeName);
  gPARMS->SetDefaultParameter("SRC_1P2K:TREEFILE", treeFile);
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
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("kminus_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("kminus_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaPhi_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaZ_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackFCAL_DOCA_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_kminuscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_kminus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_kminus", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("kplus_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_kpluscand", "nHyp");  
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_kpluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_kpluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_kpluscand", "nHyp"); 
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaPhi_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackBCAL_DeltaZ_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("TrackFCAL_DOCA_kpluscand", "nHyp");         
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("kplus_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_kpluscand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_kplus", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_kplus", "nHyp");

  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pX_proton", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pY_proton", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("pZ_proton", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_proton", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_proton", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("FOM_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot_dedx_dc_NDF", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("prot_dedx_dc_ChiSq", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Beta_Timing_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("NDF_Timing_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("ChiSq_Timing_protcan", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_TOF_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_BCALPreshower_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigLong_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTheta_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("RMSTime_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("x_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("y_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("z_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("t_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("Energy_FCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SigTrans_BCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E1E9_FCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("E9E25_FCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumU_FCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("SumV_FCAL_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_ST_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_CDC_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("dEdx_FDC_protcand", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaTOF_prot", "nHyp");
  locTreeBranchRegister.Register_FundamentalArray<Double_t>("locDeltaBCAL_prot", "nHyp");

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
jerror_t DEventProcessor_1p2k::brun(JEventLoop *eventLoop, int32_t runnumber)
{
  dKinFitUtils = new DKinFitUtils_GlueX(eventLoop);
  dKinFitter = new DKinFitter(dKinFitUtils);

  eventLoop->GetSingle(dAnalysisUtilities);

  return NOERROR;
}

//------------------
// evnt
//------------------

jerror_t DEventProcessor_1p2k::evnt(JEventLoop *loop, uint64_t eventnumber)
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
  if (ch_tracks.size()!=3) return NOERROR;

  map<Particle_t, int> targetParticles = {
	{Proton,1},
        {KPlus,1},
        {KMinus,1}
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

     //============ KMinus Hypothesis ===========================================================//
     const DChargedTrackHypothesis *hyp_k_min   = thisHyp[KMinus][0];
     const DTrackTimeBased *k_min_track = hyp_k_min->Get_TrackTimeBased();            	    
     double FOM_kminuscand          = hyp_k_min->Get_FOM();
     double NDF_kminuscand          = hyp_k_min->Get_NDF();
     double ChiSq_kminuscand        = hyp_k_min->Get_ChiSq();
     double kminus_dedx_dc_NDF      = hyp_k_min->Get_NDF_DCdEdx();
     double kminus_dedx_dc_ChiSq    = hyp_k_min->Get_ChiSq_DCdEdx();
     double Beta_Timing_kminuscand  = hyp_k_min->measuredBeta();
     double NDF_Timing_kminuscand   = hyp_k_min->Get_NDF_Timing();
     double ChiSq_Timing_kminuscand = hyp_k_min->Get_ChiSq_Timing();
     double dEdx_TOF_kminuscand     = (hyp_k_min->Get_TOFHitMatchParams() != NULL) ? hyp_k_min->Get_TOFHitMatchParams()->dEdx : 0.0;
     double dEdx_ST_kminuscand      = (hyp_k_min->Get_SCHitMatchParams()  != NULL) ? hyp_k_min->Get_SCHitMatchParams()->dEdx : 0.0;
     double dEdx_CDC_kminuscand      = (hyp_k_min->Get_TrackTimeBased() != NULL) ? hyp_k_min->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
     double dEdx_FDC_kminuscand      = (hyp_k_min->Get_TrackTimeBased() != NULL) ? hyp_k_min->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
     const DBCALShower* showerkminus = NULL;
     if (hyp_k_min->Get_BCALShowerMatchParams() != NULL) showerkminus = hyp_k_min->Get_BCALShowerMatchParams()->dBCALShower;
     double Energy_BCAL_kminuscand  = (showerkminus != NULL ) ? showerkminus->E : 0.0;
     double Energy_BCALPreshower_kminuscand  = (showerkminus != NULL ) ? showerkminus->E_preshower : 0.0;
     double SigLong_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->sigLong : 0.0;
     double SigTheta_BCAL_kminuscand= (showerkminus != NULL ) ? showerkminus->sigTheta : 0.0;
     double SigTrans_BCAL_kminuscand= (showerkminus != NULL ) ? showerkminus->sigTrans : 0.0;
     double RMSTime_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->rmsTime : 0.0;
     double E_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->E : 0.0;
     double x_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->x : 0.0;
     double y_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->y : 0.0;
     double z_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->z : 0.0;
     double t_BCAL_kminuscand = (showerkminus != NULL ) ? showerkminus->t : 0.0;

     const DFCALShower* FCALshowerkminus = NULL;
     if (hyp_k_min->Get_FCALShowerMatchParams() != NULL) FCALshowerkminus = hyp_k_min->Get_FCALShowerMatchParams()->dFCALShower;
     double Energy_FCAL_kminuscand = (FCALshowerkminus != NULL) ? FCALshowerkminus->getEnergy() : 0.0;
     double E1E9_FCAL_kminuscand   = (FCALshowerkminus != NULL) ? FCALshowerkminus->getE1E9() : 0.0;
     double E9E25_FCAL_kminuscand  = (FCALshowerkminus != NULL) ? FCALshowerkminus->getE9E25() : 0.0;
     double SumU_FCAL_kminuscand   = (FCALshowerkminus != NULL) ? FCALshowerkminus->getSumU() : 0.0;
     double SumV_FCAL_kminuscand   = (FCALshowerkminus != NULL) ? FCALshowerkminus->getSumV() : 0.0;

     double TrackBCAL_DeltaPhi_kminuscand = ( hyp_k_min->Get_BCALShowerMatchParams()  != NULL) ? hyp_k_min->Get_BCALShowerMatchParams()->dDeltaPhiToShower : 999.0;
     double TrackBCAL_DeltaZ_kminuscand   = ( hyp_k_min->Get_BCALShowerMatchParams()  != NULL) ? hyp_k_min->Get_BCALShowerMatchParams()->dDeltaZToShower : 999.0;
     double TrackFCAL_DOCA_kminuscand     = ( hyp_k_min->Get_FCALShowerMatchParams()  != NULL) ? hyp_k_min->Get_FCALShowerMatchParams()->dDOCAToShower : 999.0;  

     double locStartTime_kminus         = locParticleID->Calc_PropagatedRFTime(hyp_k_min, locEventRFBunch);
     auto  locTOFHitMatchParams_kminus = hyp_k_min->Get_TOFHitMatchParams();     
     double locDeltaTOF_kminus = ( locTOFHitMatchParams_kminus != NULL ) ? locTOFHitMatchParams_kminus->dHitTime - locTOFHitMatchParams_kminus->dFlightTime - locStartTime_kminus : 999.0;  

     auto locBCALShowerMatchParams_kminus    = hyp_k_min->Get_BCALShowerMatchParams();
    double locDeltaBCAL_kminus = 999.0;
    if(locBCALShowerMatchParams_kminus != NULL){
        const DBCALShower* locBCALShower_kminus = locBCALShowerMatchParams_kminus->dBCALShower;
        locDeltaBCAL_kminus = locBCALShower_kminus->t - locBCALShowerMatchParams_kminus->dFlightTime - locStartTime_kminus;
    }

     dTreeFillData.Fill_Array<Double_t>("FOM_kminuscand",FOM_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("NDF_kminuscand",NDF_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_kminuscand",ChiSq_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("kminus_dedx_dc_NDF",kminus_dedx_dc_NDF, j);
     dTreeFillData.Fill_Array<Double_t>("kminus_dedx_dc_ChiSq",kminus_dedx_dc_ChiSq, j);
     dTreeFillData.Fill_Array<Double_t>("Beta_Timing_kminuscand",Beta_Timing_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("NDF_Timing_kminuscand",NDF_Timing_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_kminuscand",ChiSq_Timing_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_kminuscand",ChiSq_Timing_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_kminuscand",dEdx_TOF_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_ST_kminuscand",dEdx_ST_kminuscand, j);	
     dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_kminuscand",dEdx_CDC_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_kminuscand",dEdx_FDC_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_kminuscand",Energy_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_kminuscand",Energy_BCALPreshower_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_kminuscand",SigLong_BCAL_kminuscand, j); 
     dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_kminuscand",SigTheta_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_kminuscand",SigTrans_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_kminuscand",RMSTime_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E_BCAL_kminuscand",E_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("x_BCAL_kminuscand",x_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("y_BCAL_kminuscand",y_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("z_BCAL_kminuscand",z_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("t_BCAL_kminuscand",t_BCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_kminuscand",Energy_FCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_kminuscand",E1E9_FCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_kminuscand",E9E25_FCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_kminuscand",SumU_FCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_kminuscand",SumV_FCAL_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaPhi_kminuscand",TrackBCAL_DeltaPhi_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaZ_kminuscand",TrackBCAL_DeltaZ_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("TrackFCAL_DOCA_kminuscand",TrackFCAL_DOCA_kminuscand, j);
     dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_kminus",locDeltaTOF_kminus, j);
     dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_kminus",locDeltaBCAL_kminus, j);

    //============ KPlus Hypothesis ===========================================================//
    const DChargedTrackHypothesis *hyp_k_plus   = thisHyp[KPlus][0];
    const DTrackTimeBased *k_plus_track = hyp_k_plus->Get_TrackTimeBased();
    double FOM_kpluscand = hyp_k_plus->Get_FOM();
    double NDF_kpluscand = hyp_k_plus->Get_NDF();
    double ChiSq_kpluscand = hyp_k_plus->Get_ChiSq();
    double kplus_dedx_dc_NDF = hyp_k_plus->Get_NDF_DCdEdx();
    double kplus_dedx_dc_ChiSq  = hyp_k_plus->Get_ChiSq_DCdEdx();
    double Beta_Timing_kpluscand = hyp_k_plus->measuredBeta();
    double NDF_Timing_kpluscand   = hyp_k_plus->Get_NDF_Timing();
    double ChiSq_Timing_kpluscand = hyp_k_plus->Get_ChiSq_Timing();
    double dEdx_TOF_kpluscand = (hyp_k_plus->Get_TOFHitMatchParams() != NULL) ? hyp_k_plus->Get_TOFHitMatchParams()->dEdx : 0.0;
    double dEdx_ST_kpluscand  = (hyp_k_plus->Get_SCHitMatchParams()  != NULL) ? hyp_k_plus->Get_SCHitMatchParams()->dEdx : 0.0;
    double dEdx_CDC_kpluscand      = (hyp_k_plus->Get_TrackTimeBased() != NULL) ? hyp_k_plus->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
    double dEdx_FDC_kpluscand      = (hyp_k_plus->Get_TrackTimeBased() != NULL) ? hyp_k_plus->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
    const DBCALShower* showerkplus = NULL;
    if (hyp_k_plus->Get_BCALShowerMatchParams() != NULL) showerkplus = hyp_k_plus->Get_BCALShowerMatchParams()->dBCALShower;
    double Energy_BCAL_kpluscand  = (showerkplus != NULL ) ? showerkplus->E : 0.0;
    double Energy_BCALPreshower_kpluscand  = (showerkplus != NULL ) ? showerkplus->E_preshower : 0.0;
    double SigLong_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->sigLong : 0.0;
    double SigTheta_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->sigTheta : 0.0;
    double SigTrans_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->sigTrans : 0.0;
    double RMSTime_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->rmsTime : 0.0;
    double E_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->E : 0.0;
    double x_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->x : 0.0;
    double y_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->y : 0.0;
    double z_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->z : 0.0;
    double t_BCAL_kpluscand = (showerkplus != NULL ) ? showerkplus->t : 0.0;

    const DFCALShower* FCALshowerkplus = NULL;
    if (hyp_k_plus->Get_FCALShowerMatchParams() != NULL) FCALshowerkplus = hyp_k_plus->Get_FCALShowerMatchParams()->dFCALShower;
    double Energy_FCAL_kpluscand = (FCALshowerkplus != NULL) ? FCALshowerkplus->getEnergy() : 0.0;
    double E1E9_FCAL_kpluscand = (FCALshowerkplus != NULL) ? FCALshowerkplus->getE1E9() : 0.0;
    double E9E25_FCAL_kpluscand = (FCALshowerkplus != NULL) ? FCALshowerkplus->getE9E25() : 0.0;
    double SumU_FCAL_kpluscand = (FCALshowerkplus != NULL) ? FCALshowerkplus->getSumU() : 0.0;
    double SumV_FCAL_kpluscand = (FCALshowerkplus != NULL) ? FCALshowerkplus->getSumV() : 0.0;

    double TrackBCAL_DeltaPhi_kpluscand = ( hyp_k_plus->Get_BCALShowerMatchParams()  != NULL) ? hyp_k_plus->Get_BCALShowerMatchParams()->dDeltaPhiToShower : 999.0;
    double TrackBCAL_DeltaZ_kpluscand   = ( hyp_k_plus->Get_BCALShowerMatchParams()  != NULL) ? hyp_k_plus->Get_BCALShowerMatchParams()->dDeltaZToShower : 999.0;
    double TrackFCAL_DOCA_kpluscand     = ( hyp_k_plus->Get_FCALShowerMatchParams()  != NULL) ? hyp_k_plus->Get_FCALShowerMatchParams()->dDOCAToShower : 999.0;
 
     double locStartTime_kplus         = locParticleID->Calc_PropagatedRFTime(hyp_k_plus, locEventRFBunch);
     auto  locTOFHitMatchParams_kplus   = hyp_k_plus->Get_TOFHitMatchParams();
     double locDeltaTOF_kplus = ( locTOFHitMatchParams_kplus != NULL ) ? locTOFHitMatchParams_kplus->dHitTime - locTOFHitMatchParams_kplus->dFlightTime - locStartTime_kplus : 999.0;
     
    auto locBCALShowerMatchParams_kplus    = hyp_k_plus->Get_BCALShowerMatchParams();
    double locDeltaBCAL_kplus = 999.0;
    if(locBCALShowerMatchParams_kplus != NULL){
        const DBCALShower* locBCALShower_kplus = locBCALShowerMatchParams_kplus->dBCALShower;
        locDeltaBCAL_kplus = locBCALShower_kplus->t - locBCALShowerMatchParams_kplus->dFlightTime - locStartTime_kplus;
    }

    dTreeFillData.Fill_Array<Double_t>("FOM_kpluscand",FOM_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("NDF_kpluscand",NDF_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("ChiSq_kpluscand",ChiSq_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("kplus_dedx_dc_NDF",kplus_dedx_dc_NDF, j);
    dTreeFillData.Fill_Array<Double_t>("kplus_dedx_dc_ChiSq",kplus_dedx_dc_ChiSq, j);
    dTreeFillData.Fill_Array<Double_t>("Beta_Timing_kpluscand",Beta_Timing_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("NDF_Timing_kpluscand",NDF_Timing_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_kpluscand",ChiSq_Timing_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_kpluscand",dEdx_TOF_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_ST_kpluscand",dEdx_ST_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_kpluscand",dEdx_CDC_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_kpluscand",dEdx_FDC_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_kpluscand",Energy_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_kpluscand",Energy_BCALPreshower_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_kpluscand",SigLong_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_kpluscand",SigTheta_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_kpluscand",SigTrans_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_kpluscand",RMSTime_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E_BCAL_kpluscand",E_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("x_BCAL_kpluscand",x_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("y_BCAL_kpluscand",y_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("z_BCAL_kpluscand",z_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("t_BCAL_kpluscand",t_BCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_kpluscand",Energy_FCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_kpluscand",E1E9_FCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_kpluscand",E9E25_FCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_kpluscand",SumU_FCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_kpluscand",SumV_FCAL_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaPhi_kpluscand",TrackBCAL_DeltaPhi_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackBCAL_DeltaZ_kpluscand",TrackBCAL_DeltaZ_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("TrackFCAL_DOCA_kpluscand",TrackFCAL_DOCA_kpluscand, j);
    dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_kplus",locDeltaTOF_kplus, j);
    dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_kplus",locDeltaBCAL_kplus, j);
     
    //============ Proton Hypothesis ===========================================================//
    const DChargedTrackHypothesis *hyp_proton   = thisHyp[Proton][0];
    const DTrackTimeBased *proton_track = hyp_proton->Get_TrackTimeBased();	    
    
   double FOM_protcand = hyp_proton->Get_FOM();
   double NDF_protcand = hyp_proton->Get_NDF();
   double ChiSq_protcand = hyp_proton->Get_ChiSq();
   double prot_dedx_dc_NDF  = hyp_proton->Get_NDF_DCdEdx();
   double prot_dedx_dc_ChiSq  = hyp_proton->Get_ChiSq_DCdEdx();
   double Beta_Timing_protcand = hyp_proton->measuredBeta();
   double NDF_Timing_protcand   = hyp_proton->Get_NDF_Timing();
   double ChiSq_Timing_protcan = hyp_proton->Get_ChiSq_Timing();
   double dEdx_TOF_protcand = (hyp_proton->Get_TOFHitMatchParams() != NULL) ? hyp_proton->Get_TOFHitMatchParams()->dEdx : 0.0;
   double dEdx_ST_protcand  = (hyp_proton->Get_SCHitMatchParams()  != NULL) ? hyp_proton->Get_SCHitMatchParams()->dEdx : 0.0;
   double dEdx_CDC_protcand      = (hyp_proton->Get_TrackTimeBased() != NULL) ? hyp_proton->Get_TrackTimeBased()->ddEdx_CDC : 0.0;
   double dEdx_FDC_protcand      = (hyp_proton->Get_TrackTimeBased() != NULL) ? hyp_proton->Get_TrackTimeBased()->ddEdx_FDC : 0.0;
   const DBCALShower* showerproton = NULL;
   if (hyp_proton->Get_BCALShowerMatchParams() != NULL) showerproton = hyp_proton->Get_BCALShowerMatchParams()->dBCALShower;
   double Energy_BCAL_protcand  = (showerproton != NULL ) ? showerproton->E : 0.0;
   double Energy_BCALPreshower_protcand  = (showerproton != NULL ) ? showerproton->E_preshower : 0.0;
   double SigLong_BCAL_protcand = (showerproton != NULL ) ? showerproton->sigLong : 0.0;
   double SigTheta_BCAL_protcand = (showerproton != NULL ) ? showerproton->sigTheta : 0.0;
   double SigTrans_BCAL_protcand = (showerproton != NULL ) ? showerproton->sigTrans : 0.0;
   double RMSTime_BCAL_protcand  = (showerproton != NULL ) ? showerproton->rmsTime : 0.0;
   double E_BCAL_protcand = (showerproton != NULL ) ? showerproton->E : 0.0;
   double x_BCAL_protcand = (showerproton != NULL ) ? showerproton->x : 0.0;
   double y_BCAL_protcand = (showerproton != NULL ) ? showerproton->y : 0.0;
   double z_BCAL_protcand = (showerproton != NULL ) ? showerproton->z : 0.0;
   double t_BCAL_protcand = (showerproton != NULL ) ? showerproton->t : 0.0;

   const DFCALShower* FCALshowerproton = NULL;
   if (hyp_proton->Get_FCALShowerMatchParams() != NULL) FCALshowerproton = hyp_proton->Get_FCALShowerMatchParams()->dFCALShower;
   double Energy_FCAL_protcand = (FCALshowerproton != NULL) ? FCALshowerproton->getEnergy() : 0.0;
   double E1E9_FCAL_protcand = (FCALshowerproton != NULL) ? FCALshowerproton->getE1E9() : 0.0;
   double E9E25_FCAL_protcand = (FCALshowerproton != NULL) ? FCALshowerproton->getE9E25() : 0.0;
   double SumU_FCAL_protcand = (FCALshowerproton != NULL) ? FCALshowerproton->getSumU() : 0.0;
   double SumV_FCAL_protcand = (FCALshowerproton != NULL) ? FCALshowerproton->getSumV() : 0.0;

   double locStartTime_prot          = locParticleID->Calc_PropagatedRFTime(hyp_proton, locEventRFBunch);
   auto  locTOFHitMatchParams_prot   = hyp_proton->Get_TOFHitMatchParams();
   double locDeltaTOF_prot = ( locTOFHitMatchParams_prot != NULL ) ? locTOFHitMatchParams_prot->dHitTime - locTOFHitMatchParams_prot->dFlightTime - locStartTime_prot : 999.0;

   auto locBCALShowerMatchParams_prot    = hyp_proton->Get_BCALShowerMatchParams();
   double locDeltaBCAL_prot = 999.0;
   if(locBCALShowerMatchParams_prot != NULL){
	const DBCALShower* locBCALShower_prot = locBCALShowerMatchParams_prot->dBCALShower;
        locDeltaBCAL_prot = locBCALShower_prot->t - locBCALShowerMatchParams_prot->dFlightTime - locStartTime_prot;
   }
   dTreeFillData.Fill_Array<Double_t>("FOM_protcand",FOM_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_protcand",NDF_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_protcand",ChiSq_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("prot_dedx_dc_NDF",prot_dedx_dc_NDF, j);
   dTreeFillData.Fill_Array<Double_t>("prot_dedx_dc_ChiSq",prot_dedx_dc_ChiSq, j);
   dTreeFillData.Fill_Array<Double_t>("Beta_Timing_protcand",Beta_Timing_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("NDF_Timing_protcand",NDF_Timing_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("ChiSq_Timing_protcan",ChiSq_Timing_protcan, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_TOF_protcand",dEdx_TOF_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_ST_protcand",dEdx_ST_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_CDC_protcand",dEdx_CDC_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("dEdx_FDC_protcand",dEdx_FDC_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCAL_protcand",Energy_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_BCALPreshower_protcand",Energy_BCALPreshower_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("SigLong_BCAL_protcand",SigLong_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTheta_BCAL_protcand",SigTheta_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("SigTrans_BCAL_protcand",SigTrans_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("RMSTime_BCAL_protcand",RMSTime_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("E_BCAL_protcand",E_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("x_BCAL_protcand",x_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("y_BCAL_protcand",y_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("z_BCAL_protcand",z_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("t_BCAL_protcand",t_BCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("Energy_FCAL_protcand",Energy_FCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("E1E9_FCAL_protcand",E1E9_FCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("E9E25_FCAL_protcand",E9E25_FCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("SumU_FCAL_protcand",SumU_FCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("SumV_FCAL_protcand",SumV_FCAL_protcand, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaTOF_prot",locDeltaTOF_prot, j);
   dTreeFillData.Fill_Array<Double_t>("locDeltaBCAL_prot",locDeltaBCAL_prot, j);
 

	 vector<const DTrackTimeBased*> locTrackTimeBasedVectorForVertexing;
	 locTrackTimeBasedVectorForVertexing.push_back(k_min_track);
	 locTrackTimeBasedVectorForVertexing.push_back(k_plus_track);
	 locTrackTimeBasedVectorForVertexing.push_back(proton_track);
	 DVector3 locRoughPosition = dAnalysisUtilities->Calc_CrudeVertex(locTrackTimeBasedVectorForVertexing);
	 TVector3 locTRoughPosition(locRoughPosition.X(), locRoughPosition.Y(), locRoughPosition.Z());


      //--------------------------------
      // Kinematic fit
      //--------------------------------
      dKinFitter->Reset_NewFit();
      set<shared_ptr<DKinFitParticle>> FinalParticles, NoParticles;

      shared_ptr<DKinFitParticle>myProton=dKinFitUtils->Make_DetectedParticle(proton_track);
      shared_ptr<DKinFitParticle>myKMinus=dKinFitUtils->Make_DetectedParticle(k_min_track);
      shared_ptr<DKinFitParticle>myKPlus=dKinFitUtils->Make_DetectedParticle(k_plus_track);

      FinalParticles.insert(myProton);
      FinalParticles.insert(myKMinus);
      FinalParticles.insert(myKPlus);
     
      //  Production Vertex constraint
      set<shared_ptr<DKinFitParticle>> locFullConstrainParticles;
      locFullConstrainParticles.insert(myKPlus);
      locFullConstrainParticles.insert(myKMinus);
      locFullConstrainParticles.insert(myProton);
      
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
		shared_ptr<DKinFitParticle> fitProton = NULL;
		shared_ptr<DKinFitParticle> fitKPlus = NULL;
		shared_ptr<DKinFitParticle> fitKMinus = NULL;

		for(; locParticleIterator != myParticles.end(); ++locParticleIterator){
			 if ((*locParticleIterator)->Get_KinFitParticleType()==d_DetectedParticle) {
				 vertex_kf=(*locParticleIterator)->Get_Position();
				 dTreeFillData.Fill_Array<Double_t>("T_vertex",  (*locParticleIterator)->Get_Time(),j);
			 }

			 int pid = (*locParticleIterator)->Get_PID();

			 switch (pid){
			 case 2212:
				 fitProton = (*locParticleIterator);
				 break;
			 case 321:
				 fitKPlus = (*locParticleIterator);
				 break;
			 case -321:
				 fitKMinus = (*locParticleIterator);
				 break;
			 default:
				 break;
			 }
		}


		 //cout << hex << "0x" << fitProton << "  0x" << fitKPlus << "  0x" << fitKMinus << endl;
	 
		dTreeFillData.Fill_Array<Double_t>("X_vertex",vertex_kf[0], j);
		dTreeFillData.Fill_Array<Double_t>("Y_vertex",vertex_kf[1], j);
		dTreeFillData.Fill_Array<Double_t>("Z_vertex",vertex_kf[2], j);
		dTreeFillData.Fill_Array<Double_t>("CLKinFit",_CL, j);
		dTreeFillData.Fill_Array<Double_t>("NDF", dKinFitter->Get_NDF(), j);
		dTreeFillData.Fill_Array<Double_t>("ChiSqFit", dKinFitter->Get_ChiSq(), j);
		dTreeFillData.Fill_Array<Double_t>("Common_Time", fitKPlus->Get_CommonTime(), j);

		dTreeFillData.Fill_Array<Double_t>("pX_kminus", fitKMinus->Get_Momentum().X(),j);
		dTreeFillData.Fill_Array<Double_t>("pY_kminus", fitKMinus->Get_Momentum().Y(),j);
		dTreeFillData.Fill_Array<Double_t>("pZ_kminus", fitKMinus->Get_Momentum().Z(),j);
		dTreeFillData.Fill_Array<Double_t>("E_kminus",  fitKMinus->Get_Energy(),j);
		dTreeFillData.Fill_Array<Double_t>("t_kminus",  fitKMinus->Get_Time(),j);

		dTreeFillData.Fill_Array<Double_t>("pX_kplus", fitKPlus->Get_Momentum().X(),j);
		dTreeFillData.Fill_Array<Double_t>("pY_kplus", fitKPlus->Get_Momentum().Y(),j);
		dTreeFillData.Fill_Array<Double_t>("pZ_kplus", fitKPlus->Get_Momentum().Z(),j);
		dTreeFillData.Fill_Array<Double_t>("E_kplus",  fitKPlus->Get_Energy(),j);
		dTreeFillData.Fill_Array<Double_t>("t_kplus",  fitKPlus->Get_Time(),j);

		dTreeFillData.Fill_Array<Double_t>("pX_proton", fitProton->Get_Momentum().X(),j);
		dTreeFillData.Fill_Array<Double_t>("pY_proton", fitProton->Get_Momentum().Y(),j); 
		dTreeFillData.Fill_Array<Double_t>("pZ_proton", fitProton->Get_Momentum().Z(),j);
		dTreeFillData.Fill_Array<Double_t>("E_proton",  fitProton->Get_Energy(),j);
		dTreeFillData.Fill_Array<Double_t>("t_proton",  fitProton->Get_Time(),j);

		dTreeInterface->Fill(dTreeFillData);

      }//CL

  }// for hyp

  UnlockState(); //RELEASE PROCESSOR LOCK

  return NOERROR;

}

//------------------
jerror_t DEventProcessor_1p2k::erun(void)
{
	// Any final calculations on histograms (like dividing them)
	// should be done here. This may get called more than once.
	return NOERROR;
}

//------------------
// fini
//------------------

jerror_t DEventProcessor_1p2k::fini(void)
{
	delete dTreeInterface; //saves trees to file, closes file
	return NOERROR;
}

// Recursive function for determining possible particle assignments

void DEventProcessor_1p2k::GetHypotheses(vector<const DChargedTrack *> &tracks,
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



