package com.example.quarter_pounder.models

data class CryptoGetModel (
    val buy_price: String = "",
    val sell_price: String = "",
    val last_trade: String = "",
    val high: String = "",
    val low: String = "",
    val avg: String = "",
    val vol: String = "",
    val vol_curr: String = "",
    val updated: Int = 0
    /*val userId: Int = 0,
    val id: Int = 0,
    val title: String = "",
    val body: String = ""*/
)