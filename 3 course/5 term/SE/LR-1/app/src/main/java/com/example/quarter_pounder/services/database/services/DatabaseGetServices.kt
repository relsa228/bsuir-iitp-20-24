package com.example.quarter_pounder.services.database.services

import com.example.quarter_pounder.models.CryptocurrencyModel

class DatabaseGetServices {
    fun getEthToLtc(): Double{
        val model: CryptocurrencyModel = CryptocurrencyModel.last(CryptocurrencyModel::class.java)
        return model.ethToLtc
    }

    fun getEthToBtc(): Double{
        val model: CryptocurrencyModel = CryptocurrencyModel.last(CryptocurrencyModel::class.java)
        return model.ethToBtc
    }

    fun getLtcToBtc(): Double{
        val model: CryptocurrencyModel = CryptocurrencyModel.last(CryptocurrencyModel::class.java)
        return model.ltcToBtc
    }
}