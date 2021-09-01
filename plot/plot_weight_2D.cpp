void format_canvas(TCanvas *c) {
  	c->SetFillColor(0);
 	c->SetBorderMode(0);
  	c->SetBorderSize(2);
  	c->SetTickx(1);
  	c->SetTicky(1);
  	c->SetLeftMargin(0.18);
  	c->SetRightMargin(0.05);
  	c->SetTopMargin(0.1);
  	c->SetBottomMargin(0.15);
  	c->SetFrameFillStyle(0);
  	c->SetFrameBorderMode(0);
  	c->SetFrameFillStyle(0);
  	c->SetFrameBorderMode(0);
}
void plot_weight_2D() {
		double p2weight=0.65/0.3;
  	TString fileNames[] = {"new_new_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_1TopNanoAODv6p1_2018.root"};
  	//TString legend[] = {"wrong reco", "non reco", "background", "right reco"};
  	TString xvars = "rapidity_tt";//,"delta_rapidity_gen","rectop_pt","neutrino_pz"};
  	TString yvars = "mass_tt";//,"M_tt_gen"};
  	TString xtitle = "#Deltay_{t#bar{t}}"; //"M_{t#bar{t}} [GeV]","#Deltay_{t#bar{t}}","likelihood","P_{T}(t) [GeV]","P_{z}^{#nu} [GeV]"};
  	TString ytitle = "M_{t#bar{t}} [GeV]";
  	TString title[] = {"reco","gen"};
  	float xlow = -4.0;
  	float ylow = 350.0;
  	float xup = 4.0;
  	float yup = 950.0;
  	int color[] = {2, 1, 226, 4, 6, kOrange + 2, 2, kYellow, 93};
  	int xbins = 20;
  	int ybins = 30;
  	TString cuts1[] = {"tt_efficiency==2||tt_efficiency==4||tt_efficiency==5",
                    "tt_efficiency==1", "tt_efficiency==0", "tt_efficiency==3"};
    TString weight[] ={"weight_kappa10","weight_kappa20","weight_kappa02","weight_kappa22","weight_kappa02","weight_kappa11","weight_kappa22",
    "weight_kappa22","weight_kappa00"};
    TString legend[]={"kappa10","kappa20","kappa02","kappa22","kappa02","kappa11","kappa22"};
  	TString seletName[] = {"wrong_reco", "non_reco", "background", "right_reco"};
   	auto c2 = new TCanvas("c2", "c2", 8, 30, 650, 600); // draw on this canvas
   	format_canvas(c2);
   	c2->Divide(2,2);
    for (int m = 0; m < 4; m++) {   // select: all, right, wrong
    		auto c1 = new TCanvas("c1", "c1", 8, 30, 650, 600); // temporary canvas
	    	TFile *file = TFile::Open(fileNames[0]);
	      TH2F *h0 = new TH2F("h0", "", xbins, xlow, xup,ybins,ylow,yup);
	      
	      TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
	      c1->cd();
	      tree->Draw(yvars+":"+xvars + ">>h0",cuts1[m]);
    		for(int j=0;j<4;j++){
        		TFile *file = TFile::Open(fileNames[0]);
        		TH2F *h1 = new TH2F("h1", "", xbins, xlow, xup,ybins,ylow,yup);
          	TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
          	c1->cd();
          	tree->Draw(yvars+":"+xvars+ ">>h1", "("+cuts1[m]+")"+"*"+weight[j]);
          	h1->Add(h0,-1);
          	h1->Divide(h0);
        		h1->SetLineColor(kBlue);
						h1->SetLineWidth(2);
						h1->SetStats(kFALSE);
						h1->GetXaxis()->SetTitle(xtitle);
						h1->GetYaxis()->SetTitle(ytitle);
						h1->SetTitle(legend[j]);
						h1->GetXaxis()->CenterTitle();
						h1->GetYaxis()->CenterTitle();
						h1->GetXaxis()->SetTitleSize(0.06);
						h1->GetYaxis()->SetTitleSize(0.06);
						h1->GetXaxis()->SetTitleOffset(1.5);
						h1->GetYaxis()->SetTitleOffset(1.6);
						h1->GetXaxis()->SetLabelSize(0.05);
						h1->GetYaxis()->SetLabelSize(0.05);
						h1->GetZaxis()->SetRangeUser(-0.1,0.1);
						c2->cd(j+1);
						h1->Draw("surf2");    		
    		}
	    
	 
	    //gPad->SetBottomMargin(0.2);
					c2->Print( seletName[m]+".png");
	//    c2->Print(title[i] + ".pdf");
	  }
 }
