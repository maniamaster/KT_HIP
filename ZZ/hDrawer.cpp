#define HDRAWER_CPP
//#include "compareDatasets.hpp"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TMath.h"
#include "TCanvas.h"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "TROOT.h"

class event {
	private:
	int m_ientry;
	char* m_filename;
	TFile *file;
	TTree *tree;
	int m_nentries;
	void make4Vectors();
	char* m_datasetname;
	char* m_title;
	
	public:
	event(char* filename, char* title="untitled");
	~event();
	bool GetNextEntry();
	void SetFileName(char* filename);
	string GetFileName();
	void initialize();
	double lep_energy[10];
	double lep_px[10];
	double lep_py[10];
	double lep_pz[10];
	double lep_eta[10];
	double lep_id[10];
	double lep_phi[10];
	double lep_drjet[10];
	double lep_pt[10];
	double lep_etiso[10];
	double etmis;
	double ptmisx;
	double ptmisy;
	double ptmis;
	double sumet;
	double sumetjets;
	int njet;
	int nlep;
	int nphot;
	TLorentzVector lep[10];
	TLorentzVector lep1;
	TLorentzVector lep2;
	TLorentzVector lep3;
	TLorentzVector lep4;
	int GetEntries();
	int GetIentry();
	char* GetDatasetName();
	void SetTitle(char* title);
	char* GetTitle();

};

event::event(char* filename, char* title) 
{
	SetFileName( filename );
	SetTitle( title );
	initialize(); 
	m_ientry = -1;

}
event::~event() {
	if (file) 
	{
	file->Close();
	delete file;
	}
	if (tree) delete tree;
}
void event::SetFileName(char* filename) 
{ 
	m_filename = filename; 
	m_datasetname = filename;
	
}
string event::GetFileName() { return m_filename; }

void event::initialize()
{
	file = new TFile(m_filename);
	tree = (TTree*) file->Get("tree");
	
	tree->SetBranchAddress("lep_energy", lep_energy);
	tree->SetBranchAddress("lep_px", lep_px);
	tree->SetBranchAddress("lep_py", lep_py);
	tree->SetBranchAddress("lep_pz", lep_pz);
	tree->SetBranchAddress("lep_eta", lep_eta);
	tree->SetBranchAddress("lep_id", lep_id);
	tree->SetBranchAddress("lep_phi", lep_phi);
	tree->SetBranchAddress("lep_drjet", lep_drjet);
	tree->SetBranchAddress("lep_pt", lep_pt);
	tree->SetBranchAddress("lep_etiso", &lep_etiso);
	tree->SetBranchAddress("etmis", &etmis);
	tree->SetBranchAddress("ptmisx", &ptmisx);
	tree->SetBranchAddress("ptmisy", &ptmisy);
	tree->SetBranchAddress("sumet", &sumet);
	tree->SetBranchAddress("sumetjets", &sumetjets);
	tree->SetBranchAddress("njet" ,&njet);
	tree->SetBranchAddress("nlep", &nlep);
	tree->SetBranchAddress("nphot", &nphot);
	
	m_nentries = tree->GetEntries();
	//tree->GetEntry(0);

	//cout << "Tree: " << tree << endl;
	//cout << "File: " << file << endl;
}

int event::GetEntries() { return m_nentries; }
int event::GetIentry() { return m_ientry; }

void event::make4Vectors()
{
	//lep.clear();
	for (int i=0; i<nlep; i++)
	{
		TLorentzVector tlvec;
		tlvec.SetPxPyPzE( lep_px[i], lep_py[i], lep_pz[i], lep_energy[i] );
		lep[i] = tlvec;
		//delete tlvec;
	}
	lep1 = lep[0];
	lep2 = lep[1];
	lep3 = lep[2];
	lep4 = lep[3];
	
}

bool event::GetNextEntry() 
{
	if (m_ientry < m_nentries - 1)
	{
		m_ientry++;
		tree->GetEntry(m_ientry);
		make4Vectors();
		return true;
	}
	else return false;
}

char* event::GetDatasetName() { return m_datasetname; }

void event::SetTitle(char* title) { m_title = title; }

char* event::GetTitle() { return m_title; }

// bool next_entry(event *ev1, event *ev2, event *ev3, event *ev4)
// {
// 	bool go_on = ev1->GetNextEntry() || ev2->GetNextEntry() || ev3->GetNextEntry();
// 
// 	return go_on;
// }

