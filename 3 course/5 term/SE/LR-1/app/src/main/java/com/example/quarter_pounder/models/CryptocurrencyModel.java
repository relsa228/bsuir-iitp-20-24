package com.example.quarter_pounder.models;

import com.orm.SugarRecord;

public class CryptocurrencyModel extends SugarRecord {
    double ethToBtc = 0.0;
    double ltcToBtc = 0.0;
    double ethToLtc = 0.0;

    public CryptocurrencyModel() {};
    public CryptocurrencyModel(double inEthToBtc, double inLtcToBtc, double inEthToLtc){
        this.ethToLtc = inEthToLtc;
        this.ethToBtc = inEthToBtc;
        this.ltcToBtc = inLtcToBtc;
    }

    public double getEthToLtc() {
        return ethToLtc;
    }
    public double getEthToBtc() { return ethToBtc; }
    public double getLtcToBtc() {
        return ltcToBtc;
    }
}
