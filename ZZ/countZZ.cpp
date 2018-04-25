{

// do not change here
// Make Event-Objects for each MC Training Set. 
event *atlas_event = new event("ATLASDATA-ZZ-calib.root", "ATLAS");
event *zz_event = new event("testsample-ZZ.root", "ZZ");
//event *ttbar_event = new event("testsample-ttbar.root", "ttbar");
//event *zbb_event = new event("testsample-Zbb.root", "zbb");

// Get hDrawer and Event-Objects

hDrawer *drawer = new hDrawer();

// search for new physics
drawer->Add(atlas_event);
drawer->Add(zz_event);
	
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

while (drawer->go_on)
{
  event* ev = drawer->GetNextEvent();

  // insert your event selection here

  // if (ev->lep_id[0]*ev->lep_id[1]*ev->lep_id[2]*ev->lep_id[3]<0) continue;
  // event selection end
  
  // define your binning here
  drawer->Binning(10, 0., 10.);

  // insert your lepton pairings here, 
  // which leptons are paired together, use the lep_id for it!!


  // determine what kind of Z pair you have
  int zztype;  // zztype =1 both are real, ZZtype=2 both are virtual, ZZtype=3 mixed case

  zztype=1; // dummy value, fill this with something useful

  TLorentzVector l4=ev->lep[0]+ev->lep[1]+ev->lep[2]+ev->lep[3]; // four-lepton-invariant mass

  // your results are now filled into a histogram, different slots for below and above threshold!

  if ( l4.M() < 2.*91.2 - 6.25) // well below threshold
    {
      drawer->Fill(zztype);
    }
  else if ( l4.M() > 2.*91.2 + 6.25) // well above threshold             
    {
      drawer->Fill(zztype+5); 
    }

}

drawer->DrawCanvas();
	
	
}
