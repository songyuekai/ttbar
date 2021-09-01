//draw deltay and mtt for reconstructed level and gen level with weight in one graph 
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
void plot_weight1() {
		double p2weight=0.65/0.3;
  	TString fileNames[] = {"new_new_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_1TopNanoAODv6p1_2018.root"};
  	//TString legend[] = {"wrong reco", "non reco", "background", "right reco"};
  	TString xvars[] = {"rapidity_tt", "mass_tt"};
  	TString xvars1[]={"delta_rapidity_gen","M_tt_gen"};
  	TString xtitle[] = {"#Deltay_{t#bar{t}}", "M_{t#bar{t}} [GeV]"};
  	TString title[] = {"detlay", "mtt"};
  	float xlow[] = {-4.0, 330,-4,330,17.0,0.0,-1100.0};
  	float xup[] = {4.0, 2000.0,4,1200,20.0,1000.0,1100.0};
  	int color[] = {3, 1, 226, 4, 6, kOrange + 2, 2, kYellow, 93};
  	int xbins[] = {32, 30,32,30, 60, 50,110};
  	float yup[]={0.06,0.12};
  	float ylow[]={-0.08,-0.16};
  	int ydivisions[]={7,7};
  	float x,y;
  	TString cuts1[] = {"tt_efficiency==2",
                    "tt_efficiency==1", "tt_efficiency==0", "tt_efficiency==3"};
    TString weight[] ={"weight_kappa10","weight_kappa20","weight_kappa02","weight_kappa22","weight_kappa02","weight_kappa11","weight_kappa22",
    "weight_kappa22","weight_kappa00"};
    TString legend[]={"kappa10","kappa20","kappa02","kappa22","kappa02","kappa11","kappa22"};
    TString legend1[]={"kappa10_gen","kappa20_gen","kappa02_gen","kappa22_gen"};
  	TString seletName[] = {"wrong_reco", "non_reco", "background", "right_reco"};
  	
  	for (int i = 0; i < 2; i++) {                         // loop over variables
   	
    	

    	for (int m = 0; m < 4; m++) {   // select: all, right, wrong
    	auto c1 = new TCanvas("c1", "c1", 8, 30, 650, 600); // temporary canvas
    	auto c2 = new TCanvas("c2", "c2", 8, 30, 650, 600); // draw on this canvas
   		format_canvas(c2);
    	TPad *pad1 = new TPad("pad1","This is pad1",0.05,0.32,0.95,0.97);
    	TPad *pad2 = new TPad("pad2","This is pad2",0.05,0.02,0.95,0.32);
    	c2->cd();
    	pad1->Draw();
    	pad2->Draw();
    	pad1->cd();
    	pad1->SetTopMargin(0.3);
    	pad1->SetBottomMargin(0.02);
    	pad1->SetLeftMargin(0.15);

    	pad1->SetTopMargin(0);
    	pad2->cd();
    //	pad2->SetTopMargin(0);
      pad2->SetTopMargin(0.03);
      pad2->SetBottomMargin(0.35);
      pad2->SetLeftMargin(0.15);
    	TFile *file = TFile::Open(fileNames[0]);
      TH1F *h0 = new TH1F("h0", "", xbins[i], xlow[i], xup[i]);
      TH1F *h00 = new TH1F("h00", "", xbins[i], xlow[i], xup[i]);
      TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
      c1->cd();
      tree->Draw(xvars[i] + ">>h0",cuts1[m]);
      tree->Draw(xvars1[i] + ">>h00",cuts1[m]);
     // x=h0->Integral();
      //h0->Scale(1/x);
    	auto leg = new TLegend(.65, .55, .85, .95);
    	leg->SetFillColor(0);
   		leg->SetLineColor(0);
   		leg->SetEntrySeparation(0.3);
    	leg->SetBorderSize(0);
    	leg->SetFillStyle(0);
    	leg->SetTextFont(42);
    	leg->SetTextSize(0.052);
    		for(int j=0;j<4;j++){
        		TFile *file = TFile::Open(fileNames[0]);
        		TH1F *h1 = new TH1F("h1", "", xbins[i], xlow[i], xup[i]);
        		TH1F *h2 = new TH1F("h2", "", xbins[i], xlow[i], xup[i]);
        		TH1F *h3 = new TH1F("h3", "", xbins[i], xlow[i], xup[i]);
        		TH1F *h4 = new TH1F("h4", "", xbins[i], xlow[i], xup[i]);
          	TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
          	c1->cd();
          	tree->Draw(xvars[i] + ">>h1", "("+cuts1[m]+")"+"*"+weight[j]);
          	tree->Draw(xvars[i] + ">>h2", "("+cuts1[m]+")"+"*"+weight[j]);
          	tree->Draw(xvars1[i] + ">>h3", "("+cuts1[m]+")"+"*"+weight[j]);
          	tree->Draw(xvars1[i] + ">>h4", "("+cuts1[m]+")"+"*"+weight[j]);
       			h1->Add(h0,-1);
       			h1->Divide(h0);
       			h3->Add(h00,-1);
       			h3->Divide(h00);
       			h1->SetLineColor(color[j+1]);
        		h1->SetLineWidth(2);
        		h1->SetStats(kFALSE);
        		h1->GetXaxis()->SetTitle(xtitle[i]);
        		h1->GetYaxis()->SetTitle("Ratio");
        		h1->SetTitle("");
        		h1->GetXaxis()->CenterTitle();
        		h1->GetYaxis()->CenterTitle();
        		h1->GetYaxis()->SetNdivisions(ydivisions[i]);
        		h1->GetXaxis()->SetTitleSize(0.15);
       			h1->GetYaxis()->SetTitleSize(0.06*p2weight);
        		h1->GetXaxis()->SetTitleOffset(0.9);
	        	h1->GetYaxis()->SetTitleOffset(1.1/p2weight);
	        	h1->GetXaxis()->SetLabelSize(0.05*p2weight);
	        	h1->GetYaxis()->SetLabelSize(0.05*p2weight);
	        	h1->GetYaxis()->SetRangeUser(ylow[i], yup[i]);
	        	h1->GetXaxis()->SetRangeUser(xlow[i], xup[i]);	    
    				h2->SetLineColor(color[j+1]);
        		h2->SetLineWidth(2);
        		h2->SetStats(kFALSE);
        		h2->GetXaxis()->SetTitle("");
        		h2->GetYaxis()->SetTitle("Events/bin");
        		//h1->GetYaxis()->SetTitle("Normalized");
        		h2->SetTitle("");
        		h2->GetXaxis()->CenterTitle();
        		h2->GetYaxis()->CenterTitle();
        		h2->GetXaxis()->SetTitleSize(0.09);
       			h2->GetYaxis()->SetTitleSize(0.06);
        		h2->GetXaxis()->SetTitleOffset(0.9);
	        	h2->GetYaxis()->SetTitleOffset(1.1);
	        	h2->GetXaxis()->SetLabelSize(0.0);
	        	h2->GetYaxis()->SetLabelSize(0.05);
	        	h2->GetYaxis()->SetRangeUser(0, h2->GetMaximum()*1.3);
	        	h2->GetXaxis()->SetRangeUser(xlow[i], xup[i]);
	        	h3->SetLineColor(color[j+1]);
	        	h3->SetLineStyle(2);
        		h3->SetLineWidth(2);
        		h3->SetStats(kFALSE);      
	        	h4->SetLineColor(color[j+1]);
        		h4->SetLineWidth(2);
        		h4->SetStats(kFALSE);
        		h4->SetLineStyle(2);
						pad2->cd();
	        	if (j < 1) {
	          		h1->Draw("hist");
						} else
	          		h1->Draw("histsame");
	          h3->Draw("histsame");
	          pad1->cd();
	       		
	        	if (j < 1) {
	          		h2->Draw("hist");
				} else
	          		h2->Draw("histsame");
	          h4->Draw("histsame");
	        	TLegendEntry *leg_entry0 = leg->AddEntry(h2, legend[j]);
	        	TLegendEntry *leg_entry1 = leg->AddEntry(h4, legend1[j]);
	        	leg_entry0->SetTextColor(color[j+1]);
	        	leg_entry1->SetTextColor(color[j+1]);
      		
    	}
	    pad1->cd();
	    leg->Draw("same");
	    pad2->cd();
	    c2->Print(title[i] + seletName[m]+".png");
	//    c2->Print(title[i] + ".pdf");
	  }
  	}
  	
}
