{
  
  bool zzpart=true;  // set false for search for new physics
  
  // do not change here
  // Make Event-Objects for each MC Training Set. 
  event *atlas_data   = new event("ATLAS_DATA.root", "ATLAS Data");
  
  event *zz_event        = new event("MCsample-ZZ.root", "ZZ");
  event *ttbar_event     = new event("MCsample-ttbar.root", "ttbar");
  event *zbb_event       = new event("MCsample-Zbb.root", "zbb");

  event *atlas_mystery1 = new event("ATLAS-Mystery1.root", "Mystery 1");
  event *atlas_mystery2 = new event("ATLAS-Mystery2.root", "Mystery 2");
  event *atlas_mystery3 = new event("ATLAS-Mystery3.root", "Mystery 3");
  event *atlas_mystery4 = new event("ATLAS-Mystery4.root", "Mystery 4");
  
 
  
  // Get hDrawer and Event-Objects
  
  hDrawer *drawer = new hDrawer();
   
  if (zzpart){
    // investigation of z-pairs
    drawer->Add(zz_event);
    drawer->Add(ttbar_event);
    drawer->Add(zbb_event);
    drawer->Add(atlas_data);
    
    // look at this only when you confident of the cuts you applied
    // drawer->Add(atlas_data);

  }
  else{
    // search for new physics
    //drawer->Add(atlas_mystery1);
    drawer->Add(atlas_data);
    drawer->Add(atlas_mystery2);
    drawer->Add(atlas_mystery3);
    drawer->Add(atlas_mystery4);

    



  }
  
// You can (and should!) leave everything above this line as it was!

// MAIN LOOP
//
// HOW TO USE 'event' objects. With the event object 'ev' you can access
// every variable that is stored in the ntuples by typing ev->variable.
//
// e.g. ev->lep_px[0] gives you the x-component of the momentum of the 
// first lepton in the current event.
//
// As an additional feature you also have 4-vectors for each lepton in
// the current event.
//
// e.g. ev->lep[0].Px() gives you the same result as in the example above.
// But you can do more than that:
// ev->lep[0].DeltaR(ev->lep[2]) returns delta R between both leptons.
// Those 4-vectors are of type TLorentzVector. You can create your own by
// typing 
// TLorentzVector tvec;
// With this you can (e.g.) get invariant masses by doing
// tvec = ev->lep[0] + ev->lep[1];
// tvec.M()
// 
// HOW TO USE 'hDrawer'. hDrawer is a tool that does for you all the
// strenuous (and boring) work of comparing different datasets and creating
// histograms.
// Just calculate the variable you want to compare using your event object
// 'ev' and put it into the drawer->Fill() statement.
//
// e.g. 
// TLorentzVector tvec = ev->lep[0] + ev->lep[1];
// drawer->Fill( tvec.M() );
  
 //bool cut = true;
 bool cut = true;
int ZZover=0;
int ZZunder=0;
int zZover=0;
int zZunder=0;
int zzover=0;
int zzunder=0;
  while (drawer->go_on)
    {
      event* ev = drawer->GetNextEvent();
      
  // insert your event selection here
  
  // number of leptons ?
  // if (ev->nlep < 3) continue;  // example cut
  //drawer->DrawCanvas("njets");// requiring 3 or more leptons

  // charges of the leptons ?
  // PID of the leptons (electron or muon) ?
  // cuts on eta and pT of the leptons ?
  // need cuts on MET or njets ?

  // calculate something
  TLorentzVector leps= ev->lep[0] + ev->lep[1] + ev->lep[2] + ev->lep[3];
  std::cout << leps.M() << std::endl;
  // event selection end

  // define your own binning here
  //drawer->Binning(20, 0., 300.);

  // fill your histogram here 
  //drawer->Fill(leps.M());
  
  /// or just plot the variable
  drawer->Binning(40, 0, 400);
  
  bool cutcond = ((cut==true)&&(ev->lep_etiso[0]<=5)&&(ev->lep_etiso[1]<=5)&&(ev->lep_etiso[2]<=5)&&(ev->lep_etiso[3]<=5)&&ev->njet<=2);
  //bool cutcond = ((cut==true)&&(ev->sumet>700)&&(ev->etmis>200));


  int anzel=0;
  for (int i=0;i<4;i++){
   if (abs(ev->lep_id[i])==11)
	anzel+=1 ;
  }  

TLorentzVector ze;
TLorentzVector zm;




if (anzel==2){ 

  

  if (cutcond ||(cut == false)){
	
        for (int i=0;i<4;i++){
           if (abs(ev->lep_id[i])==11)
	     ze+=(ev->lep[i]);
	   else
	     zm+=(ev->lep[i]);
        }  
	 

     
	if ((fabs(ze.M()-91.1876)<=2*2.4952)&&(fabs(zm.M()-91.1876)<=2*2.4952)){
	       continue;
           }
	/*	else if ((fabs(ze.M()-91.1876)>2*2.4952)&&(fabs(zm.M()-91.1876)>2*2.4952)){
			zzunder+=1;
		}
		else zZunder+=1;
        
  drawer->DrawCanvas("njets");
	else{
		if ((fabs(ze.M()-91.1876)<=2*2.4952)&&(fabs(zm.M()-91.1876)<=2*2.4952)){
		       ZZover+=1;
                }
		else if ((fabs(ze.M()-91.1876)>2*2.4952)&&(fabs(zm.M()-91.1876)>2*2.4952)){
			zzover+=1;
		}
		else zZover+=1;
        }
*/	
        //drawer->Fill(ev->etmis);
	//drawer->Fill(ev->nphot);

	//drawer->Fill(ev->njet);
	//drawer->Fill(ev->sumet);

        drawer->Fill(leps.M());
	//drawer->Fill(ev->lep_drjet[3]);
	//drawer->Fill(ev->lep_pt[3]);
	//drawer->Fill(ev->lep_eta[0]);

      	//drawer->Fill(ev->lep_etiso[3]);

        //drawer->Fill(ev->sumet);
	//drawer->Fill(ev->sumet+ev->etmis);
	//drawer->Fill(ev->nlep);
	//drawer->Fill(ev->sumetjets);


  //drawer->XAxis("njet");

}
  



 }  

  // END
 }

  //drawer->DrawCanvas("et_iso [GeV]");
  drawer->DrawCanvas("m [GeV]");
  //drawer->DrawCanvas("njets");
  //drawer->DrawCanvas("sumet [GeV]");
  //drawer->DrawCanvas("lep_etiso [GeV]");
  //drawer->DrawCanvas("etmis [GeV]");
  //drawer->DrawCanvas("nphot");
  //drawer->DrawCanvas("dRjet1");
  //drawer->DrawCanvas("leppt4");
  //drawer->DrawCanvas("leppeta1");
  //drawer->DrawCanvas("sumet+etmis [GeV]");
  //drawer->DrawCanvas("nlep");
  //drawer->DrawCanvas("sumetjets [GeV]");

  // draw and use the name in X axis 
  
 
 
  cout << "ZZunder" << ZZunder << endl;
cout << "zzunder" << zzunder << endl;
cout << "zZunder" << zZunder << endl;
 cout << "ZZover" << ZZover << endl;
cout << "zzover" << zzover << endl;
cout << "zZover" << zZover << endl;
}
