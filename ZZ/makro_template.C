{
	gROOT->Reset();
// Erstellen der TChain

	TChain *chain = new TChain( "tree" );

	// Mit Chain->Add( "FileName" ) koennen weitere ROOT-Files hinzugefuegt werden.
        chain->Add( "ATLASDATA-ZZ-calib.root");

// Definiere Variablen

	// Hier werden die Variablen definiert, die aus dem Ntuple extrahiert werden sollen.
	// Hier am besten nichts anfassen!

	Double_t lep_energy[20], lep_px[20], lep_py[20], lep_pz[20], lep_eta[20], lep_id[20];
	Double_t lep_phi[20], lep_drjet[20], lep_pt[20], ptmisx, ptmisy, sumet, sumetjets;
	Int_t njet, nlep, nphot;
	
	chain->SetBranchAddress("lep_energy", lep_energy);
	chain->SetBranchAddress("lep_px", lep_px);
	chain->SetBranchAddress("lep_py", lep_py);
	chain->SetBranchAddress("lep_pz", lep_pz);
	chain->SetBranchAddress("lep_eta", lep_eta);
	chain->SetBranchAddress("lep_id", lep_id);
	chain->SetBranchAddress("lep_phi", lep_phi);
	chain->SetBranchAddress("lep_drjet", lep_drjet);
	chain->SetBranchAddress("lep_pt", lep_pt);
	chain->SetBranchAddress("ptmisx", &ptmisx);
	chain->SetBranchAddress("ptmisy", &ptmisy);
	chain->SetBranchAddress("sumet", &sumet);
	chain->SetBranchAddress("sumetjets", &sumetjets);
	chain->SetBranchAddress("njet" ,&njet);
	chain->SetBranchAddress("nlep", &nlep);
	chain->SetBranchAddress("nphot", &nphot);

// Definiere Histogramme

	// Hier werden die Histogramme definiert. TH1F bedeutet, dass es sich um ein 1-D Histogramm
	// mit Fliesskommaeintraegen (float) handelt. Der erste Parameter sollte dem Namen (links)
	// ohne dem * entsprechen. Der zweite Eintrag ist der Titel des Histogramms, der beim 
	// Anzeigen eingeblenden wird. die letzten drei Parameter stellen die Anzahl der Bins im
	// Histogramm, sowie den linken Rand des ersten Bins und den Rechten Rand des letzten Bins
	// dar.

	// Beispiel:
	// TH1F *m_llll = new TH1F("m_llll", "invarianter Masse aller vier Leptonen", 50, 0, 250);



// Haupt-Loop
	
	int nentries = 0;

	nentries = chain->GetEntries();

	for (int ientry = 0; ientry < nentries; ientry++)
	{
		chain->GetEntry(ientry);
		
		// Die eigentliche Analyse findet hier statt. Die "for"-Schleife laeuft ueber alle Ereignisse
		// im Ntuple. Die Variablen (z.B. lep_px) enthalten immer die Daten des aktuellen Ereignisses.
		// Wurden fuer ein Eregnis z.B. vier Leptonen gefunden, sind in lep_px[0] bis lep_px[3] die
		// entsprechenden x-Komponenten der Impulse dieser vier Leptonen zu finden.

		// Die oben definierten Histogramme lassen sich mit name->Fill( variable ) fuellen.
		// Beispiel:
		// ptmiss->Fill( sqrt(ptmisx^2 + ptmisy^2) )

		// TIPPS
		//
		// Machmal ist es sehr nuetzlich, sich 4er-Vektoren zu definieren. Diese heissen in ROOT
		// TLorentzVector und haben viele Faehigkeiten. Ein neuer TLorentzVector wird mit
		// TLorentzVector *tlvec = new TLorentzVector definiert. Fuellen kann man ihn mit
		// tlvec->SetPxPyPzE( px, py, pz, e ) bzw. tlvec->SetPtEtaPhiE( pt, eta, phi, e ) (je 
		// nachdem, was man zur Verfuegung hat). Um z.B. die invariante Masse zweier Teilchen
		// zu bestimmen kann man zwei 4er-Vektoren fuellen und (tlvec1 + tlvec2).M() eingeben.

		// (siehe auch http://root.cern.ch/root/html/TLorentzVector.html)
		
		
	}
}
