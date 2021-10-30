 #contour2D(TString datafile,TString xvar, int xbins, float xmin, float xmax, TString yvar, int ybins, float ymin, 
 #float ymax, float smx=1.0, float smy=1.0, TString name="contour2D",TString xtitle="#mu_{ggH,bbH,ttH}", 
 #TString ytitle="#mu_{VBF,VH}",TFile *fOut=0 )

root -l -q -b contour2D.cxx"(\"limit_ttbar_4jets_2Dyk.root\",\"y\",60,-2.0,2.0,\"k\",60,-2.0,2.0001,0.,0.,\"scan2D_yk_4jets\",\"C_{#varphiu}\",\"Im(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_4jets_2Dyz.root\",\"y\",60,-2.0,2.0,\"z\",60,-1.0,3.0001,0.,0.,\"scan2D_yz_4jets\",\"C_{#varphiu}\",\"Re(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_4jets_2Dzk.root\",\"z\",60,-1.0,3.0,\"k\",60,-2.0,2.0001,0.,0.,\"scan2D_zk_4jets\",\"Re(C_{u#varphi})\",\"Im(C_{u#varphi})\")"

root -l -q -b contour2D.cxx"(\"limit_ttbar_3jets_2Dyk.root\",\"y\",60,-2.5,2.5,\"k\",60,-2.5,2.5001,0.,0.,\"scan2D_yk_3jets\",\"C_{#varphiu}\",\"Im(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_3jets_2Dyz.root\",\"y\",60,-2.5,2.5,\"z\",60,-1.0,3.0001,0.,0.,\"scan2D_yz_3jets\",\"C_{#varphiu}\",\"Re(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_3jets_2Dzk.root\",\"z\",60,-1.0,3.0,\"k\",60,-2.5,2.5001,0.,0.,\"scan2D_zk_3jets\",\"Re(C_{u#varphi})\",\"Im(C_{u#varphi})\")"

root -l -q -b contour2D.cxx"(\"limit_ttbar_semi_2Dyk.root\",\"y\",60,-2.0,2.0,\"k\",60,-2.0,2.0001,0.,0.,\"scan2D_yk_semi\",\"C_{#varphiu}\",\"Im(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_semi_2Dyz.root\",\"y\",60,-2.0,2.0,\"z\",60,-1.0,3.0001,0.,0.,\"scan2D_yz_semi\",\"C_{#varphiu}\",\"Re(C_{u#varphi})\")"
root -l -q -b contour2D.cxx"(\"limit_ttbar_semi_2Dzk.root\",\"z\",60,-1.0,3.0,\"k\",60,-2.0,2.0001,0.,0.,\"scan2D_zk_semi\",\"Re(C_{u#varphi})\",\"Im(C_{u#varphi})\")"