// event* ev_initialize(char* filename, char* title="untitled")
// {
// 	event *ev = new event();
// 	ev->SetFileName(filename);
// 	ev->SetTitle( title );
// 	ev->initialize();
// 	
// 	
// 	return ev;	
// }

class hDrawer {
private:
  int m_ihisto;
  int m_ievent;
  vector<TH1D> histos;
  vector<event*> datasets;
  vector<double> prehisto;
  void makeHistogram();
  int man_nbins;
  double man_bin_min;
  double man_bin_max;
  bool manual_binning;
  
public:
  hDrawer();
  ~hDrawer();
  void Add(event* ev);
  void Fill(double var);
  //  void XAxis(string name); 
  void DrawCanvas(const char* name);
  event* GetNextEvent();
  bool go_on;
  void Binning(int nb, double b_min, double b_max);
};


hDrawer::hDrawer() 
{
  m_ihisto = 0;
  m_ievent = 0;
  go_on = true;
  prehisto.clear();
  datasets.clear();
  manual_binning = true;
}
hDrawer::~hDrawer() {
}

void hDrawer::Add(event* ev) {
  datasets.push_back(ev);
}

void hDrawer::Fill(double var) 
{
  if (go_on) prehisto.push_back(var);
}

void hDrawer::DrawCanvas( const char* name) 
{
  TCanvas *canvas = new TCanvas();
  canvas->Divide(2,2);
  
  
  cout <<" Plotting " <<  histos.size() << " histograms..." << endl;
  for (int i=0; i<histos.size(); i++)
    {
      canvas->cd(i+1);
      histos[i].SetTitle( datasets[i]->GetTitle() );
      histos[i].Scale(1./histos[i].Integral());
      histos[i].Draw();
      histos[i].SetLineWidth(2);
      TAxis* xax = histos[i].GetXaxis();
      xax->SetTitle( name ); 
    }
  canvas->cd();
}

void hDrawer::makeHistogram() {
  double min=0, max=0;
  
  for (int i=0; i<prehisto.size(); i++)
    {
      if (i==0)
	{
	  min=prehisto[i];
	  max=prehisto[i];
	}
      if (prehisto[i] < min) min = prehisto[i];
      if (prehisto[i] > max) max = prehisto[i];
    }
  TH1D histo1 = TH1D("temp", "temp", 10000, min, max);
  for (int i=0; i<prehisto.size(); i++)
    {
      histo1.Fill(prehisto[i]);
    }
  int nbins;
  
  if (manual_binning == true) {
    double binsize;
    int nq=2;
    double xq[nq];
    double yq[nq];
    xq[0]=0.25;
    xq[1]=0.75;
    histo1.GetQuantiles(nq, yq, xq);
    //cout << "25% : " << yq[0] << "  75% : " << yq[1] << endl;
    double n = (double) prehisto.size();
    double n13 = pow(n,-0.3333333);
    //cout << "n : " << n << "  n^-1/3 : " << n13 << endl;
    binsize=0.5*(yq[1]-yq[0])*n13;
    
    nbins=TMath::Nint((max-min)/binsize);
    //cout << "binsize : " << binsize << "  nbins : " << nbins << endl;
  }
  else
    {
      nbins = man_nbins;
      min = man_bin_min;
      max = man_bin_max;
    }
  
  TH1D histo2 = TH1D(datasets[m_ievent]->GetDatasetName(), "Title", nbins, min, max);
  for (int i=0; i<prehisto.size(); i++)
    {
      histo2.Fill(prehisto[i]);
    }
  histos.push_back(histo2);
  prehisto.clear();
  
}

event* hDrawer::GetNextEvent() 
{
  if (datasets[m_ievent]->GetNextEntry()) return datasets[m_ievent];
  else
    {
      //cout << "creating histogram" << endl;
      makeHistogram();
      //		go_on = false;
      //		return datasets[m_ievent];
      if (m_ievent < (int) datasets.size()-1 && datasets[m_ievent+1]->GetNextEntry() )
	{
	  //cout << "going to next dataset" << endl;
	  m_ievent++;
	  return datasets[m_ievent];
	}
      else
	{
	  // cout << "finished" << endl;
	  go_on = false;
	  return datasets[m_ievent];
	}
    }
}

void hDrawer::Binning(int nb, double b_min, double b_max)
{
  manual_binning = false;
  man_nbins = nb;
  man_bin_min = b_min;
  man_bin_max = b_max;
}	
