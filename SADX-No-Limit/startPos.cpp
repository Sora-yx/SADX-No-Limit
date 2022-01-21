#include "pch.h"
#include "startpos.h"


void init_StartPosHack() {

	for (int i = 0; i < LengthOfArray(New_StartPosSonic); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Sonic, New_StartPosSonic[i]);
	}


	for (int i = 0; i < LengthOfArray(New_StartPosMiles); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Tails, New_StartPosMiles[i]);
	}


	for (int i = 0; i < LengthOfArray(New_StartPosKnux); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Knuckles, New_StartPosKnux[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosAmy); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Amy, New_StartPosAmy[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosGamma); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Gamma, New_StartPosGamma[i]);
	}

	for (int i = 0; i < LengthOfArray(New_StartPosBig); i++) {

		HelperFunctionsGlobal.RegisterStartPosition(Characters_Big, New_StartPosBig[i]);
	}
}