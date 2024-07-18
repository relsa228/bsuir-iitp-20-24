package com.example.quarter_pounder.services.helpers

import android.content.Context
import android.util.Log
import android.widget.Toast
import com.example.quarter_pounder.models.CryptoGetModel
import com.example.quarter_pounder.models.CryptocurrencyModel
import com.example.quarter_pounder.services.database.services.DatabasePushServices
import retrofit2.Call
import retrofit2.Callback
import retrofit2.Response

class ResponseHelper constructor(appContext: Context): Callback<MutableMap<String, CryptoGetModel>> {
    private var resultMap: Map<String, CryptoGetModel> = mapOf("" to CryptoGetModel())
    private val context: Context

    init {
        context = appContext
    }

    override fun onResponse(call: Call<MutableMap<String, CryptoGetModel>>, response: Response<MutableMap<String, CryptoGetModel>>) {
        if(response.isSuccessful) {
            resultMap = response.body()!!.toMap()

            val cryptoModel = CryptocurrencyModel(resultMap["ETH_BTC"]!!.buy_price.toDouble(),
                resultMap["LTC_BTC"]!!.buy_price.toDouble(), resultMap["ETH_LTC"]!!.buy_price.toDouble())
            cryptoModel.save()

            val dbClear = DatabasePushServices()
            dbClear.dbClear()

            Toast.makeText(context, "Данные котировок успешно обновлены", Toast.LENGTH_SHORT).show()
            Log.e("ok", "it's ok, we get data")
        }
    }

    override fun onFailure(call: Call<MutableMap<String, CryptoGetModel>>, t: Throwable) {
        Log.e("error", "your connection is suck")
        Toast.makeText(context, "Не удалось получить ответ от сервера", Toast.LENGTH_SHORT).show()
    }
}

