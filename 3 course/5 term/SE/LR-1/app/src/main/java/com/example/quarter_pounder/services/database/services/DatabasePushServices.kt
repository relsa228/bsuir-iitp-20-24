package com.example.quarter_pounder.services.database.services

import android.content.Context
import com.example.quarter_pounder.models.CryptocurrencyModel
import com.example.quarter_pounder.services.database.services.datawork.DataInterface
import com.example.quarter_pounder.services.database.services.datawork.ServiceGenerator
import com.example.quarter_pounder.services.helpers.ResponseHelper

class DatabasePushServices {
    private var initPerfom: Boolean = true

    fun initDb(context: Context){
        if (initPerfom)
            dbUpdate(context)
        initPerfom = false
    }
    fun dbUpdate(context: Context) {
        val serviceGenerator = ServiceGenerator.buildService(DataInterface::class.java)
        val call = serviceGenerator.getData()
        val responseHelper = ResponseHelper(context)

        call.enqueue(responseHelper)
    }

    fun dbClear(){
        val model: CryptocurrencyModel = CryptocurrencyModel.last(CryptocurrencyModel::class.java)
        CryptocurrencyModel.deleteAll(CryptocurrencyModel::class.java)
        model.save()
    }
}