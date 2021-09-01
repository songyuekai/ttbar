//plot some distributions for signal in stack graphs 
void format_canvas(TCanvas *c) {
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(2);
  c->SetTickx(1);
  c->SetTicky(1);
  c->SetLeftMargin(0.18);
  c->SetRightMargin(0.05);
  c->SetTopMargin(0.03);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
}
void plot1() {
  TString fileNames[] = {"new_p_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_"
                         "1TopNanoAODv6p1_2018.root"}; // first is ttsemi
  TString legend1[] = {"wrong reco", "non reco", "background", "right reco"};
  TString legend2[] = {};
  TString xvars[] = {"rapidity_tt", "mass_tt", "likelihood", "rectop_pt",
                     "neutrino_pz"};
  TString xtitle[] = {"#Deltay_{t#bar{t}}", "M_{t#bar{t}} [GeV]", "likelihood",
                      "P_{T}(t) [GeV]", "P_{z}^{#nu} [GeV]"};
  TString title[] = {"detlay", "mtt", "likelihood", "pt", "neutrino_pz"};
  TString weight1[] = {"1.1","1.0","1.0","1.0"}; // real events of process(files)
  TString weight2[] = {""};
  Float_t nevents, newscale;
  float xlow[] = {-4.0, 0.0, 17.5, 0.0, -1100.0};
  float xup[] = {4.0, 1400.0, 21.0, 1000.0, 1100.0};
  int color1[] = {2, 1, 4, 226, 6, kOrange + 2, 3, kYellow, 93};
  int color2[] = {};
  int xbins[] = {40, 70, 35, 50, 110};
  TString cuts[] = {"tt_efficiency==2||tt_efficiency==4||tt_efficiency==5",
                    "tt_efficiency==1", "tt_efficiency==0", "tt_efficiency==3"};
  //	TString seletName[] = {"wrong_reco", "non_reco", "background",
  //"right_reco"};
  for (int i = 0; i < 5; i++) {                         // loop over variables
    auto c1 = new TCanvas("c1", "c1", 8, 30, 600, 600); // temporary canvas
    auto c2 = new TCanvas("c2", "c2", 8, 30, 600, 650); // draw on this canvas
    format_canvas(c2);
    THStack *hstack = new THStack("hstack", "");
    c2->cd();
    TLegend *leg = new TLegend(0.2, .80, .35, .95);
    leg->SetNColumns(1);
    leg->SetColumnSeparation(0.5);
    leg->SetEntrySeparation(0.0);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.025);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    for (int k = 0; k < 1; k++) { // loop over files
      if (k == 0) {
        for (int m = 0; m < 4; m++) { // select: all, right, wrong
          TFile *file = TFile::Open(fileNames[k]);
          TH1F *h1 = new TH1F("h1", "", xbins[i], xlow[i], xup[i]);
          TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
          c1->cd();
          tree->Draw(xvars[i] + ">>h1", weight1[m] + "*" + cuts[m]);
          h1->SetFillColor(color1[m]);
          hstack->Add(h1);
          c2->cd();
          TLegendEntry *leg_entry0 =leg->AddEntry(h1, legend1[m], "f");
          //leg_entry0
        }
      } else {
        TFile *file = TFile::Open(fileNames[k]);
        TH1F *h1 = new TH1F("h1", "", xbins[i], xlow[i], xup[i]);
        TTree *tree = (TTree *)file->Get("mytree"); // draw from tree
        c1->cd();
        tree->Draw(xvars[i] + ">>h1", weight2[k - 1]);
        h1->SetFillColor(color2[k - 1]);
        hstack->Add(h1);
        c2->cd();
        leg->AddEntry(h1, legend2[k - 1], "f");
      }
    }
    c2->cd();
    hstack->Draw("hist");
    hstack->GetXaxis()->SetNdivisions(505);
    hstack->GetXaxis()->SetLabelFont(42);
    hstack->GetXaxis()->SetLabelOffset(0.007);
    hstack->GetXaxis()->SetLabelSize(0.04);
    hstack->GetXaxis()->SetTitleSize(0.06);
    hstack->GetXaxis()->SetTitleOffset(0.9);
    hstack->GetXaxis()->SetTitleFont(42);

    hstack->GetYaxis()->SetNdivisions(505);
    hstack->GetYaxis()->SetLabelFont(42);
    hstack->GetYaxis()->SetLabelOffset(0.007);
    hstack->GetYaxis()->SetLabelSize(0.04);
    hstack->GetYaxis()->SetTitleSize(0.04);
    hstack->GetYaxis()->SetTitleOffset(1.9);
    hstack->GetYaxis()->SetTitleFont(42);

    hstack->GetXaxis()->CenterTitle();
    hstack->GetYaxis()->CenterTitle();
    hstack->GetXaxis()->SetTitle(xtitle[i]);
    hstack->GetYaxis()->SetTitle("Events/bin");
    hstack->SetMaximum(hstack->GetMaximum() * 1.5);
    c2->cd();
    leg->Draw("same");
    //c2->SetLogy();
    c2->Print(title[i] + "1.png");
  }

  //    c2->Print(title[i] + ".pdf");
}
