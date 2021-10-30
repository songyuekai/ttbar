//plot some distributions for signal and background in stack graphs 
void format_canvas(TCanvas *c) {
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.18);
  c->SetRightMargin(0.05);
  c->SetTopMargin(0.05);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
}
void plot_QCD() {
    TString fileNames[8] = {

                            "new_QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                    };
    TString xvars[] = {"rapidity_tt", "mass_tt"};
    TString xtitle[] = {"#Deltay_{t#bar{t}}", "M_{t#bar{t}} [GeV]"};
    TString title[] = {"detlay", "mtt"};
    Float_t cross_sections[8]={27990000, 1712000, 347700, 32100, 6831, 1207, 119.9, 25.2};
    float lumi=137.1;           
    //TString weight1[] = {"96.738,","96.738,","96.738,","1.0"}; // real events of process(files)
    //TString weight2[] = {""};
    float xlow[] = {-5.0, 0.0,};
    float xup[] = {5.0, 2000.0};
    int color[] = {2, 1, 4, 226, 6, kOrange + 2, 3, kYellow, 93};
    int xbins[] = {40, 50};
    for(int i=0;i<8;i++)
        fileNames[j]=fileNames[j].ReplaceAll(".root","_*.root");
    for (int i = 0; i < 2; i++) {                         // loop over variables
        auto c1 = new TCanvas("c1", "c1", 8, 30, 600, 600); // temporary canvas
        auto c2 = new TCanvas("c2", "c2", 8, 30, 600, 650); // draw on this canvas
        format_canvas(c2);
        TH1F *h1 = new TH1F("h1", "", xbins[i], xlow[i], xup[i]);
        for(int j=0;j<8;j++){// loop over files
            TChain* tree=new TChain("mytree");
            TChain* tree1=new TChain("rawtree"); 
            tree->Add(fileNames[j]);
            tree1->Add(fileNames[j]);
            TH1F* hist=new TH1F("hist", "", xbins[i], xlow[i], xup[i]);
            float weight1=cross_sections[j]*lumi/(tree1->GetEntries())*1000;
            TString weight=Form("%f",weight1);
            c1->cd();
            tree->Draw(xvars[i] + ">>hist", weight+"*(jet_num>=4)");
            if(j==0)
                h1=hist;
            else
                h1->Add(hist);
        }
        h1->SetLineColor(color[i]);
        h1->SetLineWidth(2);
        h1->SetStats(kFALSE);
        h1->GetXaxis()->SetTitle(xtitle[i]);
        h1->GetYaxis()->SetTitle("Normalized");
        h1->SetTitle("");
        h1->GetXaxis()->CenterTitle();
        h1->GetYaxis()->CenterTitle();
        h1->GetXaxis()->SetTitleSize(0.06);
        h1->GetYaxis()->SetTitleSize(0.06);
        h1->GetXaxis()->SetTitleOffset(0.9);
        h1->GetYaxis()->SetTitleOffset(1.3);
        h1->GetXaxis()->SetLabelSize(0.05);
        h1->GetYaxis()->SetLabelSize(0.05);
        h1->GetXaxis()->SetRangeUser(xlow[i], xup[i]);
        h1->GetYaxis()->SetRangeUser(0., h1->GetMaximum()*1.4);
        c2->cd();
        h1->Draw("hist");
        cout<<h1->GetSumOfWeights()<<endl;
        c2->cd();
        //c2->SetLogy();
        c2->Print(title[i] + "_QCD.pdf");
    }
    //c2->Print(title[i] + ".pdf");
}
