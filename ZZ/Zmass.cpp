

#include <TLorentzVector.h>
#include <iostream.h>

using namespace std;

void Zmass(){

	//track
	TLorentzVector v1;
	TLorentzVector v2;

	v1.SetPtEtaPhiE(-19.20,0.610,5.860,22.88);
	v2.SetPtEtaPhiE(25.38,-1.953,2.771,91.29);

	TLorentzVector z1= v1+v2;

	cout << z1.M() << endl;

	//cal
	TLorentzVector v3;
	TLorentzVector v4;

	v3.SetPtEtaPhiE(-18.6,0.610,5.860,22.2);
	v4.SetPtEtaPhiE(24.6,-1.953,2.771,88.6);

	TLorentzVector z2= v3+v4;

	cout << z2.M() << endl;

	//track
	TLorentzVector v1;
	TLorentzVector v2;

	v1.SetPtEtaPhiE(-44.75,2.193,5.187,202.97);
	v2.SetPtEtaPhiE(3.72,2.432,1.485,21.84);

	TLorentzVector z1= v1+v2;

	cout << z1.M() << endl;

	//cal
	TLorentzVector v3;
	TLorentzVector v4;

	v3.SetPtEtaPhiE(-38.6,2.193,5.187,175.4);
	v4.SetPtEtaPhiE(45.5,2.432,1.485,259);

	TLorentzVector z2= v3+v4;

	cout << z2.M() << endl;

	//track
	TLorentzVector v1;
	TLorentzVector v2;

	v1.SetPtEtaPhiE(-41.69,-0.610,0.826,49.69);
	v2.SetPtEtaPhiE(39.98,-0.983,3.926,60.92);

	TLorentzVector z1= v1+v2;

	cout << z1.M() << endl;

	//cal
	TLorentzVector v3;
	TLorentzVector v4;

	v3.SetPtEtaPhiE(-42.0,-0.610,0.826,49.9);
	v4.SetPtEtaPhiE(38.4,-0.983,3.926,58.0);

	TLorentzVector z2= v3+v4;

	cout << z2.M() << endl;

}





