package com.example.quarter_pounder.services.database.services.datawork

import com.example.quarter_pounder.models.CryptoGetModel
import retrofit2.Call
import retrofit2.http.GET

interface DataInterface {
    @GET("ticker")
    fun getData(): Call<MutableMap<String, CryptoGetModel>>
}