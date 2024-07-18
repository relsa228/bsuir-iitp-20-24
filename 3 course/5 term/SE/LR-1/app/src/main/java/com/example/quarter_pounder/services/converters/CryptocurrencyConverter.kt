package com.example.quarter_pounder.services.converters

import com.example.quarter_pounder.services.database.services.DatabaseGetServices

class CryptocurrencyConverter {
    private val dbGet = DatabaseGetServices()

    fun ethToLTC(ETHorLTC: Double, option: Boolean): Double {
        if(option)
            return ETHorLTC * dbGet.getEthToLtc();
        return ETHorLTC / dbGet.getEthToLtc();
    }

    fun ethToBTC(ETHorBTC: Double, option: Boolean): Double {
        if(option)
            return ETHorBTC * dbGet.getEthToBtc();
        return ETHorBTC / dbGet.getEthToBtc();
    }

    fun ltcToBTC(LTCorBTC: Double, option: Boolean): Double {
        if(option)
            return LTCorBTC * dbGet.getLtcToBtc();
        return LTCorBTC / dbGet.getLtcToBtc();
    }
}