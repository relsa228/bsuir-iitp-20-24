package com.example.quarter_pounder.services.database.services.datawork

import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory

object ServiceGenerator {
    private val client = OkHttpClient.Builder().build()
    private val retrofit = Retrofit.Builder()
        .baseUrl("https://api.exmo.com/v1.1/")
        .addConverterFactory(GsonConverterFactory.create())
        .client(client)
        .build();

    fun<T> buildService(service: Class<T>): T{
        return retrofit.create(service)
    }
}